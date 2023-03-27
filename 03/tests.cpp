#include <gtest/gtest.h>
#include "matrix.h"


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
    ASSERT_EQ(m[0][1], 2);
    ASSERT_EQ(m[1][0], 3);
    ASSERT_EQ(m[1][1], 4);

	ASSERT_EQ( m.getRows(), 2);
    ASSERT_EQ( m.getCols(), 2);

	m *= 2;
	ASSERT_EQ( m[0][0], 2);
	ASSERT_EQ( m[0][1], 4);
    ASSERT_EQ( m[1][0], 6);
    ASSERT_EQ( m[1][1], 8);

	Matrix n(2, 2);
    n[0][0] = 3;
    n[0][1] = 3;
    n[1][0] = 3;
    n[1][1] = 3;
	auto x = n + m;	
    ASSERT_EQ( x[0][0], 5);
    ASSERT_EQ( x[0][1], 7);
    ASSERT_EQ( x[1][0], 9);
    ASSERT_EQ( x[1][1], 11);

	ASSERT_EQ(m==n, false);
	ASSERT_EQ(m==m, true);

    n[0][0] -= 1;
    n[0][1] += 1;
    n[1][0] += 3;
    n[1][1] += 5;
    ASSERT_EQ(m==n, true);
}

TEST(TestUtils, out_of_range)
{
    Matrix m(2, 2);
    EXPECT_THROW({
         try
         {
             m[5][0] = 3;
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "Rows index out of range", e.what() );
             throw;
         }
     }, std::out_of_range );

    EXPECT_THROW({
         try
         {
             m[0][5] = 3;
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "Columns index out of range", e.what() );
             throw;
         }
     }, std::out_of_range );

    m[1][1] = 1;
    ASSERT_EQ(m[1][1], 1);
    EXPECT_THROW({
     try
     {
         m[-1][0];
     }
     catch( const std::out_of_range& e )
     {
         // and this tests that it has the correct message
         EXPECT_STREQ( "Rows index out of range", e.what() );
         throw;
     }
 }, std::out_of_range );

}

TEST(TestUtils, different_sizes)
{
    Matrix m(1, 1);
    m[0][0] = 300;
    ASSERT_EQ(m[0][0], 300);

    Matrix n(1, 3);
    n[0][0] = 0;
    n[0][1] = 1;
    n[0][2] = 2;
    ASSERT_EQ(n[0][0], 0);
    ASSERT_EQ(n[0][1], 1);
    ASSERT_EQ(n[0][2], 2);

    Matrix k(3, 1);
    k[0][0] = 0;
    k[1][0] = 1;
    k[2][0] = 2;
    ASSERT_EQ(k[0][0], 0);
    ASSERT_EQ(k[1][0], 1);
    ASSERT_EQ(k[2][0], 2);

    EXPECT_THROW({
         try
         {
             m[1][0];
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "Rows index out of range", e.what() );
             throw;
         }
     }, std::out_of_range );

    EXPECT_THROW({
         try
         {
             n[1][0];
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "Rows index out of range", e.what() );
             throw;
         }
     }, std::out_of_range );

    EXPECT_THROW({
         try
         {
             k[0][1];
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "Columns index out of range", e.what() );
             throw;
         }
     }, std::out_of_range );

}

TEST(TestUtils, different_sizes_addition){

    EXPECT_THROW({
         try
         {
             Matrix(2, 2) + Matrix(2, 4);
         }
         catch( const std::out_of_range& e )
         {
             // and this tests that it has the correct message
             EXPECT_STREQ( "matricies shapes are not equal", e.what() );
             throw;
         }
     }, std::out_of_range );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
