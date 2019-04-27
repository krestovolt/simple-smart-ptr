#ifndef REF_COUNTER_H
#define REF_COUNTER_H
#include <stdint.h>

namespace lib {

class RefCounter {
private:
  uint8_t count;

public:
  RefCounter();
  void keep();
  uint8_t release();
};

} // namespace lib

#endif