#pragma once
#include <string>
#include <cstring>
#define SCAST_NUMBER(x) static_cast<Number*>(x)
using namespace std;

class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2)  = 0;
	virtual Number *sub(Number *number2)  = 0;
	virtual Number *mul(Number *number2)  = 0;
	virtual Number *div(Number *number2)  = 0;
	virtual Number *Max(Number *number2)  = 0;
	virtual Number *Min(Number *number2)  = 0;
	virtual Number *quotient(Number *number2)  = 0;
	virtual Number *remainder(Number *number2)  = 0;
	virtual Number *gcd(Number *number2)=0;
	virtual Number *lcm(Number *number2)=0;
	virtual Number *abs() = 0;
	virtual Number *Sqrt() = 0;
	virtual Number *Expt(Number *number2) = 0;
	virtual Number *Floor() = 0;
	virtual Number *ceiling() = 0;
	virtual Number *truncate() = 0;
	virtual Number *Round() = 0;
	virtual Number *Numerator() = 0;
	virtual Number *Denominator() = 0;
	virtual Number *RAtional() = 0;
	virtual Number *Sin() = 0;
	virtual Number *Cos() = 0;
	virtual Number *Asin() = 0;
	virtual Number *Acos() = 0;
	virtual Number *Tan() = 0;
	virtual Number *Atan() = 0;
	virtual Number *Log() = 0;
	virtual bool isInteger() = 0;
	virtual bool isOdd() = 0;
	virtual bool isEven() = 0;
	virtual int toInt()=0;
	virtual string toString() = 0;
	virtual int czero() = 0; 
	virtual void print() = 0;
};
