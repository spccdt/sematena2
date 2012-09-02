#pragma once

#include <Namespaces.h>

SEMATENA_AVLIB_NAMESPACE_BEGIN 

	public enum class PlayState { Closed, Opening, Playing, Paused, Stopped, Error };

public ref struct MediaStateChangedEventArgs sealed
{
	property PlayState NewState;
};

[Windows::Foundation::Metadata::WebHostHidden]
public delegate void MediaOpenedHandler( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );

[Windows::Foundation::Metadata::WebHostHidden]
public delegate void MediaEndedHandler( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );

[Windows::Foundation::Metadata::WebHostHidden]
public delegate void MediaFailedHandler( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );

[Windows::Foundation::Metadata::WebHostHidden]
public delegate void MediaStateChangedHandler( Platform::Object^ sender, MediaStateChangedEventArgs^ args );

[Windows::Foundation::Metadata::WebHostHidden]
public delegate void VolumeChangedHandler( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );

[Windows::Foundation::Metadata::WebHostHidden]
public interface class IAvLib
{
public:
	event MediaOpenedHandler^ MediaOpened;
	event MediaEndedHandler^ MediaEnded;
	event MediaFailedHandler^ MediaFailed;
	event MediaStateChangedHandler^ MediaStateChanged;

	event VolumeChangedHandler^ VolumeChanged;

public:
	property Windows::Foundation::TimeSpan MediaDuration
	{
		Windows::Foundation::TimeSpan get();
	}

	property Windows::Foundation::TimeSpan MediaPosition
	{
		Windows::Foundation::TimeSpan get();
		void set( Windows::Foundation::TimeSpan value );
	}

	property double PlaybackRate
	{
		double get();
		void set( double value );
	}

	property double Volume
	{
		double get();
		void set( double value );
	}

public:
	void OpenFile(Windows::Storage::StorageFile^ file);

	void Play();

	void Pause();

	void Stop();

	void Close();
};

SEMATENA_AVLIB_NAMESPACE_END