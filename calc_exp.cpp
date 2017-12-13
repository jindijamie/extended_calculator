#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstdio>

COmplex *calc_exp(){
    char *tk0 = next_token();
    COmplex *res;
    if (*tk0 == '(')
    {
        char *tk1 = next_token();
        Opt *opt;
        Cons *cons = new Cons(NULL, NULL), *tail = cons;
        COmplex *val;
		if(tk1==NULL){printf("123");throw 0;}
		if(strcmp(tk1,"+")==0)opt=new Add();
		else if(strcmp(tk1,"-")==0)opt=new Sub();
		else if(strcmp(tk1,"*")==0)opt=new Mul();
		else if(strcmp(tk1,"/")==0)opt=new Div();
		else if(strcmp(tk1,"max")==0)opt=new Max();
		else if(strcmp(tk1,"min")==0)opt=new Min();
		else if(strcmp(tk1,"abs")==0)opt=new ABs();
		else if(strcmp(tk1,"quotient")==0)opt=new Quotient();
		else if(strcmp(tk1,"remainder")==0)opt=new Remainder();
		else if(strcmp(tk1,"modulo")==0)opt=new Modulo();
		else if(strcmp(tk1,"floor")==0)opt=new FLoor();
		else if(strcmp(tk1,"round")==0)opt=new ROund();
		else if(strcmp(tk1,"ceiling")==0)opt=new Ceiling();
		else if(strcmp(tk1,"truncate")==0)opt=new Truncate();
		else if(strcmp(tk1,"modulo")==0)opt=new Modulo();
		else if(strcmp(tk1,"expt")==0)opt=new EXpt();
		else if(strcmp(tk1,"sqrt")==0)opt=new SQrt();
		else if(strcmp(tk1,"real-part")==0)opt=new Realpart();
		else if(strcmp(tk1,"imag-part")==0)opt=new Imagpart();
		else if(strcmp(tk1,"gcd")==0)opt=new Gcd();
		else if(strcmp(tk1,"lcm")==0)opt=new Lcm();
		else if(strcmp(tk1,"gcd")==0)opt=new Gcd();
		else if(strcmp(tk1,"numerator")==0)opt=new NUmerator();
		else if(strcmp(tk1,"denominator")==0)opt=new DEnominator();
		else if(strcmp(tk1,"inexact->exact")==0)opt=new Toexact();
		else if(strcmp(tk1,"exact->inexact")==0)opt=new Toinexact();
		else if(strcmp(tk1,"sin")==0)opt=new SIn();
		else if(strcmp(tk1,"cos")==0)opt=new COs();
		else if(strcmp(tk1,"tan")==0)opt=new TAn();
		else if(strcmp(tk1,"atan")==0)opt=new ATan();
		else if(strcmp(tk1,"asin")==0)opt=new ASin();
		else if(strcmp(tk1,"acos")==0)opt=new ACos();
		else if(strcmp(tk1,"log")==0)opt=new LOg();
		else if(strcmp(tk1,"make-rectangular")==0)opt=new MakeRectangular();
		else if(strcmp(tk1,"make-polar")==0)opt=new MakePolar();
		else if(strcmp(tk1,"exact?")==0)opt=new Exact();
		else if(strcmp(tk1,"inexact?")==0)opt=new Inexact();
		else if(strcmp(tk1,"real?")==0)opt=new Real();
		else if(strcmp(tk1,"odd?")==0)opt=new Odd();
		else if(strcmp(tk1,"even?")==0)opt=new Even();
		else if(strcmp(tk1,"zero?")==0)opt=new Zero();
		else if(strcmp(tk1,"negative?")==0)opt=new Negative();
		else if(strcmp(tk1,"positive?")==0)opt=new Positive();
		else if(strcmp(tk1,"integer?")==0)opt=new Integer();
		else if(strcmp(tk1,"rational?")==0)opt=new RATional();
		else if(strcmp(tk1,"complex?")==0)opt=new COMplex();
		else if(strcmp(tk1,"number?")==0)opt=new NUmber();	
		else if(strcmp(tk1,">")==0)opt=new Bigger();
		else if(strcmp(tk1,">=")==0)opt=new BiggerEqual();
		else if(strcmp(tk1,"<")==0)opt=new Smaller();
		else if(strcmp(tk1,">=")==0)opt=new SmallerEqual();	
		else if(strcmp(tk1,"char?")==0)opt=new Char();
		else if(strcmp(tk1,"char<?")==0)opt=new CharSmaller();
		else if(strcmp(tk1,"char-ci<?")==0)opt=new CharCiSmaller();
		else if(strcmp(tk1,"char<=?")==0)opt=new CharSmallerEqual();
		else if(strcmp(tk1,"char-ci<=?")==0)opt=new CharCiSmallerEqual();
		else if(strcmp(tk1,"char-alphabetic?")==0)opt=new CharAlphabetic();
		else if(strcmp(tk1,"char-numeric?")==0)opt=new CharNumeric();
		else if(strcmp(tk1,"char-whitespace?")==0)opt=new CharWhitespace();
		else if(strcmp(tk1,"char-upper-case?")==0)opt=new CharUppercase();
		else if(strcmp(tk1,"char-lower-case?")==0)opt=new CharLowercase();
		else if(strcmp(tk1,"char->integer")==0)opt=new CharToInteger();
		else if(strcmp(tk1,"integer->char")==0)opt=new IntegerToChar();
		else if(strcmp(tk1,"char-upcase")==0)opt=new ToCharUppercase();
		else if(strcmp(tk1,"char-downcase")==0)opt=new ToCharLowercase();
		else if(strcmp(tk1,"string?")==0)opt=new STring();
		else if(strcmp(tk1,"make-string")==0)opt=new MakeString();
		else if(strcmp(tk1,"string")==0)opt=new String();
		else if(strcmp(tk1,"string-length")==0)opt=new StringLength();
		else if(strcmp(tk1,"string-ref")==0)opt=new StringRef();
		else if(strcmp(tk1,"string<?")==0)opt=new StringSmaller();
		else if(strcmp(tk1,"string-ci?")==0)opt=new StringCiSmaller();
		else if(strcmp(tk1,"string<=?")==0)opt=new StringSmallerEqual();
		else if(strcmp(tk1,"string-ci<=?")==0)opt=new StringCiSmallerEqual();
		else if(strcmp(tk1,"substring")==0)opt=new Substring();
		else if(strcmp(tk1,"string-append")==0)opt=new StringAppend();
		else if(strcmp(tk1,"string-copy")==0)opt=new StringCopy();
				
		
		/*string?, make-string, string, string-length, string-ref,   
		string<? string-ci<?, string<=? string-ci<=?, substring, string-append, string-copy*/
		else throw 0;
        while ((val = calc_exp()))
        {
            tail->cdr = new Cons(val, NULL);
            tail = tail->cdr;
        }
        res = opt->calc(cons->cdr);
        //res->print();
        
        for (Cons *np; cons; cons = np)
        {
            np = cons->cdr;
            delete cons;
        }
    }
    else if (*tk0 == ')')
	{
        return NULL;
	}
    else
    {
		res=COmplex::from_string(tk0);
		//if(!res) {res = Float::from_string(tk0);}
		if(res==NULL){throw 0;}
    }
    return res;
}
