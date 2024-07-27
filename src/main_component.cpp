#include <main_component.h>

MainComponent::MainComponent() {
    setSize(1200, 900);

	// TODO: add menu items to menuModel
    //const juce::MenuBarModel menuModel;
	//menuBar.setModel(menuModel);

	// TODO: style menubar
    addAndMakeVisible(menuBar);

	lines.reserve(100);
    populateLines(lines);
}

void MainComponent::populateLines(std::vector<juce::Line<float>> &line_list) {
	const float margin = 48;
	juce::Point<float> staff_dim = { getWidth() - 2 * margin, 150 };

	juce::Rectangle<float> staff_border = { margin, margin, staff_dim.getX(), staff_dim.getY() };

	line_list.push_back({ staff_border.getX(), staff_border.getY(), staff_border.getWidth(), staff_border.getY() });
	line_list.push_back({ staff_border.getX(), staff_border.getY(), staff_border.getX(), staff_border.getHeight() });
	line_list.push_back({ staff_border.getX(), staff_border.getHeight(), staff_border.getWidth(), staff_border.getHeight() });
	line_list.push_back({ staff_border.getWidth(), staff_border.getY(), staff_border.getWidth(), staff_border.getHeight() });

	for (int i = 1; i < 5; ++i) {
		float sub_line_y = (staff_border.getHeight() / 7) * i + staff_border.getY();
		line_list.push_back({ staff_border.getX(), sub_line_y, staff_border.getWidth(), sub_line_y });
	}
}

void MainComponent::paint(juce::Graphics& g) {
	g.fillAll(juce::Colours::black);
	g.setColour(juce::Colours::white);

	for (auto &line : lines) {
		g.drawLine(line, 0.5f);
	}

	// big assumption here
	const juce::Line<float> begin_line = lines.at(0);
	g.drawLine({ begin_line.getStart().getX(), begin_line.getStart().getY(), begin_line.getStart().getX(), begin_line.getEnd().getY() }, 5.f);
}

void MainComponent::resized() {
	menuBar.setBounds(0, 0, getWidth(), 24);

}
