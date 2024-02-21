#pragma once

double controller_map(double i);
double controller_map2(double input, double k = 2.7);
double ptv(double percent);
double profile(double input, int direction);
double c(double min, double max, double value);
double slew(double rate, int count, double target, double base);
double sign(double x);
double dist(double x1, double y1, double x2, double y2);
double positive_fmod(double a, double b);
double transform_angle(double angle, bool radians = true);