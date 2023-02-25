#include "page_allocator.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LTL example workflow with generational indices:
// - On call to SceneDefer, instead of passing a void* params, pass a PageAllocatorID params
// - Within SceneDefer, change SceneDeferParams object to store a PageAllocatorID instead of a void*
// - In each of the <EntityName>Builder functions, use the PageAllocatorID to get the actual
// address/void* of the page.
//   Pass this void* into the <EntityName>BuilderHelper function.
// - Above is slightly safer because we can verify the generational ID of the page, but is a little
// more complicated.
//   Not having generational indices keeps the current workflow the same except for replacing malloc
//   with our own PageAllocator methods.


static void PrintPageAllocatorID(PageAllocatorID id)
{
    printf("INDEX: %d, GENERATION: %d\n", id.pageIndex, id.generation);
}

PageAllocator PageAllocatorNew(u32 numPages, u32 pageSize)
{
	// Metadata will contain a METADATA_TYPE for every page.
	u32 metadataSize = sizeof(METADATA_TYPE) * numPages;

	return (PageAllocator) {
		.heap = calloc(1, metadataSize + pageSize * numPages),
		.numPages = numPages,
		.pageSize = pageSize,
	};
}

static PageAllocatorID Allocate(PageAllocator* self)
{
	u32 freeIndex = 0;
	METADATA_TYPE generation = 0;
	METADATA_TYPE* metadata = self->heap;

	for (usize i = 0; i < self->numPages; ++i)
	{
		METADATA_TYPE data = metadata[i];
		METADATA_TYPE flag = data & 1;

		if (flag == 0)
		{
			freeIndex = i;
			generation = data >> 1;
			metadata[i] = generation << 1;
			metadata[i] |= 1;
			break;
		}
	}

	return (PageAllocatorID) {
		.pageIndex = freeIndex,
		.generation = generation,
	};
}

void* PageAllocatorGet(PageAllocator* self, PageAllocatorID id)
{
	METADATA_TYPE* metadata = self->heap;
	METADATA_TYPE data = metadata[id.pageIndex];
	METADATA_TYPE generation = data >> 1;
	bool flag = data & 1;

	PrintPageAllocatorID(id);

	if (flag == 0 || generation != id.generation)
	{
		assert(false);
	}

	u32 metadataSize = sizeof(METADATA_TYPE) * self->numPages;
	return ((char*)self->heap) + metadataSize + (id.pageIndex * self->pageSize);
}

PageAllocatorID PageAllocatorWrite(PageAllocator* self, void* src, usize bytes)
{
	assert(bytes <= self->pageSize);

	PageAllocatorID id = Allocate(self);
	void* dest = PageAllocatorGet(self, id);
	memcpy(dest, src, bytes);

	return id;
}

void PageAllocatorEvict(PageAllocator* self, PageAllocatorID id)
{
	METADATA_TYPE* metadata = self->heap;
	METADATA_TYPE data = metadata[id.pageIndex];
	METADATA_TYPE generation = data >> 1;
	bool flag = data & 1;

	if (generation != id.generation || flag == 0)
	{
		assert(false);
	}

	METADATA_TYPE newMetadata = (generation + 1) << 1;
	metadata[id.pageIndex] = newMetadata;
}

static void VisualizeAllocator(PageAllocator* self)
{
	printf("[");
	METADATA_TYPE* metadata = self->heap;
	for (usize i = 0; i < self->numPages; ++i)
	{
		METADATA_TYPE flag = metadata[i] & 1;
		if (flag == 0)
		{
			printf("O");
		}
		else
		{
			printf("X");
		}
	}
	printf("]\n");
}
