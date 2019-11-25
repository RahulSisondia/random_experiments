#include "pch.h"
//#include <iostream>
//#include <memory>
//using namespace std;
//
//class B;
//
//class A {
//public:
//	A() {
//		m_sp_b = nullptr;
//		cout << "Default A::A()\n";
//	};
//
//	A(shared_ptr<B>& b) {
//		m_sp_b = b;
//		cout << "A::A()\n";
//	};
//
//	~A() {
//		cout << "A::~A()\n";
//	}
//
//	void print() {
//		cout << "A::m_sp_b, pointer to B's object :" << m_sp_b.use_count() << endl;
//	}
//
//	shared_ptr<B> m_sp_b;
//};
//
//
//class B {
//public:
//	B() {
//		cout << "Default B::B()\n";
//	};
//
//	B(shared_ptr<A>& a) :
//		m_sp_a(a)
//	{
//		a->m_sp_b.reset(this);
//		cout << "B::B()\n";
//	}
//
//	~B() {
//		cout << "B::~B()\n";
//	}
//
//	void print() {
//		cout << "B::m_sp_a, pointer to A's Object :";// << m_sp_a.use_count() << endl;
//	}
//
//	weak_ptr<A> m_sp_a;
//};
//
//int main() {
//	A *a = new A();
//	a->print();
//	shared_ptr<A> astp(a);
//	B *b = new B(astp);
//
//	a->print();
//	b->print();
//
//	delete (a);
//
//	//a->print();
//	b->print();
//	std::cout << "Jello";
//	return 0;
//}
