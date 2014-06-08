#ifndef CONFORMANCE_TEST_MODULE
#define CONFORMANCE_TEST_MODULE

#include <Insanity.hpp>

class ConformanceTestMod : public virtual Insanity::IMod
{
public:
	virtual char const * GetValue() = 0;
};

#endif