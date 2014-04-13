#ifndef _FILESORT_CHUNK_
#define _FILESORT_CHUNK_

#include "common.h"
#include <cstdio>

// RAII storage type aligned file chunk 
// create from buffer and reading only one time

template <typename T> 
class chunk
{
public: 
    chunk(const std::vector<T> &data,size_t elements) :
        size(elements * sizeof(T)),
        tag(".chunk#" + std::to_string(next::natural<uint64_t>()))
    {
        if(data.size() != elements)
            throw std::runtime_error("[chunk] buffer size mismatch");
            
        std::ofstream out(tag, std::ios::out | std::ios::binary);
        if(!out)  
            throw std::runtime_error("[chunk] can't create file " + tag);
        out.write(reinterpret_cast<const char *>(&data[0]),size);
        out.close();
        in.open(tag, std::ios::in | std::ios::binary);
        if(!in)  
            throw std::runtime_error("[chunk] can't open file " + tag);
        pop();
    } 
   
    virtual ~chunk()    
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

private:
    size_t        size;    // size in bytes
    std::string   tag;     // filename
    std::ifstream in;      // read stream 
    T             value;   // curent value
};
   


#endif
