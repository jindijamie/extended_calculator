#include "rational.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>

Rational::Rational(int numerator, int denominator) : numerator_(numerator),
	denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::Rational(string numerator, string denominator) : numerator_(numerator),
	denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::~Rational(){

}

void Rational::reduce(){
	assert(denominator_ && "denominator is zero");
	LongInt one(1);
	if(!numerator_){
		denominator_ = 1;
		return;
	}
	//if(int(denominator_ )== 1) return; 
	LongInt big, small, tmp;
	big = max(numerator_, denominator_);
	small = min(numerator_, denominator_);
	while(tmp = big % small){
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if(denominator_ < LongInt(0)){
		numerator_ = LongInt(0)-numerator_;
		denominator_ = LongInt(0)-denominator_;
	}
}


Number *Rational::convert(Number *number2){
	//assert(number2->type_ <= type_);
	Rational *result = new Rational();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->numerator_ = tmp->numerator_;
			result->denominator_ = tmp->denominator_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Rational::add( Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->denominator_;
	result->denominator_ = denominator_ * tmp->numerator_;
	result->reduce();
	return result;
}

Number *Rational::Min(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	if((this->sub(number2))->czero()<=0) result->numerator_ = numerator_,result->denominator_= denominator_ ;
	else result->numerator_ = tmp->numerator_,result->denominator_= tmp->denominator_ ;
	result->reduce();
	return result;
}

Number *Rational::Max(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	if(this->sub(number2)->czero()>=0) result->numerator_ = numerator_,result->denominator_= denominator_ ;
	else result->numerator_ = tmp->numerator_,result->denominator_= tmp->denominator_ ;
	result->reduce();
	return result;
}

Number *Rational:: quotient(Number *number2){
	Number *res=this->div(number2);
	Rational *tmp = SCAST_RATIONAL(number2);
	if(denominator_!=LongInt("1")||tmp->denominator_!=LongInt("1")) throw(1);
	Rational *result = SCAST_RATIONAL(res);
	result->numerator_=result->numerator_/result->denominator_;
	result->denominator_.number_="1";
	return result;
}

Number *Rational:: remainder(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(denominator_!=LongInt("1")||tmp->denominator_!=LongInt("1")) throw(1);
	Rational *result = new Rational("0","1");
	result->numerator_=numerator_%tmp->numerator_;
	return result;
}

Number *Rational:: gcd(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(denominator_!=LongInt("1")||tmp->denominator_!=LongInt("1")) throw(1);
	Number *result = this->abs()->div(number2->abs());
	Rational *tmp2 = SCAST_RATIONAL(result);
	tmp2->numerator_=LongInt("1");
	return result->mul(number2);
}

Number *Rational:: lcm(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if(denominator_!=LongInt("1")||tmp->denominator_!=LongInt("1")) throw(1);	
	return this->mul(number2)->div(this->gcd(number2));
}

Number *Rational::abs(){
	numerator_.symbol=denominator_.symbol=1; 
	return this;
}

Number *Rational::Sqrt(){
	throw (1);
}

Number *Rational::Expt(Number* number2){
	throw (1);
}

Number *Rational::Floor(){
	Rational* result=new Rational();
	result->numerator_=numerator_/denominator_;
	if(numerator_%denominator_<LongInt(0)) result->numerator_=result->numerator_-LongInt(1);
	result->denominator_=LongInt("1");
	return result;
}

Number *Rational::ceiling(){
	Rational* result=new Rational();
	result->numerator_=numerator_/denominator_;
	if(LongInt(0)<numerator_%denominator_) result->numerator_=result->numerator_+LongInt(1);
	result->denominator_=LongInt("1");
	return result;
}


Number *Rational::Round(){
	Rational* result=new Rational();
	bool flag=0;
	flag=(numerator_.symbol+denominator_.symbol)%2;
	numerator_.symbol=0;
	denominator_.symbol=0;
	result->numerator_=numerator_/denominator_;
	//(denominator_/LongInt(2)).print();
	//cout<<endl;
	//(numerator_%denominator_).print();
	//cout<<endl;
	//cout<<((denominator_/LongInt(2)<numerator_%denominator_))<<endl;
	if(denominator_/LongInt(2)<numerator_%denominator_) result->numerator_=result->numerator_+LongInt(1);
	result->denominator_=LongInt("1");
	result->numerator_.symbol=flag;
	return result;
}

Number *Rational::truncate(){
	if(this->czero()) return this->Floor();
	else return this->ceiling();
}

Number *Rational::Numerator(){
	denominator_=LongInt("1");
	return this;
}

Number *Rational::Denominator(){
	numerator_=denominator_;
	denominator_=LongInt("1");
	return this;
}

Number *Rational::RAtional(){

	return this;
}

Number *Rational::Sin(){
	throw(1);
	return this;
}

Number *Rational::Cos(){
	throw(1);
	return this;
}

Number *Rational::Asin(){
	throw(1);
	return this;
}

Number *Rational::Acos(){
	throw(1);
	return this;
}

Number *Rational::Tan(){
	throw(1);
	return this;
}

Number *Rational::Atan(){
	throw(1);
	return this;
}

Number *Rational::Log(){
	throw(1);
	return this;
}

int Rational::czero()
{
	if(!bool(numerator_)) return 0;
	if(LongInt("0")<numerator_) return 1;
	if(numerator_<LongInt("0")) return -1;
	return 0;
}

bool Rational::isInteger()
{
	if(denominator_-LongInt("1")) return 0;
	return 1;
}

bool Rational::isOdd()
{
	if(denominator_-LongInt("1")) return 0;
	if(bool(numerator_%LongInt("2"))) return 1;
	return 0;
}

bool Rational::isEven()
{
	if(denominator_-LongInt("1")) return 0;
	return !(this->isOdd());
}



void Rational::print(){
	this->reduce();
	numerator_.print();
	if(denominator_ != (LongInt)1){
		printf("/");
		denominator_.print();
	}
	//printf("\n");
}

int Rational::toInt()
{
	this->reduce();
	if(denominator_!=LongInt(1)) throw(0);
	return int(numerator_);
}
string Rational::toString(){
	string a=this->numerator_.number_+"\\"+this->denominator_.number_;
	return a;
	
}

Rational *Rational::from_string(char *expression){
    char* end_pointerr;
    char* i;
    char *separate_pos = strchr(expression, '/');
    char *point= strchr(expression, '.');
    if(!point)point= strchr(expression, 'e');
    if(point) return NULL;
    if(separate_pos){
        *separate_pos='\0';
        i=expression;
        if(*i=='-') i++;
        for(;i<separate_pos;i++)
			if(*i<'0' || *i>'9') return NULL;
        string numerator(expression);
        *separate_pos='/';
          
        //if( end_pointerr == expression || end_pointerr != separate_pos )
        	//return NULL;
        for(i=separate_pos + 1;*i!='\0';i++)
			if(!*i || *i<'0' || *i>'9') return NULL;
        
        string denominator(separate_pos + 1);
        return new Rational(numerator,denominator);
    }else{
    	string numerator(expression);
    	i=expression;
    	if(*i=='-') i++;
        for(;*i!='\0';i++)
			if(*i<'0' || *i>'9') return NULL;
        return new Rational(numerator , "1");
    }
}
