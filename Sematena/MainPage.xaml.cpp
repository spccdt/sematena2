//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include <ppltasks.h>
#include "MainPage.xaml.h"

using namespace Sematena;
using namespace Sematena::ViewModel;
using namespace Sematena::AvLib;

using namespace Platform;
using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
	InitializeComponent();

	_loadedEventRegToken = Loaded += ref new RoutedEventHandler( this, &MainPage::OnLoaded );
	_unloadedEventRegToken = Unloaded += ref new RoutedEventHandler( this, &MainPage::OnUnloaded );

	_avLib = ref new MEAvLib( MediaPlayer );

	_playerViewModel = ref new PlayerViewModel(this, _avLib);
	DataContext = _playerViewModel;

	setupResources();
}

void MainPage::setupResources()
{
	auto resourceLoader = ref new Windows::ApplicationModel::Resources::ResourceLoader();
	
	auto playText = resourceLoader->GetString( L"PlayText" );
	playButton->Content = playText;

	// TODO: populate other control text here.
}

MainPage::~MainPage()
{
	Loaded -= _loadedEventRegToken;
	Unloaded -= _unloadedEventRegToken;
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	(void) sender;
	(void) e;

	// TODO
	auto musicLib = Windows::Storage::KnownFolders::MusicLibrary;
	create_task( musicLib->GetFileAsync( L"BBC\\48502_1745.wav" ) ).then( [this] ( task<StorageFile^> t )
	{
		try
		{
			auto file = t.get();
			if ( file )
			{
				_avLib->OpenFile( file );
			}
		}
		catch ( ... )
		{
			// temp
		}
	}, task_continuation_context::use_current() );
}

void MainPage::OnUnloaded(Object^ sender, RoutedEventArgs^ e)
{
	(void) sender;
	(void) e;

	_avLib->Close();
}

void MainPage::LoadState(Object^ navigationParameter, IMap<String^, Object^>^ pageState)
{
	(void) navigationParameter;
	(void) pageState;

}

void MainPage::SaveState(IMap<String^, Object^>^ pageState)
{
	(void) pageState;

	if ( _playerViewModel->Playing )
	{
		_avLib->Pause();
	}
}

void Sematena::MainPage::mediaSlider_PointerEntered_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	_playerViewModel->UserChangingMediaPosition = true;
}

void Sematena::MainPage::mediaSlider_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	_playerViewModel->UserChangingMediaPosition = false;
}

void Sematena::MainPage::mediaSlider_PointerCaptureLost_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	_playerViewModel->SetPosition( mediaSlider->Value );
	_playerViewModel->UserChangingMediaPosition = false;
}
