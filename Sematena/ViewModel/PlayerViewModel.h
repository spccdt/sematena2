#pragma once

#include "Common\BindableBase.h"
#include <Namespaces.h>

SEMATENA_VIEWMODEL_NAMESPACE_BEGIN

	[Windows::UI::Xaml::Data::Bindable]
[Windows::Foundation::Metadata::WebHostHidden]
public ref class PlayerViewModel sealed : public Sematena::Common::BindableBase
{
public:
	PlayerViewModel(Windows::UI::Xaml::Controls::Control^ view,
		Sematena::AvLib::IAvLib^ avLib );
	virtual ~PlayerViewModel();

	void SetPosition( double value );

public:
	property double MinMediaDuration
	{
		double get() { return _minMediaDuration; }
		void set(double value)
		{
			_minMediaDuration = value;
			OnPropertyChanged( "MinMediaDuration" );
		}
	}

	property double MaxMediaDuration
	{
		double get() { return _maxMediaDuration; }
		void set(double value)
		{
			_maxMediaDuration = value;
			OnPropertyChanged( "MaxMediaDuration" );
		}
	}

	property double MediaStep
	{
		double get() { return _mediaStep; }
		void set(double value)
		{
			_mediaStep = value;
			OnPropertyChanged( "MediaStep" );
		}
	}

	property double MediaPosition
	{
		double get() { return _mediaPosition; }
		void set(double value)
		{
			_mediaPosition = value;
			OnPropertyChanged( "MediaPosition" );
		}
	}

	property double PlaybackRate
	{
		double get() { return _playbackRate; }
		void set(double value)
		{
			_playbackRate = value;
			OnPropertyChanged( "PlaybackRate" );
		}
	}

	property double Volume
	{
		double get() { return _volume; }
		void set(double value)
		{
			_volume = value;
			OnPropertyChanged( "Volume" );
		}
	}

	property bool UserChangingMediaPosition;

	property bool Playing
	{
		bool get() { return _playing; }
		void set( bool value )
		{ 
			_playing = value;
			OnPropertyChanged( "Playing" );
		}
	}

	property bool Ready
	{
		bool get() { return _ready; }
		void set( bool value )
		{ 
			_ready = value;
			OnPropertyChanged( "Ready" );
		}
	}

public:
	property Windows::UI::Xaml::Input::ICommand^ PlayCommand
	{
		Windows::UI::Xaml::Input::ICommand^ get();
	}

	property Windows::UI::Xaml::Input::ICommand^ LeftCommand
	{
		Windows::UI::Xaml::Input::ICommand^ get();
	}

	property Windows::UI::Xaml::Input::ICommand^ RightCommand
	{
		Windows::UI::Xaml::Input::ICommand^ get();
	}

private:
	void togglePlay( Platform::Object^ parameter );
	void goLeft( Platform::Object^ parameter );
	void goRight( Platform::Object^ parameter );
	void setupTimer( double intervalInSeconds );
	void startTimer();
	void stopTimer();
	void reset();

private:
	void OnMediaOpened( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void OnMediaEnded( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void OnMediaFailed( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args );
	void OnMediaStateChanged( Platform::Object^ sender, Sematena::AvLib::MediaStateChangedEventArgs^ args );

	void OnSliderUpdateTimerTick( Platform::Object^ sender, Platform::Object^ args );

	Windows::Foundation::EventRegistrationToken _mediaOpenedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaEndedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaFailedEventRegToken;
	Windows::Foundation::EventRegistrationToken _mediaStateChangedEventRegToken;

	Windows::Foundation::EventRegistrationToken _sliderUpdateTimerTickEventRegToken;

	bool _playing;
	bool _ready;
	double _minMediaDuration;
	double _maxMediaDuration;
	double _mediaStep;
	double _mediaPosition;
	double _playbackRate;
	double _volume;

	Windows::UI::Xaml::DispatcherTimer _sliderUpdateTimer;

private:
	Sematena::AvLib::IAvLib^ _avLib;

	Windows::UI::Xaml::Controls::Control^ _view;

	Windows::UI::Xaml::Input::ICommand^ _playCommand;
	Windows::UI::Xaml::Input::ICommand^ _leftCommand;
	Windows::UI::Xaml::Input::ICommand^ _rightCommand;
};

SEMATENA_VIEWMODEL_NAMESPACE_END