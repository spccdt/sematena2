#include "pch.h"
#include "XamlExtensions\DelegateCommand.h"

#include "PlayerViewModel.h"

using namespace Sematena::ViewModel;
using namespace Sematena::XamlExtensions;
using namespace Sematena::AvLib;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;

// the view is necessary to use the VSM :(
PlayerViewModel::PlayerViewModel( Control^ view, IAvLib^ avLib )
	: _view( view ),
	_avLib( avLib )
{
	//VisualStateManager::GoToState( view, "Stopped", false );

	_avLib->StateChanged += ref new StateChangedHandler( this, &PlayerViewModel::OnStateChanged );
}

void PlayerViewModel::OnStateChanged( Object^ sender, StateChangedEventArgs^ args )
{
	Playing = args->NewState == PlayState::Playing ? true : false;
}

ICommand^ PlayerViewModel::PlayCommand::get()
{
	if ( _playCommand == nullptr )
	{
		_playCommand = ref new DelegateCommand( ref new ExecuteDelegate( this, &PlayerViewModel::TogglePlay ), nullptr );
	}

	return _playCommand;
}

void PlayerViewModel::TogglePlay( Object^ parameter )
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
