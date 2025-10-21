#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "linked_list.h"
#include "stack.h"

struct TestPair{
    std::unique_ptr<int> x;
    std::unique_ptr<int> y;
};

//======================================================
// |||          Singly Linked List Tests            |||             
//======================================================

TEST(LinkedListsTests, SingleConstructors){
    std::shared_ptr<int> test_int_ptr = std::make_shared<int>(10);
    mgg::LinkedList<int> ll1, ll2(test_int_ptr);

    EXPECT_EQ(ll1.size(), 0);
    EXPECT_EQ(ll2.size(), 1);    
    EXPECT_TRUE(ll2.contains(test_int_ptr));

    mgg::LinkedList<int> ll3(std::move(ll2));
    EXPECT_EQ(ll3.size(), 1);
    EXPECT_TRUE(ll3.contains(test_int_ptr));

    TestPair tp = {std::make_unique<int>(2), std::make_unique<int>(2)};
    std::shared_ptr<TestPair> tp_ptr = std::make_shared<TestPair>(std::move(tp));
    mgg::LinkedList<TestPair> tp_ll(tp_ptr);
    EXPECT_EQ(tp_ll.size(), 1);
    EXPECT_TRUE(tp_ll.contains(tp_ptr));
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

TEST(LinkedListsTest, SingleOperators){
    mgg::LinkedList<int> ll1;
    ll1.add(std::make_shared<int>(10));
    ll1.add(std::make_shared<int>(100));

    mgg::LinkedList<int> ll2 = std::move(ll1);
    EXPECT_EQ(ll2.size(), 2);
    EXPECT_TRUE(ll2.contains(std::make_shared<int>(100)));

    TestPair tp = {std::make_unique<int>(2), std::make_unique<int>(2)};
    TestPair tp2 = {std::make_unique<int>(-1), std::make_unique<int>(5)};
    std::shared_ptr<TestPair> tp_ptr = std::make_shared<TestPair>(std::move(tp));
    std::shared_ptr<TestPair> tp_ptr2 = std::make_shared<TestPair>(std::move(tp2));

    mgg::LinkedList<TestPair> tp_ll;
    tp_ll.add(tp_ptr);
    tp_ll.add(tp_ptr2);

    tp_ll2 = std::move(tp_ll);
    EXPECT_EQ(tp_ll2.size(), 2);
    EXPECT_TRUE(tp_ll2.contains(tp_ptr));
    EXPECT_TRUE(tp_ll2.contains(tp_ptr2));
}

//======================================================
// |||              Stack List Tests                |||             
//======================================================

TEST(StackTest, ConstructorsBasicType){
    mgg::Stack<int> stack;
    stack.push(10);
    mgg::Stack<int> other_stack(std::move(stack));
    EXPECT_EQ(other_stack.size(), 1);
    EXPECT_EQ(other_stack.storage(), 16);
}

TEST(StackTest, ConstructorsObjectType){
    mgg::Stack<TestPair> tp_stack;
    TestPair first = {std::make_unique<>(1), std::make_unique<>(1)};
    TestPair second = {std::make_unique<>(-1), std::make_unique<>(5)};
    tp_stack.push(first);
    tp_stack.push(second);
    mgg::Stack<TestPair> other_tp_stack = std::move(tp_stack);
    EXPECT_EQ(other_tp_stack.size(), 2);
    EXPECT_EQ(other_tp_stack.storage(), 16);
}

TEST(StackTest, OperationsBasicType){
    mgg::Stack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.storage(), 16);

    for(int i = 0; i < 18; ++i){
        stack.push(i);
        EXPECT_EQ(stack.top(), i);
        EXPECT_EQ(stack.size(), i+1);
        if (i >= 16){
            EXPECT_EQ(stack.storage(), 32);
        } else {
            EXPECT_EQ(stack.storage(), 16);
        }
    }

    for(int i = 17; i >= 0; --i){
        EXPECT_EQ(stack.top(), i);
        EXPECT_EQ(stack.size(), i+1);
        EXPECT_EQ(stack.storage(), 32);
        stack.pop();
    }
    EXPECT_EQ(stack.size(), 0);
    EXPECT_THROW({stack.top();}, std::out_of_range);
}

TEST(StackTest, OperationsObjectType){
    mgg::Stack<TestPair> stack;

    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.storage(), 16);

    for(int i = 0; i < 18; ++i){
        TestPair temp = {std::make_unique<>(i), std::make_unique<>(i)};
        stack.push(temp);
        EXPECT_EQ(stack.top(), i);
        EXPECT_EQ(stack.size(), i+1);
        if (i >= 16){
            EXPECT_EQ(stack.storage(), 32);
        } else {
            EXPECT_EQ(stack.storage(), 16);
        }
    }

    for(int i = 17; i >= 0; --i){
        EXPECT_EQ(stack.top(), i);
        EXPECT_EQ(stack.size(), i+1);
        EXPECT_EQ(stack.storage(), 32);
        stack.pop();
    }
    EXPECT_EQ(stack.size(), 0);
    EXPECT_THROW({stack.top();}, std::out_of_range);
}