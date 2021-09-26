#pragma once

#include <yaclib/util/type_traits.hpp>

#include <exception>
#include <system_error>
#include <variant>

namespace yaclib::util {

template <typename T>
class Result;

namespace detail {

template <typename U>
struct ResultValue {
  using type = U;
};

template <typename U>
struct ResultValue<Result<U>> {
  using type = U;
};

template <typename T>
using ResultValueT = typename ResultValue<T>::type;

}  // namespace detail

/**
 * Result states \see Result
 * \enum Empty, Value, Error, Exception
 */
enum class ResultState {
  Empty = 0,
  Value,
  Error,
  Exception,
};

/**
 * \class Exception for std::error_code
 * \see Result
 */
class ResultError : public std::exception {
 public:
  explicit ResultError(std::error_code error) : _error{error} {
  }
  std::error_code Get() const {
    return _error;
  }

 private:
  std::error_code _error;
};

struct ResultEmpty : std::exception {};

/**
 * Encapsulated return value from caller
 *
 * \tparam T type to store in Result
 */
template <typename T>
class Result {
  static_assert(!std::is_reference_v<T>,
                "Result cannot be instantiated with reference, "
                "you can use std::reference_wrapper or pointer");
  static_assert(!std::is_volatile_v<T> && !std::is_const_v<T>,
                "Result cannot be instantiated with cv qualifiers, because it's unnecessary");
  static_assert(!util::IsResultV<T>, "Result cannot be instantiated with Result");
  static_assert(!util::IsFutureV<T>, "Result cannot be instantiated with Future");
  static_assert(!std::is_same_v<T, std::error_code>, "Result cannot be instantiated with std::error_code");
  static_assert(!std::is_same_v<T, std::exception_ptr>, "Result cannot be instantiated with std::exception_ptr");

  struct Unit {};
  using VariantT =
      std::variant<std::monostate, std::error_code, std::exception_ptr, std::conditional_t<std::is_void_v<T>, Unit, T>>;

 public:
  static Result Default() {
    static_assert(std::is_void_v<T>, "Only for void");
    return {Unit{}};
  }

  Result() : _result{std::monostate{}} {
  }

  Result(Result&& other) noexcept(std::is_nothrow_move_constructible_v<VariantT>) : _result{std::move(other._result)} {
  }

  Result& operator=(Result&& other) noexcept(std::is_nothrow_move_assignable_v<VariantT>) {
    _result = std::move(other._result);
    return *this;
  }

  Result(const Result& other) = delete;
  Result& operator=(const Result& other) = delete;

  template <typename U>
  Result(U&& result) : _result{std::forward<U>(result)} {
  }

  template <typename U>
  void Set(U&& result) {
    _result = std::forward<U>(result);
  }

  explicit operator bool() const noexcept {
    return State() == ResultState::Value;
  }

  T Ok() && {
    switch (State()) {
      case ResultState::Value: {
        if constexpr (std::is_void_v<T>) {
          return;
        } else {
          return std::move(std::get<T>(_result));
        }
      }
      case ResultState::Exception: {
        std::rethrow_exception(std::get<std::exception_ptr>(_result));
      }
      case ResultState::Error: {
        throw ResultError{std::get<std::error_code>(_result)};
      }
      case ResultState::Empty: {
        throw ResultEmpty{};
      }
    }
  }

  [[nodiscard]] ResultState State() const noexcept {
    if (std::holds_alternative<std::monostate>(_result)) {
      return ResultState::Empty;
    } else if (std::holds_alternative<std::error_code>(_result)) {
      return ResultState::Error;
    } else if (std::holds_alternative<std::exception_ptr>(_result)) {
      return ResultState::Exception;
    } else {
      return ResultState::Value;
    }
  }

  T Value() && noexcept {
    if constexpr (!std::is_void_v<T>) {
      return std::move(std::get<T>(_result));
    }
  }

  std::error_code Error() && noexcept {
    return std::get<std::error_code>(_result);
  }

  std::exception_ptr Exception() && noexcept {
    return std::get<std::exception_ptr>(_result);
  }

 private:
  VariantT _result;
};

}  // namespace yaclib::util
