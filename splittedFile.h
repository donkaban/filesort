#ifndef _FILESORT_SPLITTED_FILE_
#define _FILESORT_SPLITTED_FILE_

#include "common.h"
#include "chunk.h"
#include <list>

// nb: mem limit is type aligned

template<typename T, size_t limit>
class splittedFile
{
public:
    
    using buff_t     = std::vector<T>;
    using predicat_t = std::function<bool(T &, T &)>; 

    splittedFile(const std::string &tag, const predicat_t &predicat) :
        tag(tag),
        infile(tag, std::ios::in | std::ios::binary),
        predicat(predicat)
    {
        infile.seekg(0, std::ios::end);
        filesize = infile.tellg();
        infile.seekg(0, std::ios::beg);
        if(filesize % sizeof(T) != 0)
            throw std::runtime_error("[splittedFile] file size not aligned for data type");
        capacity      = filesize/ sizeof(T);
        numFullChunks = capacity / limit;
        remainSize    = capacity % limit;
    } 

    virtual ~splittedFile()
    {}

    virtual void split()
    {
        std::cout << "[split] limit: "<< B2M(limit*sizeof(T)) << "Mb  ch: " << numFullChunks << " remain: " << remainSize << std::flush;
        for(auto i = 0u; i< numFullChunks; i++)
            addChunk();
        // if(remainSize > 0)
        //     addChunk(remainSize);

    }
    virtual void merge()
    {
        auto outtag = tag + ".processed";
        std::cout << "[merge] limit: "<< B2M(limit*sizeof(T)) << "Mb  ch: " << numFullChunks << " remain: " << remainSize << std::flush;
        std::ofstream out(outtag, std::ios::out | std::ios::binary);
        if(!out)  
            throw std::runtime_error("[splittedFile] can't create file " + outtag);
        while(!chunks.empty())
        {    
           T val = find();
           out.write(reinterpret_cast<char *>(&val),sizeof(T));
        }
        out.close();
    }

private:
    std::string tag;                // filename
    std::ifstream infile;           // file stream  
    size_t filesize = 0;            // file size     
    size_t capacity = 0;            // type aligned file size 
    size_t numFullChunks = 0;       // full chunks amount 
    size_t remainSize = 0;          // remain chunk size
    predicat_t predicat;            // split predicat lambda
    std::list<chunk<T> *> chunks;   // split chunks
    buff_t  data;                   // limited i/o memory buffer 

    void addChunk(size_t size = limit)
    {
        data.resize(size);
        infile.read(reinterpret_cast<char *>(&data[0]),size);
        std::sort(data.begin(),data.end(),predicat);
        chunks.push_back(new chunk<T>(data,size));
    }
   
    T find()  
    {
        auto it  = chunks.begin(); 
        auto val = (*it)->get();

        for(auto i = it; i != chunks.end(); i++)
        {
            auto cur = (*i)->get();
            if(!predicat(val,cur)) 
            {    
                val = cur; 
                it = i;
            }
        }
        if((*it)->pop())
        {
            delete (*it);
            chunks.erase(it);
        }   
        return val;
    }
 
};

#endif