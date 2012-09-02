#pragma once

#include "IAvLib.h"

SEMATENA_AVLIB_NAMESPACE_BEGIN

[Windows::Foundation::Metadata::WebHostHidden]
public ref class MEAvLib sealed : public [Windows::Foundation::Metadata::Default] IAvLib
{
private:
	~MEAvLib();

public:
	MEAvLib( Windows::UI::Xaml::Controls::MediaElement^ mediaElement );

public:
	virtual event MediaOpenedHandler^ MediaOpened;
	virtual event MediaEndedHandler^ MediaEnded;
	virtual event MediaFailedHandler^ MediaFailed;
	virtual event MediaStateChangedHandler^ MediaStateChanged;

	virtual event VolumeChangedHandler^ VolumeChanged;

public:
	virtual property Windows::Foundation::TimeSpan MediaDuration
	{
		Windows::Foundation::TimeSpan get();
	}

	virtual property Windows::Foundation::TimeSpan MediaPosition
	{
		Windows::Foundation::TimeSpan get();
		void set( Windows::Foundation::TimeSpan value );
	}
	
	virtual property double PlaybackRate
	{
		double get();
		void set( double value );
	}

	virtual property double Volume
	{
		double get();
		void set( double value );
	}

public:
	virtual void OpenFile(Windows::Storage::StorageFile^ file);

	virtual void Play();

	virtual void Pause();

	virtual void Stop();

	virtual void Close();

private:
	void raiseStateChange( PlayState state );

	void MEAvLib::OnMediaOpened( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void MEAvLib::OnMediaEnded( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void MEAvLib::OnMediaFailed( Platform::Object^ sender, Windows::UI::Xaml::ExceptionRoutedEventArgs^ args );
	void MEAvLib::OnMediaStateChanged( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void MEAvLib::OnVolumeChanged( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );

private:
	//shared_ptr<MEAvLibImpl> _impl;
	Windows::UI::Xaml::Controls::MediaElement^ _mediaElement; // TODO: move me to adapter

	Windows::Foundation::EventRegistrationToken _mediaOpenedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaEndedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaFailedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaStateChangedRegToken;
	Windows::Foundation::EventRegistrationToken _volumeChangedEventRegToken;
};

SEMATENA_AVLIB_NAMESPACE_END