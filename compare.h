#include "opt.h"
#include "float.h"
#include "rational.h"
#include "number.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <complex>
#include <cstdlib>
#include <string>
#include <algorithm>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Add : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = new COmplex();
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->add(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->add(opr);
			}
			
            delete last;
            delete conv;
			//res->print();
        }
        return res;
    }
};
class Sub:public Opt{
	COmplex *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		COmplex *res=new COmplex(),*last;
		COmplex *opr = con->car, *conv;
		last=res;
		if(cnt==1)
		{
			if (res->real_->type_  > opr->real_->type_ )
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->real_->type_  > opr->real_->type_ )
            res = res->add(conv = res->convert(opr));
        else
            res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->real_->type_ > opr->real_->type_)
				res=res->sub(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->sub(opr);
			//res->print();
			delete last;
			delete conv;
		}
		return res;
	}
};
class Mul : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = COmplex::from_string("1");
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_ > opr->real_->type_)
			{
				//cout<<"!";
				//res->print();
				res = res->mul(conv = res->convert(opr));
			}
            else
			{
				//cout<<"?";
				//opr->print();
                res = (conv = opr->convert(res))->mul(opr);
			}
			
            //delete last;
            //delete conv;
			
        }
        return res;
    }
};
class Div:public Opt{
	COmplex *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		COmplex *res=COmplex::from_string("1"),*last;
		COmplex *opr=con->car,*conv;
		last=res;
		COmplex *zero = new COmplex(2);
		if(cnt==1)
		{
			if(res->real_->type_ > opr->real_->type_)
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);
			delete last;
			delete conv;
			return res;
		}
		if(res->real_->type_ > opr->real_->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->real_->type_ >opr->real_->type_ )
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};


class Imagpart : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		if(con->car->type_==1) res=new COmplex(1);
		else res=new COmplex(2);
        //}
        res->real_=con->car->imag_;
        return res;
    }
};

class Realpart : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		if(con->car->type_==1) res=new COmplex(1);
		else res=new COmplex(2);
        //}
        res->real_=con->car->real_;
        return res;
    }
};



class Max : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = con->car;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->max(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->max(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class Min : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = con->car;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->min(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->min(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class Quotient : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = con->car;
		con=con->cdr;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->quotient(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->quotient(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class Remainder : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res = con->car;
		con=con->cdr;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->add(conv = res->remainder(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->remainder(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class Modulo : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		COmplex *res = con->car;
		con=con->cdr;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->modulo(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->modulo(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class Gcd : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
    	if(con==NULL) return COmplex::from_string("0");
		COmplex *res = con->car;
		con=con->cdr;
		if(res->real_->czero()==0 )
		{
			res=new COmplex(1);
			return res;
		} 
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if(opr->real_->czero()==0 )
			{	
				res=new COmplex(1);
				return res;
			}	 
            if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->add(conv = res->gcd(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->gcd(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res->abs();
    }
};

class Lcm : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
    	if(con==NULL) return COmplex::from_string("1");
		COmplex *res = con->car;
		con=con->cdr;
		if(res->real_->czero()==0 )
			{	
				res=new COmplex(1);
				return res;
			}
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
            if(opr->real_->czero()==0 )
			{	
				res=new COmplex(1);
				return res;
			}
			
			if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->add(conv = res->lcm(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->lcm(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res->abs();
    }
};
class EXpt : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
    	if(con==NULL) return COmplex::from_string("1");
		COmplex *res = con->car;
		con=con->cdr;
		COmplex *last;	
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *opr = con->car, *conv;
            last = res;
           
			res=res->expt(opr);
			//res->print();
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};

class ABs : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->abs();
            } 
};

class SQrt: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->SQRt();
            } 
};

class FLoor : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->floor();
            } 
};
class Ceiling : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->ceiling();
            } 
};

class Truncate : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->truncate();
            } 
};

class ROund : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->round();
            } 
};

class NUmerator : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			
            return con->car->rational()->Numerator();
            } 
};

