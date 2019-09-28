#include "util.h"

double Util::lerp(double start, double end, double p)
{
	return start + (end - start) * p;
}

double Util::map(double value, double inMin, double inMax, double outMin, double outMax)
{
	return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}