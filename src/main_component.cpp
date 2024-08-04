#include <main_component.h>

#include <fmt/core.h>

namespace fs = std::filesystem;

MainComponent::MainComponent()
	: string_count(6)
	, config_path(fs::temp_directory_path()/"strumscore_document.xml") // TODO: this document for testing, come up with more proper design
	, document(juce::File{juce::String{config_path.string()}}) // TODO: eww
{
    setSize(1200, 900);

	// TODO: add menu items to menuModel
    //const juce::MenuBarModel menuModel;
	//menuBar.setModel(menuModel);

	// TODO: style menubar
    addAndMakeVisible(menu_bar);

    validateDirectories();

    populateLines();
    populateDrawables();
}

void MainComponent::validateDirectories() {
	if (!fs::exists(config_path)) {
		fmt::print(stderr, "WARNING: config path doesnt exist. Creating new default config.\n");
	}

	fs::path resource_path = fs::current_path()/"res";
	if (!fs::exists(resource_path)) {
		fmt::print(stderr, "ERROR: Resource path not found. Make sure program launched from root project directory.\n");
		return;
	}

	std::vector<std::string> valid_resources = {
		"Music0.svg",
		"Music10.svg",
		"Music11.svg",
		"Music12.svg",
		"Music13.svg",
		"Music14.svg",
		"Music16.svg",
		"Music17.svg",
		"Music18.svg",
		"Music1.svg",
		"Music2.svg",
		"Music3.svg",
		"Music4.svg",
		"Music5.svg",
		"Music6.svg",
		"Music7.svg",
		"Music8.svg",
		"Music9.svg",
	};

	for (auto const &dir_entry : fs::directory_iterator{resource_path}) {
		auto found_iter = std::find(valid_resources.begin(), valid_resources.end(), dir_entry.path().filename().string());
		if (found_iter != valid_resources.end()) {
			valid_resources.erase(found_iter);
		}
	}

	for (auto const &s : valid_resources) {
		fmt::print(stderr, "ERROR: Could not find the resource: {}\n", s);
	}
}

void MainComponent::appendLineWithStroke(juce::Line<float> a_line, float a_stroke) {
	lines.push_back({ a_line, a_stroke });
}

void MainComponent::populateDrawables() {
	drawables.reserve(100); // TODO: tune this value

	fs::path res_path = fs::current_path()/"res";
	if (fs::exists(res_path)) {
		// TODO: detect time signatures in document
		std::unique_ptr<juce::Drawable> beat_count_time_sig = loadDrawable(res_path/"Music4.svg");
		std::unique_ptr<juce::Drawable> beat_length_time_sig = loadDrawable(res_path/"Music4.svg");

		drawables.emplace_back(std::move(beat_count_time_sig));
		drawables.emplace_back(std::move(beat_length_time_sig));

	} else {
		fmt::print(stderr, "ERROR: Cannot locate resource directory\n");
	}
}

std::unique_ptr<juce::Drawable> MainComponent::loadDrawable(const fs::path &p) {
	juce::File svg_file = { p.string() };
	std::unique_ptr<juce::XmlElement> parsed_svg = juce::XmlDocument::parse(svg_file);
	return juce::Drawable::createFromSVG(*parsed_svg);
}


void MainComponent::populateLines() {
	const float margin = 48;

	juce::Rectangle<float> staff_border = { margin, margin, getWidth() - 2 * margin, 150 };

	lines.reserve(100); // TODO: tune this value
	// bad potentially - this performs two copies and two destructions, but runs on load so eh?
	appendLineWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getTopRight() });
	appendLineWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getBottomLeft() });
	appendLineWithStroke(juce::Line<float>{ staff_border.getBottomLeft(), staff_border.getBottomRight() });
	appendLineWithStroke(juce::Line<float>{ staff_border.getTopRight(), staff_border.getBottomRight() });

	// big stroke on beginning of first measure in a chart, and one at the end
	appendLineWithStroke(juce::Line<float>{ staff_border.getTopLeft(), staff_border.getBottomLeft() }, 15.f);
	appendLineWithStroke(juce::Line<float>{ staff_border.getTopRight(), staff_border.getBottomRight() }, 15.f);

	for (int i = 1; i < string_count; ++i) {
		float sub_line_y = (staff_border.getHeight() / string_count) * i + staff_border.getY();
		appendLineWithStroke(juce::Line<float>{ staff_border.getX(), sub_line_y, staff_border.getRight(), sub_line_y });
	}
}

void MainComponent::paint(juce::Graphics& g) {
	g.fillAll(juce::Colours::lightgrey);
	g.setColour(juce::Colours::black);

	for (auto &line_pair : lines) {
		auto [line, stroke] = line_pair;
		g.drawLine(line, stroke);
	}

	drawables[0]->drawAt(g, 64, 60, 1.f);
	drawables[0]->drawAt(g, 64, 120, 1.f);
}

void MainComponent::resized() {
	menu_bar.setBounds(0, 0, getWidth(), 24);

}
