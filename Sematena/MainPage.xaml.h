//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "Common\LayoutAwarePage.h" // Required by generated header
#include "MainPage.g.h"

// for [Bindable] types
#include "ViewModel\PlayerViewModel.h"

namespace Sematena
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	private:
		~MainPage();

	public:
		MainPage();

	protected:
		virtual void LoadState(Platform::Object^ navigationParameter,
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;
		virtual void SaveState(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState) override;

	private:
		void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnUnloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		Windows::Foundation::EventRegistrationToken _loadedEventRegToken;
		Windows::Foundation::EventRegistrationToken _unloadedEventRegToken;

	private:
		Sematena::AvLib::IAvLib^ _avLib;
		Sematena::ViewModel::PlayerViewModel^ _playerViewModel;
	};
}
