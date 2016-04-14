filesort
========
### interview c++ file merge sort test

*   gcc 4.7 or newer
*   clang 3.2 or newer
*   tested on macOS (64bit) 10.9.2 with clang 3.3 and ubuntu (32bit) 12.04 with gcc 4.7.2

### goals
* 4 hours from scratch
* clean and simple code
* test results

###test results :
-----------------
    bash-3.2$ ./test
    [create]test.bin; capacity: 268435456; size: 1024 Mb -> 9.29266 sec.
    [split] limit: 25Mb ch: 40 remain: 6Mb -> 26.7809 sec.
    [merge] limit: 25Mb ch: 40 remain: 6Mb -> 52.4279 sec.
    [check] test.result1 ok! -> 6.47656 sec.
    [split] limit: 50Mb ch: 20 remain: 6Mb -> 27.7005 sec.
    [merge] limit: 50Mb ch: 20 remain: 6Mb -> 33.4748 sec.
    [check] test.result2 ok! -> 6.81033 sec.
    [split] limit: 100Mb ch: 10 remain: 6Mb -> 26.6209 sec.
    [merge] limit: 100Mb ch: 10 remain: 6Mb -> 22.9036 sec.
    [check] test.result3 ok! -> 6.87742 sec.

####NB: multithreaded ops and windows builds not implemented for this interview

