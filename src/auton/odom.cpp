#include "main.h"

using namespace okapi;

double final_speed = 0.6;

void start_odom(double initial_x, double initial_y, double angle) {
    /*
    Create odometry chassis with external linkage
    2.75" wheels, 14.5" track width, 600rpm
    2.75" tracking wheels, 11.5" track width, 3" offset from tracking center
    */
    chassis_l.setPose(initial_y, initial_x, -angle * pi / 180, true);
    left_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);
    right_drive_o.setBrakeMode(AbstractMotor::brakeMode::hold);

    final_speed = 0; //Default starting speed target for initial slew rate
}

void drive_to(double target_x, double target_y, double target_speed, bool backwards, double threshold, double kp_angle, double angle_threshold) {    
    const double pi = 3.1415926535897932384626433832795;

    double x = chassis_l.getPose().y; //Coordinates
    double y = chassis_l.getPose().x;
    double angle = -chassis_l.getPose(true).theta; //Absolute angle, degrees, counterclockwise is positive, [-pi, pi]
    const double distance = dist(target_x, target_y, x, y); //Euclidean distance to target from starting position
    const int sign = backwards ? -1 : 1; //-1 for backwards, 1 for forwards, used to reverse movement direction

    double base_voltage = 0; //Base voltage used for moving to target, [-1.0, 1.0]
    double turn_voltage = 0;
    double left_voltage = 0; //Adjusted voltages to turn to face target, [-1.0, 1.0]
    double right_voltage = 0;

    double angle_error = 0; //Angle error, if a left turn is needed, angle_error > 0 [-pi, pi]
    double distance_error = distance; //Euclidean distance to target from current position
    double position = 0; //Fraction of distance currently traveled, [0.0, 1.0]

    double past_angle_error = 0; //Used for calculating derivative terms
    double past_position = 0;

    const double kd_angle = 0.5; //Kd constant, slows down turning

    double left_power = 0; //Final power sent to the motors, [-12000, 12000]
    double right_power = 0;

    while (distance_error > threshold) {
        x = chassis_l.getPose().y; //Update values
        y = chassis_l.getPose().x;
        angle = transform_angle(-chassis_l.getPose(true).theta); //Update angle and remap to (-pi, pi]

        /*
        * Start with inverse tangent of target point, finding the angle from the x-axis to the target
        * Take the current angle and subtract from this angle to find the angle error
        * Modify the target angle by pi radians if backwards is active to set target to the back
        * If backwards is false, then multiplier is 0 and is ignored
        */
        angle_error = atan2(target_y - y, target_x - x) - angle; //Subtract to find error
        angle_error = transform_angle(angle_error); //Remap to (-pi, pi]
        angle_error = transform_angle(angle_error + pi * backwards); //If backwards is true then modify target angle
        /*
        * transform_angle() can be composed with itself without making changes so the value is not modified if backwards
        * is set to false
        */

        distance_error = dist(target_x, target_y, x, y); //Compute distance between target and current position
        position = 1 - distance_error / distance; //Set position to fraction of distance traveled [0.0, 1.0]

        /*
        * Early exit condition if change in position is less than 0.5% and over 50% of distance has been traveled
        * Since not all movements end with a target speed of 0, the loop also ends early if over 50% of the distance
        * has been traveled
        */
        if (fabs(position - past_position) == 0 && position > 0.5) { 
            pros::screen::print(TEXT_MEDIUM, 9, "Exited");
            break;
        }
        
        /*
        * Base voltage uses a quadratic speed controller depending on the position variable in [0.0, 1.0]
        * Input starting velocity is the larger of either the ending speed of the last movement or 35%
        * Quadratic profile can be inverted if backwards is true, with a final range between [-1.0, 1.0]
        * Base voltage is 0 if the angle error is less than the threshold, forcing the robot to turn on a point
        * when off by a large angle instead of making a wider arc
        * 
        * If angle error is lower than the threshold, base voltage is stopped so a point turn is made
        */
        base_voltage = (fabs(angle_error) < angle_threshold) * quadratic_profile(fmax(final_speed, 0.35), target_speed, 1.0, position, backwards);
        turn_voltage = kp_angle * angle_error * circle(1, position) + kd_angle * (angle_error - past_angle_error);
        /*
        * Power is base power ± turn modifier
        * Turn modifier uses a PD controller for angle
        * Since a positive angle error requires a counterclockwise (left turn) then the right speed must be 
        * increased when angle error > 0, so it is added. The proportional constant is scaled down by sqrt(1 - x^2)
        * to prevent reaction to large angle changes as the robot approaches the target
        * 
        * If angle error is decreasing, then Δerror * kd_angle < 0 and can be added to the right_power to decrease it 
        * and slow down
        * The opposite applies for left turns when angle error is increasing and the right power is negative, thus
        * adding to right_power which has a negative base voltage and slows it down
        * Mirrors for left power
        * 
        * When moving backwards with a positive angle error, |right| < |left| and right < 0, and is overall rotating left
        * Δerror * kd_angle < 0 and so in order to increase right drive speed (negative net change) and counteract the
        * turn, kd_angle must become negative, thus making Δerror * kd_angle positive if kd_angle > 0
        * Similarly, left speed must decrease (positive net change) to also counteract the turn, and Δerror * kd_angle < 0
        * means it should be subtracted to make that change
        * 
        * The ptv() function transforms from percentage to voltage. Since the input is instead between [-1.0, 1.0] it
        * is scaled again by 100x to reach the millivolt range [-12000mV, 12000mV]
        * Adding the kp and kd terms also means that the expression is no longer bounded by [-1.0, 1.0] so it needs to
        * be constrained again
        */
        left_power = c(-12000, 12000, 100 * ptv(base_voltage - turn_voltage));
        right_power = c(-12000, 12000, 100 * ptv(base_voltage + turn_voltage));
        left_drive.move_voltage(left_power);
        right_drive.move_voltage(right_power);
        
        pros::screen::print(TEXT_MEDIUM, 0, "Position: %f, %f (%f)", x, y, position);
        pros::screen::print(TEXT_MEDIUM, 1, "Angle: %f rad, %f deg", angle, angle * 180 / pi);
        pros::screen::print(TEXT_MEDIUM, 2, "Error: %f, %f deg", distance_error, angle_error);
        pros::screen::print(TEXT_MEDIUM, 3, "Base Voltage: %f", base_voltage);
        pros::screen::print(TEXT_MEDIUM, 4, "Turn Voltage: %f", turn_voltage);
        pros::screen::print(TEXT_MEDIUM, 5, "Distance Error: %f", distance_error);
        pros::screen::print(TEXT_MEDIUM, 6, "Quadratic Profile: %f", quadratic_profile(fmax(final_speed, 0.35), target_speed, 1.0, position, backwards));
        pros::screen::print(TEXT_MEDIUM, 7, "Position position: %f", position);
        pros::screen::print(TEXT_MEDIUM, 8, "Power: %f, %f", left_power, right_power);


        past_angle_error = angle_error; //Update past angle for derivative calculations
        past_position = position; //Past position is only used for exit loop condition, not 
        pros::delay(10); //Update evey 10ms
    }
    
    //Set final speed once loop is exited to the target speed
    //If the final speed is zero, do a full stop instead of coasting
    if (final_speed) {
        left_drive.move_voltage(ptv(100 * target_speed));
        right_drive.move_voltage(ptv(100 * target_speed));
    } else {
        pros::screen::print(TEXT_MEDIUM, 10, "Stopped");
        left_drive.move_velocity(0);
        right_drive.move_velocity(0);
    } 
    final_speed = target_speed; //Update for the next movement
}

