#ifndef REF_COUNTER_H
#define REF_COUNTER_H
#include <stdint.h>

namespace libk {

class RefCounter {
private:
  uint8_t _count;

public:
  RefCounter();
  void keep();
  uint8_t release();
};

} // namespace libk

#endif