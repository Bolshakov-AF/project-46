#include <string>
#include "sort.h"
#include "fileArray.h"
#include "files.h"

const int MASK = 0x1;

void sort(FileArray&, size_t);

void sort(const std::string& filename)
{
	FileArray arr(filename, TRUNC);

	for (size_t shift = 0; shift < 8 * sizeof(int); ++shift)
	{
		sort(arr, shift);
	}

	arr.finalise();
}

void sort(FileArray& arr, size_t shift)
{
	FileArray zero(ZERO, OUT, true), one(ONE, OUT, true);

	arr.switchMode(IN);

	while (!arr.empty())
	{
		int item = arr.next();

		int compare = shift == 8 * sizeof(int) - 1 ? ~item : item;


		if ((compare >> shift) & MASK)
		{
			one.push(item);
		}
		else
		{
			zero.push(item);
		}
	}

	arr.switchMode(OUT);
	arr.add(zero);
	arr.add(one);
}
