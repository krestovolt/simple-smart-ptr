#include "ref_counter.h"

libk::RefCounter::RefCounter() { _count = 1; }

void libk::RefCounter::keep() { _count++; }

uint8_t libk::RefCounter::release() { return _count == 0 ? _count : --_count; }