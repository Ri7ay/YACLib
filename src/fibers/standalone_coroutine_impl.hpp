#pragma once
#include "coroutine_impl.hpp"

#include <yaclib/fibers/default_allocator.hpp>
#include <yaclib/fibers/stack.hpp>
#include <yaclib/fibers/stack_allocator.hpp>
#include <yaclib/fibers/standalone_coroutine.hpp>

namespace yaclib {

class StandaloneCoroutineImpl : public IStandaloneCoroutine {
 public:
  StandaloneCoroutineImpl(StackAllocator& allocator, Routine routine);

  void operator()() override;

  void Resume() override;

  bool IsCompleted() const override;

  ~StandaloneCoroutineImpl() override = default;

  static void Yield();

  void IncRef() noexcept override;

  void DecRef() noexcept override;

 private:
  Stack _stack;
  CoroutineImpl _impl;
};

}  // namespace yaclib
