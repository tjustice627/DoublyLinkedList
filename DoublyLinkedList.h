#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED

template <class T>
struct Node {
	T info;
	Node<T> * next;
	Node<T> * prev;
};

template <class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() { head = tail = curr = nullptr; }
    DoublyLinkedList(const DoublyLinkedList<T> & rhs) { deepCopy(rhs); }
    DoublyLinkedList<T> & operator = (const DoublyLinkedList<T> & rhs);
    ~DoublyLinkedList() { makeEmpty(); }

    bool getFirst(T & el);          // O(1) steps
    bool getNext(T & el);           // O(1) steps
	bool getLast(T & el);           // O(1) steps
	bool getPrev(T & el);           // O(1) steps

    void insert(const T & el);      // O(1) steps
    bool find(const T & el);        // O(n) steps
    bool retrieve(T & el);          // O(n) steps
    bool replace(const T & el);     // O(1) steps
    bool remove(T & el);            // O(n) steps

    bool isEmpty() { return (head == nullptr); }
    void makeEmpty();
private:
    Node <T> * head;
    Node <T> * tail;
    Node <T> * curr;
    void deepCopy(const DoublyLinkedList<T> & rhs);
};

template <class T>
DoublyLinkedList<T> & DoublyLinkedList<T>::operator = (const DoublyLinkedList<T> & rhs) {
    if (this == &rhs) return (*this);
    makeEmpty(); deepCopy(rhs); return (*this);
}

template <class T>
bool DoublyLinkedList<T>::getFirst(T & el) {      // O(1) steps
    if (head == nullptr) return false;
    el = head->info;
    curr = head;
    return true;
}

template <class T>
bool DoublyLinkedList<T>::getNext(T & el) {   // get the next node to where curr is pointing
    if (curr == nullptr) return false;      // O(1) steps
    curr = curr->next;
    if (curr == nullptr) return false;
    el = curr->info;
    return true;
}

template <class T>
bool DoublyLinkedList<T>::getLast(T & el) {      // O(1) steps
    if (tail == nullptr) return false;
    curr = tail;
    el = curr->info;
    return true;
}

template <class T>
bool DoublyLinkedList<T>::getPrev(T & el) {   // get the prev node to where curr is pointing
    if (curr == nullptr) return false;
    curr = curr->prev;
    if (curr == nullptr) return false;
    el = curr->info;
    return true;
}

template <class T>
void DoublyLinkedList<T>::insert(const T & el) {     // O(1) steps
	Node<T> * newNode = new Node<T>;
	if (tail == nullptr)
    {
        tail = newNode;
    }
	newNode->info = el; 	// 	(*newNode).info = el;
	newNode->next = head;
	if (head != nullptr) newNode->next->prev = newNode;
	head = newNode;
	head->prev = nullptr;
    curr = nullptr;
}

template <class T>
bool DoublyLinkedList<T>::find(const T & el) {        // O(n) steps
    T currEl;
    if (getFirst(currEl) == false) return false;
    if (currEl == el) return true;
    while (getNext(currEl)) {
        if (currEl == el) return true;
    }
    return false;
}

template <class T>
bool DoublyLinkedList<T>::retrieve(T & el) {          // O(n) steps
    if (find(el) == false) return false;
    el = curr->info;
    return true;
}

template <class T>
bool DoublyLinkedList<T>::replace(const T & el) {     // O(1) steps
    if (curr == nullptr) return false;
    curr->info = el;
    return true;
}

template <class T>
bool DoublyLinkedList<T>::remove(T & el) {
	if (!retrieve(el)) return false;
	if (retrieve(el))
    {
        if (curr == head)
        {
            head = curr->next;
        }
        if (curr == tail)
        {
            tail = curr->prev;
        }
        if (curr->next != nullptr)
        {
            curr->next->prev = curr->prev;
        }
        if (curr->prev != nullptr)
        {
            curr->prev->next = curr->next;
        }
        delete(curr);
        curr = nullptr;
        return true;
    }
}

template <class T>
void DoublyLinkedList<T>::makeEmpty() {
	curr = head;
	while (curr != nullptr) {
		Node<T> * temp = curr;
		curr = curr->next;
		delete temp;
	}
	head = tail = nullptr;
}

template <class T>
void DoublyLinkedList<T>::deepCopy(const DoublyLinkedList<T> & rhs) {
    if (rhs.head == nullptr) { head = tail = curr = nullptr; return; }
    curr = nullptr;
    Node<T> * prevNode = new Node<T>;
    head = prevNode;
    prevNode->info = rhs.head->info; prevNode->prev = nullptr;
    if (rhs.curr == rhs.head) curr = head;
    Node<T> * rhsNode = rhs.head->next;
    while (rhsNode != nullptr) {
        Node<T> * currNode = new Node<T>;
        prevNode->next = currNode; currNode->info = rhsNode->info;
        currNode->prev = prevNode;
        if (rhs.curr == rhsNode) curr = currNode;
        rhsNode = rhsNode->next;
        prevNode = currNode;
    }
    prevNode->next = nullptr; tail = prevNode;
}

#endif // DOUBLYLINKEDLIST_H_INCLUDED
