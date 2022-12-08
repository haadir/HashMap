//
// CS104 HW6 hash func tests
//
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "hash.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

TEST(HashFunc,ExampleOne){
	MyStringHash hashk(true);
	string k("abc");
	size_t hk = hashk(k);
	size_t exp = 9953503400;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,ExampleTwo){
	MyStringHash hashk(true);
	string k("abc123");
	size_t hk = hashk(k);
	size_t exp = 473827885525100;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,ExampleThree){
	MyStringHash hashk(true);
	string k("antidisestablishmentarianism");
	size_t hk = hashk(k);
	size_t exp = 1137429692708383810;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,LargestInputString){
	MyStringHash hashk(true);
	string k("9999999999999999999999999999");
	size_t hk = hashk(k);
	size_t exp = 7116200424364995040;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,StringEmpty){
	MyStringHash hashk(true);
	string k("");
	size_t hk = hashk(k);
	size_t exp = 0;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,String1){
	MyStringHash hashk(true);
	string k("B");
	size_t hk = hashk(k);
	size_t exp = 261934300;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,String7){
	MyStringHash hashk(true);
	string k("gfedcba");
	size_t hk = hashk(k);
	size_t exp = 80987980279261566;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,String12){
	MyStringHash hashk(true);
	string k("abcdefghijkl");
	size_t hk = hashk(k);
	size_t exp = 99959782498362165;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,String13){
	MyStringHash hashk(true);
	string k("abcdefghijklm");
	size_t hk = hashk(k);
	size_t exp = 177508434398820306;
	EXPECT_EQ(hk,exp);
}

TEST(HashFunc,StringCase){
	string k1("usccs103landcs104l");
	string k2("USCCS103LandCS104L");
	MyStringHash hasha(true);
	MyStringHash hashb(true);
	size_t h_small_case = hasha(k1);
	size_t h_mix_case = hashb(k2);
	size_t exp = 2322055531449905840;
	EXPECT_EQ(h_small_case,exp);
	EXPECT_EQ(h_small_case,h_mix_case);
}

TEST(HashFunc,TestRandomize){
	string k("AntidisEstablishmentAriaNism");
	vector<size_t> hash_values;
	MyStringHash hash_a(true);
	size_t exp = 1137429692708383810;
	hash_values.push_back(hash_a(k));
	EXPECT_EQ(hash_values.back(),exp);
	for(int i = 0; i<5; i++){
		MyStringHash hash_f(false);
		hash_values.push_back(hash_f(k));
		//wait for a second to ensure we get a different seed number
		//each run should produce different hash values.
		sleep(1);
	}
	set<size_t> hash_unique_vals(hash_values.begin(),hash_values.end());
	EXPECT_EQ(hash_values.size(),hash_unique_vals.size());
}