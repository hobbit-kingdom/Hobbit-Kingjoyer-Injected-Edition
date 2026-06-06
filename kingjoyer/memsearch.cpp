#include <string.h>
#include <stdio.h>
#include <windows.h>

#include "memsearch.h"

void* memsearch(const void* pattern, size_t pattern_size)
{
	const size_t PAGE_SIZE = 4096;

	for (size_t page = 0; page < 0x100000000ull / PAGE_SIZE;) {
		MEMORY_BASIC_INFORMATION info;

		if (VirtualQuery(LPVOID(page * PAGE_SIZE), &info, PAGE_SIZE) == 0)
			return NULL;

		if (info.State != MEM_COMMIT) {
			page += info.RegionSize / PAGE_SIZE;
			continue;
		}

		if ((info.Protect & (PAGE_READWRITE)) == 0 || (info.Protect & (PAGE_GUARD)) != 0) {
			page += info.RegionSize / PAGE_SIZE;
			continue;
		}

		//printf("region = %p, size = %u\n", (const char *)(page * PAGE_SIZE), info.RegionSize);

		const char* ptr = (const char*)(page * PAGE_SIZE);
		size_t pos = 0;
		while (info.RegionSize - pos >= pattern_size) {
			if ((ptr + pos) != pattern && memcmp(ptr + pos, pattern, pattern_size) == 0)
				return (void*)(ptr + pos);
			pos++;
		}

		page += info.RegionSize / PAGE_SIZE;
	}

	return NULL;
}