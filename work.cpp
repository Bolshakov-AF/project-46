#include <iostream>
#include <fstream>
#include <string>
#include "work.h"
#include "create.h"
#include "sort.h"

void work(const std::string& filename)
{
	std::ifstream file(filename);

	if (file.good())
	{
		std::cout << filename << " allready exists." << std::endl;
	}
	else
	{
		std::cout << "Creating " << filename << "..." << std::endl;
		create(filename);
	}

	std::cout << "Sorting " << filename << "..." << std::endl;
	sort(filename);
	std::cout << filename << " sorted." << std::endl;
}
