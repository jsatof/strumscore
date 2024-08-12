#include <components/menu_bar_model.h>

namespace Strumscore {

MenuBarModel::MenuBarModel() {

}

juce::StringArray MenuBarModel::getMenuBarNames() {
	return {};
}

juce::PopupMenu MenuBarModel::getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName) {
	juce::ignoreUnused(topLevelMenuIndex, menuName);
	return {};
}

void MenuBarModel::menuItemSelected(int menuItemId, int topLevelMenuIndex) {
	juce::ignoreUnused(menuItemId, topLevelMenuIndex);
}

}
