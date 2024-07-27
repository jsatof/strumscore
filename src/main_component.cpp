#include <main_component.h>

MainComponent::MainComponent() : string_count(6) {
    setSize(1200, 900);

	// TODO: add menu items to menuModel
    //const juce::MenuBarModel menuModel;
	//menuBar.setModel(menuModel);

	// TODO: style menubar
    addAndMakeVisible(menuBar);

    populateLines();
}

void MainComponent::appendWithStroke(juce::Line<float> a_line, float a_stroke) {
	lines.push_back({ a_line, a_stroke });
}

void MainComponent::populateLines() {
	const float margin = 48;

	juce::Rectangle<float> staff_border = { margin, margin, getWidth() - 2 * margin, 150 };

	lines.reserve(100);
	// bad potentially - this performs two copies and two destructions, but runs on load so eh?
	appendWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getTopRight() });
	appendWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getBottomLeft() });
	appendWithStroke(juce::Line<float>{ staff_border.getBottomLeft(), staff_border.getBottomRight() });
	appendWithStroke(juce::Line<float>{ staff_border.getTopRight(), staff_border.getBottomRight() });

	// big stroke on beginning of first measure in a chart, and one at the end
	appendWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getBottomLeft() }, 15.f);
	appendWithStroke(juce::Line<float>{ staff_border.getTopRight(), staff_border.getBottomRight() }, 15.f);

	for (int i = 1; i < string_count; ++i) {
		float sub_line_y = (staff_border.getHeight() / string_count) * i + staff_border.getY();
		appendWithStroke(juce::Line<float>{ staff_border.getX(), sub_line_y, staff_border.getRight(), sub_line_y });
	}
}

void MainComponent::paint(juce::Graphics& g) {
	g.fillAll(juce::Colours::black);
	g.setColour(juce::Colours::white);

	for (auto &line_pair : lines) {
		auto [line, stroke] = line_pair;
		g.drawLine(line, stroke);
	}
}

void MainComponent::resized() {
	menuBar.setBounds(0, 0, getWidth(), 24);

}
