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

#include "smart_ptr.tpp"

#endif