/*
* A straight movement preceding a turn must have a final speed of zero
* This turn uses the inertial sensors to turn to an absolute angle
* Needs to be tested to see if it is more accurate to just turn using the odometry
* If the inertial is better
*/
void turn_to(double x, double y, double slew_rate, double threshold, int timeout) {
    //calculate target
	double target = transform_angle(atan2(y - chassis_l.getPose().y, x - chassis_l.getPose().x)); //target angle

	double position = -chassis_l.getPose(true).theta; //get current angle, inverted so counterclockwise is positive
	double error = target - position;
    double power = 0; //output power
	double kp = 80; //proportional constant

	double past_error = 0; //used for derivative term
	double kd = 5;

	int slew_count = 0; //slew counter for acceleration control and timing
	int step = 10; //delay between each loop iteration
	
    pros::screen::print(TEXT_MEDIUM, 4, "Condition: %f", abs(error));

	while (slew_count * step < timeout && fabs(error) > threshold) {
		position = -chassis_l.getPose(true).theta; //update position, error, power
		error = target - position;
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 45); //slew, start at 35, increase by input slew rate every 10ms
		power = power + kd * (error - past_error); //
		power = c(-100, 100, power);

        left_drive.move_voltage(ptv(-power));
        right_drive.move_voltage(ptv(power));

		pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position * 180 / pi);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 3, "Target: %f", target);

        if (past_error == error && slew_count > 30) {
            break;
        }

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
    
    left_drive.move_velocity(0);
    right_drive.move_velocity(0);
}

