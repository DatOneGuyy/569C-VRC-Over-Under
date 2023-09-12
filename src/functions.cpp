#include "main.h"

double controller_map(double input) {
  double output = 0;
  if (fabs(input) > 0.05) {
    output = 4 * pow(fabs(input) - 0.5, 3) + 0.5;
  }
  return output * sign(input);
}

double ptv(double percent) {
	return percent * 120;
}

double avg(double a, double b) {
  return (a + b) / 2;
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

double circle(double radius, double value) {
  return std::sqrt(radius * radius - value * value);
}

double quadratic_profile(double initial, double final, double maximum, double position, bool inverted) {
  double n = 0;
  const double f = 1.5; //sharpness of velocity curve, roughly equivalent to slew rate
  const double degree = 4; //sharpness of deceleration curve
  double p = 0;
  double A = 0;
  double B = 0;
  double pos = position;

  double output = 0;

  if (position < 0) {
    pos = 0;
  } else if (position > 1) {
    pos = 1;
  }

  if (final < initial) {
    output = (initial - final) * pow(1 - pow(pos, degree), 1 / degree) + final;
  } else {
    n = fmin(initial, final) / fmax(initial, final);
    n = n / (n + 1);
    p = f * initial * initial + f * final * final;
    A = (p - initial + n * (initial - final)) / (n * n - n);
    B = (initial - p + n * n * (final - initial)) / (n * n - n);
    
    output = fmin(A * pos * pos + B * pos + initial, maximum);
  }

  return output * (inverted ? -1 : 1);
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