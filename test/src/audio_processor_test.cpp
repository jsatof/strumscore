#include <filesystem>
#include <gtest/gtest.h>

//#ifndef JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
//#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
//#endif
#include <document.h>


namespace fs = std::filesystem;

namespace StrumscoreTest {

TEST(StrumscoreTestSuite, ChangeFileName) {
	Strumscore::Document doc = {};

	fs::path new_path = { fs::temp_directory_path()/"new_temp_strumscore_doc.xml" };
	fs::remove(new_path);

	juce::XmlElement old_root = doc.getRoot();
	juce::String old_root_name = old_root.getTagName();
	int old_children_count = old_root.getNumChildElements();

	doc.changeFileName(new_path);
	juce::XmlElement new_root = doc.getRoot();

	ASSERT_TRUE(old_root_name == new_root.getTagName());
	ASSERT_TRUE(old_children_count == new_root.getNumChildElements());
}

}
