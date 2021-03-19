#pragma once

// ------ Includes and Namespaces ------ //
#include <vector>


/**
* Returns the largest power of the given base that fits in the input
*
* @param base: Base of the power
* @param input: Number in which the power should fit
* @return The largest possible power
*/
int getLargestPower(int input, int base);


/**
* Returns a vector of consecetive powers of the base up-til-and-including the max exponent
*
* @param[in] max outcome of the base to the pow power of the base
* @param[in] base of which the powers are taken
* @return list of powers in vector<int> form
*/
std::vector<int> getPowerVector(int max, int power);
