#pragma once
#include <iostream>
#include <memory>
#include <mutex>
using namespace std;
/**
 - We are creating thread safe templatized singleton class here.
 - I have created two ways of creating the object, we could use either of them.
 -  Since local static variable initialization thread-safe in C++11, therefore
    we could just use that which is also known as Meyer's singleton. It is also
    lazy initialization.
 - We could also use the std::call_once to do the initialization.
 - References:
 https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton
 https://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex/50346374#50346374
*/
template <class T>
class Singleton {
  Singleton<T>(const Singleton<T>&) = delete;
  Singleton<T>& operator=(const Singleton<T>&) = delete;
  static unique_ptr<Singleton<T>> m_ins;
  static once_flag m_once;
  Singleton();  // = default;

 public:
  ~Singleton<T>();  // = default;

  static Singleton<T>& get_instance();
  static Singleton<T>& getInstance();
};

template <typename T>
std::unique_ptr<Singleton<T>> Singleton<T>::m_ins;
template <typename T>
std::once_flag Singleton<T>::m_once;

template <typename T>
Singleton<T>::Singleton() {
  cout << "Singleton::Singleton()\n";
}

template <typename T>
Singleton<T>::~Singleton() {
  cout << "Singleton::~Singleton()\n";
}
/*
C++11 removes the need for manual locking. Concurrent execution shall wait if a
static local variable is already being initialized.
*/
template <typename T>
Singleton<T>& Singleton<T>::get_instance() {
  cout << "Singleton::get_instance()\n";
  static Singleton<T> t;
  return t;
}

template <typename T>
Singleton<T>& Singleton<T>::getInstance() {
  cout << "Singleton::getInstance()\n";
  std::call_once(m_once, [&]() { m_ins.reset(new Singleton<T>); });
  return *m_ins.get();
}

void check_singleton() {
  Singleton<int>& s1 = Singleton<int>::get_instance();
  Singleton<int>& s2 = Singleton<int>::getInstance();
  Singleton<int>::get_instance();
  Singleton<int>::getInstance();
  cout << "Create char type" << std::endl;
  Singleton<char>::get_instance();
  Singleton<char>::getInstance();
  Singleton<char>::get_instance();
  Singleton<char>::getInstance();
}