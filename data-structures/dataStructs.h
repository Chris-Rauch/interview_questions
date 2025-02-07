/* Binary Tree Implementation
 *
 * Description:
 *     Maintains a binary tree. Uses template types
 */
#ifndef BINARYTREE
#define BINARYTREE
#include <iostream>

namespace space {

template <class T>
class binaryTree {

    //internal node container
	struct node {
    T val;
    node *rightNode;
    node *leftNode;  
    node(T rVal): val(rVal), rightNode(nullptr), leftNode(nullptr){} 
    };

    public:
        binaryTree() : root(nullptr){};
        ~binaryTree() {destroyTree();}

        void insert(const T &val) {insert(val, &root);}
        void destroyTree() {destroy(root);}
        T* find(const T &val);
        void dispTree() {inOrderDisplay(root);}
        T getRoot() {return root->val;}
        
        bool isEmpty() {return ( (root==nullptr) ? true:false);}
        
    private:
        void destroy(node *treeNode);
        void insert(const T &val, node **ptr);
        void inOrderDisplay(node *root) const;

    private:
        node *root;
};

/* Insert
 *
 */
template <class T>
void binaryTree<T>::insert(const T &val, node **ptr) {
	if(*ptr == nullptr) {
		*ptr = new node(val);
        return;
    }
    if(val < (*ptr)->val)
        insert(val, &((*ptr)->leftNode));
    else
        insert(val, &((*ptr)->rightNode));
}

/* Destroy
 *
 */
template <class T>
void binaryTree<T>::destroy(node *nodePtr) {
    if(nodePtr == nullptr)
        return;

    destroy(nodePtr->leftNode);
    destroy(nodePtr->rightNode);

    delete nodePtr;
}

/* Find
 *
 */
template <class T>
T* binaryTree<T>::find(const T &val) {
    //TODO
}
/* InOrder Display
 *
 * Uses InOrder traversal to display
 */
template <class T>
void binaryTree<T>::inOrderDisplay(node *root) const {
    if(root == nullptr)
        return;
        
    inOrderDisplay(root->leftNode);
    std::cout << root->val << " ";
    inOrderDisplay(root->rightNode);    
}
}

#endif

#ifndef LINKEDLIST
#define LINKEDLSIT

template <class T>
class LinkedList {
    struct node {
        T val;
        node *next;
        node(const T &rVal) : val(rVal), next(nullptr) {} 
    };

    public:
        LinkedList() : head(nullptr), tail(nullptr), size(0) {}
        LinkedList(const LinkedList &rhs);
        ~LinkedList() {destroyList();}

        void destroyList();

        T get_front() {return head->val;}
        T get_back() {return tail->val;}
        T get_index(int index);
        void pop_front();
        void pop_back();
        bool pop_index(int index);//EDIT
        void push_front(const T &rVal);
        void push_back(const T &rVal);
        bool push_index(const T &rVal, int index);
        
        int getSize() {return size;}
        int getIndex(const T &val);//TODO
        
        bool remove(const T &target);
        bool removeAll(const T &target);
        void swap(T lhs, T rhs);//TODO
        bool isEmpty() {return ((size == 0) ? true:false);}
        node* getHead() {return head;} 

    private:
        node *head;
        node *tail;
        int size;
};

/* Copy Constructor
 *
 */
template <class T>
LinkedList<T>::LinkedList(const LinkedList &rhs) : head(nullptr), tail(nullptr), size(0) {
    node *oldList = rhs.head;
    node *newList1 = nullptr, *newList2 = nullptr;
    int rSize = rhs.size;
    
    //copy list 
    for( ; this->size < rSize; ++this->size, oldList = oldList->next) {
        if(this->size == 0)
            this->head = this->tail = newList1 = newList2 = new node(oldList->val);
        else if(this->size == (rSize-1))
            this->tail = new node(oldList->val);
        else {
            newList2 = new node(oldList->val);
            newList1->next = newList2;
        }
    }
}

/* push_front
 *
 */
template <class T>
void LinkedList<T>::push_front(const T &rVal) {
    if(size == 0)
        head = tail = new node(rVal);

    else {
        node *temp = head;
        head = new node(rVal);
        head->next = temp;
    }
    ++size;
}

/* push_back
 *
 */
template <class T>
void LinkedList<T>::push_back(const T &rVal) {
    if(size == 0)
        head = tail = new node(rVal);

    else {
        node *temp = tail;
        tail = new node(rVal);
        temp->next = tail;
    }
    ++size;
}

/* pop_front
 *
 * deletes the head element from the list
 */
template <class T>
void LinkedList<T>::pop_front() {
    if(size == 0)
        return;
        
    else if(size == 1) {
        delete head;
        head = tail = nullptr;
        --size;
    }
    else {
        node *temp = head;
        head = head->next;
        delete temp;
        --size;
    }
}

/* pop_back
 *
 * deletes the tail element from the list
 */