void push(double time, double time2, double reverse) {
    left_drive.move_voltage(12000);
    right_drive.move_voltage(12000);
    pros::delay(time);
    if (time2 == 0) {
        left_drive.move_voltage(0);
        right_drive.move_voltage(0);
    } else {
        left_drive.move_voltage(-12000);
        right_drive.move_voltage(-12000);
        pros::delay(reverse);
        left_drive.move_voltage(12000);
        right_drive.move_voltage(12000);
        pros::delay(time2);
        left_drive.move_voltage(0);
        right_drive.move_voltage(0);
    }
}

void turn_to_angle(double angle, int swing, double kp, double slew_rate, double threshold, int timeout) {
	double target = angle; //target angle
    
	double position = transform_angle(-chassis_l.getPose(false).theta, false); //get current angle, inverted so counterclockwise is positive
	double error = target - position;
    double power = 0; //output power

	double past_error = 0; 
	double kd = 0.3;

	int slew_count = 0; //slew counter
	int step = 10; //delay between each loop iteration
	
	while (slew_count * step < timeout && fabs(error) > threshold) {
		position = transform_angle(-chassis_l.getPose(false).theta, false); //update position, error, power
		error = target - position;
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 45); //slew, start at 35, increase by input slew rate every 10ms
		power = power + kd * (error - past_error); 
		power = c(-100, 100, power);

        if (swing == 0) {
            left_drive.move_voltage(ptv(-power));
            right_drive.move_voltage(ptv(power));
        } else if (abs(swing) == 1) {
            left_drive.move_voltage(ptv(-power) * sign(swing));
        } else {
            right_drive.move_voltage(ptv(power) * sign(swing));
        }

		pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Slew count: %d", slew_count);
		pros::screen::print(TEXT_MEDIUM, 3, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 4, "Target: %f", target);
        pros::screen::print(TEXT_MEDIUM, 5, "Past error: %f", past_error);

        if (fabs(past_error - error) < 0.01 && slew_count > 30) {
            break;
        }

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
    
    left_drive.move_velocity(0);
    right_drive.move_velocity(0);
}

void drive_to_point(double x, double y, double slew_rate[], double threshold[], int timeout[]) {
    double current_x = chassis_l.getPose().y;
    double current_y = chassis_l.getPose().x;
    double distance = dist(current_x, current_y, x, y);
    
    double target_angle = transform_angle(atan2(y - current_y, x - current_x));

    turn_to_angle(target_angle, slew_rate[0], threshold[0], timeout[0]);
    drive_for(distance, slew_rate[1], threshold[1], timeout[1]);
}

void drive_for(double distance, double slew_rate, double threshold, int timeout) {
    //calculate target
    left_tracker.reset();

	double target = distance; //target angle
    
	double position = 0; 
	double error = target - position;
    double power = 0; //output power
	double kp = 0.7; //proportional constant

	double past_error = 0; //used for derivative term
	double kd = 0.3;

    double angle_initial = -chassis_l.getPose(false).theta;
    double error_angle = 0;
    double kg = 0;

	int slew_count = 0; //slew counter for acceleration control and timing
	int step = 10; //delay between each loop iteration
	int threshold_count = 0; //counter for exiting once within the target threshold for a certain period of time

	while (slew_count * step < timeout && fabs(error) > threshold) {
		position = left_tracker.get_value(); //update position, error, power
		error = target - position;
        error_angle = -chassis_l.getPose(false).theta - angle_initial;
		power = kp * error;
		power = slew(slew_rate, slew_count, power, 45); //slew, start at 35, increase by input slew rate every 10ms
		power = power + kd * (error - past_error); //
		power = c(-80, 80, power);

        left_drive.move_voltage(ptv(power - kg * error_angle * error / distance));
        right_drive.move_voltage(ptv(power + kg * error_angle * error / distance));

		pros::screen::print(TEXT_MEDIUM, 0, "Position: %f", position);
		pros::screen::print(TEXT_MEDIUM, 1, "Error: %f", error);
		pros::screen::print(TEXT_MEDIUM, 2, "Angle error: %f", error_angle);
		pros::screen::print(TEXT_MEDIUM, 3, "Power: %f", power);
        pros::screen::print(TEXT_MEDIUM, 4, "Target: %f", target);
        pros::screen::print(TEXT_MEDIUM, 5, "Angle: %f", -chassis_l.getPose(false).theta);
        pros::screen::print(TEXT_MEDIUM, 6, "Initial: %f", angle_initial);
        pros::screen::print(TEXT_MEDIUM, 7, "Past error: %f, Error: %f", past_error, error);
        pros::screen::print(TEXT_MEDIUM, 8, "Slew count: %d", slew_count);
        
        if (past_error == error && slew_count > 30) {
            break;
        }

		slew_count++;
		past_error = error;

		pros::delay(step);
	}
    
    left_drive.move_velocity(0);
    right_drive.move_velocity(0);
}