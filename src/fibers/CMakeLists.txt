list(APPEND YACLIB_INCLUDES
  ${YACLIB_INCLUDE_DIR}/fibers/coroutine_impl.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/coroutine_base.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/stack.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/stack_allocator.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/stack_view.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/default_allocator.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/detail/setup_stack_x64.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/detail/execution_context.hpp
  ${YACLIB_INCLUDE_DIR}/fibers/detail/machine_context.hpp
  )

list(APPEND YACLIB_HEADERS
  # TODO(myannyax): pick based on a system
  ${CMAKE_CURRENT_SOURCE_DIR}/context/asm/switch_context_x86_64.hpp
  )

SET(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")

list(APPEND YACLIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/coroutine_base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/coroutine_impl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/context/execution_context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/context/machine_context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/context/default_allocator.cpp
  # TODO(myannyax): pick based on a system
  ${CMAKE_CURRENT_SOURCE_DIR}/context/setup_stack_x64.cpp
  )

list(APPEND YACLIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/context/asm/switch_context_x86_64.S
  )

add_files()
