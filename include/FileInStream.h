#ifndef FILEINSTREAM_H
#define FILEINSTREAM_H
#include "JNIHelper.h"
#include "Exceptions.hpp"

typedef unsigned char byte;

class FileInStream
{
    public:
        FileInStream();
        FileInStream(jobject AlluxioInStream);
         ~FileInStream();
        AlluxioStatus read( ) ;
        AlluxioStatus read(char* b) ;
        AlluxioStatus read(char* b, int off, int len);
        void close();
    private:
        jobject inStream;
        JniHelper::LocalRefMapType localRefs;
};

#endif // FILEINSTREAM_H
