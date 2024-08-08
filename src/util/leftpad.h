#pragma once

#include <cstring>
#include <string>

namespace Strumscore {
namespace Util {

// TODO: Maybe consider using an external dependency for this
inline std::string leftPad(const std::string &s, size_t spaces) {
	auto new_string = std::string(s.size() + spaces, ' ');
	std::memcpy(new_string.data() + spaces, s.data(), s.size());
	return new_string;
}

}
}
