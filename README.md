# Introduction

UI framework that uses skia as a low-level drawing toolkit.
It uses the newest features of the C++ Standard library (currently targetting C++14).
This including Technical Specifications (TS) that introduce "desktop" facilities such as `<filesystem>`.

# Status

Skui is in a pre-release development phase, and the API is definitely not stable.
New functionality must be accompanied by corresponding tests.

[![Build Status](https://travis-ci.org/skui-org/skui.svg?branch=master)](https://travis-ci.org/skui-org/skui)
[![Build status](https://ci.appveyor.com/api/projects/status/s9t7o9k8u0p15e0x?svg=true)](https://ci.appveyor.com/project/RubenVanBoxem/skui)

| Operating System | Compiler             |     Supported      | Notes |
| -----------------| -------------------- |:------------------:| ----- |
| Windows          | Visual Studio 2015   | :heavy_check_mark: |       |
| Windows          | VS 2015 Clang/C2     |        :x:         | Skia fails to compile due to unimplemented LLVM intrinsics. |
| Windows          | VS 2015 Clang/LLVM   | :heavy_check_mark: |       |
| Windows          | MinGW-w64 GCC 6.3+   | :heavy_check_mark: | Cross-compilation is possible. |
| Windows          | MinGW-w64 Clang 3.9+ | :heavy_check_mark: | Cross-compilation is possible. |
| Windows          | Intel C++ 17.0.4     |        :x:         | Fails to compile value_ptr. See https://software.intel.com/en-us/comment/1895294 |
| Linux            | GCC 6.3+             | :heavy_check_mark: |       |
| Linux            | Clang 4.0            | :heavy_check_mark: |       |
| Linux            | Intel C++ 17.0.4     |        :x:         | Fails to compile value_ptr. See https://software.intel.com/en-us/comment/1895294 |
| Mac OS X 10.12   | XCode 8.3 Clang      |        :x:         | Missing implementation of core window/application classes. |
| Mac OS X 10.12   | Homebrew GCC 6.3+    |        :x:         | Missing implementation of core window/application classes. |

# Components

Skui is subdivided in several modules which can depend on other modules but shouldn't become a dependency mess:

 * Core: basic functionality, including signals, properties, strings, application
 * ...

This list will grow (and change) as the library's design takes shape.

## Roadmap


### 0.0.x

 * establish a logical basis for UI functionality, including:
   * signals, properties, strings
   * basic drawing functionality
   * event handling
   * basic UI controls
   * Application abstraction

### 0.1.x

 * Application window abstraction
   * Windows
   * Linux
   * OS X
   * ...
 * OS Notification system implementation
   * taskbar icon
   * notifications
   * ...
 * Improve core logic and functionality.

### 0.x.x

 * Windows, Linux, OS X support of the above
 * More application logic (model/views, ...)
 * process handling
 * advanced drawing
 * advanced UI controls, including:
   * scrollbars
   * tables, lists, etc.
 * OS theming of all controls and windows
 * File I/O systems?
 * Add missing unit tests
 * Add missing documentation
 * ...

### 1.x.x

 * Stability and features of a basic UI framework
 * Improve platform support
 * Solve all them bugs.
 * Correct all them documentation typos.

### x.x.x

 * Supreme world domination through superiour benevolent A.I.
