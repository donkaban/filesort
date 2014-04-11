#ifndef _FILESORT_CHUNK_
#define _FILESORT_CHUNK_

#include "common.h"
#include <cstdio>

// size in elements aligned

template <typename T, size_t elements>
class chunk
{
public: 

    using data_t = std::vector<T> &;

    chunk(const std::string &tag, data_t data) :
        size(elements * sizeof(T)),
        tag(tag),
        out(tag, std::ios::out | std::ios::binary),
        in(tag,  std::ios::in  | std::ios::binary),
        data(data)
    {
        if(!out)  
            throw std::runtime_error("[chunk] can't open file " + tag);
    }
    ~chunk()    
    {
        in.close();
        out.close();
        if(std::remove(tag.c_str()) != 0)
            throw std::runtime_error("[chunk] can't delete file " + tag);
            

    }
    void flush()
    {
        out.write(reinterpret_cast<char *>(&data[0]),size);
        out.flush();
    }
    void read()
    {
        data.resize(size);
        in.seekg(0);
        in.read(reinterpret_cast<char *>(&data[0]), size);
    }
    
    T get() const 
    {
        return value;
    }
    void next()   
    {

        in.read(reinterpret_cast<char *>(&value),sizeof(T));
    }

#ifdef UNIT_TEST
    static bool test()
    {
        bool passed = true;
        auto buff = createRandomChunk<T,elements>();
        
        chunk<T, elements> ch1("ch1.dat",buff);
        chunk<T, elements> ch2("ch2.dat",buff);
        
        ch1.flush();
        ch2.flush();



        return passed; 
    }     
#endif

private:
    size_t        size;
    std::string   tag;
    std::ofstream out;
    std::ifstream in;
    data_t        data;
    T             value;
};
   


#endif