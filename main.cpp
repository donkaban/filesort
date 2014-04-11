#include "common.h"
#include "chunk.h"

#include <vector>
#include <array>
#include <cstdio>








// memory limit in bytes 

template <typename T, size_t limit> 
class ISort
{
public:
    ISort(const std::string & name) 
    {
        in.open(name,std::ios::in | std::ios::binary);
        out.open(name + ".sorted",std::ios::out | std::ios::binary);
        if(!in)  throw std::runtime_error("can't open file " + name);
        if(!out) throw std::runtime_error("can't create out file ");
        createChunkHolders();
        
        for(size_t i = 0; i < numChunks; i++)
        {   
            loadChunk(i);
            saveChunk(i);
        
        }   

    }
    virtual ~ISort()
    {
        in.close();
        for(auto &s : out_tmp)
        { 
            s->close();
            delete s;
        }
        out.close();    
        deleteChunkHolders();
    }

    //virtual void doIt() = 0;

private:    
    std::ifstream in;
    std::ofstream out;
    std::vector<std::ofstream *> out_tmp;
    std::vector<std::ifstream *> in_tmp;
    
    std::array<T,limit>  dataChunk;  
    size_t  numChunks = 0;

    void deleteChunkHolders()
    {
    }
    void createChunkHolders() 
    {
        in.seekg(0, std::ifstream::end);
        auto filesize = in.tellg(); 
        numChunks = (filesize % limit > 0) ? filesize / limit + 1 : filesize / limit;
        for(auto i = 0u; i < numChunks; i++)
        {   
            auto name = "temp."+std::to_string(i);
            auto out = new std::ofstream(name,std::ios::out | std::ios::binary);
            if(!*out) throw std::runtime_error("can't create temp file " +name );
            out_tmp.push_back(out);
        }   
    }

    void loadChunk(size_t num)
    {
        if(num > numChunks ) throw std::runtime_error("try load not exist chunk.");
        in.seekg(num * limit);
        in.read(reinterpret_cast<char *>(dataChunk.data()),limit);
    }

    void saveChunk(size_t num)
    {
        if(num > numChunks) throw std::runtime_error("try save not exist chunk.");
        out_tmp[num]->write(reinterpret_cast<char *>(dataChunk.data()), limit);
    }


};





int main()
{
    try
    {
        #ifdef UNIT_TEST
            std::cout << "chunk test [int32] : " << std::boolalpha << chunk<uint32_t,10000>::test() << std::endl;
            std::cout << "chunk test [int64] : " << std::boolalpha << chunk<uint64_t,10000>::test() << std::endl;


        #endif

//        std::cout << trace(createGarbageFile<int32_t>,"test.bin", 1000000) << " sec." << std::endl;
    
        //ISort<int32_t,40000> sort1("test.bin");

    }
    catch(const std::exception &e)
    {
        std::cout << "error! " << e.what() << std::endl;
    }

    return 0;
}
