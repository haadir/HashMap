#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

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
        // Add your code here

				//might have to change type
				std::vector<long long unsigned> kVec;

				// std::cout << "HERE1: " << letterDigitToNumber(k[0]) << std::endl;
				for (unsigned int i = 0; i < k.size(); i++) {
					kVec.push_back(letterDigitToNumber(k[i]));
				}
				
				//check if we can do 6 at a time, if not push NULL so we dont seg fault
				if (k.size() == 0) {
					return 0;
				}
				else if (kVec.size() % 6 != 0) {
					int temp = 6 - (kVec.size() % 6);
					for (int i = 0; i < temp; i++) {
						kVec.insert(kVec.begin(), ' ');
					}
				}
				else if (kVec.size() % 6 == 0) {
					kVec.insert(kVec.begin(), ' ');
				}

				//w vec for final h(k)
				std::vector<unsigned long long> w;

				//start from end
				int count = 6;
				int exp = 0;
				unsigned long long sum = 0;
				while (!kVec.empty()) {
					if (kVec.back() == 32) {
						//std::cout << "CLEARING" << std::endl;
						kVec.clear();
						w.push_back(sum);
					}
					else if (count > 0) {
						sum += kVec.back() * pow(36, exp);
						//std::cout << "SUM: " << sum << std::endl;
						kVec.pop_back();
						count--;
						exp++;
					}
					//once we have added 6 indicies, reset sum to 0
					else {
						//std::cout << "HERE!";
						w.push_back(sum);
						sum = 0;
						count = 6;
						exp = 0;
					}
				}
				
				//convert to hash index and 
				HASH_INDEX_T h = 0;
				for (unsigned int i = 0; i < w.size(); i++) {
					h += (rValues[5 - i - 1] * w[i]);
				}
				return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

				//lowercase
        if (letter >= 'a' && letter <= 'z') {
					return (HASH_INDEX_T)(letter) - 97;
				}

				//uppercase
				if (letter >= 'A' && letter <= 'Z') {
					return (HASH_INDEX_T)(letter) - 65;
				}

				//numbers
				if (letter >= '0' && letter <= '9') {
					return (HASH_INDEX_T)(letter) - 22;
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
