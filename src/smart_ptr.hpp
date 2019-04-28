#ifndef SMART_PTR_H
#define SMART_PTR_H
#include "ref_counter.h"

namespace lib {

template <typename T> class SmartPtr {
private:
  T *data_ptr;
  RefCounter *reference;

public:
  SmartPtr();
  SmartPtr(T *);
  SmartPtr(const SmartPtr<T> &);
  ~SmartPtr();
  RefCounter *ref() const;
  T *ptr() const;
  T &operator*();
  T *operator->();
  SmartPtr<T> &operator=(const SmartPtr<T> &);
};

} // namespace lib

/** Implementation of lib::SmartPtr **/

template <typename T> lib::SmartPtr<T>::SmartPtr() {
  data_ptr = new T();
  reference = new lib::RefCounter();
}

template <typename T> lib::SmartPtr<T>::SmartPtr(T *p_data_ptr) {
  data_ptr = p_data_ptr;
  reference = new lib::RefCounter();
}

template <typename T>
lib::SmartPtr<T>::SmartPtr(const lib::SmartPtr<T> &other_ptr) {
  data_ptr = new T(*(other_ptr.data_ptr));
  reference = new RefCounter();
}

template <typename T> lib::SmartPtr<T>::~SmartPtr() {
  if (reference != nullptr && reference->release() == 0) {
    delete data_ptr;
    delete reference;
    data_ptr = nullptr;
    reference = nullptr;
  }
}

template <typename T> lib::RefCounter *lib::SmartPtr<T>::ref() const {
  return reference;
}

template <typename T> T *lib::SmartPtr<T>::ptr() const { return data_ptr; }

template <typename T> T &lib::SmartPtr<T>::operator*() { return *data_ptr; }

template <typename T> T *lib::SmartPtr<T>::operator->() { return data_ptr; }

template <typename T>
lib::SmartPtr<T> &lib::SmartPtr<T>::
operator=(const lib::SmartPtr<T> &other_ptr) {
  if (this != &other_ptr) {
    if (reference->release() == 0) {
      delete data_ptr;
      delete reference;
    }

    data_ptr = other_ptr.data_ptr;
    reference = other_ptr.reference;

    reference->keep();
  }
  return *this;
}

#endif