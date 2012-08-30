// AvLib.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "MEAvLib.h"

using namespace Sematena::AvLib;
using namespace Platform;

void MEAvLib::OpenFile( String^ path )
{

}

void MEAvLib::Play()
{
	// TODO

	raiseStateChange( PlayState::Playing );
}

void MEAvLib::raiseStateChange( PlayState state )
{
	auto args = ref new AvLibStateEventArgs();
	args->NewState = state;
	StateChanged( this, args );
}

void MEAvLib::Stop()
{
	// TODO

	raiseStateChange( PlayState::Stopped );
}