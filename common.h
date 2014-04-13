#ifndef _FILESORT_COMMON_
#define _FILESORT_COMMON_

#include <stdexcept>
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <fstream>
#include <limits> 
#include <random>
#include <algorithm>


// ONLY FOR TESTING. ANY OPTIMIZATION HERE IS THE ROOT OF ALL EVIL


constexpr size_t M2B(size_t size) {return 1024 * 1024 * size;} // Megabytes to bytes
constexpr float  B2M(size_t size) {return size/1024./1024.;}   // Bytes to Megabytes

template <typename FT, typename ... AT>
void trace(FT && func, AT &&... args)
{
    std::cout << "> " << std::flush;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    func(args...);
    std::chrono::duration<float> dt(std::chrono::system_clock::now() - start);
    std::cout << " -> " << dt.count() << " sec." << std:: endl;
} 

namespace next
{
    template <typename T>
    T natural()
    {
        static T ret = 0;
        return ret++;
    }
    template <typename T>
    T random()
    {
        static std::mt19937 rng;
        std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(),std::numeric_limits<T>::max());
        return dist(rng);
    }
    template <typename T>
    T constant()
    {
        return 42;
    }
}

template <typename T> 
void createFile(const std::string &tag, size_t cap,const std::function<T()> &next)
{
	std::ofstream stream(tag, std::ios::out | std::ios::binary);
	std::cout << "[create] " << tag <<"; capacity: " << cap << "; size: " << B2M(cap * sizeof(T)) << " Mb" << std::flush;
    for(auto i = 0u; i< cap; i++)
    {	
    	T val = next();
        stream.write(reinterpret_cast<char *>(&val), sizeof(T));
    }
    stream.close();
}



#endif