class DEnominator : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->rational()->Denominator();
            } 
};

class Magnititude : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->magnititude();
            } 
};
class Angle : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Angle();
            } 
};

class Toinexact : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
	COmplex *complex2=new COmplex(2);
            return complex2->convert(con->car);
            } 
};

class Toexact : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->rational();
            } 
};

class SIn : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Sin();
            } 
};

class COs : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Cos();
            } 
};

class ASin : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Asin();
            } 
};

class ACos : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Acos();
            } 
};

class TAn : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Tan();
            } 
};

class ATan : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Atan();
            } 
};

class LOg : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->Log();
            } 
};

class MakeRectangular: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->makeRectangular(con->cdr->car);
            } 
};

class MakePolar: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            return con->car->makePolar(con->cdr->car);
            } 
};

class Bigger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			if(res->imag_->czero()!=0 || opr->imag_->czero()!=0) throw(0);
			if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->sub(res->convert(opr));
			}
            else
			{
                res = (opr->convert(res))->sub(opr);
			}
			result=result&&(res->real_->czero()>0);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};
class BiggerEqual: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			if(res->imag_->czero()!=0 || opr->imag_->czero()!=0) throw(0);
			if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->sub(res->convert(opr));
			}
            else
			{
                res = (opr->convert(res))->sub(opr);
			}
			result=result&&(res->real_->czero()>=0);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};
class Smaller: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			if(res->imag_->czero()!=0 || opr->imag_->czero()!=0) throw(0);
			if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->sub(res->convert(opr));
			}
            else
			{
                res = (opr->convert(res))->sub(opr);
			}
			result=result&&(res->real_->czero()<0);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};
class SmallerEqual: public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			if(res->imag_->czero()!=0 || opr->imag_->czero()!=0) throw(0);
			if (res->real_->type_  > opr->real_->type_ )
			{
				res = res->sub(res->convert(opr));
			}
            else
			{
                res = (opr->convert(res))->sub(opr);
			}
			result=result&&(res->real_->czero()<=0);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};


class Exact : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->real_->type_==1) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Inexact : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->real_->type_==2) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Zero : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
    		COmplex* res;
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			if(!con->car->real_->czero() &&!con->car->imag_->czero()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Negative : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			COmplex* res;
			if(con->car->real_->czero()<0 &&!con->car->imag_->czero()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Positive : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			COmplex* res;
			if(con->car->real_->czero()>0 &&!con->car->imag_->czero()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Real : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			COmplex* res;
			if(con->car->type_>3||con->car->type_<1)
			{
				res=new COmplex(4);
				return res;
			}
			if(!con->car->imag_->czero()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class RATional : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			COmplex* res;
			if(con->car->type_>3||con->car->type_<1)
			{
				res=new COmplex(4);
				return res;
			}
			//COmplex* res;
			if(!con->car->imag_->czero()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};



class COMplex : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			COmplex* res;
			if(con->car->type_>3||con->car->type_<1)
			{
				res=new COmplex(4);
				return res;
			}
			//COmplex* res;
			res=new COmplex(3);
			return res;
            } 
};



class NUmber : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			COmplex* res;
			if(con->car->type_>3||con->car->type_<1)
			{
				res=new COmplex(4);
				return res;
			}
			//COmplex* res;
			res=new COmplex(3);
			return res;
            } 
};
class Integer : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			COmplex* res;
			if(con->car->imag_->czero()==0 && con->car->real_->isInteger()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Odd : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			COmplex* res;
			if(con->car->imag_->czero()==0 && con->car->real_->isOdd()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Even : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
			COmplex* res;
			if(con->car->imag_->czero()==0 && con->car->real_->isEven()) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Char : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};
class CharUppercase : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5 && con->car->str[0]<='Z'&&con->car->str[0]>='A') res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class CharLowercase : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5 && con->car->str[0]<='z'&&con->car->str[0]>='a') res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};
class CharAlphabetic : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5 && ((con->car->str[0]<='Z'&&con->car->str[0]>='A')||(con->car->str[0]<='z'&&con->car->str[0]>='a'))) 
				res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class CharNumeric : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5 && con->car->str[0]<='9'&& con->car->str[0]>='0') 
				res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class CharWhitespace : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==5 && (con->car->str[0]==' ' ||con->car->str[0]=='\t'||con->car->str[0]=='\n') )
				res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};


