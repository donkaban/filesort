#ifndef _FILESORT_COMMON_
#define _FILESORT_COMMON_

#include <chrono>
#include <functional>
#include <fstream>
#include <limits> 
#include <iostream>
#include <vector>
#include <random>


static std::mt19937 rng;

constexpr size_t M2B(size_t size) {return 1024 * 1024 * size;}

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

template <typename T>
T getRandom()
{
    std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(),std::numeric_limits<T>::max());
    return dist(rng);
}

template <typename T, size_t size>
std::vector<T> createRandomChunk()
{
    std::vector<T> res;
    res.reserve(size);
    for(auto i = 0; i < size; i++)
    {    
        res.push_back(getRandom<T>());
    }
    return res;
}

template <typename T> 
void createGarbageFile(const std::string & name, size_t elements)
{
	std::ofstream stream(name, std::ios::out | std::ios::binary);
	std::cout << "create file " << name <<"; elements: " << elements << "; size: " << elements * sizeof(T) << " bytes -> ";
	std::cout.flush();
    for(auto i = 0u; i< elements; i++)
    {	
    	T val = getRandom<T>();
        stream.write(reinterpret_cast<char *>(&val), sizeof(T));
    	
    }
    stream.close();
}



#endif