template <class T>
void LinkedList<T>::pop_back() {
    if(size == 0)
        return;
        
    else if(size == 1) {
        delete tail;
        head = tail = nullptr;
        --size;
    }
    else {
        delete tail;
        tail = head;
        //iterate till the second to last eliment
        for(int x = 0; x < (size-2); ++x, tail = tail->next);
        tail->next = nullptr;
        --size;
    }
}

/* remove
 *
 * deletes the first target element in the array
 * use deleteAll() function to delete every instance
 */
template <class T>
bool LinkedList<T>::remove(const T &target) {
    //check the head
    if(head->val == target) {
        pop_front();
        return true;
    }

    node *temp1 = head;
    node *temp2 = head->next;
        
    //search for the element
    for( ; temp2 != nullptr; temp1 = temp1->next, temp2 = temp2->next) 
        //break early if the element is found
        if(temp2->val == target)
            break;
            
    //if element was not found
    if (temp2 == nullptr)
        return false;
    //if it was found
    else {
        temp1->next = temp2->next;
        delete temp2;
        --size;
        return true;
    }
}

/* removeAll
 *
 * removes every target element
 */
template <class T>
bool LinkedList<T>::removeAll(const T &target) {
    bool isRemoved = false;
    while(remove(target))
        isRemoved = true;
    return isRemoved;
}

/* destroyList
 *
 * deletes the entire list
 */
template <class T>
void LinkedList<T>::destroyList() {
    while(size != 0)
        pop_front();
}

/* push_index
 *
 * insert an element into a given, zero based index
 */
template <class T>
bool LinkedList<T>::push_index(const T &rVal, int index) {
    //check out of range index
    if(index >= size) 
        return false;
    //check for front of list
    if(index == 0) {
        push_front(rVal);
        return true;
    }
    //check for back of list
    if(index == size) {
        push_back(rVal);
        return true;
    }
        
    node *temp = head;
    for( ; index != 1; temp = temp->next, --index);
    node *ptr = temp->next;
    temp->next = new node(rVal);
    temp->next->next = ptr;
    ++size;
    
    return true;
}
/* get_index
 *
 */
template <class T>
T LinkedList<T>::get_index(int index) {
    node *temp = head;
    for( int x = 0; index != x; ++x, temp = temp->next);

    return temp->val;
}

/* pop_index
 * 
 */
template <class T>
bool LinkedList<T>::pop_index(int index) {
    //check out of range index
    if(index >= size) 
        return false;
    //check for front of list
    if(index == 0) 
        pop_front();
    //check for back of list
    if(index == size) 
        pop_back();
    
    node *temp1 = head;
    node *temp2 = head->next;
    for( int x = 1; index != x; ++x, temp2 = temp2->next);

    temp1->next = temp2->next;
    delete temp2;
    --size;
    return true;    
}
#endif

/* Queue Class
 *
 * uses a circular buffer implementation
 * increases array size to avoid overwriting
 */
#ifndef QUEUE
#define QUEUE

template <class T>
class Queue {
    public:
        Queue() : front(0), back(0), size(0), STARTING_SIZE(1), circularQueue(new T[STARTING_SIZE]) {}
        ~Queue() {delete[] circularQueue;}
        void push(const T &element);
        T pop();
        bool isEmpty() {return (size==0) ? true:false;}
        size_t getSize() {return size;}

    protected:
        void incrementQueueSize();
    protected:
        size_t front;
        size_t back;
        size_t size; //the number of elements in the array
        size_t STARTING_SIZE;//amount of memory origianlly allocated
        T* circularQueue;
};


template <class T>
void Queue<T>::push(const T &elem) {
    //check for overwriting
    if((back+1) % STARTING_SIZE == front)
        incrementQueueSize();
    //add element
    circularQueue[++back % STARTING_SIZE] = elem;
    ++size;
}

/* pop
 *
 * output - returns the front element in the queue
 *       - deletes the front element
 */
template <class T>
T Queue<T>::pop() {
    size_t x = front;
    front = ((front+1) % STARTING_SIZE);
    --size;
    return circularQueue[x];
}

/* incrementQueueSize
 *
 * output - copies arr1 into arr2 and doubles the size
 *       - front is set to 0
 */
template <class T>
void Queue<T>::incrementQueueSize() {
    //create a new array and double the size
    T* newArr = new T[(this->size * 2)];
    //copy it over
    for(size_t x = 0; x < this->size; ++x, front = ((front+1) % size))
        newArr[x] = circularQueue[front];
    delete[] circularQueue;
    circularQueue = newArr;
    front = 0;
    back = (size-1);
    STARTING_SIZE *= 2;
}
#endif


#ifndef STACK
#define STACK

template <class T>
class Stack : public Queue<T> {
    public:
        Stack(Queue<T> &rhs){}
    T pop();
};

/* pop
 *
 * output - returns the front element in the queue
 *       - deletes the front element
 *//*
template <class T>
T Stack<T>::pop() {
    size_t x = front;
    front = ((front+1) % STARTING_SIZE);
    --size;
    return circularQueue[x];
}
*/
#endif
