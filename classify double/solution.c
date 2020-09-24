#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
	uint64_t mask = 1ull << index;
	uint64_t temp = mask & number;
	temp = temp >> index;
	return temp;
}

/**
	* my Addigional Checkers prototypes:
	**/

bool checkSign(uint64_t number);
bool checkInfinity(uint64_t number);
bool checkNormal(uint64_t number);
bool checkDenormal(uint64_t number) ;


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    /// Your code here.
	return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
	return  checkSign(number) && checkInfinity(number);
}

bool checkForMinusInf (uint64_t number) {
	return (~checkSign(number)) && checkInfinity(number);
}

bool checkForPlusNormal (uint64_t number) {
	return checkSign(number) && checkNormal(number);
}

bool checkForMinusNormal (uint64_t number) {
	return (~checkSign(number)) && checkNormal(number);
}

bool checkForPlusDenormal (uint64_t number) {
	return checkSign(number) && checkDenormal(number);
}

bool checkForMinusDenormal (uint64_t number) {
	return (~checkSign(number)) && checkDenormal(number);
}

bool checkForSignalingNan (uint64_t number) {
	for (uint8_t i = 52ull; i <= 62ull; ++i)
		{ if (getBit(number,i) == 0) return false; }
			
	bool has_one_flg = false;
	for (uint8_t i = 0ull; i<51ull; ++i)
		{if (getBit(number,i) == 1 ) has_one_flg = true; }
	
	if ((getBit(number,51ull) == 0 ) && (has_one_flg) ) return true;
	else return false;
}

bool checkForQuietNan (uint64_t number) {
	for (uint8_t i = 52ull; i <= 62ull; ++i)
		{ if (getBit(number,i) == 0) return false; }
	
	if (getBit(number,51ull) == 1 ) return true;
	else return false;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}

/* my Addigional Checkers  */

bool checkSign(uint64_t number){
	return getBit(number,63ull) == false;
}

bool checkInfinity(uint64_t number){
	//exponent checking
	for (uint8_t i = 52ull; i <= 62ull; ++i){ 
		if (getBit(number,i) == 0 ) return false;
		};
	//fraction checking
	for (uint8_t i = 0ull; i < 52ull; ++i ){
		if (getBit(number,i) == 1 ) return false;
		}
	return true;
}

bool checkNormal(uint64_t number) {
	//exponent checking 
	bool has_one_flg = false;
	bool has_zero_flg = false;
	for (uint8_t i = 52ull; i <= 62ull; ++i){ 
		  if (getBit(number,i) == 1){
			has_one_flg = true;
			}
		  if (getBit(number,i) == 0){
			has_zero_flg= true;
		  }
		  if (has_one_flg && has_zero_flg){
			return true;
		  }
		}
	return (has_one_flg && has_zero_flg);
}

bool checkDenormal(uint64_t number) {
	//exponent 
	for (uint8_t i = 52ull; i <= 62ull; ++i){ 
		if (getBit(number,i) == 1) return false;
		}
	//fraction
	bool has_one_flg = false;
	for (uint8_t i = 0ull; i < 52ull; ++i ){
		if (getBit(number,i) == 1 ) has_one_flg = true;
		}		
	return has_one_flg;
}