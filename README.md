# mymodc
[![Build Status][WorkflowBadge]][WorkflowUrl]

Modern C experiments

# How to test

## Prerequisites
To build, first install [vade](https://github.com/nsauzede/ns_vade).

## Run build/test
```
    CC  modc.o
    AR  modc.a
    AR  libmodc.a
    CC0 libmodc.so
    CC  test.o
    AR  modc_test.a
    AR  libmodc_test.a
    CXX modc_test.exe
    VGRUN       ./vade/target/bin/modc/modc_test.exe
[==========] Running tests from test suite.
[----------] Global test environment set-up.
[ RUN      ] modc_Test_proto_
begin
Hello world!
Answer is 42
end
testing closure: 42
float=42.000000
Succesfully loaded image
date=2021/07/02
find_first=7/02
2021
07
02
year=2021
month=07
day=02
hour=
Hello world! { } {OPT} 42
Hello world! {} {OPT} 42
Hello world! { } "{OPT}" 42
str_buf=[strbuf]
[       OK ] modc_Test_proto_ (0 ms)
[----------] Global test environment tear-down
[==========] 1 tests from test suite ran. (39 ms total)
[  PASSED  ] 1 tests.
==================================
Code coverage (1 tests)
==================================
vade/target/pkg/modc/modc.gcda: 90.91% of 176
```

# Credits
Initial ideas sparked from [Modern C and What We Can Learn From It](https://youtu.be/QpAhX-gsHMs) by Luca Sas.

[WorkflowBadge]: https://github.com/nsauzede/ns_modc/actions/workflows/vade.yml/badge.svg
[WorkflowUrl]: https://github.com/nsauzede/ns_modc/commits/main
