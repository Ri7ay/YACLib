#pragma once

#include "yaclib/fibers/stack_view.hpp"
// TODO if
#include "setup_stack_x64.hpp"

namespace yaclib {

/***
 * registers and stack switch
 */
class MachineContext {
 public:
  MachineContext() = default;

  void Setup(StackView stack, Trampoline trampoline, void* arg);

  void SwitchTo(MachineContext& target);

 private:
  YaclibFiberMachineContext _context;
};

}  // namespace yaclib
