#pragma once

#include <yaclib/fibers/coroutine_base.hpp>
#include <yaclib/fibers/default_allocator.hpp>
#include <yaclib/fibers/stack.hpp>
#include <yaclib/fibers/stack_allocator.hpp>

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
