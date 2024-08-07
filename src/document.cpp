#include <document.h>
#include <attributes.h>
#include <fmt/core.h>

namespace fs = std::filesystem;

namespace StrumScore {

Document::Document()
	: document_path(fs::temp_directory_path()/"strumscore.xml")
	, document()
	// xml elements
	, root("strumscoreRoot")
	, measure("measure")
	, first_note("note")
	, second_note("note")
{
	if (!fs::exists(document_path)) {
		initEmptyDocument();
	} else {
		fmt::print(stderr, "WARNING: {} already exists\n", document_path.string());
	}
}

void Document::initEmptyDocument() {
	/*
	   Document Structure
	   Essentially the document will contain a sequence of measures
	   Each measure will contain a sequence of notes and rests (adding up to satisfy time signature values)

	   Example structure:
	   <root "guitarStringCount"=6>
	     <measure "beatsPerMinute"=140 "timeSignature"="4/4" "comment"="custom message">
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

	root.setAttribute(Strumscore::Attributes::string_count_id, 6);

	measure.setAttribute(Strumscore::Attributes::bpm_id, 140);
	measure.setAttribute(Strumscore::Attributes::time_sig_id, "4/4");
	measure.setAttribute(Strumscore::Attributes::comment_id, "custom message");

	first_note.setAttribute(Strumscore::Attributes::duration_id, "quarter");
	first_note.setAttribute(Strumscore::Attributes::note_type_id, "played");
	first_note.setAttribute(Strumscore::Attributes::articulation_id, "fullBend");
	first_note.setAttribute(Strumscore::Attributes::guitar_string_id, 3);
	first_note.setAttribute(Strumscore::Attributes::fret_id, 4);
	measure.addChildElement(&first_note);

	second_note.setAttribute(Strumscore::Attributes::duration_id, "dottedEigth");
	second_note.setAttribute(Strumscore::Attributes::note_type_id, "played");
	second_note.setAttribute(Strumscore::Attributes::articulation_id, "vibrato");
	second_note.setAttribute(Strumscore::Attributes::guitar_string_id, 3);
	second_note.setAttribute(Strumscore::Attributes::fret_id, 6);
	measure.addChildElement(&second_note);

	root.addChildElement(&measure);

	root.writeTo(juce::File{ document_path.string() });
}

void Document::printState() {

}

}
