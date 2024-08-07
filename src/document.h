#pragma once

#include <filesystem>
#include <juce_core/juce_core.h>
#include <memory>

// storing xml attributes and mangages document state

namespace StrumScore {

class Document {
public:
	Document();


private:
	void initEmptyDocument();
	void printState();
	void writeToFile(const juce::XmlElement &root);

	std::filesystem::path document_path;
	std::unique_ptr<juce::XmlDocument> document;

	// TODO: move these somewhere better
	juce::XmlElement root;
	juce::XmlElement measure;
	juce::XmlElement first_note;
	juce::XmlElement second_note;


	//JUCE_DECLARE_COPYABLE_WITH_LEAK_DETECTOR(TabDocument)
};

}
