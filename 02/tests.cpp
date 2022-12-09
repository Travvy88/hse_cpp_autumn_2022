#include <gtest/gtest.h>
#include "parser.hpp"
#include <string>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestUtils, test_1)
{
	// test token callback, letter token callback and digit token callback
	TokenParser parser;
	auto callback =	[](std::string s){return s.insert(0, "2");};
	parser.SetCallback(callback);
	std::string test = "1 2 3 e3r love c++";
	std::string output_1 = parser.Parse(test);
	ASSERT_EQ(output_1, " 21 22 23 2e3r 2love 2c++ ");

	auto digit_callback = [](uint64_t x){return x*2;};
	parser.SetDigitTokenCallback(digit_callback);
	auto output_2 = parser.Parse(test);
	ASSERT_EQ(output_2, " 42 44 46 2e3r 2love 2c++ ");

	auto letter_callback = [](std::string s){return s.insert(0, "str_");};
    parser.SetLetterTokenCallback(letter_callback);
    auto output_3 = parser.Parse(test);
    ASSERT_EQ(output_3, " 42 44 46 str_2e3r str_2love str_2c++ ");

} 


TEST(TestUtils, test_2)
{
    // test start callback and end callback
    TokenParser parser;
    auto start_callback = [](std::string s){return s.insert(10, "start_callback ");};
    parser.SetStartCallback(start_callback);
    std::string test = "1 2 3 e3r love c++";
    std::string output_1 = parser.Parse(test);
    ASSERT_EQ(output_1, " 1 2 3 e3r start_callback love c++ ");

    auto end_callback = [](std::string s){return s.erase(0, 1);}; // delete first spcae in the output string
    parser.SetEndCallback(end_callback);
    auto output_3 = parser.Parse(test);
    ASSERT_EQ(output_3, "1 2 3 e3r start_callback love c++ "
);

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
