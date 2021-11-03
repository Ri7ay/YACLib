#include "yaclib/fibers/coroutine.hpp"

namespace yaclib {

static thread_local Coroutine* current = nullptr;

Coroutine::Coroutine(IStackAllocator& allocator, Routine routine)
    : _stack(allocator), _impl(_stack.View(), std::move(routine)) {
}

Coroutine::Coroutine(Routine routine) : Coroutine(default_allocator_instance, std::move(routine)) {
}

void Coroutine::operator()() {
  Resume();
}

void Coroutine::Resume() {
  Coroutine* prev = current;
  current = this;

  _impl.Resume();
  current = prev;
}

void Coroutine::Yield() {
  current->_impl.Yield();
}

bool Coroutine::IsCompleted() const {
  return _impl.IsCompleted();
}

}  // namespace yaclib
