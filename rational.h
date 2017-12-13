#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	Rational(int numerator , int denominator);
	Rational(string numerator = "0", string denominator = "1");
	virtual ~Rational();

	void reduce();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Number *Max(Number *number2);
	virtual Number *Min(Number *number2) ;
	virtual Number *quotient(Number *number2);
	virtual Number *remainder(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *abs();
	virtual Number *Sqrt();
	virtual Number *Expt(Number *number2);
	virtual Number *Floor();
	virtual Number *ceiling();
	virtual Number *truncate();
	virtual Number *Round();
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


	virtual bool isInteger() ;
	virtual bool isOdd() ;
	virtual bool isEven();
	virtual string toString();
	virtual int toInt();
	virtual int  czero(); 
	virtual void print();
	static Rational *from_string(char *expression);
	LongInt numerator_;
	LongInt denominator_;

};
