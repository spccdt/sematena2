#pragma once

#include <IMediaElementAdapter.h>

using namespace Sematena::AvLib;

// TODO: Replace me with a mock.
class FakeMediaElementAdapter : public IMediaElementAdapter
{
public:
	FakeMediaElementAdapter() : 
		PlayCalled(false),
		StopCalled(false) {}

public:
	virtual void Play() override { PlayCalled = true; }
	virtual void Stop() override { StopCalled = true; }

public:
	bool PlayCalled;
	bool StopCalled;
};