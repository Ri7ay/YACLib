#pragma once

#include "yaclib/fibers/stack_view.hpp"

namespace yaclib {

using Trampoline = void (*)(void* arg);

/***
 * registers and stack switch
 */
class MachineContext {
 public:
  MachineContext();

  void Setup(StackView stack, Trampoline trampoline, void* arg);

  void SwitchTo(MachineContext& target);

  ~MachineContext();

 private:
  void** _context;
};

}  // namespace yaclib
