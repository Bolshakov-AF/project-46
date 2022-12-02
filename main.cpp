#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>
#include "files.h"
#include "work.h"

int main(int argc, char** args)
{
	srand(time(nullptr));

	try
	{
		if (argc > 1)
		{
			for (int i = 1; i < argc; ++i)
			{
				work(*(args + i));
			}
		}
		else
		{
			work(ARRAY);
		}
	}
	catch (std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}

