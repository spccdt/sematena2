#pragma once

#include <Namespaces.h>

SEMATENA_AVLIB_NAMESPACE_BEGIN 

public enum class PlayState { Playing, Stopped };

public ref struct AvLibStateEventArgs sealed
{
	property PlayState NewState;
};

public delegate void StateChangedHandler( Platform::Object^ sender, AvLibStateEventArgs^ args );

public interface class IAvLib
{
public:
	event StateChangedHandler^ StateChanged;

public:
	void OpenFile(Platform::String^ path);

	void Play();

	void Stop();
};

SEMATENA_AVLIB_NAMESPACE_END