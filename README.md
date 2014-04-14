filesort
========

c++ file merge sort test

test results :
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

NB: multithreaded ops not implemented yet
-----------------------------------------