#pragma once

// A collection of utility functions
class Util
{
public:
	// Linearly interpolates between two values
	static double lerp(double start, double end, double p);

	// Map a value from an input range to an output range
	static double map(double value, double inMin, double inMax, double outMin, double outMax);
};