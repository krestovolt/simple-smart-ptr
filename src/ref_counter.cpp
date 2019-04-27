#include "ref_counter.h"

lib::RefCounter::RefCounter() { count = 1; }

void lib::RefCounter::keep() { count++; }

uint8_t lib::RefCounter::release() { return count == 0 ? count : --count; }