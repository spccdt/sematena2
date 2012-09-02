#include "pch.h"
#include "MEAvLib.h"
#include <ppltasks.h>

using namespace Sematena::AvLib;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;

MEAvLib::MEAvLib( MediaElement^ mediaElement )
	: _mediaElement( mediaElement )
{
	_mediaOpenedEventRegToken = _mediaElement->MediaOpened += ref new RoutedEventHandler( this, &MEAvLib::OnMediaOpened );
	_mediaEndedEventRegToken = _mediaElement->MediaEnded += ref new RoutedEventHandler( this, &MEAvLib::OnMediaEnded );
	_mediaFailedEventRegToken = _mediaElement->MediaFailed += ref new ExceptionRoutedEventHandler( this, &MEAvLib::OnMediaFailed );
	_mediaStateChangedRegToken = _mediaElement->CurrentStateChanged += ref new RoutedEventHandler( this, &MEAvLib::OnMediaStateChanged );

	raiseStateChange( PlayState::Closed );
}

MEAvLib::~MEAvLib()
{
	_mediaElement->MediaOpened -= _mediaOpenedEventRegToken;
	_mediaElement->MediaEnded -= _mediaEndedEventRegToken;
	_mediaElement->MediaFailed -= _mediaFailedEventRegToken;
	_mediaElement->CurrentStateChanged -= _mediaStateChangedRegToken;
}

void MEAvLib::OnMediaOpened( Object^ sender, RoutedEventArgs^ args )
{
	MediaOpened( this, ref new RoutedEventArgs() );
}

void MEAvLib::OnMediaEnded( Object^ sender, RoutedEventArgs^ args )
{
	MediaEnded( this, ref new RoutedEventArgs() );
}

void MEAvLib::OnMediaFailed( Object^ sender, ExceptionRoutedEventArgs^ args )
{
	MediaFailed( this, ref new RoutedEventArgs() );

	raiseStateChange( PlayState::Error );
}

namespace
{
	PlayState translateMediaElementState( MediaElementState meState )
	{
		switch( meState )
		{
		case MediaElementState::Opening:
			return PlayState::Opening;
		case MediaElementState::Playing:
			return PlayState::Playing;
		case MediaElementState::Paused:
			return PlayState::Paused;
		case MediaElementState::Stopped:
			return PlayState::Stopped;
		default:
			return PlayState::Error;
		}
	}
}

void MEAvLib::OnMediaStateChanged( Object^ sender, RoutedEventArgs^ args )
{
	raiseStateChange( translateMediaElementState( _mediaElement->CurrentState ) );
}

TimeSpan MEAvLib::MediaDuration::get()
{
	return _mediaElement->NaturalDuration.TimeSpan;
}

TimeSpan MEAvLib::MediaPosition::get()
{
	return _mediaElement->Position;
}

void MEAvLib::MediaPosition::set( TimeSpan value )
{
	_mediaElement->Position = value;
}

void MEAvLib::OpenFile( StorageFile^ file )
{
	auto openOp = file->OpenAsync( FileAccessMode::Read );
	create_task( openOp ).then( [this, file]( task<IRandomAccessStream^> t )
	{
		try
		{
			auto stream = t.get();
			if ( stream )
			{
				_mediaElement->SetSource( stream, file->ContentType );
			}
		}
		catch ( ... )
		{

		}
	}, task_continuation_context::use_current() );
}

void MEAvLib::Play()
{
	_mediaElement->Play();
}

void MEAvLib::Pause()
{
	_mediaElement->Pause();
}

void MEAvLib::raiseStateChange( PlayState state )
{
	auto args = ref new MediaStateChangedEventArgs();
	args->NewState = state;
	MediaStateChanged( this, args );
}

void MEAvLib::Stop()
{
	_mediaElement->Stop();

	raiseStateChange( PlayState::Stopped );
}

void MEAvLib::Close()
{
	_mediaElement->Source = nullptr;
}