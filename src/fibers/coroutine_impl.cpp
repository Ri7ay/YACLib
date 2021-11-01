#include "yaclib/fibers/coroutine_impl.hpp"

namespace yaclib {

static thread_local CoroutineImpl* current = nullptr;

CoroutineImpl::CoroutineImpl(StackAllocator& allocator, Routine routine)
    : _stack(allocator.Allocate(), allocator), _impl(_stack.View(), std::move(routine)) {
}

CoroutineImpl::CoroutineImpl(Routine routine) : CoroutineImpl(default_allocator_instance, std::move(routine)) {
}

void CoroutineImpl::operator()() {
  Resume();
}

void CoroutineImpl::Resume() {
  CoroutineImpl* prev = current;
  current = this;

  _impl.Resume();
  current = prev;
}

void CoroutineImpl::Yield() {
  current->_impl.Yield();
}

bool CoroutineImpl::IsCompleted() const {
  return _impl.IsCompleted();
}

}  // namespace yaclib
