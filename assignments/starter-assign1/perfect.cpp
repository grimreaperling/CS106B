/*
 * This is a little program to achieve the function to find perfect numbers, 
 * This program include three different method to achieve this function. 
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
using namespace std;
/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* A better way to calculate the sum of factors of a given number.
 * Input: The number that need to calculate the sum of factors.
 * Output: the sum of the factors(except this number itself).
 */
long smarterSum(long n) {
    long total = 0;
	if (n != 1) {                                // deal with the special case that n is equal to 1
        total += 1;
	    for (long divisor = 2; divisor < sqrt(n); divisor++) {
			if (n % divisor == 0) {              // if the divisor is a factor of n
                total += divisor;                // add both the divisor and its pair
			    total += n / divisor;
		    }
	    }
	    if (pow((int)(sqrt(n)), 2) == n){       // deal with the special case that n 
            total += sqrt(n);                   // is a square number.
	    }
	}
    return total;
}

/* Implement the smarter number judgement with the smarterSum method.
 * Input : The number requiring judgement.
 * Output: 1 for the perfect number, 0 for the nonperfect number.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* Implement the find perfects with the improved sum method.
 * Input: The upper bound of the search range.
 * Output: All the perfect numbers in the range above.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* The function to find the Nth perfect number by implement the euclid's algorithm.
 * Input: The number of the required perfect number.
 * Output: The required perfect numebr.
 */
long findNthPerfectEuclid(long n) {
	int number = 0;
	long result = 0;
    for (long k = 1; number < n; k++){
         if (smarterSum(pow(2, k) - 1) == 1) {      // judge whether the number is a 
            number++;                               // a prime number
		 }                                          // through the sum method.
         if (number == n) {
             result =  pow(2, k - 1) * (pow(2, k) - 1);
		 }
	}
	return result;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
	EXPECT_EQUAL(divisorSum(13),1);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

STUDENT_TEST("Test on some negative numbers") {
    EXPECT(!isPerfect(-13));
    EXPECT(!isPerfect(-25));
}

STUDENT_TEST("Test on the new smarterSum") {
    EXPECT_EQUAL(smarterSum(1), 0);
	EXPECT_EQUAL(smarterSum(6), 6);
	EXPECT_EQUAL(smarterSum(12), 16);
	EXPECT_EQUAL(divisorSum(13), 1);
	EXPECT_EQUAL(smarterSum(25), 6);
}

STUDENT_TEST("Test on the consistency of two different methods") {
    EXPECT_EQUAL(smarterSum(625), divisorSum(625));
    EXPECT_EQUAL(smarterSum(5000), divisorSum(5000));
}

STUDENT_TEST("Confirm some some perfect number is recognized by the smarter method"){
    EXPECT(isPerfectSmarter(6));
	EXPECT(isPerfectSmarter(28));
    EXPECT(isPerfectSmarter(33550336));
}


STUDENT_TEST("Time trials of findPerfectsSmarter on doubling input sizes") {
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
}

STUDENT_TEST("Test whether the numbers found by euclid algorithm are perfect numbers") {
	EXPECT(isPerfectSmarter(findNthPerfectEuclid(2)));
	EXPECT(isPerfectSmarter(findNthPerfectEuclid(3)));
	EXPECT(isPerfectSmarter(findNthPerfectEuclid(4)));
}

