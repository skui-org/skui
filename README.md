# Introduction

UI framework that uses skia as a low-level drawing toolkit.
It uses the newest features of the C++ Standard library (currently targetting C++14).
This including Technical Specifications (TS) that introduce "desktop" facilities such as `<filesystem>`.

# Status

Skui is in a pre-release development phase, and the API is definitely not stable.
New functionality must be accompanied by corresponding tests.

[![Build Status](https://travis-ci.org/skui-org/skui.svg?branch=master)](https://travis-ci.org/skui-org/skui)
[![Build status](https://ci.appveyor.com/api/projects/status/s9t7o9k8u0p15e0x?svg=true)](https://ci.appveyor.com/project/RubenVanBoxem/skui)

| Operating System | Compiler                | Supported          | Notes |
|------------------| ------------------------|--------------------| ----- |
| Windows          | Visual Studio 2015      |        :x:         | Lacks C++17 structured bindings. |
| Windows          | VS 2015 Clang/C2        |        :x:         | Skia fails to compile due to unimplemented LLVM intrinsics. |
| Windows          | VS 2015 Clang/LLVM 4.0+ | :heavy_check_mark: |       |
| Windows          | Visual Studio 2017      | :heavy_check_mark: |       |
| Windows          | VS 2017 Clang/C2        |        :x:         | Skia fails to compile due to unimplemented LLVM intrinsics. |
| Windows          | VS 2017 Clang/LLVM 4.0+ | :heavy_check_mark: |       |
| Windows          | MinGW-w64 GCC 7.1+      | :heavy_check_mark: | Requires Boost. |
| Windows          | MinGW-w64 Clang 4.0+    | :heavy_check_mark: | Requires Boost. |
| Windows          | Intel C++ 18+           | :heavy_check_mark: |       |
| Linux            | GCC 7.1+                | :heavy_check_mark: |       |
| Linux            | Clang 4.0+              | :heavy_check_mark: |       |
| Linux            | Intel C++ 18+           | :heavy_check_mark: |       |
| Mac OS X 10.12   | XCode 9.2 Clang         |      :soon:        | Missing implementation of core window/application classes. |
| Mac OS X 10.12   | Homebrew GCC 7.1+       |      :soon:        | Missing implementation of core window/application classes. |

# Components

Skui is subdivided in several modules which can depend on other modules but shouldn't become a dependency mess:

 * Core: basic functionality, including signals, properties, strings, paths, application, os abstraction...
 * Graphics: graphical functionality such as canvases, contexts, shapes, text, ...
 * GUI: abstraction of platform-specific UI code, including event loops, windows, ...
 * OpenGL: abstraction of platform-specific OpenGL initialization code, header differences, ...
 * ...
 * Examples: example programs showing SkUI features
 * Tests: unit tests for various components to ensure correct and expected behaviour now and in the future.

This list will grow (and change) as the library's design takes shape.

## Roadmap

### 0.0.x

 * establish a logical basis for UI functionality, including:
   * signals, properties, strings
   * basic drawing functionality
   * event handling
   * basic UI controls and layout engine
   * Application window and event abstraction
     * Windows
     * Linux
     * OS X
     * ...

### 0.1.x

 * OS Notification system implementation
   * taskbar icon
   * notifications
   * ...
 * Improve core logic and functionality.
 * OS theming of all controls and windows

### 0.x.x

 * More application logic (model/views, ...)
 * process handling
 * advanced drawing
 * advanced UI controls, including:
   * scrollbars
   * tables, lists, etc.
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
