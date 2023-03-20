#include <gtest/gtest.h>
#include "parser.hpp"
#include <string>
#include <math.h>

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
	std::string test = "1 2 3 e3r love c++";

	auto digit_callback = [](uint64_t x){return x*2;};
	parser.SetDigitTokenCallback(digit_callback);
	auto output_2 = parser.Parse(test);
	ASSERT_EQ(output_2, " 2 4 6 e3r love c++ ");

	auto letter_callback = [](std::string s){return s.insert(0, "str_");};
    parser.SetLetterTokenCallback(letter_callback);
    auto output_3 = parser.Parse(test);
    ASSERT_EQ(output_3, " 2 4 6 str_e3r str_love str_c++ ");
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
    ASSERT_EQ(output_3, "1 2 3 e3r start_callback love c++ ");

}

TEST(TestUtils, test_3)
{
    TokenParser parser;
    auto letter_callback = [](std::string s){return s.insert(0, "str_");};
    auto digit_callback = [](uint64_t x){return x*2;};

    parser.SetLetterTokenCallback(letter_callback);


    std::string spaces = "    ";
    std::string empty = "";

    auto spaces_output = parser.Parse(spaces);
    ASSERT_EQ(spaces_output, "    ");

    auto empty_output = parser.Parse(empty);
    ASSERT_EQ(empty_output, "");

    parser.SetDigitTokenCallback(digit_callback);
    std::string one_char_tokens_letter = "a";
    auto one_char_tokens_letter_output = parser.Parse(one_char_tokens_letter);
    ASSERT_EQ(one_char_tokens_letter_output, " str_a ");

    std::string one_char_tokens_digit = "2";
    auto one_char_tokens_digit_output = parser.Parse(one_char_tokens_digit);
    ASSERT_EQ(one_char_tokens_digit_output, " 4 ");

    std::string multimodal_tokens = "42str str42 2str4 s24tr";
    auto multimodal_tokens_output = parser.Parse(multimodal_tokens);
    ASSERT_EQ(multimodal_tokens_output, " str_42str str_str42 str_2str4 str_s24tr ");

    auto digit_callback_ = [](uint64_t x){return x - 5;};
    parser.SetDigitTokenCallback(digit_callback_);

    std::string not_long = "18446744073709551615"; // 2**64 - 1
    auto not_long_output = parser.Parse(not_long);
    ASSERT_EQ(not_long_output, " 18446744073709551610 ");

    std::string too_long = "18446744073709551616"; // 2**64
    auto too_long_output = parser.Parse(too_long);
    ASSERT_EQ(too_long_output, " str_18446744073709551616 ");

    std::string very_long = "36893488147419103232"; // 2**65
    auto very_long_output = parser.Parse(very_long);
    ASSERT_EQ(very_long_output, " str_36893488147419103232 ");
}

TEST(TestUtils, all_nullptr)
{
    TokenParser parser;
    auto output = parser.Parse("abc efg");
    ASSERT_EQ(output, " abc efg ");
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
