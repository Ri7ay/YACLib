#pragma once
#include "yaclib/fibers/coroutine_base.hpp"

#include "default_allocator.hpp"
#include "stack.hpp"
#include "stack_allocator.hpp"

namespace yaclib {

class CoroutineImpl {
 public:
  CoroutineImpl(StackAllocator& allocator, Routine routine);

  CoroutineImpl(Routine routine);

  void operator()();

  void Resume();

  bool IsCompleted() const;

  ~CoroutineImpl() = default;

  static void Yield();

 private:
  Stack _stack;
  CoroutineBase _impl;
};

}  // namespace yaclib
