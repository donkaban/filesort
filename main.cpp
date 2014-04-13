#include "common.h"
#include "chunk.h"
#include "splittedFile.h"

using      DATA_TYPE = int32_t;                     // Storage data type  
const auto MEM_LIMIT = M2B(10);                     // memory limit for buffering
const auto LIMIT     = MEM_LIMIT/sizeof(DATA_TYPE); // type aligned limit size

// RAM : stl sort -> O(N*log(N))

int main()
{
    try
    {
        trace(createFile<DATA_TYPE>,"test.bin", LIMIT * 50 , next::random<DATA_TYPE>);

        splittedFile<DATA_TYPE, LIMIT> mergeSort("test.bin",std::greater<DATA_TYPE>());
            trace([&]{mergeSort.split();});
            trace([&]{mergeSort.merge();});

    
    }
    catch(const std::exception &e)
    {
        std::cout << "\nerror: " << e.what() << std::endl;
    }

    return 0;
}
