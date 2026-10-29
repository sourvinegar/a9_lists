#pragma once

#include <stdexcept>
#include <iostream>
#include <utility>     // provides std::swap

namespace dsac::list{
/// circular forward list
template <typename T>
class CircularlyLinkedList {
    private:
        class Node {
            public:
            T elem;
            Node* next;
            Node(const T& element, Node* nxt = nullptr)
            : elem{element}, next{nxt} {}
        };
    private:
        int sz{0};
        Node* tail{nullptr};
    public:
        /// Constructs an empty list
        CircularlyLinkedList() = default;

        /// Returns the number of elements stored
        /// @return the number of elements stored
        int size() const{
            return sz;
        }

        /// Tests whether the list is empty.
        /// @return true if the list is empty, false otherwise
        bool empty() const{
            return sz == 0;
        }

        /// Returns live reference to the first element of the list; behavior undefined if list is empty
        /// @return reference to first element of the list
        T& front(){
            return tail->next->elem;
        }

        /// Returns const reference to the first element of the list; behavior undefined if list is empty
        /// @return reference to first element of the list
        const T& front() const{
            return tail->next->elem;
        }

        /// Returns live reference to the last element of the list; behavior undefined if list is empty
        /// @return reference to last element of the list
        T& back(){
            return tail->elem;
        }

        /// Returns const reference to the last element of the list; behavior undefined if list is empty
        /// @return reference to last element of the list
        const T& back() const{
            return tail->elem;
        }

        /// Inserts element at the beginning of the list
        /// @param elem   the new element
        void push_front(const T& elem){
            if(sz>0)
                tail->next = new Node(elem, tail->next);
            else{
                tail = new Node(elem);
                tail->next = tail;
            }
            sz++;
        }

        /// Inserts element at the end of the list
        /// @param elem   the new element
        /// you can use push_front
        void push_back(const T& elem){
            push_front(elem);
            tail = tail->next;
        }

        /// Removes the first element of the list
        /// behavior undefined if list is empty
        void pop_front(){
            Node* head = tail->next;
            if (head == tail)
                tail = nullptr;
            else
                tail->next = head->next;
            delete head;
            sz--;
        }

        /// Rotates first element to the back of list
        void rotate(){
            Node* head = tail->next->next;
            tail = tail->next;
            tail->next = head;
        }
    public:
        /// Split *this into two circular lists A and B, each with half the nodes.
        /// Precondition: sz is even. After the call, *this becomes empty and
        /// A and B each point to one of the two halves
        /// Handle the case if A and B have prior nodes
        /// Make sure A and B are circular and
        /// original list becomes empty
        void split_even(
            CircularlyLinkedList& a, 
            CircularlyLinkedList& b)
            {
                if(sz%2 != 0)
                    throw std::invalid_argument("Size must be even");
                if(this == &a || this == &b)
                    throw std::logic_error("All the same list");
                if(sz == 0)
                    return;
                    
                    a.clear();
                    b.clear();

                    Node* head = tail->next;
                    Node* middle = head;
                    int mid = sz/2;

                    for(int i = 0; i < mid-1; i++){
                        middle = middle->next;
                    }
                    Node* head_b = middle->next;

                    a.tail = middle;
                    a.tail->next = head;

                    b.tail = tail;
                    b.tail->next = head_b;
                    
                    a.sz = mid;
                    b.sz = mid;

                    tail = nullptr;
                    sz = 0;
                
            }

        
    private:
        /// presumes valid empty list when called
        /// This class is without iterators
        // so can't use range based for loop
        // Assumes the current list is empty
        void clone(const CircularlyLinkedList& other){
            if(other.size() == 0) return;
            Node* walk = other.tail->next;
            for(int i{0}; i< other.size(); i++){
                push_back(walk->elem);
                walk = walk->next;
            }
        }

    public:
        /// non-member function to swap two lists
        friend void swap(
            CircularlyLinkedList& a, 
            CircularlyLinkedList& b){
                std::swap(a.sz, b.sz);
                std::swap(a.tail, b.tail);
            }
          

        /// Resets the list to empty
        void clear(){
            while(sz > 0)
                pop_front();
        }

        /// Copy constructor
        CircularlyLinkedList(const CircularlyLinkedList& other){
            clone(other);
        }

        /// Copy assignment
        CircularlyLinkedList& operator=(const CircularlyLinkedList& other){
            if(this != &other){
                clear();
                clone(other);
            }
            return *this;
        }

        /// Move constructor
        CircularlyLinkedList(CircularlyLinkedList&& other){
            swap(*this, other);
        }

        /// Move assignment
        CircularlyLinkedList& operator=(CircularlyLinkedList&& other){
            if(this != &other)
                swap(*this, other);
            return *this;
        }

        /// default destructor
        ~CircularlyLinkedList(){
            clear();
        }

        void print() const{
            if (tail == nullptr) {
                std::cout << "List is empty.\n";
                return;
            }
            Node* curr = tail->next;
            for (int i{0}; i<size(); i++) {
                std::cout << curr->elem << " ";
                curr = curr->next;
            }
            std::cout << '\n';
        }
    };
}  // namespace dsac::list

