#include <iostream>
#include <gtest/gtest.h>

#include "allocator.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestUtils, test_1)
{
    Allocator al;
    al.makeAllocator( 10 );
    // У нас есть 10 байт свободных,
    // 5 отдадим.
    {
        char *res = al.alloc( 5 );
        ASSERT_TRUE( res != nullptr );
    }

    // У нас есть 5 (10 - 5) байт свободных,
    // 5 отдадим.
    {
        char *res = al.alloc( 5 );
        ASSERT_TRUE( res != nullptr );
    }
	
    // У нас есть 0 (10 - 0 - 0) байт свободных,
    // nullptr отдадим.
    {
        char *res = al.alloc( 1 );
        ASSERT_EQ( res, nullptr );
    }

    al.reset();
    // 10 байт доступно, запросим 1.
    {
        char *res = al.alloc( 1 );

        ASSERT_TRUE( res != nullptr );
    }
}

TEST(TestUtils, test_2)
{
    Allocator al;
    al.makeAllocator( 10 );
	// создали аллокатор, проверим исходные поля
    ASSERT_TRUE( al.data == nullptr );
	ASSERT_EQ(al.offset, 0);
	
	// аллоцируем  память и проверим оффсет и указатель
	char *all_1 = al.alloc(5);
	ASSERT_EQ(al.offset, 5);
	ASSERT_TRUE( all_1 != nullptr );
	// пробуем аллоцировать больше положенного
	char *all_2 = al.alloc(50);
	ASSERT_EQ( all_2, nullptr );

	// Делаем новый аллокатор и снова пытаемся аллоцировать память
	al.makeAllocator(100);
	char *all_3 = al.alloc(50);
    ASSERT_EQ(al.offset, 50);
    ASSERT_TRUE( all_3 != nullptr );
	// проверим оффсет 
	char *all_4 = al.alloc(33);
    ASSERT_EQ( al.offset, 83 );
	// аллоцирем больше положенного
    char *all_5 = al.alloc(33);
    ASSERT_EQ( all_5, nullptr );
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
