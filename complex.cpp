#include<iostream>
#include<cmath>
#include<complex>
using namespace std;
#include"complex2.h"
COmplex *COmplex:: convert(COmplex *complex2){
	COmplex* result;
	//cout<<"from";
	//complex2->print();
	//cout<<"to";
	//this->print(); 
	if(real_->type_<complex2->real_->type_);
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	result->real_=real_->convert(complex2->real_);
	//result->print();
	if(!complex2->imag_->czero()) return result;
	
	result->imag_=real_->convert(complex2->imag_);
	//result->print();
	return result;
}


COmplex *COmplex:: add(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	result->real_=real_->add(complex2->real_);
	if(imag_->czero()==0&&complex2->imag_->czero()==0) return result;
	result->imag_=imag_->add(complex2->imag_);
	return result;
}

COmplex *COmplex:: sub(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	result->real_=real_->sub(complex2->real_);
	if(imag_->czero()==0&&complex2->imag_->czero()==0) return result;
	result->imag_=imag_->sub(complex2->imag_);
	//result->print();
	return result;
}

COmplex *COmplex:: mul(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	//cout<<"!!";
	if(imag_->czero()==0&&complex2->imag_->czero()==0) 
	{
		result->real_=real_->mul(complex2->real_);
		return result;
	}
	result->real_=(real_->mul(complex2->real_))->sub(imag_->mul(complex2->imag_));
	result->imag_=(real_->mul(complex2->imag_))->add(imag_->mul(complex2->real_));

	return result;
}

COmplex *COmplex:: div(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	Number* a=this->real_,*b=this->imag_,*c=complex2->real_,*d=complex2->imag_;
	//x=(ac+bd)/(c^2+d^2) y=(bc-ad)/(c^2+d^2)
	
	if(imag_->czero()==0&&complex2->imag_->czero()==0) 
	{
		result->real_=real_->div(complex2->real_);
		return result;
	}
	result->real_=(a->mul(c)->add(b->mul(d)))->div(c->mul(c)->add(d->mul(d)));
	result->imag_=(b->mul(c)->sub(a->mul(d)))->div(c->mul(c)->add(d->mul(d)));
	return result;
}

COmplex *COmplex:: max(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->Max(complex2->real_);
	return result;
}
COmplex *COmplex:: min(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->Min(complex2->real_);
	return result;
}

COmplex *COmplex:: quotient(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->quotient(complex2->real_);
	return result;
}

COmplex *COmplex:: remainder(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->remainder(complex2->real_);
	return result;
}

COmplex *COmplex:: modulo(COmplex *complex2){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(real_->czero()==0)return result;
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->remainder(complex2->real_);
	if(complex2->real_->czero()!=result->real_->czero())
	{result->real_=result->real_->add(complex2->real_);
	}
	return result;
}

COmplex *COmplex:: gcd(COmplex *complex2){
	COmplex* result;
	result=new COmplex(1);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	result->real_=real_->gcd(complex2->real_);
	return result;
}

COmplex *COmplex:: lcm(COmplex *complex2){
	COmplex* result;
	//result=new COmplex(1);
	if(imag_->czero()!=0||complex2->imag_->czero()!=0) throw(1);
	//result->real_=real_->lcm(complex2->real_);
	//this->print();
	
	//(this->mul(complex2))->print();
	//cout<<"!";
	//(this->gcd(complex2))->print();
	return (this->mul(complex2))->div(this->gcd(complex2));
}

