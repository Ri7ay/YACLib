#pragma once

#include <cstddef>

namespace yaclib {

struct Allocation {
  char* start = nullptr;
  size_t size = 0;
};

/**
 * Passed to coroutine/fiber constructor, specifies the way in which
 * memory for Stack is Allocated and Released
 * \see Stack
 */
class IStackAllocator {
 public:
  [[nodiscard]] virtual Allocation Allocate() const = 0;

  virtual void Release(Allocation) = 0;

  virtual void SetMinStackSize(size_t bytes) = 0;

  virtual size_t GetMinStackSize() = 0;

  virtual ~IStackAllocator() = default;
};

}  // namespace yaclib
