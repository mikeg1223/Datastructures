#include <gtest/gtest.h>
#include <memory>

#include "linked_list.h"


TEST(LinkedListsTests, Constructors){
    std::shared_ptr<int> test_int_ptr = std::make_shared<int>(10);
    mgg::LinkedList<int> ll1, ll2(test_int_ptr);

    EXPECT_EQ(ll1.size(), 0);
    EXPECT_TRUE(ll2.contains(test_int_ptr));
}

TEST(LinkedListsTests, add){
    std::shared_ptr<int> test_int_ptr = std::make_shared<int>(0);
    mgg::LinkedList<int> ll1, ll2(test_int_ptr);

    ll1.add(test_int_ptr);
    EXPECT_EQ(ll1.size(), 1);
    EXPECT_TRUE(ll1.contains(test_int_ptr));

    std::shared_ptr<int> test_int_ptr2(1);
    ll2.add(test_int_ptr2);
    EXPECT_EQ(ll2.size(), 2);
    EXPECT_TRUE(ll2.contains(test_int_ptr2));
}

TEST(LinkedListsTests, remove){
    mgg::LinkedList<int> ll(std::make_shared<int>(0));

    ll.add(std::make_shared<int>(1));
    ll.add(std::make_shared<int>(2));
    ll.add(std::make_shared<int>(3));

    ll.remove(std::make_shared<int>(2));

    EXPECT_FALSE(ll.contains(std::make_shared<int>(2)));
    EXPECT_EQ(ll.size(), 3);

}