#include "float.h"
#include "rational.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <math.h>
#include <iostream>
#include <iomanip> 
#include <strstream>  
#define ABS(x) ((x)<0?(-(x)):(x))
using namespace std;
Float::Float(long double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

Number *Float::convert(Number *number2){
	assert(number2->type_ <= type_);
	Float *result = new Float();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->number_ = (long double)tmp->numerator_ / (long double)tmp->denominator_;
			//printf("!!!%lf", result->number_);
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->number_ = tmp->number_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	return result;
}

Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ + tmp->number_);
	return result;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ - tmp->number_);
	return result;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ * tmp->number_);
	return result;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	//assert(ABS(tmp->number_)>1e-10000 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Number *Float::Max(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float();
	if(number_>tmp->number_) result->number_=number_;
	else result->number_=tmp->number_;
	return result;

}

Number *Float::Min(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float();
	if(number_<tmp->number_) result->number_=number_;
	else result->number_=tmp->number_;
	return result;

}

Number *Float::quotient(Number *number2){
	Number *tmp=this->div(number2);
	Number *result=tmp->truncate();
	throw(1);
	return result; 
}

Number *Float::remainder(Number *number2){
	
	return this->sub(this->quotient(number2)); 
}

Number *Float::Expt(Number *number2)
{
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float();
	result->number_=pow(this->number_,tmp->number_);
	return result;
}



Number *Float::abs()
{
	if(number_<0) number_=-number_;
	return this;
}

Number *Float::Sqrt()
{
	if(number_>=0) number_= sqrt(number_);
	else throw(1);
	return this;
}

Number *Float::Sin()
{
	number_= sin(number_);
	return this;
}
Number *Float::Cos()
{
	number_= cos(number_);
	return this;
}
Number *Float::Asin()
{
	number_= asin(number_);
	return this;
}
Number *Float::Acos()
{
	number_= acos(number_);
	return this;
}
Number *Float::Atan()
{
	number_= atan(number_);
	return this;
}
Number *Float::Tan()
{
	number_= tan(number_);
	return this;
}

Number *Float::Log()
{
	number_= log(number_);
	return this;
}


Number *Float::Floor()
{
	int number;
	Float* result=new Float(); 
	result->number_= floor(number_);
	return result;
}

Number *Float::truncate()
{
	int number; 
	if(this->czero()<0) return this->ceiling();
	else return this->Floor();
}

Number *Float::ceiling()
{
	int number; 
	Float* result=new Float();
	result->number_= ceil(number_);
	return result;
}

int Float::czero(){
	if(number_>0) return 1;
	if(number_<0) return -1;
	return 0;
}

bool Float::isInteger(){
	if(number_-floor(number_)<1e-1000) return 1;
	return 0;
}

bool Float::isEven(){
	if(number_/2.0-floor(number_/2.0)<1e-1000) return 1;
	return 0;
}
bool Float::isOdd(){
	return this->isInteger()&&!(this->isEven());
}

Number *Float::Round()
{
	int number;
	Float* result=new Float(); 
	result->number_= round(number_);
	return result;
}
Number *Float::Numerator()
{
	throw(1);
	return NULL;
}

Number *Float::Denominator()
{
	throw(1);
	return NULL;
}

Number *Float::RAtional()
{
	
	Rational two(2,1);
	Rational *b=new Rational(1,1); 
	long long int number;
	while((number_-floor(number_))>1e-1000 )
	{
		number_*=2;
		b->numerator_=b->numerator_*LongInt(2);
		//b->numerator_.print();
		//cout<<endl;
		//cout<<number_<<endl;
		 
	}
	//cout<<number_<<endl;
	number=number_;
	Rational* result=new Rational();
	result->numerator_=LongInt(number_);
	//result->print();
	//cout<<endl;
	//b.print();
	return result->div(b);
}

Number *Float::gcd(Number* number2)
{
	Float *t = SCAST_FLOAT(number2);
	Number* tmp=new Rational(int(number_),1);
	Number* tmp2=new Rational(int(t->number_),1);
	return  tmp->gcd(tmp2);
}

Number *Float::lcm(Number* number2)
{
	Float *t = SCAST_FLOAT(number2);
	Number* tmp=new Rational(int(number_),1);
	Number* tmp2=new Rational(int(t->number_),1);
	return  tmp->lcm(tmp2);
}

void Float::print(){
	cout<<setprecision(10)<<number_;
}

int Float::toInt()
{
	if(number_-floor(number_)<1e-1000)
		return int(number_);
	else throw(0);
}

string Float::toString(){
	string s;  
    std::strstream ss;  
    ss << this->number_;  
    ss >> s;  
    return s; 

}

Float *Float::from_string(char *expression){
    char *end_pointer;
    long double val = strtod(expression, &end_pointer);
    if (end_pointer == expression || end_pointer != expression + strlen(expression))
	    return NULL;
    return new Float(val);
}


// int main(){
// 	Float *a = new Float(1.2);
// 	Float *b = new Float(1.3);
// 	(a->add(b))->print();
// }
