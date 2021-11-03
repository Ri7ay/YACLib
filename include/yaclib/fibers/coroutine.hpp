#pragma once

#include "default_allocator.hpp"
#include "stack.hpp"
#include "stack_allocator.hpp"
#include "yaclib/fibers/coroutine_base.hpp"

namespace yaclib {

class Coroutine {
 public:
  Coroutine(IStackAllocator& allocator, Routine routine);

  Coroutine(Routine routine);

  void operator()();

  void Resume();

  bool IsCompleted() const;

  ~Coroutine() = default;

  static void Yield();

 private:
  Stack _stack;
  CoroutineBase _impl;
};

}  // namespace yaclib
