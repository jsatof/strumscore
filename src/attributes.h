#pragma once

#include <juce_core/juce_core.h>

namespace Strumscore {
namespace Attributes {

const auto string_count_id = juce::Identifier{ "guitarStringCount" };
const auto tempo_id = juce::Identifier{ "tempo" };
const auto time_sig_id = juce::Identifier{ "timeSignature" };
const auto comment_id = juce::Identifier{ "comment" };
const auto duration_id = juce::Identifier{ "duration" };
const auto note_type_id = juce::Identifier{ "type" };
const auto articulation_id = juce::Identifier{ "articulation" };
const auto guitar_string_id = juce::Identifier{ "guitarString" };
const auto fret_id = juce::Identifier{ "fret" };

}
}
