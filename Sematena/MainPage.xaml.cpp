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
using namespace Windows::ApplicationModel::Resources;

MainPage::MainPage()
{
	InitializeComponent();

	_loadedEventRegToken = Loaded += ref new RoutedEventHandler( this, &MainPage::OnLoaded );
	_unloadedEventRegToken = Unloaded += ref new RoutedEventHandler( this, &MainPage::OnUnloaded );

	_avLib = ref new MEAvLib( MediaPlayer );

	_playerViewModel = ref new PlayerViewModel(this, _avLib);
	_playerViewModelPropChangedEventRegToken = 
		_playerViewModel->PropertyChanged += ref new PropertyChangedEventHandler( this, &MainPage::OnPlayerViewModelPropChanged );
	DataContext = _playerViewModel;

	setupResources();
}

MainPage::~MainPage()
{
	_playerViewModel->PropertyChanged -= _playerViewModelPropChangedEventRegToken;

	Loaded -= _loadedEventRegToken;
	Unloaded -= _unloadedEventRegToken;
}

// Hook the binding update system to apply conditional styling. This is an 
// acceptable hack for now since XAML/WPF on WinRT doesn't yet support 
// triggers... and because the VST is overkill for what we need here.
void MainPage::OnPlayerViewModelPropChanged( Object^ sender, PropertyChangedEventArgs^ args )
{
	if ( args->PropertyName == "Playing" )
	{
		if ( _playerViewModel->Playing )
		{
			playButton->Content = _resourceLoader->GetString( L"PauseText" );
		}
		else
		{
			playButton->Content = _resourceLoader->GetString( L"PlayText" );
		}
	}
}

void MainPage::setupResources()
{
	_resourceLoader = ref new ResourceLoader();
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

void Sematena::MainPage::playButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
