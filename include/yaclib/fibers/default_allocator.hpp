#pragma once

#include <yaclib/fibers/stack_allocator.hpp>

#include <vector>

namespace yaclib {

// TODO(myannyax) won't work for win
/**
 * Allocator used by default
 */
class DefaultAllocator : public IStackAllocator {
 public:
  [[nodiscard]] Allocation Allocate() const override;

  void Release(Allocation allocation) override;

  void SetMinStackSize(size_t bytes) override;

  size_t GetMinStackSize() override;

 private:
  size_t _stack_size_pages = 2;
  std::vector<Allocation> _pool;
};

extern DefaultAllocator default_allocator_instance;

}  // namespace yaclib
