#include <gtest/gtest.h>
#include "serializer.hpp"
#include "deserializer.hpp"


    struct Data
    {
        uint64_t a;
        bool b;
        uint64_t c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }

        template <class deSerializer>
        Error deserialize(deSerializer& deserializer)
        {
            return deserializer(a, b, c);
        }
    };

    struct DataWrong
    {
        bool a;
        bool b;
        bool c;

        template <class Serializer>
        Error serialize(Serializer& serializer)
        {
            return serializer(a, b, c);
        }

        template <class deSerializer>
        Error deserialize(deSerializer& deserializer)
        {
            return deserializer(a, b, c);
        }
    };





class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestUtils, test_true)
{
 	Data x { 1, true, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data y { 0, false, 0 };

	deSerializer deserializer(stream);
	const Error err = deserializer.load(y);

	ASSERT_EQ(err, Error::NoError);

	ASSERT_EQ(x.a, y.a);
	ASSERT_EQ(x.b, y.b);
	ASSERT_EQ(x.c, y.c);
}

TEST(TestUtils, test_wrong)
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataWrong y { false, false, false };

    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

