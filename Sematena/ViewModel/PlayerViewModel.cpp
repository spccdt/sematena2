#include "pch.h"
#include "PlayerViewModel.h"
#include "XamlExtensions\DelegateCommand.h"

#include <cmath>

using namespace Sematena::ViewModel;
using namespace Sematena::XamlExtensions;
using namespace Sematena::AvLib;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;

// the view is necessary to use the VSM :(
PlayerViewModel::PlayerViewModel( Control^ view, IAvLib^ avLib )
	: _view( view ),
	_avLib( avLib ),
	_minMediaDuration( 0. ),
	_maxMediaDuration( 1. ),
	_mediaStep( 1. ),
	_mediaPosition( 0. )
{
	//VisualStateManager::GoToState( view, "Stopped", false );

	_mediaOpenedEventRegToken = _avLib->MediaOpened += ref new MediaOpenedHandler( this, &PlayerViewModel::OnMediaOpened );
	_mediaEndedEventRegToken = _avLib->MediaEnded += ref new MediaEndedHandler( this, &PlayerViewModel::OnMediaEnded );
	_mediaFailedEventRegToken = _avLib->MediaFailed += ref new MediaFailedHandler( this, &PlayerViewModel::OnMediaFailed );
	_mediaStateChangedEventRegToken = _avLib->MediaStateChanged += ref new MediaStateChangedHandler( this, &PlayerViewModel::OnMediaStateChanged );
}
;
PlayerViewModel::~PlayerViewModel()
{
	_avLib->MediaOpened -= _mediaOpenedEventRegToken;
	_avLib->MediaEnded -= _mediaEndedEventRegToken;
	_avLib->MediaFailed -= _mediaFailedEventRegToken;
	_avLib->MediaStateChanged -= _mediaStateChangedEventRegToken;
}

void PlayerViewModel::SetPosition( double value )
{
	TimeSpan newPos;
	newPos.Duration = (int64)value * 10000000; // seconds -> 100-nanoseconds
	_avLib->MediaPosition = newPos;
}

namespace
{
	double calcSecondsInStep( double totalSeconds )
	{
		double secondsInStep = 1;

		double totalMinutes = std::ceil( totalSeconds / 60 );
		double totalHours = std::ceil( totalSeconds / 60 / 60 );

		if ( totalMinutes >= 10 && totalMinutes < 30 )
		{
			secondsInStep = 10;
		}
		else if ( totalMinutes >= 30 && totalMinutes < 60 )
		{
			secondsInStep = 30;
		}
		else if ( totalHours >= 1 )
		{
			secondsInStep = 60;
		}

		return secondsInStep;
	}
}

void PlayerViewModel::OnMediaOpened( Object^ sender, RoutedEventArgs^ args )
{
	double totalSeconds = std::ceil( _avLib->MediaDuration.Duration / 10000000 /* 100-nanoseconds -> seconds */ );
	MinMediaDuration = 0.;
	MaxMediaDuration = totalSeconds;
	MediaStep = calcSecondsInStep( totalSeconds );

	setupTimer( 1 /* second */ );
}

void PlayerViewModel::setupTimer( double intervalInSeconds )
{
	TimeSpan span;
	span.Duration = (int64)intervalInSeconds * 10000000; // seconds -> 100-nanoseconds
	_sliderUpdateTimer.Interval = span;
}

void PlayerViewModel::startTimer()
{
	_sliderUpdateTimerTickEventRegToken = 
		_sliderUpdateTimer.Tick += ref new EventHandler<Object^>( this, &PlayerViewModel::OnSliderUpdateTimerTick );
	_sliderUpdateTimer.Start();
}

void PlayerViewModel::stopTimer()
{
	_sliderUpdateTimer.Stop();
	_sliderUpdateTimer.Tick -= _sliderUpdateTimerTickEventRegToken;
}

void PlayerViewModel::OnSliderUpdateTimerTick( Object^ sender, Object^ args )
{
	if ( !UserChangingMediaPosition )
	{
		MediaPosition = (double)_avLib->MediaPosition.Duration / 10000000;
	}
}

void PlayerViewModel::OnMediaEnded( Object^ sender, RoutedEventArgs^ args )
{
	reset();
}

void PlayerViewModel::reset()
{
	if ( _sliderUpdateTimer.IsEnabled )
		stopTimer();

	MediaPosition = 0.;
}

void PlayerViewModel::OnMediaFailed( Object^ sender, RoutedEventArgs^ args )
{
	reset();

	// TODO: report error
}

void PlayerViewModel::OnMediaStateChanged( Object^ sender, MediaStateChangedEventArgs^ args )
{
	Playing = args->NewState == PlayState::Playing ? true : false;
	Ready = args->NewState != PlayState::Closed && args->NewState != PlayState::Error;

	if ( Playing )
	{
		startTimer();
	}
	else
	{
		stopTimer();
	}

	if ( args->NewState == PlayState::Stopped || 
		args->NewState == PlayState::Closed || 
		args->NewState == PlayState::Error )
	{
		reset();
	}
}

ICommand^ PlayerViewModel::PlayCommand::get()
{
	if ( _playCommand == nullptr )
	{
		_playCommand = ref new DelegateCommand( ref new ExecuteDelegate( this, &PlayerViewModel::togglePlay ), nullptr );
	}

	return _playCommand;
}

void PlayerViewModel::togglePlay( Object^ parameter )
{
	if ( Playing )
	{
		_avLib->Pause();
	}
	else
	{
		_avLib->Play();
	}
}
