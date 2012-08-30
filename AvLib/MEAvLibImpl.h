#pragma once

#include "Namespaces.h"

#include <memory>
#include <string>

SEMATENA_AVLIB_NAMESPACE_BEGIN

class IMediaElementAdapter;

class MEAvLibImpl
{
public:
	MEAvLibImpl( std::shared_ptr<IMediaElementAdapter> adapter )
		: _adapter( adapter ) {}

	void OpenFile( const std::string& path );

	void Play();

	void Stop();

private:
	std::shared_ptr<IMediaElementAdapter> _adapter;
};

SEMATENA_AVLIB_NAMESPACE_END