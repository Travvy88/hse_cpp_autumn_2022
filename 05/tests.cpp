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

struct DataOneFieldBool
{
    bool a;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class deSerializer>
    Error deserialize(deSerializer& deserializer)
    {
        return deserializer(a);
    }
};

struct DataOneFieldInt
{
    uint64_t a;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class deSerializer>
    Error deserialize(deSerializer& deserializer)
    {
        return deserializer(a);
    }
};

struct DataBool
{
    bool a;
    bool b;
    bool c;
    bool d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }

    template <class deSerializer>
    Error deserialize(deSerializer& deserializer)
    {
        return deserializer(a, b, c, d);
    }
};

struct DataInt
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d);
    }

    template <class deSerializer>
    Error deserialize(deSerializer& deserializer)
    {
        return deserializer(a, b, c, d);
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
    Data x { 18446744073709551615, true, 2 }; // 18446744073709551615 is max uint64

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataWrong y { false, false, false };

    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}

TEST(TestUtils, test_stoull_int64_t)
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

TEST(TestUtils, one_field_int)
{
    DataOneFieldInt x { 1};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneFieldInt y { 1};

    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(x.a, y.a);
}

TEST(TestUtils, one_field_bool)
{
    DataOneFieldInt x { true};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataOneFieldInt y { true};

    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(x.a, y.a);
}

TEST(TestUtils, weird_bool)
{
    DataBool x {true, false, 1, 0 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    DataBool y { false, false, false, false };

    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
    ASSERT_EQ(x.d, y.d);
}

TEST(TestUtils, weird_string)
{
    std::stringstream stream;
    stream << "42str " << "1false " << "false1" << "truefalse";
    DataBool y { false, false, false, false };
    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);
    ASSERT_EQ(err, Error::CorruptedArchive);
}


TEST(TestUtils, too_big_int)
{
    std::stringstream stream;
    stream << "18446744073709551616";
    DataOneFieldInt y { 0 };
    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);
    ASSERT_EQ(err, Error::CorruptedArchive);
}

TEST(TestUtils, zero_one_int)
{
    std::stringstream stream;
    stream << "0 " << "1 " << "1";
    Data y { 0, 0, 0 };
    deSerializer deserializer(stream);
    const Error err = deserializer.load(y);
    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(y.a, 0);
    ASSERT_EQ(y.b, true);
    ASSERT_EQ(y.c, 1);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

