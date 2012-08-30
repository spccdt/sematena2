#pragma once

#include <Namespaces.h>

SEMATENA_AVLIB_NAMESPACE_BEGIN

class __declspec(novtable) IMediaElementAdapter
{
public:
	virtual void Play() = 0;
	virtual void Stop() = 0;
};

SEMATENA_AVLIB_NAMESPACE_END