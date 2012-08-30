#include "MEAvLibImpl.h"
#include "Include/IMediaElementAdapter.h"

using namespace Sematena::AvLib;
using std::string;

void MEAvLibImpl::OpenFile( const string& path )
{
	// TODO
	//_adapter->OpenFile( path );
}

void MEAvLibImpl::Play()
{
	_adapter->Play();
}

void MEAvLibImpl::Stop()
{
	_adapter->Stop();
}