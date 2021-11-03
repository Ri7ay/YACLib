#include "yaclib/fibers/detail/execution_context.hpp"
// TODO(myannyax) if
#include "asm/setup_stack_x64.hpp"

extern "C" void yaclib_switch_context(void* from_context, void* to_context);

namespace yaclib {

ExecutionContext::ExecutionContext() : _context(new void*[kYaclibContextSize]) {
}

void ExecutionContext::Setup(StackView stack, Trampoline trampoline, void* arg) {
  SetupStack(stack, trampoline, arg, _context);
}

void ExecutionContext::SwitchTo(ExecutionContext& other) {
  yaclib_switch_context(_context, other._context);
}

ExecutionContext::~ExecutionContext() {
  delete[] _context;
}

}  // namespace yaclib
