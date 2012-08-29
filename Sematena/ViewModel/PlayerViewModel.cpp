#include "pch.h"
#include "XamlExtensions\DelegateCommand.h"

#include "PlayerViewModel.h"

using namespace Sematena::ViewModel;
using namespace Sematena::XamlExtensions;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Controls;

PlayerViewModel::PlayerViewModel( ::Control^ view )
	: _view( view )
{
	VisualStateManager::GoToState( view, "Stopped", false );
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
	OutputDebugString( L"Play toggled\r\n" );
}