class CharBigger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str[0]>opr->str[0]);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharCiBigger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(tolower(res->str[0])>tolower(opr->str[0]));
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharSmaller : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str[0]<opr->str[0]);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharCiSmaller : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(tolower(res->str[0])<tolower(opr->str[0]));
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharBiggerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str[0]>=opr->str[0]);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharCiBiggerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(tolower(res->str[0])>=tolower(opr->str[0]));
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharSmallerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str[0]<=opr->str[0]);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharCiSmallerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(tolower(res->str[0])<=tolower(opr->str[0]));
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str[0]==opr->str[0]);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class CharCiEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=5||con->cdr->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(tolower(res->str[0])==tolower(opr->str[0]));
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class ToCharUppercase : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res=con->car;
			if(con->car->type_!=5)throw(0);
			res->str[0]=toupper(con->car->str[0]);
			return res;
            } 
};

class ToCharLowercase : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res=con->car;
			if(con->car->type_!=5)throw(0);
			res->str[0]=tolower(con->car->str[0]);
			return res;
            } 
};



class CharToInteger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			char b[2];
			b[0]=con->car->str[0];
			b[1]='\0';
			if(con->car->type_!=5)throw(0);
			res=COmplex::from_string(b);
			return res;
            } 
};

class IntegerToChar : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res=new COmplex(5);
			if(con->car->real_->type_!=1)throw(0);
			Rational* a=static_cast<Rational*>(con->car->real_);
			res->str=a->numerator_.number_;
			return res;
            } 
};

class String : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a;
		bool result=1; 	
        for (; con; con = con->cdr)
        {
			if(con->car->type_!=5)
			{
				throw 0;
			}
            COmplex *res=con->car;
			
			a=a+res->str[0];
			
            //delete last;
            //delete conv;
			//res->print();
        }
        res=new COmplex(6);
        res->str=a;
        return res;
    }
};


class MakeString : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *num;
		COmplex *ch;
		int k;
		num=con->car;
		if(con->cdr) ch=con->cdr->car;
		else ch=new COmplex(5); 	
        if(ch->type_!=5) throw 0;
        k=num->ToInt();
        string a(k,ch->str[0]);
        COmplex* res=new COmplex(6);
        res->str=a;
        return res;
    }
};

class StringRef : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *num;
		COmplex *s;
		int k;
		//string a;
		s=con->car;
		num=con->cdr->car;
		k=num->ToInt();
		//cout<<"k"<<k<<endl;	
		//cout<<(s->type_!=6)<<endl<<!(num->type_<3 && num->type_>0)<<endl<<(k>s->str.length())<<endl;
		
        if(s->type_!=6|| !(num->type_<3 && num->type_>0) || k<0 ||  k>s->str.length()) throw 0;
        
        string a(1,s->str[k]);
        COmplex* res=new COmplex(5);
        res->str=a;
        return res;
    }
};

class StringLength : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *num;
		COmplex *s=con->car;
		Rational* k;
		if(s->type_!=6) throw 0;
		int n=s->str.length();
        k=new Rational(n,1);
        COmplex *res=new COmplex(1);
        res->real_=k;
        return res;
    }
};



class StringCopy : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *num;
		COmplex *s=con->car;
		Rational* k;
		int n;
		if(s->type_!=6) throw 0;
        COmplex *res=new COmplex(6);
        res->str=s->str;
        return res;
    }
};
class StringAppend : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a;
		bool result=1; 	
        for (; con; con = con->cdr)
        {
			if(con->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car;
			
			a=a+res->str;
			
            //delete last;
            //delete conv;
			//res->print();
        }
        res=new COmplex(6);
        res->str=a;
        return res;
    }
};

