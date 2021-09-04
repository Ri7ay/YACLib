#pragma once

#include <yaclib/async/detail/core.hpp>
#include <yaclib/executor/executor.hpp>
#include <yaclib/util/type_traits.hpp>

namespace yaclib::async {

template <typename T>
class Future final {
 public:
  static_assert(!util::IsFutureV<T>, "Future cannot be instantiated with Future");
  static_assert(!util::IsResultV<T>, "Future cannot be instantiated with Result");
  static_assert(!std::is_same_v<util::DecayT<T>, std::error_code>,
                "Future cannot be instantiated with std::error_code");
  static_assert(!std::is_same_v<util::DecayT<T>, std::exception_ptr>,
                "Future cannot be instantiated with std::exception_ptr");

  Future(const Future&) = delete;
  Future& operator=(const Future&) = delete;

  Future() = default;
  explicit Future(detail::FutureCorePtr<T> core);

  Future(Future&& other) noexcept = default;
  Future& operator=(Future&& other) noexcept = default;

  ~Future();

  bool IsReady() const noexcept;

  util::Result<T> Get() const&;  // You can use this iff you want call Get multiple times
  util::Result<T> Get() &&;
  util::Result<T> Get() const&& = delete;  // TODO maybe add as ref to 'Get() &&'
  util::Result<T> Get() & = delete;

  void Cancel() &&;

  template <typename Functor>
  auto Then(Functor&& functor) &&;

  template <typename Functor>
  auto Then(executor::IExecutorPtr executor, Functor&& functor) &&;

  template <typename Functor>
  void Subscribe(Functor&& functor) &&;

  template <typename Functor>
  void Subscribe(executor::IExecutorPtr executor, Functor&& functor) &&;

 private:
  template <typename U>
  friend class Future;

  template <typename U, typename Functor>
  Future<U> ThenResult(Functor&& functor);

  template <typename U, typename Functor>
  Future<U> AsyncThenResult(Functor&& functor);

  detail::FutureCorePtr<T> _core;
};

}  // namespace yaclib::async
