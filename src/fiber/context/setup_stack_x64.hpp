#pragma once

#include "yaclib/fiber/detail/execution_context.hpp"
#include "yaclib/fiber/stack_view.hpp"

namespace yaclib {

// TODO(myannyax) check how much saving on stack is better
extern const size_t kAsmContextSize;

void SetupStack(StackView stack, Trampoline trampoline, void* arg, void** context);

}  // namespace yaclib
