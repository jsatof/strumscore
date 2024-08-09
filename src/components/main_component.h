#pragma once

#ifndef JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
#endif

#include <juce_gui_extra/juce_gui_extra.h>
#include <filesystem>
#include <document.h>

class MainComponent final : public juce::Component {
public:
    MainComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
	void populateLines();
	void populateDrawables();
	std::unique_ptr<juce::Drawable> loadDrawable(const std::filesystem::path &p);
	void validateResourceDirectory();
	void appendLineWithStroke(juce::Line<float> a_line, float stroke = 0.5f);

	std::vector<std::pair<juce::Line<float>, float>> lines;
	std::vector<std::unique_ptr<juce::Drawable>> drawables;
	juce::MenuBarComponent menu_bar;

	int string_count;

	std::filesystem::path config_path;
	Strumscore::Document document;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
