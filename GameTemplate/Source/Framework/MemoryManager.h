#pragma once
#include <deque>

using namespace std;

struct FreeMemoryBlock
{
    void* BlockPosition;
    int BlockSize;
    void* Split(size_t);
    void CombineFromLeft(size_t);
};

class MemoryManager
{
public:
    MemoryManager();

    void* Allocate(size_t);
    void  Free(void*, size_t SizeReturned);

private:
    //static const long long MemSizeBytes = 1073741274; // 1GB
    //static const long long MemSizeBytes = 536870912; // 512MB
    static const long long MemSizeBytes = 268435456; // 256MB
    //static const long long MemSizeBytes = 134217728; // 128MB
    char Buffer[MemSizeBytes];
    void * PointerToFreeSpace;
    deque<FreeMemoryBlock> FreeSpaceBlocks;
};

