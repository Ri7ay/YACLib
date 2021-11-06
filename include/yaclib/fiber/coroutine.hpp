#pragma once

#include <yaclib/fiber/coroutine_base.hpp>
#include <yaclib/fiber/default_allocator.hpp>
#include <yaclib/fiber/stack.hpp>
#include <yaclib/fiber/stack_allocator.hpp>

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
