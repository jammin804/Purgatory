#include "MemoryManager.h"

void* FreeMemoryBlock::Split(size_t SizeNeeded)
{
    if (SizeNeeded < BlockSize)
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
    for (FreeMemoryBlock& MemoryBlock : FreeSpaceBlocks)
    {
        if (MemoryBlock.BlockSize > SizeWanted)
        {
            return MemoryBlock.Split(SizeWanted);
        }
    }
    return nullptr;
}

void MemoryManager::Free(void* Location, size_t SizeReturned)
{
    FreeMemoryBlock BlockFreed;
    BlockFreed.BlockPosition = Location;
    BlockFreed.BlockSize = SizeReturned;

    bool bBlockCombined = false;
    for (FreeMemoryBlock& MemoryBlock : FreeSpaceBlocks)
    {
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