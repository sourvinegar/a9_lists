#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "list/circularly_linked.hpp"
#include "list/double_linked.hpp"
#include "list/singly_linked.hpp"

TEST_CASE("Basic function tests for singly linked list")
{
    dsac::list::SinglyLinkedList<int> list;
    REQUIRE(list.empty() == true);
    list.push_back(5);
    list.push_back(4);
    list.push_back(3);
    REQUIRE(list.size() == 3);
    REQUIRE(list.front() == 5);
    REQUIRE(list.back() == 3);
    list.push_front(6);
    REQUIRE(list.front() == 6);
    REQUIRE(list.size() == 4);
    list.pop_front();
    REQUIRE(list.front() == 5);
    REQUIRE(list.size() == 3);
    int elem = 5;
    for(auto it = list.begin(); it != list.end(); it++)
    {
        REQUIRE(*it == elem);
        elem--;
    }
    auto itr = list.begin();
    itr++;
    list.insert_after(itr, 10);
    REQUIRE(list.size() == 4);
    dsac::list::SinglyLinkedList<int> another = list;
    dsac::list::SinglyLinkedList<int> more(another);
}

TEST_CASE("Special function tests for singly linked list"){
    dsac::list::SinglyLinkedList<int> list1;
    list1.push_back(5);
    list1.push_back(4);
    list1.push_back(3);
    dsac::list::SinglyLinkedList<int> list2;
    list2.push_back(2);
    list2.push_back(1);
    list2.push_back(0);
    list1.concatenate(list2);
    REQUIRE(list2.empty() == true);
    REQUIRE(list1.size() == 6);
}

TEST_CASE("Basic function tests for circularly linked list")
{
    dsac::list::CircularlyLinkedList<int> list;

    REQUIRE(list.empty() == true);
    list.push_back(5);
    list.push_back(4);
    list.push_back(3);
    REQUIRE(list.size() == 3);
    REQUIRE(list.front() == 5);
    REQUIRE(list.back() == 3);
    list.push_front(6);
    REQUIRE(list.front() == 6);
    REQUIRE(list.size() == 4);
    list.pop_front();
    REQUIRE(list.front() == 5);
    REQUIRE(list.size() == 3);
    list.rotate();
    REQUIRE(list.front() == 4);

}

TEST_CASE("Special function tests for circularly linked list")
{
    dsac::list::CircularlyLinkedList<int> source;
    dsac::list::CircularlyLinkedList<int> a;
    dsac::list::CircularlyLinkedList<int> b;
    a.push_back(120);
    b.push_back(140);
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    source.push_back(4);
    source.push_back(5);
    REQUIRE_THROWS_AS(source.split_even(a, b), std::invalid_argument);
    source.push_back(6);
    source.split_even(a,b);
    REQUIRE(source.empty() == true);
    REQUIRE(a.size() == 3);
    REQUIRE(b.size() == 3);
    REQUIRE(a.front() == 1);
    REQUIRE(a.back() == 3);
    REQUIRE(b.front() == 4);
    REQUIRE(b.back() == 6);

}

TEST_CASE("Basic function tests for doubly linked list")
{
    dsac::list::DoublyLinkedList<int> list;
    REQUIRE(list.empty() == true);
    list.push_back(5);
    list.push_back(4);
    list.push_back(3);
    REQUIRE(list.size() == 3);
    REQUIRE(list.front() == 5);
    REQUIRE(list.back() == 3);
    list.push_front(6);
    REQUIRE(list.front() == 6);
    REQUIRE(list.size() == 4);
    list.pop_front();
    REQUIRE(list.front() == 5);
    REQUIRE(list.size() == 3);
    int elem = 5;
    for(auto it = list.begin(); it != list.end(); it++)
    {
        REQUIRE(*it == elem);
        elem--;
    }
}

TEST_CASE("Special function tests for doubly linked list")
{
    dsac::list::DoublyLinkedList<int> list1;
    list1.push_back(5);
    list1.push_back(4);
    list1.push_back(3);
    dsac::list::DoublyLinkedList<int> list2;
    list2.push_back(2);
    list2.push_back(1);
    list2.push_back(0);
    list1.concatenate(list2);
    REQUIRE(list2.empty() == true);
    REQUIRE(list1.size() == 6);
}



