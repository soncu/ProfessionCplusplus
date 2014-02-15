#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
	//my public data field
	int myPub;
protected:
	/*my protected data member*/
	int myProt;
private:
	//my private data member
	int myPriv;
};


class Derived1 : public Base {
};


class Derived2 : public Base {
public:
	int a;
	void Fpub(){
		this->a = this->b + this->c;

		this->myPub += this->myProt;

		//Error, Base::myPriv is inaccessible
		//this->myPub += this->myPriv;
	}
	void FTemp(){
		Base bas;
		bas.myPub = 5;

		//Error. Base::myProt is not accessible through "Base" object
		//bas.myProt = 6;

		//bas.myPriv = 7;		//Base::myPriv is inaccessible
	}
protected:
	int b;
	void Fprot(void){
		this->c = myPub + myProt;

		//Error, Base::myPriv is inaccessible
		//this->c += myPriv;
	}
private:
	int c;
	void Fpriv(void){
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
		cout << myPub << endl;
		cout << myProt << endl;

		//Error, Base::myPriv is inaccessible
		//cout << myPriv <<endl;
	}
};


class Derived3 : public Base {    //default private implicitly
public:
	int z;
	void D3(){
		this->x = myPub;
		x += myProt;

		//Error, Base::myPriv is inaccessible
		//x += myPriv;
	}
protected:
	int y;
private:
	int x;
};

class GrandChild : public Derived3 {
public:
	void Met(){
		this->i = this->myPub;
		i = myProt;
		//i = myPriv;		//Base::myPriv is inaccessible

		int Base::* ptr = &Derived3::myPub;
	}

private:
	int i;
};

struct s1{
protected:
	int x;
	int y;
	void F(void){}
};

struct s2 : s1 {
	int z;
	using s1::F;	//inherited protected member and expose it as public
	using s1::x;	//inherited protected member is being made as puclic
};


class IS{	//abstract class, cannot be instantiated
public:
	virtual void f(void) = 0;	//pure virtual method
};


class B {
public:
	virtual void fun(void) = 0;
};

class D : public B {
private:
	void fun(void) { cout << "executing D::fun" << endl; }
};



int main(int argc, char* argv[])
{
	/*	1-)	-----------------------------------------------*/

	Base b;
	b.myPub = 1;
	
	//compile time error. Base::myProt is inaccessible
	//b.myProt = 2;

	//Error. Base::myPriv is inaccessible
	//b.myPriv = 3;
	
	/*	2-)	------------------------------------------------*/
	
	Derived1 d1;
	d1.myPub = 9;

	//error, Base::myProt is inaccessible
	//d1.myProt = 8;

	//error, Base::myPriv is inaccessible
	//d1.myPriv = 7;

	/*	3-)	-------------------------------------------------*/

	Derived2 d2;
	d2.a = 10;

	//d2.b = 11;		//Derived2::b is inaccessible

	//d2.c = 12;		//Derived2::c is inaccessible

	d2.myPub = 13;
	
	//d2.myProt = 14;		//Base::myProt is inaccessible

	//d2.myPriv = 15;		//Base::myPriv is inaccessible

	d2.Fpub();

	//d2.Fprot();		//Derived2::Fprot is inaccessible

	//d2.Fpriv();		//Derived2:Fpriv is inaccessible

	/*	4-) ---------------------------------------------------*/

	GrandChild cg;
	cg.myPub = 11;
	cg.Met();


	/*	5-) ---------------------------------------------------------*/
	s1 S1;
	s2 S2;

	//S1.x = 1;

	S2.z = 4;
	S2.F();
	S2.x = 5;
	//S2.y = 6;		//inherited data member is protected so inaccessible

	cout << sizeof(s1) << endl;
	cout << sizeof(s2) << endl;

	/*	6-)--------------------------------------------------------------*/

	//IS is an abstract class, can not be made an instance of it
	//IS is;

	/*	7-)-------------------------------------------------------------*/

	D d;
	//d.fun();	//Error, D::fun is private

	D* dptr = &d;
	B* bptr = &d;

	//dptr->fun();	//D::fun is inaccessible
	//The access for a virtual function is specified when it is declared
	bptr->fun();	//strangely accessible, D::fun is executed but B::fun access level used(public)

	system("PAUSE");
	return EXIT_SUCCESS;
}



/*
class A 
{
public:
    int x;
protected:
    int y;
private:
    int z;
};

class B : public A
{
    // x is public
    // y is protected
    // z is not accessible from B	; occupy memory
};

class C : protected A
{
    // x is protected
    // y is protected
    // z is not accessible from C	; occupy memory
};

class D : private A
{
    // x is private
    // y is private
    // z is not accessible from D	; occupy memory
};
*/

