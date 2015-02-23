#include "stdafx.h"


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
		return StatusCode::FAILURE;
	}
	return StatusCode::SUCCESS;

}