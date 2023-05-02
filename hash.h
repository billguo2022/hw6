#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
HASH_INDEX_T operator()(const std::string& k) const
    {
      
unsigned long long blocks[5] = {0};

// Initialize an array of 6 HASH_INDEX_T integers to 0
HASH_INDEX_T subStr[6] = {0};

// Initialize an unsigned long long integer to 0
unsigned long long hashVal = 0;

// Initialize some integer variables
int strIndex = 0;
int blockIndex = 4;
int subStrIndex = 0;
int strSize = k.size() - 1;


// Loop through the characters in the string k
while (strIndex < (strSize + 1)){  
    // If we have processed 6 characters, store the resulting hash value in the blocks array
    if(subStrIndex == 6){  
        blocks[blockIndex] = bidec(subStr);  // Call the bidec function to compute the hash value and store it in the blocks array
        blockIndex--; // Move to the next index in the blocks array
        std::fill(subStr, subStr+6, 0); // Reset the subStr array to 0
        subStrIndex = 0; // Reset the subStrIndex variable to 0
    }
    // Get the numeric value of the current character in the string k
    HASH_INDEX_T letterNumber = letterDigitToNumber(k.at(strSize - strIndex)); 

    // Store the numeric value in the subStr array
    subStr[subStrIndex] = letterNumber;

    subStrIndex++; // Move to the next index in the subStr array
    strIndex++; // Move to the next character in the string k
}
// Store the final hash value in the blocks array
blocks[blockIndex] = bidec(subStr);  

// Compute the final hash value by multiplying each element in the blocks array by a corresponding value in the rValues array and adding them up
for (int i = 0; i < 5; i++)  
    hashVal += (rValues[i] * blocks[i]);
    
// Return the final hash value
return hashVal;
}

// This function computes the hash value of a sub-string of length 6
unsigned long long bidec(HASH_INDEX_T k[6]) const{ 
        
    return ((((((k[5]) * 36 + k[4]) * 36 + k[3]) * 36 + k[2]) * 36 + k[1]) * 36 + k[0]);
        
}

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
       
        HASH_INDEX_T x = tolower(letter);  
        if(x >= 48 and x <= 57){  
            return x -= 22;
        }
        else{
            return x-= 97;  
        }
        
    }

    

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
