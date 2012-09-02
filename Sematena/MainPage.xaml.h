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

		void OnPlayerViewModelPropChanged( Platform::Object^ sender, Windows::UI::Xaml::Data::PropertyChangedEventArgs^ args );
		
		void mediaSlider_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void mediaSlider_PointerEntered_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void mediaSlider_PointerCaptureLost_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void playbackSlider_PointerEntered_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void playbackSlider_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void playbackSlider_PointerCaptureLost_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void volumeSlider_PointerEntered_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void volumeSlider_PointerExited_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void volumeSlider_PointerCaptureLost_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

	private:
		void setupResources();

	private:
		Windows::Foundation::EventRegistrationToken _loadedEventRegToken;
		Windows::Foundation::EventRegistrationToken _unloadedEventRegToken;

		Windows::Foundation::EventRegistrationToken _playerViewModelPropChangedEventRegToken;

	private:
		Sematena::AvLib::IAvLib^ _avLib;
		Sematena::ViewModel::PlayerViewModel^ _playerViewModel;

		Windows::ApplicationModel::Resources::ResourceLoader^ _resourceLoader;
	};
}
