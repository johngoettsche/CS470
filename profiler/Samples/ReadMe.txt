Embedded Profiler Samples
=========================
All samples are configured to demonstrate proper usage of the EProfiler
library and to avoid struggling with your project configuration.

Building
--------
To build a sample go to a subdirectory corresponding to your platform.
Under MSVC just open an included solution and build the sample.
For other platforms just call 'make' since there is a Makefile for each
platform. A symbol file will be generated automatically in a post build action.

Running
-------
It is possible to run samples in two profiling modes:
- Call Tree Mode and 
- Function List Mode.
There are scripts to show how to run it properly in each platform subdirectory.
They are bash scripts for Unix like platform and batch files for Windows.

Notes
-----
- Samples are so simple that MSVC is able to inline everything to a single
  main function. Therefore the Inline Function Expansion option is set to
  'Only __inline (/Ob1)' to generate complete call tree or function list.
  Otherwise the produced log would contain only the main function because
  MSVC does not support instrumentation of inlined functions. Purpose of these
  examples is just to provide an easy way of the embedded profiler usage,
  so it is easier just to forbid inlining than to create a complex sample.
- For MinGW platform, it is supposed that bash is available 
  (only bash scripts are included for running samples).
