#include "common.h"
#include "splittedFile.h"
#include "threadedFile.h"

using      DATA_TYPE = int32_t;                     // Storage data type  
const auto MEM_LIMIT = M2B(25);                     // memory limit for buffering
const auto LIMIT     = MEM_LIMIT/sizeof(DATA_TYPE); // type aligned limit size
const auto PREDICAT  = std::greater<DATA_TYPE>();   // sorting predicat

// O(N*log(N)) + filesize x2 

int main()
{
    try
    {
        trace(createFile<DATA_TYPE>,"test.bin", M2B(1024)/sizeof(DATA_TYPE) , next::random<DATA_TYPE>);

        splittedFile<DATA_TYPE, LIMIT * 1> limitX1("test.bin","test.result1",PREDICAT);
            trace([&]{limitX1.split();});
            trace([&]{limitX1.merge();});
        trace(checkFile<DATA_TYPE>,"test.result1",PREDICAT);    
    
        splittedFile<DATA_TYPE, LIMIT * 2> limitX2("test.bin","test.result2",PREDICAT);
            trace([&]{limitX2.split();});
            trace([&]{limitX2.merge();});
        trace(checkFile<DATA_TYPE>,"test.result2",PREDICAT);    
    
        splittedFile<DATA_TYPE, LIMIT * 4> limitX4("test.bin","test.result3",PREDICAT);
            trace([&]{limitX4.split();});
            trace([&]{limitX4.merge();});
        trace(checkFile<DATA_TYPE>,"test.result3",PREDICAT);    
    

        /*
        threadedFile<DATA_TYPE, LIMIT> multiSort("test.bin","test.result2",PREDICAT);
            trace([&]{multiSort.split();});
            trace([&]{multiSort.merge();});
        trace(checkFile<DATA_TYPE>,"test.result2",PREDICAT);    
        */
    

    }
    catch(const std::exception &e)
    {
        std::cout << "\nerror: " << e.what() << std::endl;
    }

    return 0;
}
