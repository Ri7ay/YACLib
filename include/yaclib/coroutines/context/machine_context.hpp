#pragma once
#include <yaclib/coroutines/context/stack_view.hpp>
//TODO if
#include "coroutines/context/setup_stack/setup_stack_x64.hpp"

using Trampoline = void (*)(void* arg);

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
