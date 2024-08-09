#pragma once

#include <filesystem>
#include <juce_core/juce_core.h>
#include <memory>

// storing xml attributes and mangages document state

namespace Strumscore {

class Document {
public:
	Document();

	std::pair<int, int> getTimeSignature() const;
	double getTempo() const;
	juce::XmlElement &getRoot() const;

	void changeFileName(const std::filesystem::path &new_path);

private:
	void initEmptyDocument();
	void printState();
	void writeToFile(const juce::XmlElement &root);

	std::filesystem::path document_path;
	std::unique_ptr<juce::XmlElement> root_element;

	//JUCE_DECLARE_COPYABLE_WITH_LEAK_DETECTOR(TabDocument)
};

}
