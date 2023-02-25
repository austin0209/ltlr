#pragma once
#include <stddef.h>
#include <stdint.h>

#define METADATA_TYPE uint32_t

typedef size_t usize;
typedef uint32_t u32;

typedef struct
{
	// The heap contains the metadata for the allocator as well as the actual pages.
	// Each metadata entry contains the generational index of the page, and a flag to signify if the
	// page is free. If N is the # of bits in METADATA_TYPE, the first N-1 higher order bits are the
	// generational index (read as an unsigned integer), and the last bit is the flag.
	void* heap;
	u32 numPages;
	u32 pageSize;
} PageAllocator;

// TODO: are generational indices necessary? We can easily return void* instead of using
// PageAllocatorIDs.
typedef struct
{
	u32 pageIndex;
	METADATA_TYPE generation;
} PageAllocatorID;

PageAllocator PageAllocatorNew(u32 numPages, u32 pageSize);
void* PageAllocatorGet(PageAllocator* self, PageAllocatorID id);
PageAllocatorID PageAllocatorWrite(PageAllocator* self, void* src, usize bytes);
void PageAllocatorEvict(PageAllocator* self, PageAllocatorID id);
