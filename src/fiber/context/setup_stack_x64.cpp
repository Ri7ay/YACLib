#include "setup_stack_x64.hpp"

#include "asm/switch_context_x86_64.hpp"

namespace yaclib {

extern "C" void yaclib_trampoline();

static const int kAlignment = 16;

const size_t kAsmContextSize = (YACLIB_RIP_INDEX + 1) * sizeof(void*);

void SetupStack(StackView stack, Trampoline trampoline, void* arg, void** context) {
  stack.Align(kAlignment);

  stack.Push((void*)trampoline);
  stack.Push(arg);

  context[YACLIB_RSP_INDEX] = stack.Back();
  context[YACLIB_RIP_INDEX] = (void*)(yaclib_trampoline);
}

}  // namespace yaclib
