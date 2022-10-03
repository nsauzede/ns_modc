# mymodc
Modern C experiments

# How to test

## Prerequisites
To build, first install vade :
[vade](https://github.com/nsauzede/ns_vade)

## Run build/test
```
~/perso/git/mymodc$ vade clean test
    RM  vade/pkg
    RM  vade/bin
    CC  modc.o
    AR  modc.a
    AR  libmodc.a
    CC  modc_test.o
    CC  test.o
    AR  modc_test.a
    AR  libmodc_test.a
    CXX modc_test.exe
    CC  modc_proto.o
    AR  modc_proto.a
    AR  libmodc_proto.a
    CXX modc_proto.exe
    VGRUN       ./vade/bin/modc_test.exe
[==========] Running tests from test suite.
[----------] Global test environment set-up.
[ RUN      ] modc_TestMock_
[       OK ] modc_TestMock_ (0 ms)
[----------] Global test environment tear-down
[==========] 1 tests from test suite ran. (12 ms total)
[  PASSED  ] 1 tests.
```

# Credits
Initial ideas sparked from [Modern C and What We Can Learn From It](https://youtu.be/QpAhX-gsHMs) by Luca Sas.
