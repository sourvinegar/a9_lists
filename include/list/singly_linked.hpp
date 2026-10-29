#pragma once

#include <utility>     // provides std::swap

namespace dsac::list {

/// singly linked list, akin to std::forward_list
template <typename T>
class SinglyLinkedList {
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
        Node* head{nullptr};
        Node* tail{nullptr};
    public:
        /// Constructs an empty SinglyLinkedList list
        SinglyLinkedList() = default;

        /// Returns the number of elements stored
        /// @return the number of elements stored
        int size() const
        {
            return sz;
        }

        /// Tests whether the list is empty.
        /// @return true if the list is empty, false otherwise
        bool empty() const
        {
            return sz == 0;
        }

        /// Returns live reference to the first element of the list; behavior undefined if list is empty
        /// @return reference to first element of the list
        T& front(){
            return head->elem;
        }

        /// Returns const reference to the first element of the list; behavior undefined if list is empty
        /// @return reference to first element of the list
        const T& front() const{
            return head->elem;
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
            head = new Node(elem, head);
            if(sz == 0){
                tail = head;
            }
            sz++;
        }

        /// Removes the first element of the list
        /// behavior undefined if list is empty
        void pop_front(){
            Node* old{head};
            head = head->next;
            delete old;
            sz--;
            if (sz == 0)
            tail = nullptr;
        }

        /// Inserts element at the end of the list
        /// @param elem   the new element
        void push_back(const T& elem){
            Node *newest{new Node(elem, nullptr)};
            if(sz == 0)
                head = newest;
            else 
                tail->next = newest;
            tail = newest;
            sz++;
        }

    public:
        // Concatenate other to the back of this in O(1) time
        /// Afterward, other becomes empty
        /// no action if self concatenation
        void concatenate(SinglyLinkedList& other){
            if(this != &other)
            {
                tail->next = other.head;
                sz = sz + other.size();
                other.sz = 0;
                other.head = nullptr;
                other.tail = nullptr;
            }
        }

        /// Reverses the singly linked list in place
        ///
        /// Initially:
        /// prev = nullptr, curr = 1
        /// nullptr    1 -> 2 -> 3 -> 4 -> nullptr
        ///  prev     curr
        ///
        /// next_node = 2
        /// nullptr <- 1    2 -> 3 -> 4 -> nullptr
        ///            prev curr
        ///
        /// next_node = 3
        /// nullptr <- 1 <- 2    3 -> 4 -> nullptr
        ///                 prev curr
        ///
        /// next_node = 4
        /// nullptr <- 1 <- 2 <- 3    4 -> nullptr
        ///                      prev curr
        ///
        /// next_node = nullptr
        /// nullptr <- 1 <- 2 <- 3 <- 4
        ///                           prev
        /// curr = nullptr
        ///
        /// Finally, head = prev (node 4).
        /// Result: 4 -> 3 -> 2 -> 1 -> nullptr
        ///
        /// Time: O(n), Space: O(1)

        void reverse(){
            Node* prev = nullptr;
            Node* curr = head;

            for(int i = 0; i < sz; i++){
                curr->next = prev;
                prev = curr;
            }
            head = prev;
        }
    public:
        class iterator {
            friend class SinglyLinkedList;
            private:
                Node* node_ptr{nullptr};
            public:
                iterator() = default; //i think this is wrong
                iterator(Node* ptr = nullptr):
                node_ptr(ptr) {}

                T& operator*() const{
                    return node_ptr->elem;
                }

                T* operator->() const{
                    return *node_ptr->elem;
                }

                iterator& operator++(){
                    node_ptr = node_ptr->next;
                    return (*this);
                }

                iterator operator++(int){
                    iterator temp(*this);
                    ++(*this);
                    return temp;
                }

                bool operator==(iterator rhs) const{
                    return node_ptr == rhs.node_ptr;
                }

                bool operator!=(iterator rhs) const{
                    return node_ptr != rhs.node_ptr;
                }
        };

    public:
        class const_iterator {
            private:
                Node* node_ptr{nullptr};
            public:
                const_iterator();
                const_iterator(Node* ptr):
                node_ptr(ptr) {};

                const T& operator*() const{
                    return node_ptr->elem;
                }

                const T* operator->() const{
                    return &node_ptr->elem;
                }

                const_iterator& operator++(){
                    node_ptr = node_ptr->next;
                    return *this;
                }

                const_iterator operator++(int){
                    iterator temp(*this);
                    ++(*this);
                    return temp;
                }

                bool operator==(const_iterator rhs) const{
                    return node_ptr == rhs.node_ptr;
                }

                bool operator!=(const_iterator rhs) const{
                    return node_ptr != rhs.node_ptr;
                }
        };

    public:
        /// Returns iterator for the front of the list
        iterator begin(){
            return iterator(head);
        }

        /// Returns const_iterator for the front of the list
        const_iterator begin() const{
            return const_iterator(head);
        }

        /// Returns iterator for the end of the list
        /// fictional position after the last element
        iterator end(){
            return iterator(nullptr);
        }

        /// Returns const_iterator for the end of the list
        /// fictional position after the last element
        const_iterator end() const{
            return const_iterator(nullptr);
        }

        /// Inserts new element just after the given position
        /// @param it     iterator defining position
        /// @param elem   element to insert
        /// @return       iterator of newly inserted element
        /// return the iterator to new node
        iterator insert_after(iterator it, const T& elem){
            it.node_ptr->next = new Node(elem, it.node_ptr->next);
            if(tail == it.node_ptr)
                tail = it.node_ptr->next;
            sz++;
            return(it.node_ptr->next);
        }

        /// Removes the element just after the given position
        /// @param it     iterator defining position
        /// @return       iterator of position just beyond the removed element
        /// return iterator to what newly follows the original iterator
        iterator erase_after(iterator it){
            Node *dead = it.node_ptr->next;
            if(tail == dead)
                tail = it.node_ptr;
            it.node_ptr->next = dead->next;
            delete dead;
            sz--;
            return iterator(it.node_ptr->next);
        }

    private:
        /// presumes valid empty list when called
        void clone(const SinglyLinkedList& other){
            for(T e : other)
                push_back(e);
        }

    public:
        /// non-member function to swap two lists
        friend void swap(
            SinglyLinkedList& a, SinglyLinkedList& b){
                std::swap(a.sz, b.sz);
                std::swap(a.head, b.head);
                std::swap(a.tail, b.tail);
            }

        /// resets the list to empty
        void clear(){
            while(sz > 0)
                pop_front();
        }
    public:
        /// copy constructor
        SinglyLinkedList(const SinglyLinkedList& other){
            clone(other);
        }

        /// copy assignment
        SinglyLinkedList& operator=(const SinglyLinkedList& other){
            if(this != &other){
                clear();
                clone(other);
            }
            return *this;
        }

        /// move constructor
        SinglyLinkedList(SinglyLinkedList&& other){
            swap(*this, other);
        }

        /// move assignment
        SinglyLinkedList& operator=(SinglyLinkedList&& other){
            if(this != &other)
                swap(*this,other);
            return *this;
        }

        /// destructor
        ~SinglyLinkedList(){
            clear();
        }

};

} // namespace
