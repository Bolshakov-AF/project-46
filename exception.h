#pragma once
#include <exception>

class EndOfFileException final : public std::exception
{
public:
	virtual const char* what()const noexcept override final;
};

