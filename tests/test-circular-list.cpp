/* Platon Lukyanov st128133@student.spbu.ru
 * Problem 7
 */
#include "CircularList.h"
#include "gtest/gtest.h"

TEST(CircularList, test_constructor) {
    CircularList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CircularList, test_push_back) {
    CircularList<int> list;
    list.push_back(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    list.push_back(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(CircularList, test_push_front) {
    CircularList<int> list;
    list.push_front(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    list.push_front(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 1);
    list.push_front(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
}

TEST(CircularList, test_pop_back) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    list.pop_back();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CircularList, test_pop_front) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);
    list.pop_front();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CircularList, test_clear) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CircularList, test_swap) {
    CircularList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    CircularList<int> list2;
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
    list1.swap(list2);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_FALSE(list1.empty());
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list1.back(), 6);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_FALSE(list2.empty());
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 3);
}

TEST(CircularList, test_assign) {
    CircularList<int> list;
    list.assign(3, 1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    list.assign(2, 2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST(CircularList, test_insert) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.insert(list.begin(), 4);
    EXPECT_EQ(list.size(), 4);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 4);
    EXPECT_EQ(list.back(), 3);
    list.insert(list.end(), 5);
    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 4);
    EXPECT_EQ(list.back(), 5);
}

TEST(CircularList, test_erase) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    list.erase(list.begin());
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
    list.erase(list.begin());
    list.erase(list.begin());
    EXPECT_THROW(list.erase(list.begin()), std::out_of_range);
    EXPECT_THROW(list.front(), std::out_of_range);
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(CircularList, test_iterator) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    auto iter = list.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
}

TEST(CircularList, test_copy_constructor) {
    CircularList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    try {
        CircularList<int> list2(list1);
        EXPECT_EQ(list2.size(), 3);
        EXPECT_EQ(list2.front(), 1);
        EXPECT_EQ(list2.back(), 3);
        EXPECT_TRUE(list1 == list2);
    } catch (const std::exception& e) {
        FAIL() << "Exception during copy: " << e.what();
    }
}

TEST(CircularList, test_move_constructor) {
    CircularList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    CircularList<int> list2(std::move(list1));
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
    EXPECT_TRUE(list1.empty());
}

TEST(CircularList, test_copy_assignment) {
    CircularList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    CircularList<int> list2;
    list2 = list1;
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
    EXPECT_TRUE(list1 == list2);
}

TEST(CircularList, test_move_assignment) {
    CircularList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    CircularList<int> list2;
    list2 = std::move(list1);
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
    EXPECT_TRUE(list1.empty());
}

TEST(CircularList, test_comparison_operators) {
    CircularList<int> a, b, c;
    a.push_back(1); a.push_back(2);
    b.push_back(1); b.push_back(2);
    c.push_back(2); c.push_back(3);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a >= b);
}

TEST(CircularList, test_const_iterator) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    const CircularList<int>& clist = list;
    auto it = clist.cbegin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(CircularList, test_reverse_iterator) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    auto rit = list.rbegin();
    EXPECT_EQ(*rit, 3);
    ++rit;
    EXPECT_EQ(*rit, 2);
    ++rit;
    EXPECT_EQ(*rit, 1);
}

TEST(CircularList, test_const_reverse_iterator) {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    const CircularList<int>& clist = list;
    auto rit = clist.crbegin();
    EXPECT_EQ(*rit, 3);
    ++rit;
    EXPECT_EQ(*rit, 2);
    ++rit;
    EXPECT_EQ(*rit, 1);
}

TEST(CircularList, test_iterators_on_empty) {
    CircularList<int> list;
    EXPECT_TRUE(list.begin() == list.end());
    EXPECT_TRUE(list.cbegin() == list.cend());
    EXPECT_TRUE(list.rbegin() == list.rend());
    EXPECT_TRUE(list.crbegin() == list.crend());
}
