# jenkins_log_cpp_writer
> 
> - Create Jenkins conformed test log file in cpp with help of tinyxml http://www.grinninglizard.com/tinyxml2/
> - Please check test/main.cpp for the usage.
> - test/example_log.xml is the output file from main.cpp, which is accepted by jenkins.

## Requirement
>
> - Platform: Windows 10
> - Compiler: >= {MSVC++ 10.0  _MSC_VER == 1600 (Visual Studio 2010 version 10.0)}

## Motivation

This small library aims to generate Jenkins log file when 
>
> - running test on Jenkins (mostly the runtime test, not static test, e.g. by google test) for cpp module
> - you don't have a handy tool to record you test results in xml
