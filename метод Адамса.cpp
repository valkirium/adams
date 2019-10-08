
#include <math.h>
#include <stdio.h>
#include <conio.h>
const float a = 0, b = 1;             // bounds of the interval
const int num_points = 10,         // number of points to solve
num_starting_points = 4; // number of points to solve with Runge-Kutta method
float x0 = 0;
float yl = 1;

float f(float x, float y)
{
	return -x * y + (1 - x) * exp(x) * y * y;
}
// this function realises Runge-Kutta method for n starting points
void calculate(float* y)
{
	float k1, k2, k3, k4, x, yi, h;
	h = (b - a) / num_points;  // step
	yi = yl; x = x0;
	for (int i = 0; i < num_starting_points; i++)
	{
		k1 = h * f(x, yi);
		k2 = h * f(x + h / 2, yi + k1 / 2);
		k3 = h * f(x + h / 2, yi + k2 / 2);
		k4 = h * f(x + h, yi + k3);
		yi += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		x += h;
		*(y + i + 1) = yi;
	}
}
void main(void)
{
	float y[num_points + 1], h;
	y[0] = yl;
	// apply Runge-Kutta method
	calculate(y);
	h = (b - a) / num_points;
	// extrapolating
	for (int i = num_starting_points; i < num_points; i++)
		y[i] = y[i - 1] + h / 24 * (55 * f(x0 + (i - 1) * h, y[i - 1]) - 59 * f(x0 + (i - 2) * h, y[i - 2]) + 37 * f(x0 + (i - 3) * h, y[i - 3]) - 9 * f(x0 + (i - 4) * h, y[i - 4]));
	printf("X\t\tY\t\tExact solution\n");
	for (int i = 0; i < num_points; i++)
		printf("%f\t%f\t%f\n", (x0 + i * h), y[i], (1 / (-exp(x0) + 2 * exp(0.5 * x0 * x0))));
	_getch();
}