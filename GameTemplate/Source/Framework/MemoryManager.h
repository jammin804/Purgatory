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

    static void* Allocate(size_t);
    static void  Free(void*, size_t SizeReturned);

private:
    //static const long long MemSizeBytes = 1073741274; // 1GB
    //static const long long MemSizeBytes = 536870912; // 512MB
    static const long long MemSizeBytes = 268435456; // 256MB
    //static const long long MemSizeBytes = 134217728; // 128MB
    static char Buffer[MemSizeBytes];
    static void * PointerToFreeSpace;
    static deque<FreeMemoryBlock> FreeSpaceBlocks;
};

static MemoryManager MemManager;

template <typename T>
class stl_allocator
{
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    stl_allocator() {}
    ~stl_allocator() {}

    template <class U> struct rebind { typedef stl_allocator<U> other; };
    template <class U> stl_allocator(const stl_allocator<U>&) {}

    pointer address(reference x) const { return &x; }
    const_pointer address(const_reference x) const { return &x; }
    size_type max_size() const throw() { return size_t(-1) / sizeof(value_type); }

    pointer allocate(size_type n)
    {
        return static_cast<pointer>(MemManager.Allocate(n));
    }

    void deallocate(pointer p, size_type n)
    {
        MemManager.Free(p, n);
    }

    void construct(pointer p, const T& val)
    {
        new(static_cast<void*>(p)) T(val);
    }

    void construct(pointer p)
    {
        new(static_cast<void*>(p)) T();
    }

    void destroy(pointer p)
    {
        p->~T();
    }
};

