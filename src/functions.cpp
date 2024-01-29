#include "main.h"

double controller_map(double input) {
    double output = 0;
    if (fabs(input) > 0.05) {
        output = 4 * pow(fabs(input) - 0.5, 3) + 0.5;
    }
    return output * sign(input);
}

double profile(double input, int direction) {
    if (input == 0) {
        return direction * 0.35;
    } else if (fabs(input) < 1) {
        return sign(input) * fmin(10 * fabs(input) + 0.35, pow(fabs(1 - input * input), 0.5) * (-fabs(fabs(input) - 1)) / (fabs(input) - 1));
    } else {
        return 36.0 * (fabs(input) - 1) * -sign(input);
    }
}

double ptv(double percent) {
	return percent * 120;
}

double c(double min, double max, double value) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

double slew(double rate, int count, double target, double base) {
	if (fabs(base + rate * count) < fabs(target)) {
		return (base + rate * count) * sign(target);
	} else {
		return target;
	}
}

double sign(double x) {
    if (x == 0) {
        return 0;
    } else {
        return fabs(x) / x;
    }
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double positive_fmod(double a, double b) {
    return a - floor(a / b) * b;
}

double transform_angle(double angle, bool radians) {
    double output = 0;
    if (radians) {
        output = -positive_fmod(-angle + okapi::pi, 2 * okapi::pi) + okapi::pi;
    } else {
        output = -positive_fmod(-angle + 180, 360) + 180;
    }
    return output;
}