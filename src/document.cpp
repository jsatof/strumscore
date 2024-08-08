#include <attributes.h>
#include <document.h>
#include <fmt/core.h>
#include <util/io.h>
#include <util/leftpad.h>

namespace fs = std::filesystem;

namespace Strumscore {

Document::Document()
	: document_path(fs::temp_directory_path()/"strumscore.xml")
{
	if (!fs::exists(document_path)) {
		fmt::print("STATUS: {} doesn't exist. Creating default document\n", document_path.string());
		initEmptyDocument();
	} else {
		fmt::print("STATUS: Found {}. Beginning to parse\n", document_path.string());
		root_element = std::move(juce::XmlDocument::parse(juce::File{ document_path.string() }));
		printState();
	}
}

// FIXME: on creation, there is an unwanted automatic destruction happening during destruction of this Document
// very much suspected that it comes from here
void Document::initEmptyDocument() {
	/*
	   Document Structure
	   Essentially the document will contain a sequence of measures
	   Each measure will contain a sequence of notes and rests (adding up to satisfy time signature values)

	   Example structure:
	   <root "guitarStringCount"=6>
	     <measure "tempo"=140 "timeSignature"="4/4" "comment"="custom message">
			<note "duration"="quarter" "type"="played" dynamics="" articulation="fullBend" "guitarString"=3 "fret"=4></note>
			<note "duration"="dottedEighth" "type"="played" dynamics="" articulation="vibrato" "guitarString"=3 "fret"=6></note>

			-- The rests at the end of a measure should be implicit
			-- But just showing what a rest element would look like:
			<note "duration"="half" "type"="rest"></note>
			<note "duration"="sixteenth" "type"="rest"></note>
	     </measure>
	   </root>

	   Note that a full measure in 4/4 - so a Quarter Note + Dotted Eight Note = 7 Sixteenth Notes.
	   The remaining 9 Sixteenth notes are added as rests
	*/
	// TODO: add metadata like document name, transcriber name, song credits, etc
	auto root = juce::XmlElement{ "strumscoreRoot" };
	auto measure = juce::XmlElement{ "measure" };
	auto first_note = juce::XmlElement{ "note" };
	auto second_note = juce::XmlElement{ "note" };

	root.setAttribute(Attributes::string_count_id, 6);

	measure.setAttribute(Attributes::tempo_id, 140);
	measure.setAttribute(Attributes::time_sig_id, "4/4");
	measure.setAttribute(Attributes::comment_id, "custom message");

	first_note.setAttribute(Attributes::duration_id, "quarter");
	first_note.setAttribute(Attributes::note_type_id, "played");
	first_note.setAttribute(Attributes::articulation_id, "fullBend");
	first_note.setAttribute(Attributes::guitar_string_id, 3);
	first_note.setAttribute(Attributes::fret_id, 4);
	measure.addChildElement(&first_note);

	second_note.setAttribute(Attributes::duration_id, "dottedEigth");
	second_note.setAttribute(Attributes::note_type_id, "played");
	second_note.setAttribute(Attributes::articulation_id, "vibrato");
	second_note.setAttribute(Attributes::guitar_string_id, 3);
	second_note.setAttribute(Attributes::fret_id, 6);
	measure.addChildElement(&second_note);

	root.addChildElement(&measure);

	auto out_file = juce::File{ document_path.string() };
	root.writeTo(out_file);
	root_element = std::move(juce::XmlDocument::parse(out_file));
}

void Document::printState() {
	using Util::leftPad;
	fmt::println("\nSTATUS: DOCUMENT STATE");
	juce::XmlElement doc_root = getRoot(); // using the getter for testing
	std::string root_string = fmt::format("strumscoreRoot [children: {}]", doc_root.getNumChildElements());
	fmt::print("{}\n", leftPad(root_string, 4));
	for (auto *element : doc_root.getChildIterator()) {
		if (element->hasTagName("measure")) {
			std::string measure_string = fmt::format("{} [children: {}]", element->getTagName().toStdString(), element->getNumChildElements());
			fmt::print("{}\n", leftPad(measure_string, 8));
			for (auto *note_element : doc_root.getChildByName("measure")->getChildIterator()) {
				if (note_element->hasTagName("note")) {
					std::string note_string = fmt::format("{}", note_element->getTagName().toStdString());
					fmt::print("{}\n", leftPad(note_string, 12));
				}
			}
		}
	}

	fmt::print("Tempo: {}\n", getTempo());
	auto [beat_count, beat_value] = getTimeSignature();
	fmt::print("Time Signature: {}/{}\n", beat_count, beat_value);
}

std::pair<int, int> Document::getTimeSignature() const {
	std::pair<int, int> time_sig = { 0, 0 };
	for (const auto* element : root_element->getChildIterator()) {
		if (element->hasTagName("measure")) {
			std::string time_sig_string = element->getStringAttribute("timeSignature").toStdString();
			time_sig.first = std::stoi(time_sig_string.substr(0, 1));
			time_sig.second = std::stoi(time_sig_string.substr(2, 3));
		}
	}
	return time_sig;
}

double Document::getTempo() const {
	double tempo = 0.0;
	juce::XmlElement *element = root_element->getChildByName("measure");
	if (element) {
		tempo = element->getIntAttribute("tempo");
	}
	return tempo;
}

juce::XmlElement &Document::getRoot() const {
	return *root_element;
}

void Document::changeFileName(const fs::path &new_path) {
	if (fs::exists(new_path)) {
		fmt::print(stderr, "ERROR: new document path {} already exists.\n", new_path.string());
		return;
	}

	root_element->writeTo(Util::convertToJuceFile(new_path));
	document_path = new_path;
}

}
