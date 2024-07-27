#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class MainComponent final : public juce::Component {
public:
    MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
	void populateLines(std::vector<juce::Line<float>> &line_list);

	std::vector<juce::Line<float>> lines;
	juce::MenuBarComponent menuBar;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
