#pragma once
#include "yaclib/fibers/detail/execution_context.hpp"

#include "stack_view.hpp"
#include <yaclib/util/func.hpp>

#include <utility>

namespace yaclib {

using Routine = yaclib::util::IFuncPtr;

/***
 * base coroutine class
 */
class CoroutineBase {
 public:
  CoroutineBase(const StackView& stack_view, Routine routine) : _routine(std::move(routine)) {
    _context.Setup(stack_view, Trampoline, this);
  }

  void operator()();

  void Resume();

  void Yield();

  [[nodiscard]] bool IsCompleted() const;

 private:
  [[noreturn]] static void Trampoline(void* arg);

  void Complete();

  ExecutionContext _context{};
  ExecutionContext _caller_context{};
  Routine _routine;
  bool _completed = false;
  std::exception_ptr _exception;
};

}  // namespace yaclib
