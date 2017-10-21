#pragma once

#include <stdlib.h>
#include <cstddef>

#include "pointer.hpp"
#include "error.hpp"

#define ALLOC_DEBUG 1

class Allocator
{
public:
    Allocator(size_t size, void* start);
    virtual ~Allocator();

    virtual void* allocate(size_t size, u8 alignment = 4) = 0;

    virtual void deallocate(void* p) = 0;

    void* getStart() const;

    size_t getSize() const;

    size_t getUsedMemory() const;

    size_t getNumAllocations() const;

protected:
    void*         startPtr;
    size_t        allocSize;

    size_t        usedMem;
    size_t        numAllocs;

private:
    Allocator(const Allocator&); //Prevent copies because it might cause errors
    Allocator& operator=(const Allocator&);
};

namespace mem
{
    template <class T> T* New(Allocator& allocator)
    {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T;
    }

    template <class T> T* New(Allocator& allocator, const T& t)
    {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
    }

    template<class T> void Delete(Allocator& allocator, T& object)
    {
        object.~T();
        allocator.deallocate(&object);
    }

    template<class T> T* NewArray(Allocator& allocator, size_t length)
    {
        ASSERT(length != 0);

        u8 headerSize = sizeof(size_t)/sizeof(T);

        if(sizeof(size_t)%sizeof(T) > 0)
            headerSize += 1;

        // Allocate extra space to store array length in the bytes before the array
        T* p = ( (T*) allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T)) ) + headerSize;

        *( ((size_t*)p) - 1 ) = length;

        for(size_t i = 0; i < length; i++)
            new (&p[i]) T;

        return p;
    }

    template<class T> void DeleteArray(Allocator& allocator, T* array)
    {
        ASSERT(array != nullptr);

        size_t length = *( ((size_t*)array) - 1 );

        for(size_t i = 0; i < length; i++)
            array[i].~T();

        //Calculate how much extra memory was allocated to store the length before the array
        u8 headerSize = sizeof(size_t)/sizeof(T);

        if(sizeof(size_t)%sizeof(T) > 0)
            headerSize += 1;

        allocator.deallocate(array - headerSize);
    }
}

/// LinearAllocator
class LinearAllocator : public Allocator
{
public:
    LinearAllocator(size_t size, void* start);
    ~LinearAllocator();

    void* allocate(size_t size, u8 alignment) override;

    void deallocate(void* p) override;

    void clear();

private:
    void* marker;
};

/// StackAllocator
class StackAllocator : public Allocator
{
public:
    StackAllocator(size_t size, void* start);
    ~StackAllocator();

    void* allocate(size_t size, u8 alignment) override;

    void deallocate(void* p) override;

private:
    struct AllocationHeader
    {
        #if ALLOC_DEBUG
        void* prev_address;
        #endif
        u8 adjustment;
    };

    #if ALLOC_DEBUG
    void* prev_marker;
    #endif

    void*  marker;
};

/// FreeListAllocator
class FreeListAllocator : public Allocator
{
public:
    FreeListAllocator(size_t size, void* start);
    ~FreeListAllocator();

    void* allocate(size_t size, u8 alignment) override;

    void deallocate(void* p) override;

private:
    struct AllocationHeader
    {
        size_t size;
        u8     adjustment;
    };

    struct FreeBlock
    {
        size_t     size;
        FreeBlock* next;
    };

    FreeBlock* free_blocks;
};


/// PoolAllocator
class PoolAllocator : public Allocator
{
public:
    PoolAllocator(size_t objectSize, u8 objectAlignment, size_t size, void* mem);
    ~PoolAllocator();

    void* allocate(size_t size, u8 alignment) override;

    void deallocate(void* p) override;

private:
    size_t     objectSize;
    u8         objectAlignment;

    void**     freeList;
};


/// ProxyAllocator
class ProxyAllocator : public Allocator
{
public:
    ProxyAllocator(Allocator& allocator);
    ~ProxyAllocator();

    void* allocate(size_t size, u8 alignment) override;

    void deallocate(void* p) override;

private:
    Allocator& allocator;
};
