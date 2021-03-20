#include "Utils.h"
#include <math.h>

int getLargestPower(int input, int base) {
	return floor(log(input) / log(base));
}


std::vector<int> getPowerVector(int max, int base) {
    // log of 0 is not defined
    if (max == 0) {
        return std::vector<int>{1};
    }

	// this can also be done with lookup tables. Unroll factors wont be that high
	int maxExponent = getLargestPower(max, base);
	int exponent = 0;
	std::vector<int> powerVector;
	while (exponent <= maxExponent) {
		powerVector.push_back(pow(base, exponent));
		exponent++;
	}
	return powerVector;
}


bool is_power_of_2(int val) {
    // powers of 2 only have one bit set
    return (val > 0) && !(val & (val - 1));
}


int closest_power_of_2(int val) {
    int low = pow(2, getLargestPower(val, 2));
    int high = low * 2;
    if ((val - low) < (high - val)) {
        return low;
    } else {
        return high;
    }
}