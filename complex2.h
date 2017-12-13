#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H
#include "number.h"
#include "rational.h"
#include "float.h"
#include <cstring>
#include <iostream>
using namespace std;

class COmplex {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		BOOLT = 3,
		BOOLF = 4,
		CHAR = 5,
		STRING = 6
	} type_;
	
	COmplex(int type=1){
	if(type==1) type_=RATIONAL,real_=new Rational(0,1),imag_=new Rational(0,1);
	else if(type==2) type_=FLOAT,real_=new Float(0),imag_=new Float(0);
	else if(type==3) type_=BOOLT,real_=imag_=NULL;
	else if(type==4) type_=BOOLF,real_=imag_=NULL;
	str="";
	if(type==5)type_=CHAR,real_=imag_=NULL,str="0";
	else if(type==6) type_=STRING,real_=imag_=NULL,str=""; 
};
	//COmplex(char* a,char* b);
	// COmplex(const COmplex &other);
	~COmplex() {}

	COmplex *convert(COmplex *COmplex2);
	COmplex *add(COmplex *COmplex2);
	COmplex *sub(COmplex *COmplex2);
	COmplex *mul(COmplex *COmplex2);
	COmplex *div(COmplex *COmplex2);
	COmplex *max(COmplex *COmplex2);
	COmplex *min(COmplex *COmplex2);
	COmplex *quotient(COmplex *COmplex2);
	COmplex *remainder(COmplex *COmplex2);
	COmplex *modulo(COmplex *COmplex2);
	COmplex *gcd(COmplex *COmplex2);
	COmplex *lcm(COmplex *COmplex2);
	COmplex *makeRectangular(COmplex *COmplex2);
	COmplex *makePolar(COmplex *COmplex2);
	
	COmplex *abs();
	COmplex *SQRt();
	COmplex *expt(COmplex *COmplex2);
	COmplex *floor();
	COmplex *ceiling();
	COmplex *truncate();
	COmplex *round();
	COmplex *Denominator();
	COmplex *Numerator();
	COmplex *rational();
	COmplex *Sin();
	COmplex *Cos();
	COmplex *Tan();
	COmplex *Atan();
	COmplex *Asin();
	COmplex *Acos();
	COmplex *Log();
	COmplex *Angle();
	COmplex *magnititude();
	string ToString();
	void print();
	int ToInt();
	static COmplex *from_string(char *expression);
	Number* real_;
	Number* imag_;
	string str;
};




#endif
