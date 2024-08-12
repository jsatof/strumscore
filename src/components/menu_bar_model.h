#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Strumscore {

class MenuBarModel : public juce::MenuBarModel {
public:
	MenuBarModel();

	juce::StringArray getMenuBarNames() override;
	juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName) override;
	void menuItemSelected(int menuItemId, int topLevelMenuIndex) override;

//private:
	
};

}
