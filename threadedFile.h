// todo : TO DO IT! ONLY PLACEHOLDER.

#ifndef _FILESORT_THREADED_FILE_
#define _FILESORT_THREADED_FILE_

#include "splittedFile.h"
#include <thread>
#include <mutex>

template<typename T, size_t limit>
class threadedFile : public splittedFile<T,limit>
{
public:
	using predicat_t = std::function<bool(T,T)>; 
   
   	threadedFile(const std::string &tag,const std::string &outtag, const predicat_t &predicat) :
   		splittedFile<T, limit>(tag,outtag,predicat)
  	{}
  	virtual ~threadedFile()
  	{}

  	virtual void split() override
    {
    	splittedFile<T,limit>::split(); // fake
    }
    virtual void merge() override
    {
   		splittedFile<T,limit>::merge(); // fake
 
    }
private:
	std::thread sortWorker;
	std::thread fileWorker;
	static std::mutex locker;
};


#endif