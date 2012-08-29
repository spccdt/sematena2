#pragma once

#include "Namespaces.h"

SEMATENA_VIEWMODEL_NAMESPACE_BEGIN

	[Windows::UI::Xaml::Data::Bindable]
public ref class PlayerViewModel sealed
{
public:
	PlayerViewModel(Windows::UI::Xaml::Controls::Control^ view);
	virtual ~PlayerViewModel(void) {}

	property bool Playing;

	property Windows::UI::Xaml::Input::ICommand^ PlayCommand
	{
		Windows::UI::Xaml::Input::ICommand^ get();
	}

private:
	void TogglePlay( Platform::Object^ parameter );

private:
	Windows::UI::Xaml::Controls::Control^ _view;

	Windows::UI::Xaml::Input::ICommand^ _playCommand;
};

SEMATENA_VIEWMODEL_NAMESPACE_END