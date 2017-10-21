#include "allocator.h" 

Allocator::Allocator(size_t size, void* start)
{
  StartParticle = start;
  AllocateSize  = size;
  
  UsedMemory = 0;
}

Allocator::~Allocator()
{
  ASSERT(NumAllocs == 0 && UsedMemory == 0);
 
}

LinearAllocator::LinearAllocator(size_t size, void* start)
    : Allocator(size, start), marker(start)
{
    ASSERT(size > 0);
}

LinearAllocator::~LinearAllocator()
{
    marker   = nullptr;
}

void* LinearAllocator::allocate(size_t size, u8 alignment)
{
    ASSERT(size != 0);

    u8 adjustment =  pointer::alignForwardAdjustment(marker, alignment);

    if(usedMem + adjustment + size > allocSize)
        return nullptr;

    u8* aligned_address = (u8*)marker + adjustment;

    marker = (void*)(aligned_address + size);

    usedMem += size + adjustment;
    numAllocs++;

    return (void*)aligned_address;
}

void LinearAllocator::deallocate(void* p)
{
    ASSERT( false && "Use clear() instead" );
}

void LinearAllocator::clear()
{
    numAllocs     = 0;
    usedMem       = 0;

    marker    = startPtr;
}

void* StackAllocator::allocate(size_t size, u8 alignment)
{
    ASSERT(size != 0);

    u8 adjustment = pointer::alignForwardAdjustmentWithHeader(marker, alignment, sizeof(AllocationHeader));

    if(usedMem + adjustment + size > allocSize)
        return nullptr;

    void* aligned_address = pointer::add(marker, adjustment);

    //Add Allocation Header
    AllocationHeader* header = (AllocationHeader*)(pointer::subtract(aligned_address, sizeof(AllocationHeader)));

    header->adjustment   = adjustment;

    #if ALLOC_DEBUG
    header->prev_address = prev_marker;

    prev_marker          = aligned_address;
    #endif

    marker = pointer::add(aligned_address, size);

    usedMem += size + adjustment;
    numAllocs++;

    return aligned_address;
}

void FreeListAllocator::deallocate(void* p)
{
    ASSERT(p != nullptr);

    AllocationHeader* header = (AllocationHeader*)pointer::subtract(p, sizeof(AllocationHeader));

    uptr   block_start = reinterpret_cast<uptr>(p) - header->adjustment;
    size_t block_size  = header->size;
    uptr   block_end   = block_start + block_size;

    FreeBlock* prev_free_block = nullptr;
    FreeBlock* free_block = free_blocks;

    while(free_block != nullptr)
    {
        if( (uptr) free_block >= block_end )
            break;

        prev_free_block = free_block;
        free_block = free_block->next;
    }

    if(prev_free_block == nullptr)
    {
        prev_free_block = (FreeBlock*) block_start;
        prev_free_block->size = block_size;
        prev_free_block->next = free_blocks;

        free_blocks = prev_free_block;
    } else if((uptr) prev_free_block + prev_free_block->size == block_start)
    {
        prev_free_block->size += block_size;
    } else
    {
        FreeBlock* temp = (FreeBlock*) block_start;
        temp->size = block_size;
        temp->next = prev_free_block->next;
        prev_free_block->next = temp;

        prev_free_block = temp;
    }

    if( free_block != nullptr && (uptr) free_block == block_end)
    {
        prev_free_block->size += free_block->size;
        prev_free_block->next = free_block->next;
    }

    numAllocs--;
    usedMem -= block_size;
}

ProxyAllocator::ProxyAllocator(Allocator& allocator)
    : Allocator(allocator.getSize(), allocator.getStart()), allocator(allocator)
{
}

ProxyAllocator::~ProxyAllocator()
{
}

void* ProxyAllocator::allocate(size_t size, u8 alignment)
{
    ASSERT(size != 0);
    numAllocs++;

    size_t mem = allocator.getUsedMemory();

    void* p = allocator.allocate(size, alignment);

    usedMem += allocator.getUsedMemory() - mem;

    return p;
}

void ProxyAllocator::deallocate(void* p)
{
    numAllocs--;

    size_t mem = allocator.getUsedMemory();

    allocator.deallocate(p);

    usedMem -= mem - allocator.getUsedMemory();
}
