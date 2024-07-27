#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class MainComponent final : public juce::Component {
public:
    MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
	void populateLines();
	void appendWithStroke(juce::Line<float> a_line, float stroke = 0.5f);

	std::vector<std::pair<juce::Line<float>, float>> lines;
	juce::MenuBarComponent menuBar;

	int string_count;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
