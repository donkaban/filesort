#ifndef _FILESORT_UTILS_
#define _FILESORT_UTILS_

#include <chrono>
#include <functional>
 
// trace time for call method

template <typename callable, typename ... arguments>
static float trace(callable && f, arguments &&... args)
{
    std::function<typename std::result_of<callable(arguments...)>::type()> 
        task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    task();
    std::chrono::duration<float> dt(std::chrono::system_clock::now() - start);
    return dt.count();
} 

// logger. only for variadic templates example







#endif