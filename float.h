#pragma once
#include<cstring>
#include "number.h"

#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Float : public Number {
public:
	Float(long double number = 0);
	virtual ~Float();

	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Number *Max(Number *number2);
	virtual Number *Min(Number *number2);
	virtual Number *quotient(Number *number2);
	virtual Number *remainder(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *abs() ;
	virtual Number *Sqrt() ;
	virtual Number *Expt(Number *number2) ;
	virtual Number *Floor() ;
	virtual Number *ceiling() ;	
	virtual Number *truncate() ;
	virtual Number *Round() ;
	virtual Number *Numerator();	
	virtual Number *Denominator();	
	virtual Number *RAtional();
	virtual Number *Sin();
	virtual Number *Cos();
	virtual Number *Asin();
	virtual Number *Acos();
	virtual Number *Tan();
	virtual Number *Atan();
	virtual Number *Log();
	virtual int toInt();
	virtual bool isInteger();
	virtual bool isOdd();
	virtual bool isEven();
	virtual string toString();
	virtual int czero(); 
	virtual void print();
	static Float *from_string(char *expression);
	long double number_;
};
