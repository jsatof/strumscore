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

private:
	void initEmptyDocument();
	void printState();
	void writeToFile(const juce::XmlElement &root);

	std::filesystem::path document_path;
	std::unique_ptr<juce::XmlElement> document_root;


	//JUCE_DECLARE_COPYABLE_WITH_LEAK_DETECTOR(TabDocument)
};

}
