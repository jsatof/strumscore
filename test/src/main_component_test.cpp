#include <gtest/gtest.h>

#include <components/main_component.h>

namespace Strumscore {

TEST(StrumscoreTestSuite, MainComponentTest) {
	MainComponent mc = {};
	ASSERT_TRUE(&mc);
}

}
