#pragma once
//
// Converting an Alphanumeric Key to a Natural Number using sum
// author: Ryan Webb
//

//#include to add any data structures used here such as #include "CeramicArray\CeramicArray1.hpp"

class convertBySum {

public:
	unsigned __int64 convertBySumU(char* vin) {
		// requires: vin is a pointer to an array of characters of length VIN-length + 1 & VIN uses capital letters
		// ensures:  32 bit result = radix conversion of all the characters in vin, using Cormen's radix conversion approach
		__int64 result;
		int asciiNumber;
		for (int i = 0; i < 36; i++) {
			if ((int)vin[i] < 58) {
				asciiNumber = (int)vin[i] - 48;  //char '0' = 48 so '0'-48 gives 0, convert char'0'-'9' to int 0-9
			}
			if ((int)vin[i] > 64) {
				asciiNumber = (int)vin[i] - 55;  //char 'A' = 65 so '0'-55 gives 10, so 'A'-'Z' is '10'-'36'
			}
			result = asciiNumber + result;
		}
		return result;
	}
};