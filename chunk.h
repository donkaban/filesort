#ifndef _FILESORT_CHUNK_
#define _FILESORT_CHUNK_

#include "common.h"
#include <cstdio>

// RAII storage type aligned file chunk 
// create from buffer and reading only one time

template <typename T, size_t elements> 
class chunk
{
public: 
    using data_t = std::vector<T> &;
    using getter = std::pair<bool, T>;

    chunk(data_t data) :
        size(elements * sizeof(T)),
        tag(".chunk#" + std::to_string(next::natural<uint64_t>())),
        data(data)
    {
        out.open(tag, std::ios::out | std::ios::binary);
        if(!out)  
            throw std::runtime_error("[chunk] can't create file " + tag);
        out.write(reinterpret_cast<char *>(&data[0]),size);
        out.close();
        in.open(tag, std::ios::in | std::ios::binary);
        if(!in)  
            throw std::runtime_error("[chunk] can't open file " + tag);
    } 
   
    ~chunk()    
    {
        in.close();
        if(std::remove(tag.c_str()) != 0)
            throw std::runtime_error("[chunk] can't delete file " + tag);
    }
    
    T    get()  const {return value;}
    bool pop()
    {
        in.read(reinterpret_cast<char *>(&value),sizeof(T));
        return in.eof(); 
    }


#ifdef UNIT_TEST
    static bool test()
    {
        auto buff = createBuffer<T,elements>(next::random<int32_t>);
        chunk<T, elements> ch1(buff);
        chunk<T, elements> ch2(buff);

        while(!ch1.pop() && !ch2.pop())
            if(ch1.get() != ch2.get()) return false;
        return true; 
    }     
#endif

private:
    static size_t uid ;    // unique chunk id    
    size_t        size;    // size in bytes
    std::string   tag;     // filename
    std::ofstream out;     // write stream
    std::ifstream in;      // read stream 
    data_t        data;    // buffer[size]
    T             value;   // curent value
};
   


#endif
