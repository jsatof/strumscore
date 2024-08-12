#include <components/menu_bar.h>

namespace Strumscore {

MenuBar::MenuBar(int width)
	: menu_model()
	, menu_bar(&menu_model)
{
	setSize(width, 24);
}

void MenuBar::paint(juce::Graphics &) {
}

void MenuBar::resized() {
	menu_bar.setBounds(0, 0, getWidth(), getHeight());
}

}
