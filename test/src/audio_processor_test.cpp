#include <filesystem>
#include <gtest/gtest.h>

#include <document.h>

namespace StrumscoreTest {

TEST(StrumscoreTestSuite, Foo) {
    ASSERT_TRUE(true);
}

TEST(StrumscoreTestSuite, ChangeFileName) {
	Strumscore::Document doc = {};

	fs::path new_path = { fs::temporary_directory()/"new_temp_strumscore_doc.xml" };
	fs::remove(new_path);

	juce::XmlElement old_root = doc.getRoot();

	doc.changeName(new_path);

	ASSERT_TRUE(old_root == doc.getRoot());
}

}
