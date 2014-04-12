#include "common.h"
#include "chunk.h"

using        DATA_TYPE = int32_t;                       // Storage data type - signed int, 32 bit  
const size_t MEM_LIMIT = M2B(10);                       // 10Mb - memory limit for buffering
const size_t LIMIT     = MEM_LIMIT/sizeof(DATA_TYPE);   // type aligned limit size

int main()
{
    try
    {
        #ifdef UNIT_TEST
            std::cout << "chunk test : " << std::boolalpha << chunk<DATA_TYPE,100>::test() << std::endl;
          

        #endif

        trace(createFile<DATA_TYPE>,"test.bin", LIMIT * 30,next::random<DATA_TYPE>);
    
      

    }
    catch(const std::exception &e)
    {
        std::cout << "fatal error: " << e.what() << std::endl;
    }

    return 0;
}
