#include <gtest/gtest.h>
#include "matrix.cpp"


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestUtils, test_1)
{
	Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;
	ASSERT_EQ(m[0][0], 1);

	ASSERT_EQ( m.getRows(), 2);
    ASSERT_EQ( m.getCols(), 2);

	m *= 2;
	ASSERT_EQ( m[0][0], 2);
	ASSERT_EQ( m[0][1], 4);

	Matrix n(2, 2);
    n[0][0] = 3;
    n[0][1] = 3;
    n[1][0] = 3;
    n[1][1] = 3;
	auto x = n + m;	
    ASSERT_EQ( x[0][0], 5);
    ASSERT_EQ( x[0][1], 7);

	ASSERT_EQ(m==n, false);
	ASSERT_EQ(m==m, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
