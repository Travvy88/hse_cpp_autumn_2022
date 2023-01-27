#include <gtest/gtest.h>
#include "format.hpp"


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestUtils, test_format)
{
	std::string s = "zero {0} two {2} one {1}";
    auto text = format(s, 0, '1', "2");
	ASSERT_EQ(text, "zero 0 two 2 one 1" );
}


TEST(Exception, test_exceptions)
{
    std::string s1 = "zero {0 string";
	std::string s2 = "{0} {1} {2234}";
	std::string s3 = "string {string} string";
	EXPECT_THROW({
            auto text1 = format(s1, 0);
    }, Error);

	EXPECT_THROW({
            auto text2 = format(s2, 0, 0, 0, 0);
    }, Error);

	EXPECT_THROW({
           	auto text3 = format(s3, 0);
    }, Error);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

