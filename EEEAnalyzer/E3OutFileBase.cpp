#include "stdafx.h"
#include "E3OutFileBase.h"


E3OutFileBase::E3OutFileBase(void)
{
}


E3OutFileBase::~E3OutFileBase(void)
{
}

StatusCode E3OutFileBase::open(const char* path)
{
	std::ofstream::open(path);
	if (!is_open()) {
		// Return 1 on error.
		std::cout << "Could not open output file: " << path << std::endl;
		return FAILURE;
	}
	return SUCCESS;

}
