#include "fibers/context/asm/setup_stack_x64.hpp"

#include "asm/switch_context_x86_64.hpp"

#include <cstdint>

namespace yaclib {

static void MachineContextTrampoline(void* arg1, void* arg2) {
  auto trampoline = (Trampoline)arg1;
  trampoline(arg2);
}

static const int kAlignment = 16;

const size_t kYaclibContextSize = (YACLIB_RIP_INDEX + 1) * sizeof(void*);

void SetupStack(StackView stack, Trampoline trampoline, void* arg, void** context) {
  size_t shift = (size_t)(stack.Back() - (sizeof(uintptr_t))) % kAlignment;
  char* top = stack.Back() - shift;

  context[YACLIB_RSP_INDEX] = top;
  context[YACLIB_RDI_INDEX] = (void*)trampoline;
  context[YACLIB_RSI_INDEX] = arg;

  context[YACLIB_RIP_INDEX] = (void*)MachineContextTrampoline;
}

}  // namespace yaclib
