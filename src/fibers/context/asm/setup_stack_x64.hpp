#pragma once

#include "yaclib/fibers/detail/machine_context.hpp"
#include "yaclib/fibers/stack_view.hpp"

namespace yaclib {

//TODO(myannyax) check how much saving on stack is better
extern const size_t kYaclibContextSize;

void SetupStack(StackView stack, Trampoline trampoline, void* arg, void** context);

}  // namespace yaclib
