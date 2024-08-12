#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <components/menu_bar_model.h>

namespace Strumscore {

class MenuBar : public juce::Component {
public:
	explicit MenuBar(int width);

    void paint(juce::Graphics &) override;
    void resized() override;

private:
	MenuBarModel menu_model;
	juce::MenuBarComponent menu_bar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuBar)
};

}
