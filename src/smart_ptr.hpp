#ifndef SMART_PTR_H
#define SMART_PTR_H
#include "ref_counter.h"

namespace libk {

template <typename T> class SmartPtr {
private:
  T *_data_ptr;
  RefCounter *_reference;

public:
  SmartPtr();
  SmartPtr(T *);
  SmartPtr(const SmartPtr<T> &);
  ~SmartPtr();
  RefCounter *reference() const;
  T *data_ptr() const;
  T &operator*();
  T *operator->();
  SmartPtr<T> &operator=(const SmartPtr<T> &);
};

} // namespace libk

/** Implementation of libk::SmartPtr **/

template <typename T> libk::SmartPtr<T>::SmartPtr() {
  _data_ptr = new T();
  _reference = new libk::RefCounter();
}

template <typename T> libk::SmartPtr<T>::SmartPtr(T *p_data_ptr) {
  _data_ptr = p_data_ptr;
  _reference = new libk::RefCounter();
}

template <typename T>
libk::SmartPtr<T>::SmartPtr(const libk::SmartPtr<T> &other_ptr) {
  _data_ptr = new T(*(other_ptr._data_ptr));
  _reference = new RefCounter();
}

template <typename T> libk::SmartPtr<T>::~SmartPtr() {
  if (_reference != nullptr && _reference->release() == 0) {
    delete _data_ptr;
    delete _reference;
    _data_ptr = nullptr;
    _reference = nullptr;
  }
}

template <typename T> libk::RefCounter *libk::SmartPtr<T>::reference() const {
  return _reference;
}

template <typename T> T *libk::SmartPtr<T>::data_ptr() const {
  return _data_ptr;
}

template <typename T> T &libk::SmartPtr<T>::operator*() { return *_data_ptr; }

template <typename T> T *libk::SmartPtr<T>::operator->() { return _data_ptr; }

template <typename T>
libk::SmartPtr<T> &libk::SmartPtr<T>::
operator=(const libk::SmartPtr<T> &other_ptr) {
  if (this != &other_ptr) {
    if (_reference->release() == 0) {
      delete _data_ptr;
      delete _reference;
    }

    _data_ptr = other_ptr._data_ptr;
    _reference = other_ptr._reference;

    _reference->keep();
  }
  return *this;
}

#endif