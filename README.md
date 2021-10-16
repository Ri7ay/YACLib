# [YACLib](https://github.com/YACLib/YACLib)
_Yet Another Concurrency Library_

[![GitHub license](
https://img.shields.io/badge/license-MIT-blue.svg)](
https://raw.githubusercontent.com/YACLib/YACLib/main/LICENSE)
[![FOSSA status](
https://app.fossa.com/api/projects/git%2Bgithub.com%2FYACLib%2FYACLib.svg?type=shield)](
https://app.fossa.com/projects/git%2Bgithub.com%2FYACLib%2FYACLib)

[![Test](
https://github.com/YACLib/YACLib/actions/workflows/test.yml/badge.svg?branch=main)](
https://github.com/YACLib/YACLib/actions/workflows/test.yml)
[![Test with Google sanitizer](
https://github.com/YACLib/YACLib/actions/workflows/google_sanitizer.yml/badge.svg?branch=main)](
https://github.com/YACLib/YACLib/actions/workflows/google_sanitizer.yml)
[![Check code format](
https://github.com/YACLib/YACLib/actions/workflows/code_format.yml/badge.svg?branch=main)](
https://github.com/YACLib/YACLib/actions/workflows/code_format.yml)

[![Test coverage](
https://codecov.io/gh/YACLib/YACLib/branch/main/graph/badge.svg)](
https://codecov.io/gh/YACLib/YACLib)
[![Codacy Badge](
https://app.codacy.com/project/badge/Grade/4113686840a645a8950abdf1197611bd)](
https://www.codacy.com/gh/YACLib/YACLib/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=YACLib/YACLib&amp;utm_campaign=Badge_Grade)


## Table of Contents
* [About YACLib](#about)
* [Useful links](#links)
* [Examples](#examples)
* [Getting started](#quickstart)
* [Requirements](#req)
* [Support](#support)
* [License](#license)

<a name="about"></a>
## About YACLib
**YACLib** is a lightweight C++ library for concurrent and parallel task execution, that is striving to satisfy the following properties:
* Easy to use
* Easy to build
* Zero cost abstractions
* Good test coverage

For more details check our design [document](doc/design.md)

<a name="links"></a>
## Useful links

### For user

* [Documentation](https://yaclib.github.io/YACLib)
* [Examples](test/example)
* [Install guide](doc/install.md)
* [Benchmarks](TODO(MBkkt))

### For developer

* [Specification](https://yaclib.github.io/YACLib)
* [Targets description](doc/target.md)
* [About dependencies](doc/dependency.md)
* [Pull request guide](doc/pr_guide.md)
* [Style guide](doc/style_guide.md)

<a name="examples"></a>
## Examples
Here are short examples of using some features from YACLib, for more details check examples in [useful links](#examples)

* Asynchronous pipeline with future
```C++
// create thread pool with 4 threads
auto tp = yaclib::MakeThreadPool(4);

auto first = [] { return 42; };
auto second = [](int r) { return r * 2; };
auto third = [](int r) { return r + 1; };
auto fourth = [](int r) { return std::to_string(r); };
auto last = [](yaclib::util::Result<std::string> r) {
    std::cout << "Pipeline result: <" 
              << std::move(r).Ok() << ">" << std::endl;
yaclib::Run(tp, first).Then(second)
                      .Then(third)
                      .Then(fourth)
                      .Subscribe(last); // 42 * 2 + 1
};
```
* Error recovering from callbacks
```
auto tp = yaclib::MakeThreadPool(4);
auto f = yaclib::Run(tp, [] { return 1; })
            .Then([](int x) { return x + 15; })
            .Then([](int y) { throw std::runtime_error{""}; })
            .Then([](std::exception_ptr) { return 15; });
int x = std::move(f).Get().Value(); // 15
```

* Serial Executor (strand)

```C++
auto tp = MakeThreadPool(4);
// decorated thread pool by serializing tasks:
auto strand = MakeSerial(tp);

size_t counter = 0;

std::vector<std::thread> threads;

for (size_t i = 0; i < 5; ++i) {
    threads.emplace_back([&] {
        for (size_t j = 0; j < 1000; ++j) {
            strand->Execute([&] {
                ++counter; // no data race!
            });
        }
    });
}
```
* Future combinators (WhenAll, WhenAny)

```C++
auto tp = yaclib::MakeThreadPool(4);
std::vector<yaclib::Future<int>> futs;

// Run sync computations in parallel
for (size_t i = 0; i < 5; ++i) {
    futs.push_back(yaclib::Run(tp, [i]() -> int {
        return i;
    }));
}

// Will be ready when all futures are ready
yaclib::Future<std::vector<int>> all = yaclib::WhenAll(futs.begin(), futs.size());
std::vector<int> ints = std::move(all).Get().Value();
```

<a name="quickstart"></a>
## Getting started
For quick start just paste this code in your `CMakeLists.txt` file
```cmake
include(FetchContent)
FetchContent_Declare(yaclib
        GIT_REPOSITORY https://github.com/YACLib/YACLib.git
        GIT_TAG main
        )
FetchContent_MakeAvailable(yaclib)
link_libraries(yaclib)
```

<a name="req"></a>
## Requirements
A recent C++ compilers that support C++17:
* Gcc-9.* and later
* Clang-11.* and later
* Apple Clang
* MSVC

<a name="support"></a>
## Support
We are always open for issues and pull requests, also you can check our emails:
* kononov.nikolay.nk1@gmail.com

<a name="license"></a>
## License
YACLib is made available under MIT License.
See [LICENSE.txt](LICENSE.txt) for details

[![FOSSA Status](
https://app.fossa.com/api/projects/git%2Bgithub.com%2FYACLib%2FYACLib.svg?type=large)](
https://app.fossa.com/projects/git%2Bgithub.com%2FYACLib%2FYACLib?ref=badge_large)
