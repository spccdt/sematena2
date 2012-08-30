#pragma once

#include "IAvLib.h"

SEMATENA_AVLIB_NAMESPACE_BEGIN

public ref class MEAvLib sealed : public IAvLib
{
public:
	virtual event StateChangedHandler^ StateChanged;

public:
	virtual void OpenFile(Platform::String^ path);

	virtual void Play();

	virtual void Stop();

private:
	void raiseStateChange( PlayState state );

private:
	//shared_ptr<MEAvLibImpl> _impl;
};

SEMATENA_AVLIB_NAMESPACE_END