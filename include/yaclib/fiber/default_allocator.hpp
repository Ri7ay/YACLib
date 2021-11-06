#pragma once

#include <yaclib/fiber/stack_allocator.hpp>

#include <vector>

namespace yaclib {

// TODO(myannyax) won't work for win
/**
 * Allocator used by default
 */
class DefaultAllocator final : public IStackAllocator {
 public:
  [[nodiscard]] Allocation Allocate() const override final;

  void Release(Allocation allocation) override final;

  void SetMinStackSize(size_t bytes) override final;

  size_t GetMinStackSize() override final;

 private:
  size_t _stack_size_pages = 2;
  std::vector<Allocation> _pool;
};

extern DefaultAllocator gDefaultAllocator;

}  // namespace yaclib
