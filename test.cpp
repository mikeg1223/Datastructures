#include <gtest/gtest.h>
#include <memory>

#include "linked_list.h"


TEST(LinkedListsTests, SingleConstructors){
    std::shared_ptr<int> test_int_ptr = std::make_shared<int>(10);
    mgg::LinkedList<int> ll1, ll2(test_int_ptr);

    EXPECT_EQ(ll1.size(), 0);
    EXPECT_EQ(ll2.size(), 1);    
    EXPECT_TRUE(ll2.contains(test_int_ptr));

    mgg::LinkedList<int> ll3(std::move(ll2));
    EXPECT_EQ(ll3.size(), 1);
    EXPECT_TRUE(ll3.contains(test_int_ptr));
}

TEST(LinkedListsTests, SingleAdd){
    std::shared_ptr<int> test_int_ptr = std::make_shared<int>(0);
    mgg::LinkedList<int> ll1, ll2(test_int_ptr);

    ll1.add(test_int_ptr);
    EXPECT_EQ(ll1.size(), 1);
    EXPECT_TRUE(ll1.contains(test_int_ptr));

    std::shared_ptr<int> test_int_ptr2 = std::make_shared<int>(2);
    ll2.add(test_int_ptr2);
    EXPECT_EQ(ll2.size(), 2);
    EXPECT_TRUE(ll2.contains(test_int_ptr2));
}

TEST(LinkedListsTests, SingleRemove){
    mgg::LinkedList<int> ll(std::make_shared<int>(0));

    ll.add(std::make_shared<int>(1));
    ll.add(std::make_shared<int>(2));
    ll.add(std::make_shared<int>(3));

    ll.remove(std::make_shared<int>(2));

    EXPECT_FALSE(ll.contains(std::make_shared<int>(2)));
    EXPECT_EQ(ll.size(), 3);
}

TEST(LinkedListsTest, SingleSearch){
    mgg::LinkedList<int> ll(std::make_shared<int>(0));
    auto test_ptr = std::make_shared<int>(10);

    ll.add(std::make_shared<int>(1));
    ll.add(test_ptr);
    ll.add(std::make_shared<int>(100));
    ll.add(std::make_shared<int>(1000));
    EXPECT_EQ(ll.size(), 5);
    EXPECT_TRUE(ll.contains(test_ptr));

    auto searched =  ll.search(test_ptr);
    EXPECT_EQ(*searched, *test_ptr);

    ll.remove(test_ptr);
    searched = ll.search(test_ptr);
    EXPECT_FALSE(searched);

    mgg::LinkedList<int> emptyLL;
    searched = emptyLL.search(test_ptr);
    EXPECT_FALSE(searched);
    
}

TEST(LinkedListsTest, Operators){
    mgg::LinkedList<int> ll1;
    ll1.add(std::make_shared<int>(10));
    ll1.add(std::make_shared<int>(100));

    mgg::LinkedList<int> ll2 = std::move(ll1);
    EXPECT_EQ(ll2.size(), 2);
    EXPECT_TRUE(ll2.contains(std::make_shared<int>(100)));
}