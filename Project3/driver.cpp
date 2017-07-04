#include "wrapper.h"
#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <limits.h>

unsigned __int32 convertByRadixMethodV1(char* vin) {
	// requires: vin is a pointer to an array of characters of length VIN-length + 1 & VIN uses capital letters
	// ensures:  32 bit result = radix conversion of all the characters in vin, using Cormen's radix conversion approach
	_ULonglong result;
	_ULonglong temp;
	bitset<64> bitset1{};
	result = 0;
	//i < 17 length of vin, every case is a character in the vin
	for (int i = 2; i < 17; i++) {
		switch (i) { //this could be done sequentially im just mentally separating the cases for each digit for now

					 /*case 0: //1 bit of information
					 temp = 1; //first 2 vin results are always 1F, just add 1 for information.
					 result = result + temp;
					 result = result << 1; //1 bit of information shift prepared for next item
					 cout << result << endl;

					 case 1: //1 bit of information
					 temp = 1; //same as above
					 result = result + temp; //since previous if shifted by 1 there is 1 bit of space for this identifier
					 result = result << 3; //reserve 3 bits for next digit
					 cout << result << endl;*/

					 //do not need to make unique identifiers for first 2 slots because they are always the same value

		case 2: //3 bits of information
			if (((int)vin[2] - 64) <= 4)
				temp = (int)vin[2] - 64; //assign 1-4 for 'A''B''C''D'
			if (((int)vin[2]) == 77)
				temp = 5; //assign 5 for M
			else
				temp = 6;//assign 6 for T
			result = result + temp; 
			result = result << 3; //reserve 3 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;

		case 3: //3 bits of information
			if (((int)vin[3] - 64) <= 3)
				temp = (int)vin[3] - 41; //assign 1-3 for 'B''C''D'			
			if (((int)vin[3]) == 70)
				temp = 4; //assign 4 for 'F'
			if (((int)vin[3]) == 72)
				temp = 5; //assign 5 for 'H'
			if (((int)vin[3]) == 75)
				temp = 6; //assign 6 for 'L'
			else
				temp = 7; //assign 7 for 'P'
			result = result + temp; //since previous if shifted by 3 there are 3 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;

		case 4: //4 bits of information
			if (((int)vin[4]) == 65)
				temp = 1; //assign 1 for 'A'			
			if (((int)vin[4]) == 70)
				temp = 2; //assign 2 for 'F'
			if (((int)vin[4]) == 75)
				temp = 3; //assign 3 for 'K'
			if (((int)vin[4]) == 77)
				temp = 4; //assign 4 for 'M'
			if (((int)vin[4] - 81) < 7)
				temp = 4 + ((int)vin[4] - 81); //assign 5-11 for 'R'-'X'
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 5: //4 bits of information
			temp = (int)vin[5] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 6: //4 bits of information
			temp = (int)vin[6] - 47; //assign 1-10 for 0-9
			if (temp > 10) {  //check if X
				temp = 11; //set 'X' to 11
			}
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 6; //reserve 6 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 7://6 bits of information
			if (((int)vin[7]) - 47 <= 10)
				temp = (int)vin[7] - 47; //assign 1-10 for 0-9
			else
				temp = 10 + ((int)vin[7] - 64); //assign 11-36 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 6 there are 6 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 8: //4 bits of information
			temp = (int)vin[8] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 6; //reserve 6 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 9://6 bits of information
			if (((int)vin[9]) - 47 <= 10)
				temp = (int)vin[9] - 47; //assign 1-10 for 0-9
			else
				temp = 10 + ((int)vin[9] - 64); //assign 11-36 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 6 there are 6 bits of space for this identifier
			result = result << 5; //reserve 5 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;

		case 10: //5 bits of information
			if (((int)vin[10]) > 35)
				temp = (int)vin[10] - 64; //assign 1-26 for 'A'-'Z'
			else
				temp = 27; //assign 27 for 5
			result = result + temp; //since previous if shifted by 5 there are 5 bits of space for this identifier
			result = result << 5; //reserve 5 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;

		case 11: //5 bits of information
			temp = (int)vin[11] - 64; //assign 1-26 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 5 there are 5 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 12: //4 bits of information
			temp = (int)vin[12] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 13: //4 bits of information
			temp = (int)vin[13] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 14: //4 bits of information
			temp = (int)vin[14] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 15: //4 bits of information
			temp = (int)vin[15] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

								  //bitset1 = result;
								  //cout << bitset1 << endl;
		case 16: //4 bits of information
			temp = (int)vin[16] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier

									//bitset1 = result;
									//cout << bitset1 << endl;
		}
		result = result / (pow(2, 32));
		//bitset1 = result;
		//cout << bitset1 << endl;
		return result;
	}
}


