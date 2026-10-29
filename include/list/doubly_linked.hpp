#pragma once

#include <utility>     // provides std::swap

namespace dsac::list{
//akin to std::list
template <typename T>
class DoublyLinkedList {
    private:
        class Node {
            public:
            T elem;
            Node* prev{nullptr};
            Node* next{nullptr};
            Node() = default;
            Node(const T& element, Node* prv, Node* nxt)
            : elem{element}, prev{prv}, next{nxt} {}
        };

    private:
        int sz{0};
        Node* header; // sentinel node
        Node* trailer;// sentinel node
        void create_sentinels(){
            header = new Node();
            trailer = new Node();
            header->next = trailer;
            trailer->prev = header;
        }

    public:
        /// Constructs an empty list
        DoublyLinkedList(){
            create_sentinels();
        }

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
            return header->next->elem;
        }

        /// Returns const reference to the first element of the list; behavior undefined if list is empty
        /// @return reference to first element of the list
        const T& front() const{
            return header->next->elem;
        }

        /// Returns live reference to the last element of the list; behavior undefined if list is empty
        /// @return reference to last element of the list
        T& back(){
            return trailer->prev->elem;
        }

        /// Returns const reference to the last element of the list; behavior undefined if list is empty
        /// @return reference to last element of the list
        const T& back() const{
            return trailer->prev->elem;
        }

    private:
        /// Inserts new element immediately before the given node and returns pointer to the new node
        /// @param successor   node just before the location where the new node is inserted
        /// @return pointer to the newly created node
        Node* insert_before(T elem, Node* successor)
        {
            Node* predecessor = successor->prev;
            Node* newest{new Node(elem, predecessor, successor)};
            predecessor->next = newest;
            successor->prev = newest;
            sz++;
            return newest;
        }

        /// Removes the given node from the list
        /// @param node    the node to be removed (must not be a sentinel)
        void erase(Node* node)
        {
            Node* predecessor = node->prev;
            Node* successor = node->next;
            predecessor->next = successor;
            successor->prev = predecessor;
            delete node;
            sz--;
        }

    public:
        /// Inserts element at the beginning of the list
        /// @param elem   the new element
        void push_front(const T& elem){
            insert_before(elem, header->next);
        }

        /// Inserts element at the end of the list
        /// @param elem   the new element
        void push_back(const T& elem){
            insert_before(elem, trailer);
        }

        /// Removes the first element of the list
        void pop_front(){
            erase(header->next);
        }

        /// Removes the last element of the list
        void pop_back(){
            erase(trailer->prev);
        }

    public:
        // Concatenate other to the back of this in O(1) time
        /// Afterward, other becomes empty
        /// no action if self concatenation
        void concatenate(DoublyLinkedList& other){
            if(other.empty())
                return;
            if(this != &other)
            {
                Node* pred = trailer->prev;
                Node* first = other.header->next;
                Node* last = other.trailer->prev;

                pred->next = first;
                first->prev = pred;
                last->next = trailer;
                trailer->prev = last;

                other.header->next = other.trailer;
                other.trailer->prev = other.header;
                
                sz = sz + other.sz;
                other.sz = 0;
            }
        }
    
        class iterator {
            friend class DoublyLinkedList;
            private:
                Node* node_ptr{nullptr};
            public:
                iterator(Node* ptr = nullptr)
                : node_ptr(ptr) {}

                T& operator*() const{
                    return node_ptr->elem;
                }
                
                T* operator->() const{
                    return &node_ptr->elem;
                }

                iterator& operator++(){
                    node_ptr = node_ptr->next;
                    return *this;
                }

                iterator operator++(int){
                    iterator temp(*this);
                    node_ptr = node_ptr->next;
                    return temp;
                }

                iterator& operator--(){
                    node_ptr = node_ptr->prev;
                    return *this;
                }

                iterator operator--(int){
                    iterator temp(*this);
                    node_ptr = node_ptr->prev;
                    return temp;   
                }

                bool operator==(const iterator& other) const{
                    return node_ptr == other.node_ptr;
                }

                bool operator!=(const iterator& other) const{
                    return node_ptr == other.node_ptr;
                }
        };

    public:
        class const_iterator {
            private:
                const Node* node_ptr{nullptr};
            public:
                const_iterator(const Node* ptr = nullptr)
                : node_ptr(ptr) {}

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
                    const_iterator temp(*this);
                    node_ptr = node_ptr->next;
                    return *this;
                }

                const_iterator& operator--(){
                    node_ptr = node_ptr->prev;
                    return *this;
                }

                const_iterator operator--(int){
                    const_iterator temp(*this);
                    node_ptr = node_ptr->prev;
                    return *this;
                }

                bool operator==(const const_iterator& other) const{
                    return node_ptr == other.node_ptr;
                }

                bool operator!=(const const_iterator& other) const{
                    return node_ptr != other.node_ptr;
                }
        };

    public:
        /// Returns iterator for the front of the list
        iterator begin(){
            return iterator(header->next);
        }

        /// Returns const_iterator for the front of the list
        const_iterator begin() const{
            return const_iterator(header->next);
        }

        /// Returns iterator for the end of the list
        iterator end(){
            return iterator(trailer);
        }

        /// Returns const_iterator for the end of the list
        const_iterator end() const{
            return const_iterator(trailer);
        }

        /// Inserts new element immediately before the given position and returns iterator to new element
        /// @param it     iterator defining position
        /// @param elem   element to insert
        /// @return       iterator of newly inserted element
        iterator insert(iterator it, const T& elem){
            Node* node = it.node_ptr;
            Node* new_node = insert_before(elem, node);
            return iterator(new_node);
        }

        /// Removes the element at the given position
        /// @param it     iterator defining position
        /// @return       iterator of position just beyond the removed element
        iterator erase(iterator it){
            Node* node = it.node_ptr;
            ++it;
            erase(node);
            return it;
        }

    private:
        // presumes valid empty list when called
        void clone(const DoublyLinkedList& other){
            for (T e : other)
                push_back(e);
        }

    public:
        /// non-member function to swap two lists
        friend void swap(
            DoublyLinkedList& a, DoublyLinkedList& b){
                std::swap(a.sz, b.sz);
                std::swap(a.header, b.header);
                std::swap(a.trailer, b.trailer);
            }
    
        /// resets the list to empty
        void clear(){
            while(sz > 0)
                pop_front();
        }

        /// copy constructor
        DoublyLinkedList(const DoublyLinkedList& other){
            create_sentinels();
            clone(other);
        }
        

        /// copy assignment
        DoublyLinkedList& operator=(
            const DoublyLinkedList& other){
                if(this != &other){
                    clear();
                    clone(other);
                }
                return *this;
            }

        /// move constructor
        DoublyLinkedList(DoublyLinkedList&& other){
            create_sentinels();
            swap(*this, other);
        }

        /// move assignment
        DoublyLinkedList& operator=(DoublyLinkedList&& other){
            if(this != &other){
                swap(*this, other); 
            }
            return *this;
        }

        /// default destructor
        /// delete sentinels also
        ~DoublyLinkedList(){
            clear();
            delete header;
            delete trailer;
        }

    public:
        void print() const{
            if(sz == 0)
            {
                std::cout <<"List is empty.\n";
                return;
            }
            for(auto it = begin(); it != end(); it++){
                std::cout << *it  << " ";    
            }
            std::cout << std::endl;
        }

};

}
