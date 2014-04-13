#include "common.h"
#include "chunk.h"
#include "splittedFile.h"

using      DATA_TYPE = int32_t;                     // Storage data type  
const auto MEM_LIMIT = M2B(10);                     // memory limit for buffering
const auto LIMIT     = MEM_LIMIT/sizeof(DATA_TYPE); // type aligned limit size
const auto PREDICAT  = std::greater<DATA_TYPE>();   // sorting predicat

// RAM : stl sort -> O(N*log(N))

int main()
{
    try
    {
        trace(createFile<DATA_TYPE>,"test.bin", LIMIT * 10 , next::random<DATA_TYPE>);

        splittedFile<DATA_TYPE, LIMIT> mergeSort("test.bin","test.result",PREDICAT);
            trace([&]{mergeSort.split();});
            trace([&]{mergeSort.merge();});
        trace(checkFile<DATA_TYPE>,"test.result",PREDICAT);    
    
    }
    catch(const std::exception &e)
    {
        std::cout << "\nerror: " << e.what() << std::endl;
    }

    return 0;
}