unsigned __int64 convertByRadixMethodV2(char* vin) {
	// requires: vin is a pointer to an array of characters of length VIN-length + 1 & VIN uses capital letters
	// ensures:  32 bit result = radix conversion of all the characters in vin, using Cormen's radix conversion approach
	_ULonglong result;
	_ULonglong temp;
	bitset<64> bitset1{};
	result = 0;
	//i < 17 length of vin, every case is a character in the vin
	for (int i = 2; i < 17; i++) {
		switch (i) { //this could be done sequentially im just mentally separating the cases for each digit for now

		/*case 0: //1 bit of information
			temp = 1; //first 2 vin results are always 1F, just add 1 for information.
			result = result + temp;
			result = result << 1; //1 bit of information shift prepared for next item
			cout << result << endl;

		case 1: //1 bit of information
			temp = 1; //same as above
			result = result + temp; //since previous if shifted by 1 there is 1 bit of space for this identifier
			result = result << 3; //reserve 3 bits for next digit
			cout << result << endl;*/

		//do not need to make unique identifiers for first 2 slots because they are always the same value

		case 2: //3 bits of information
			if (((int)vin[2] - 64) <= 4)
				temp = (int)vin[2] - 64; //assign 1-4 for 'A''B''C''D'
			if (((int)vin[2]) == 77)
				temp = 5; //assign 5 for M
			else
				temp = 6;//assign 6 for T
			result = result + temp; 
			result = result << 3; //reserve 3 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;

		case 3: //3 bits of information
			if (((int)vin[3] - 64) <= 3)
				temp = (int)vin[3] - 41; //assign 1-3 for 'B''C''D'			
			if (((int)vin[3]) == 70)
				temp = 4; //assign 4 for 'F'
			if (((int)vin[3]) == 72)
				temp = 5; //assign 5 for 'H'
			if (((int)vin[3]) == 75)
				temp = 6; //assign 6 for 'L'
			else
				temp = 7; //assign 7 for 'P'
			result = result + temp; //since previous if shifted by 3 there are 3 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;

		case 4: //4 bits of information
			if (((int)vin[4]) == 65)
				temp = 1; //assign 1 for 'A'			
			if (((int)vin[4]) == 70)
				temp = 2; //assign 2 for 'F'
			if (((int)vin[4]) == 75)
				temp = 3; //assign 3 for 'K'
			if (((int)vin[4]) == 77)
				temp = 4; //assign 4 for 'M'
			if (((int)vin[4] - 81) < 7)
				temp = 4 + ((int)vin[4] - 81); //assign 5-11 for 'R'-'X'
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 5: //4 bits of information
			temp = (int)vin[5] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;
		case 6: //4 bits of information
			temp = (int)vin[6] - 47; //assign 1-10 for 0-9
			if (temp > 10) {  //check if X
				temp = 11; //set 'X' to 11
			}
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 6; //reserve 6 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;
		case 7://6 bits of information
			if (((int)vin[7]) - 47 <= 10)
				temp = (int)vin[7] - 47; //assign 1-10 for 0-9
			else
				temp = 10 + ((int)vin[7] - 64); //assign 11-36 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 6 there are 6 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;
		case 8: //4 bits of information
			temp = (int)vin[8] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 6; //reserve 6 bits for next digit

			//bitset1 = result;
			//cout << bitset1 << endl;
		case 9://6 bits of information
			if (((int)vin[9]) - 47 <= 10)
				temp = (int)vin[9] - 47; //assign 1-10 for 0-9
			else
				temp = 10 + ((int)vin[9] - 64); //assign 11-36 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 6 there are 6 bits of space for this identifier
			result = result << 5; //reserve 5 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		
		case 10: //5 bits of information
			if (((int)vin[10]) > 35)
				temp = (int)vin[10] - 64; //assign 1-26 for 'A'-'Z'
			else
				temp = 27; //assign 27 for 5
			result = result + temp; //since previous if shifted by 5 there are 5 bits of space for this identifier
			result = result << 5; //reserve 5 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;

		case 11: //5 bits of information
			temp = (int)vin[11] - 64; //assign 1-26 for 'A'-'Z'
			result = result + temp; //since previous if shifted by 5 there are 5 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 12: //4 bits of information
			temp = (int)vin[12] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 13: //4 bits of information
			temp = (int)vin[13] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 14: //4 bits of information
			temp = (int)vin[14] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 4 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 15: //4 bits of information
			temp = (int)vin[15] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			result = result << 4; //reserve 5 bits for next digit
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		case 16: //4 bits of information
			temp = (int)vin[16] - 47; //assign 1-10 for 0-9
			result = result + temp; //since previous if shifted by 4 there are 4 bits of space for this identifier
			
			
			//bitset1 = result;
			//cout << bitset1 << endl;
		}
		return result;
	}
}
unsigned __int64 convertBySumUp(char* vin) {
	// requires: vin is a pointer to an array of characters of length VIN-length + 1 & VIN uses capital letters
	// ensures:  32 bit result = radix conversion of all the characters in vin, using Cormen's radix conversion approach
	__int64 result = 0;
	int asciiNumber;
	for (int i = 0; i < 36; i++) {
		asciiNumber = (int)vin[i];  //char '0' = 48 so '0'-48 gives 0, convert char'0'-'9' to int 0-9
		
		result = asciiNumber + result;
	}
	 return result;
}
unsigned int computeDivMethod(unsigned _int64 k, unsigned _int32 tableSize) {
	// k - is the key -- Note: you can call computeDivMethod with a 64 or a 32 bit key
	// tableSize - is the size of the hash table
	// ensures: computeDivMethod = h(k) using Cormen's division method
	int hash;
	hash = k % tableSize;
	return hash;
}
unsigned int computeMulHash(unsigned _int32 k, unsigned _int32 preComputedS, unsigned int p) {
	// k - is the key
	// preComputedS - is the 's' in Cormen's multiplication method
	// p - is the 'p' in 2^p which equals the hash table size in Cormen's multiplication method
	// ensures: computeMulMethod = 32 bit h(k) using Cormen's multiplication method
	/*__int32 A = 2654435769 / (2 ^ 32);
	__int32 m = 2 ^ p;
	int w = 32;
	__int64 s = A*(2 ^ w);*/
		//bitset<64> bitset1{};
	unsigned __int64 hash = (unsigned __int64)k*(unsigned __int64)preComputedS;
		//bitset1 = hash;
		//cout << bitset1 << endl;
		//cout << hash << endl;
	unsigned __int32 val32 = (unsigned __int32)hash;//extract low 32 bits
		//cout << val32 << endl;
	unsigned __int32 h = val32 >> (32-p);
	return (int)h;
}
/*bool prime(int num)
{
	if (num == 2 || num == 3)
		return true;
	if (num % 2 == 0 || num % 3 == 0)
		return false;
	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= num)
	{
		if (num % (divisor - 1) == 0)
			return false;
		if (num % (divisor + 1) == 0)
			return false;
		divisor += 6;
	}
	return true;
}

int nextPrime(int n)
{
	while (!prime(n)) {
		++n;
	}
	return n;
}*/
int calculateEmptyBuckets(int* hTable, int size) {
	int emptyBuckets = 0;
	for (int i = 0; i < size; i++) {
		if (hTable[i] == 0) {
			emptyBuckets = emptyBuckets + 1;
		}
	}
	return emptyBuckets;
}
int calculateUsedBuckets(int* hTable, int size) {
	int usedBuckets = 0;
	for (int i = 0; i < size; i++) {
		if (hTable[i] > 0) {
			usedBuckets = usedBuckets + 1;
		}
	}
	return usedBuckets;
}
double calculateAvg(int* hTable, int size) {
	__int32 avg = 0;

	for (int i = 0; i < size; i++) {
		avg = avg + hTable[i];
	}
	avg = avg / size;
	return (int)avg;
}
double calculateUsedAvg(int* hTable, int size) {
	__int32 avg = 0;
	int usedBuckets = 0;
	for (int i = 0; i < size; i++) {
		if (hTable[i] > 0) {
			avg = avg + hTable[i];
			usedBuckets = usedBuckets + 1;
		}
	}
	if (usedBuckets > 0) {
		avg = avg / usedBuckets;
	}
	return (int)avg;
}
int maxBucketSize(int* hTable, int size) {
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (hTable[i] > max) {
			max = hTable[i];
		}
	}
	return max;
}
int minBucketSize(int* hTable, int size) {
	int min = INT_MAX;
	for (int i = 0; i < size; i++) {
		if (hTable[i] < min) {
			min = hTable[i];
		}
	}
	return min;
}
float standardDev(int* hTable, int size, int n) {
	float alpha = n / size;
	float deviationSum = 0.0;
	float deviation;
	for (int i = 0; i < size; i++) {
		deviationSum = deviationSum + ((hTable[i] - alpha)*(hTable[i] - alpha));
	}
	deviation = sqrt(deviationSum / size);
	return deviation;
}
static void processVIN() {
	char VIN[18];
	string line;
	//input tablesize here
	static int hashTable[32771];
	int tablesize = 32771;
	int n = 1000000;
	int p = 15;
	//cout << "p is " << p << endl;
	//float A = 2654435769 / (pow(2, 32));
	//cout << A << endl;
	//__int32 m = 2 ^ p;
	int w = 32;
	int i = 0;
	unsigned __int32 s = 2654435769;
	//cout << s << endl;	
	while (getline(cin, line)) {
		strcpy(VIN, line.c_str());
		/*for (int i = 0; i < 18; i++) {
			cout << VIN[i];					
		}
		cout << endl;*/
		if (VIN[0] == 'X') {				
		}
		else {					
			//unsigned __int32 hashBase = convertByRadixMethodV1(VIN);
			unsigned __int64 hashBase = convertByRadixMethodV2(VIN);
			//unsigned __int64 hashBase = convertBySumUp(VIN);
			//cout << hashBase << endl;
			//int bucket = computeMulHash(hashBase, s, p);
			int bucket = computeDivMethod(hashBase, tablesize);
			//cout << "bucket: " << bucket << endl;
			hashTable[bucket] = hashTable[bucket] + 1;
			i = i + 1;
			//cout << "Processed " << i << " VINs" << endl;
		}		
	}
	int empty = calculateEmptyBuckets(hashTable, tablesize);
	int used = calculateUsedBuckets(hashTable, tablesize);
	double usedAvg = calculateUsedAvg(hashTable, tablesize);
	double Avg = calculateAvg(hashTable, tablesize);
	int max = maxBucketSize(hashTable, tablesize);
	int min = minBucketSize(hashTable, tablesize);
	float deviation = standardDev(hashTable, tablesize, n);
	cout << "convertByRadixMethodV2" << endl;
	cout << "computeMulHash" << endl;
	cout << "m: 32768" << endl;
	cout << "n: 1000000" << endl;
	cout << "number of empty buckets: " << empty << endl;
	cout << "number of used buckets: " << used << endl;
	cout << "maximum bucket size: " << max << endl;
	cout << "minimum bucket size: " << min << endl;
	cout << "avg hashes to each bucket: " << Avg << endl;
	cout << "avg hashes to each used bucket: " << usedAvg << endl;
	cout << "standard deviation " << deviation << endl;	
}


int main(int argc, char* argv[])
{
	//char garbage;
	//char* fileName;
	//fileName = argv[1];
	//int tableSizeM;
	//choose method with 1-3(sum up, 64 bit, 32 bit), tablesize, and mode for div method(prime vs nonprime)
	//example command line arg list
	//VINfile.txt 1 1024,  filename, method, size
	//sscanf(argv[3], "%d", (int *)&tableSizeM);
	/*int* table;
	int* table1 = new int[tableSizeM];
	int* table2 = new int[tableSizeM];
	int* table3 = new int[tableSizeM];*/
	processVIN();


	/*char testArray[17] = { '1','F','B','D','F','6','6','L','4','8','D','P','1','9','8','0','1' };
	_ULonglong test;
	test = convertByRadixMethodV2(testArray);
	cout << test << endl;
	test = convertByRadixMethodV1(testArray);
	cout << test << endl;*/
	Sleep(1000000);
}