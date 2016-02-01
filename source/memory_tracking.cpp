/**
 * @file memory_tracking.cpp
 * Implements simple memory tracking for use in C++ applications. Define 
 * TRACK_MEMORY to enable during debug and unit testing, and undef for 
 * production.
 * Version 1.01
 * 
 * Copyright (c) Josh Carter <josh@multipart-mixed.com>, 2006
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the Josh Carter nor the names of other
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "memory_tracking.h"

#include <assert.h>


#ifdef TRACK_MEMORY
#include <map>
using namespace std;

size_t gAllocatedMemory = 0;
bool gTrackAllocation = false; /* IMPORTANT: set true when your app starts */
typedef map<void*,size_t> AllocationMap;
static AllocationMap gAllocationMapStandard;
static AllocationMap gAllocationMapArray;



/**
 * Allocates using a map to keep track of sizes.
 */
inline void* tracked_new(size_t size, AllocationMap &map) throw(bad_alloc)
{

	assert(size != 0);
    void* ptr = 0;

    if (gTrackAllocation)
    {
        gAllocatedMemory += size;
        ptr = malloc(size);

        gTrackAllocation = false;
        map[ptr] = size;
        gTrackAllocation = true;

        #ifdef PRINT_MEMORY_TRACKING
		char debstr[80];
        sprintf(debstr,"mem 0x%8.8lx: %8lu (+%ld)", (unsigned long) ptr, gAllocatedMemory, size);
		DebugPrint(debstr);
        #endif
    }
    else
    {
        ptr = malloc(size);
    }

    if (ptr == 0)
        throw bad_alloc();
    else
        return ptr;
}

/**
 * Deletes stuff allocated with tracked_new.
 */
inline void tracked_delete(void* ptr, AllocationMap &map) throw()
{

    if (gTrackAllocation)
    {
        size_t size = map[ptr];
//        assert(size != 0);
        gAllocatedMemory -= size;

        #ifdef PRINT_MEMORY_TRACKING
		char debstr[80];
        sprintf(debstr,"mem 0x%8.8lx: %8ld (-%ld)\n", (unsigned long) ptr, gAllocatedMemory, size);   
		DebugPrint(debstr);
        #endif

        gTrackAllocation = false;
        map.erase(ptr);
        gTrackAllocation = true;
		
    }

    free(ptr);
}

void* operator new(size_t size) throw(bad_alloc)
{
    return tracked_new(size, gAllocationMapStandard);
}

void* operator new[](size_t size) throw(bad_alloc)
{
    return tracked_new(size, gAllocationMapArray);
}

void operator delete(void* ptr) throw()
{
    tracked_delete(ptr, gAllocationMapStandard);
}

void operator delete[](void* ptr) throw()
{
    tracked_delete(ptr, gAllocationMapArray);
}

#endif /* TRACK_MEMORY */