class Substring : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *num1,*num2;
		COmplex *s;
		int start,end;
		//string a;
		s=con->car;
		num1=con->cdr->car;
		num2=con->cdr->cdr->car;
		start=num1->ToInt();	
		end=num2->ToInt();
        if(s->type_!=6|| !(num1->type_<3 && num1->type_>=1)||!(num2->type_<3 && num2->type_>=1) || start<0 ||  start>s->str.length() || end<0 ||  end>s->str.length()) throw 0;
        
        string a=s->str.substr(start,end);
        COmplex *res=new COmplex(6);
        res->str=a;
        return res;
    }
};

class StringBigger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str>opr->str);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};


class StringSmaller : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str<opr->str);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};


class StringBiggerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str>=opr->str);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};


class StringSmallerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			
			result=result&&(res->str<=opr->str);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class StringCiBigger : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a,b;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			a=res->str;
			b=opr->str;
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);  
			for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);  
			result=result&&(a>b);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};

class StringCiSmaller : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a,b;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			a=res->str;
			b=opr->str;
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);  
			for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);  
			result=result&&(a<b);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};
class StringCiBiggerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a,b;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			a=res->str;
			b=opr->str;
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);  
			for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);  
			result=result&&(a>=b);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};
class StringCiSmallerEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
		
		COmplex *res;
		COmplex *last;
		string a,b;
		bool result=1; 	
        for (; con->cdr; con = con->cdr)
        {
			if(con->car->type_!=6||con->cdr->car->type_!=6)
			{
				throw 0;
			}
            COmplex *res=con->car,*opr=con->cdr->car;
			a=res->str;
			b=opr->str;
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);  
			for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);  
			result=result&&(a<=b);
			
            //delete last;
            //delete conv;
			//res->print();
        }
        if(result)res=new COmplex(3);
            else res=new COmplex(4);
            return res;
    }
};


class STring : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_==6) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class StringEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_!=6||con->cdr->car->type_!=6) throw 0;
			if(con->car->str==con->cdr->car->str) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class StringCiEqual : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			if(con->car->type_!=6||con->cdr->car->type_!=6) throw 0;
			string a=con->car->str,b=con->cdr->car->str;
			for(int i=0;i<a.length();i++) a[i]=tolower(a[i]);  
			for(int i=0;i<b.length();i++) b[i]=tolower(b[i]);
			if(a==b) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class Equal : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* a=con->car,*b=con->cdr->car,*c;
			bool flag=0; 
			COmplex* res;
			if(con->car->type_>1&& con->car->type_<3 &&con->cdr->car->type_>1 && con->cdr->car->type_<3)
			{
				if(a->real_->type_>b->real_->type_) c=a->sub(a->convert(b));
				else c=b->convert(a)->sub(b);
				flag=(c->real_->czero()==0)&&(c->imag_->czero()==0);
			}
			else if(a->type_>=5 && b->type_>=5) flag=(a->str==b->str)&&(a->type_==b->type_);
			else throw 0;
			if(flag) res=new COmplex(3);
			else res=new COmplex(4);
			return res;
            } 
};

class StringToNumber : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			char* a=new char [con->car->str.length()+1];
			for(int i=0;i<con->car->str.length();i++) a[i]=con->car->str[i];
			a[con->car->str.length()]='\0';
			if(con->car->type_!=6 )throw(0); 
			res=COmplex::from_string(a);
			return res;
            } 
};

class NumberToString : public Opt {
    /* Use the lowest level type */
    COmplex *calc(Cons *con) {
			
			COmplex* res;
			string str1;
			//a= con->car->str.c_str();
			if(con->car->type_<1 || con->car->type_>3 ) throw(0); 
			res=new COmplex(6);
			res->str=con->car->ToString();
			return res;
            } 
};


