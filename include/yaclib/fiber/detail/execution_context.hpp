#pragma once

#include <yaclib/fiber/stack_view.hpp>

#include <algorithm>

namespace yaclib {

using Trampoline = void (*)(void* arg);

class ExecutionContext {
 public:
  ExecutionContext();

  void Setup(StackView stack, Trampoline trampoline, void* arg);

  void SwitchTo(ExecutionContext& other);

  ~ExecutionContext();

 private:
  void** _context;
};

}  // namespace yaclib
