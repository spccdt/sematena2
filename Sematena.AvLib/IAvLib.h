#pragma once

#include <Namespaces.h>

SEMATENA_AVLIB_NAMESPACE_BEGIN 

public enum class PlayState { Closed, Opening, Playing, Paused, Stopped, Error };

public ref struct StateChangedEventArgs sealed
{
	property PlayState NewState;
};

public delegate void StateChangedHandler( Platform::Object^ sender, StateChangedEventArgs^ args );

public interface class IAvLib
{
public:
	event StateChangedHandler^ StateChanged;

public:
	void OpenFile(Windows::Storage::StorageFile^ file);

	void Play();

	void Pause();

	void Stop();

	void Close();
};

SEMATENA_AVLIB_NAMESPACE_END