COmplex *COmplex::makeRectangular(COmplex *complex2){
	COmplex* result;
	COmplex* tmp1,*tmp2;
	if(this->real_->type_<complex2->real_->type_)
	{
		tmp1=complex2->convert(this);
		tmp2=complex2;
	}
	else
	{
		tmp1=this;
		tmp2=this->convert(complex2);
	}
	result=new COmplex(MAX(this->real_->type_,complex2->real_->type_));
	result->real_=tmp1->real_;
	result->imag_=tmp2->imag_;
	return result;
}
COmplex *COmplex::makePolar(COmplex *COmplex2){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	COmplex *tmp2=result->convert(COmplex2);

	Float *a = SCAST_FLOAT(tmp->real_);
	Float *c = SCAST_FLOAT(tmp2->real_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
	g->number_=(a->number_)*cos(c->number_);
	h->number_=(a->number_)*sin(c->number_);
	//result->print();
	return result;
	
	
}

COmplex *COmplex::abs(){
	COmplex* result;
	if(real_->type_==1)result=new COmplex(1);
	else result= new COmplex(2);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->abs();
	return result;
}

COmplex *COmplex::SQRt(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	if(imag_->czero()==0 && real_->czero()>=0) 
	{
		result->real_=tmp->real_->Sqrt();
	return result;
		
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *c = new Float();
	Float *d = new Float();
	long double mol=a->number_*a->number_+b->number_*b->number_;
	long double angle=atan2(b->number_,a->number_);
	c->number_=sqrt(sqrt(mol))*cos(angle/2);
	//c->print();
	d->number_=sqrt(sqrt(mol))*sin(angle/2);
	result->real_=c;
	result->imag_=d;
	//result->print();
	return result;
}

COmplex *COmplex::magnititude(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	if(imag_->czero()==0 && real_->czero()>=0) 
	{
		result->real_=tmp->real_->abs();
	return result;
		
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *c = new Float();
	long double mol=a->number_*a->number_+b->number_*b->number_;
	long double angle=atan2(b->number_,a->number_);
	c->number_=sqrt(mol);
	result->real_=c;
	//result->print();
	return result;
}

COmplex *COmplex::Angle(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *c = new Float();
	long double mol=a->number_*a->number_+b->number_*b->number_;
	long double angle=atan2(b->number_,a->number_);
	c->number_=angle;
	result->real_=c;
	//result->print();
	return result;
}


/*先将a+bi写成rexp(iφ)的结构(a+bi)^(x+yi)=exp((r+iφ)(x+yi))=exp(rx-φy+i(xφ+yr))=exp(rx-φy)[cos(xφ+yr)+isin(xφ+yr)] */
COmplex *COmplex::expt(COmplex *COmplex2){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	COmplex *tmp2=result->convert(COmplex2);
	
	if(imag_->czero()==0 && COmplex2->imag_->czero()==0) {
		result->real_=tmp->real_->Expt(tmp2->real_);
		return result;
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *c = SCAST_FLOAT(tmp2->real_);
	Float *d = SCAST_FLOAT(tmp2->imag_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
	//long double mol=sqrt(a->number_*a->number_+b->number_*b->number_);
	//long double angle=atan2(b->number_,a->number_);
	//long double part1=exp(mol*(c->number_)-angle*(d->number_));
	//long double part2=cos(c->number_*angle+d->number_*mol);
	//long double part3=sin(c->number_*angle+d->number_*mol);
    complex <long double> n1(a->number_,b->number_);
    complex <long double> n2(c->number_,d->number_);
    long double e= real(exp(n2*log(n1)));
    long double f= imag(exp(n2*log(n1)));
    //cout<<"e"<<e<<"f"<<f<<endl;
	g->number_=e;
	h->number_=f;
	//result->print();
	return result;
	
	
}

COmplex *COmplex::Sin(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	
	if(imag_->czero()==0) {
		result->real_=tmp->real_->Sin();
		return result;
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
	//double mol=sqrt(a->number_*a->number_+b->number_*b->number_);
	//double angle=atan2(b->number_,a->number_);
	//double part1=exp(mol*(c->number_)-angle*(d->number_));
	//double part2=cos(c->number_*angle+d->number_*mol);
	//double part3=sin(c->number_*angle+d->number_*mol);
    complex <long double> n1(a->number_,b->number_);
    //complex <double> n2(c->number_,d->number_);
    long double e= real(sin(n1));
    long double f= imag(sin(n1));
    //cout<<"e"<<e<<"f"<<f<<endl;
	g->number_=e;
	h->number_=f;
	//result->print();
	return result;
	
	
}

COmplex *COmplex::Cos(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	
	if(imag_->czero()==0) {
		result->real_=tmp->real_->Sin();
		return result;
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
    complex <long double> n1(a->number_,b->number_);
    //complex <double> n2(c->number_,d->number_);
    long double e= real(cos(n1));
    long double f= imag(cos(n1));
    //cout<<"e"<<e<<"f"<<f<<endl;
	g->number_=e;
	h->number_=f;
	//result->print();
	return result;
}

COmplex *COmplex::Tan(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	
	if(imag_->czero()==0 ) {
		result->real_=tmp->real_->Tan();
		return result;
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
    complex <long double> n1(a->number_,b->number_);
    //complex <double> n2(c->number_,d->number_);
    long double e= real(tan(n1));
    long double f= imag(tan(n1));
    //cout<<"e"<<e<<"f"<<f<<endl;
	g->number_=e;
	h->number_=f;
	//result->print();
	return result;
}

COmplex *COmplex::Asin(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	Float* re=static_cast<Float*>(tmp->real_);
	COmplex *i=new COmplex(2);
	Number* one=new Float(1);
	i->imag_=i->imag_->add(Float::from_string("1.0"));
	//if(imag_->czero()==0 && re->number_<=1 && re->number_>=-1) {
	//	result->real_=tmp->real_->Asin();
	//	return result;
	//}
	COmplex *tmp2=((from_string("1.0")->sub(tmp->mul(tmp)))->SQRt())->add(i->mul(tmp));
	//tmp2->print();
	return tmp2->Log()->div(i);

}

COmplex *COmplex::Acos(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	COmplex *hfpi=new COmplex(2);
	Number* one=new Float(1);
	hfpi->real_=hfpi->real_->add(Float::from_string("1.5707963268"));	
	if(imag_->czero()==0 && real_->abs()->sub(one)->czero()<0) {
		result->real_=tmp->real_->Acos();
		return result;
	}
	return hfpi->sub(tmp->Asin());
}

COmplex *COmplex::Atan(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	COmplex *i=new COmplex(2);
	Number* one=new Float(1);
	i->imag_=i->imag_->add(Float::from_string("1.0"));
	//i->print();
	if(imag_->czero()==0) {
		result->real_=tmp->real_->Atan();
		return result;
	}
	//COmplex::from_string("1.0")->print();
	//COmplex::from_string("0.0+1.0i")->print();
	COmplex *tmp2=(from_string("1.0")->add(i->mul(tmp)))->Log();
	COmplex *tmp3=(from_string("1.0")->sub(i->mul(tmp)))->Log();
	//tmp2->print();
	//tmp3->print();
	COmplex *tmp4=(tmp2->sub(tmp3))->mul(i->mul(from_string("-0.5")));
	//tmp4->print();
	return tmp4;
}
COmplex *COmplex::Log(){
	COmplex* result;
	result= new COmplex(2);
	COmplex *tmp=result->convert(this);
	
	if(imag_->czero()==0 ) {
		result->real_=tmp->real_->Log();
		return result;
	}
	Float *a = SCAST_FLOAT(tmp->real_);
	Float *b = SCAST_FLOAT(tmp->imag_);
	Float *g = SCAST_FLOAT(result->real_);
	Float *h = SCAST_FLOAT(result->imag_);
    complex <long double> n1(a->number_,b->number_);
    //complex <double> n2(c->number_,d->number_);
    long double e= real(log(n1));
    long double f= imag(log(n1));
    //cout<<"e"<<e<<"f"<<f<<endl;
	g->number_=e;
	h->number_=f;
	//result->print();
	return result;
}



COmplex *COmplex::floor(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->Floor();
	//result->print();
	return result;
}

COmplex *COmplex::ceiling(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->ceiling();
	return result;
}

COmplex *COmplex::truncate(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->truncate();
	return result;
}
COmplex *COmplex::round(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->Round();
	return result;
}

COmplex *COmplex::rational(){
	COmplex* result;
	result= new COmplex(1);
	result->imag_=imag_->RAtional();
	result->real_=real_->RAtional(); 
	return result;
}



COmplex *COmplex::Numerator(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->Numerator();
	return result;
}
COmplex *COmplex::Denominator(){
	COmplex* result;
	result= new COmplex(1);
	if(imag_->czero()!=0) throw(1);
	result->real_=real_->Denominator();
	return result;
}


int COmplex::ToInt(){
	if(imag_->czero()!=0) throw(1);
	else return real_->toInt();
}

string COmplex::ToString()
{
	string a=this->real_->toString();
	if(imag_->czero()) a=a+"+"+this->imag_->toString()+"i";
	return a;
}

COmplex *COmplex::from_string(char *expression){
	//cout<<"!";
	string str1=expression;
	//cout<<str1<<endl;
	if(str1.length()>=3 && str1[0]=='#' && str1[1]=='\\')
	{
		COmplex* res=new COmplex(5);
		res->str=str1.substr(2,str1.length()-1);
		if(res->str=="newline") res->str=string(1,'\n');
		if(res->str=="space"||str1=="#\\") res->str=" ";
		else if(res->str=="tab")res->str=string(1,'\t');
		return res;
	}
	else if(str1.length()>=2 && str1[0]=='"' && str1[str1.length()-1]=='"')
	{
		COmplex* res=new COmplex(6);
		res->str=str1.substr(1,str1.length()-1);
		return res; 
	}
    char* end_pointerr = strchr(expression, 'i');
    char* point=strchr(expression, '.');
    if(!point)point=strchr(expression, 'e');
    char* i;
    bool flag=0;
    char* empty="";
	COmplex* result=new COmplex(1);
	Number* zero2=new Float();
	Number* zero1=new Rational(); 
    if(end_pointerr){
    	char *separate_pos = strchr(expression+1, '+');
    	while(separate_pos && *(separate_pos-1)=='e') separate_pos = strchr(separate_pos+1, '+');
    	if(!separate_pos) separate_pos = strchr(expression+1, '-'),flag=1;
    	//cout<<"----"<<endl;
    	while(separate_pos && *(separate_pos-1)=='e') separate_pos = strchr(separate_pos+1, '-');
    	
        *separate_pos='\0';
        //cout<<expression;
        *end_pointerr='\0';
        i=expression;
        result->real_=Rational::from_string(expression);
        result->imag_=Rational::from_string(separate_pos+1);
        
        if(!point)
        {
        	if(flag) result->imag_=zero1->sub(Rational::from_string(separate_pos+1));
        	else result->imag_=Rational::from_string(separate_pos+1);
        }
        
        //cout<<"----"<<endl;
        if(end_pointerr-separate_pos==1) 
			if(!flag)result->imag_=Rational::from_string("1");
			else result->imag_=Rational::from_string("-1");
        if(point)
        {
        	COmplex* result2=new COmplex(2);
        	//cout<<expression<<endl;
        	if(result->real_!=NULL) result2->real_=result2->imag_->convert(result->real_);
        	else result2->real_=Float::from_string(expression);
        	//cout<<(separate_pos+1);
        	if(result->imag_!=NULL) result2->imag_=result2->imag_->convert(result->imag_);
        	else result2->imag_=Float::from_string(separate_pos+1);
        	//result->imag_->print();
        	if(flag) result2->imag_=zero2->sub(result2->imag_);
        	
        	if(end_pointerr-separate_pos==1) 
				if(!flag)result->imag_=Float::from_string("1");
				else result->imag_=Float::from_string("-1");
			//result2->print();
			if((!result->real_||!result->imag_) && str1[0]=='#' && str1[1]=='\\') result->type_=CHAR,result2->str=str1.substr(2,str1.length());
			if(result->str=="space") result->str=" ";
    		else if(result->str=="newline")result->str=string(1,'\n');
    		
    		
    		
			return result2; 
		}

    }else{
    	if(!point)
    	{ result->real_=Rational::from_string(expression);
    	}
        else
        {
        	result=new COmplex(2);
        	result->real_=Float::from_string(expression);
		}
    }
    	
    	return result;
}

void COmplex::print(){
	if(type_==3) 
	{
		cout<<"#t"<<endl;
		return;
	}
	else if(type_==4)
	{
		cout<<"#f"<<endl;
		return;
	}
	else if(type_==5 )
	{
		cout<<"#\\";
		if(str!=" " && str!=string(1,'\n'))cout<<str<<endl;
		else if(str==" ")cout<<"space"<<endl;
		else if(str==string(1,'\n')) cout<<"newline"<<endl;
		return;
	}
	else if(type_==6 ||(real_==NULL&&imag_==NULL))
	{
		cout<<"\"";
		cout<<str;
		cout<<"\""<<endl;
		return;
	}
	real_->print();
	if(imag_->czero()!=0)
	{
		if(imag_->czero()>=0)cout<<"+";
		imag_->print();
		cout<<"i";
	}
	cout<<endl;
}

