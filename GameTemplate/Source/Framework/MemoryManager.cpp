#include "MemoryManager.h"

#pragma optimize("", off)

char MemoryManager::Buffer[];
void* MemoryManager::PointerToFreeSpace = nullptr;
deque<FreeMemoryBlock> MemoryManager::FreeSpaceBlocks;

void* FreeMemoryBlock::Split(size_t SizeNeeded)
{
    if (SizeNeeded <= BlockSize)
    {
        void* MemoryReturned = BlockPosition;
        BlockSize -= SizeNeeded;
        BlockPosition = (char*)BlockPosition + SizeNeeded;
        return MemoryReturned;
    }
    return nullptr;
}

void FreeMemoryBlock::CombineFromLeft(size_t SizeReturned)
{
    BlockPosition = (char*)BlockPosition - SizeReturned;
    BlockSize += SizeReturned;
}

MemoryManager::MemoryManager()
{
    PointerToFreeSpace = & Buffer;
    FreeMemoryBlock StartingBlock;
    StartingBlock.BlockPosition = PointerToFreeSpace;
    StartingBlock.BlockSize = MemSizeBytes;
    FreeSpaceBlocks.push_front(StartingBlock);
}

void* MemoryManager::Allocate(size_t SizeWanted)
{
    for (auto iter = FreeSpaceBlocks.begin(); iter != FreeSpaceBlocks.end();)
    {
        FreeMemoryBlock& MemoryBlock = (*iter);
        if (MemoryBlock.BlockSize >= SizeWanted)
        {
            void* AvailableMemory = MemoryBlock.Split(SizeWanted);
            if (MemoryBlock.BlockSize == 0)
            {
                iter = FreeSpaceBlocks.erase(iter);
            }
            return AvailableMemory;
        }
        ++iter;
    }
    return nullptr;
}

void MemoryManager::Free(void* Location, size_t SizeReturned)
{
    FreeMemoryBlock BlockFreed;
    BlockFreed.BlockPosition = Location;
    BlockFreed.BlockSize = SizeReturned;

    bool bBlockCombined = false;
    for (int i = 0; i < FreeSpaceBlocks.size(); ++i)
    {
        FreeMemoryBlock& MemoryBlock = FreeSpaceBlocks[i];
        if (MemoryBlock.BlockPosition > BlockFreed.BlockPosition)
        {
            void* PointerToEndOfFreeMemoryBlock = (char*)BlockFreed.BlockPosition + SizeReturned;
            if (PointerToEndOfFreeMemoryBlock == MemoryBlock.BlockPosition)
            {
                MemoryBlock.CombineFromLeft(SizeReturned);
                bBlockCombined = true;
                break;
            }
        }
    }

    if (!bBlockCombined)
    {
        FreeSpaceBlocks.push_front(BlockFreed);
    }
}

#pragma optimize("", on)