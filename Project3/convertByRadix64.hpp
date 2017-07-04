#pragma once

//
// Converting an Alphanumeric Key to a Natural Number using radix
// author: Ryan Webb
//

//#include to add any data structures used here such as #include "CeramicArray\CeramicArray1.hpp"

class convertByRadix64 {

public:
	unsigned __int64 convertByRadixMethodV2(char* vin) {
		// requires: vin is a pointer to an array of characters of length VIN-length + 1 & VIN uses capital letters
		// ensures:  32 bit result = radix conversion of all the characters in vin, using Cormen's radix conversion approach
		__int64 result;
		__int64 temp;
		//i < 17 length of vin
		for (int i = 0; i < 17; i++) {
			if(i < 2){
				temp = (int)vin[i];
				result = result + temp;
				result <<= result;
				cout << result << endl;
			}
		}
		
	}
};