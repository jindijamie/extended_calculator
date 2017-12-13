#pragma once
#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))
#include<iostream>
#include<string>
using namespace std;
class LongInt {
public:
	LongInt(int number );
	LongInt(long double number );
	LongInt(const LongInt &long_int2);
	LongInt(const string Int = "0");
	~LongInt();

	operator bool() ;
	operator long double();
	operator int();
	bool operator!=(const LongInt &long_int2) const;
	bool operator<(const LongInt &long_int2) const;
	LongInt &operator=(const LongInt &long_int2);
	LongInt operator+(const LongInt &long_int2) const;
	LongInt operator-(const LongInt &long_int2) const;
	LongInt operator*(const LongInt &long_int2) const;
	LongInt operator/(const LongInt &long_int2) const;
	LongInt operator%(const LongInt &long_int2) const;
	LongInt operator-=(const LongInt &long_int2);
	friend LongInt max(const LongInt &long_int1, const LongInt &long_int2);
	friend LongInt min(const LongInt &long_int1, const LongInt &long_int2);
	void print();
	string number_;
	bool symbol;
	void cancelz(); 
};
