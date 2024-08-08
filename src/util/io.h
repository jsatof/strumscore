#pragma once

#include <filesystem>
#include <juce_core/juce_core.h>

namespace fs = std::filesystem;

namespace Strumscore {
namespace Util {

inline juce::File convertToJuceFile(const fs::path &p) {
	return { p.string() };
}

}
}
