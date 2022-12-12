#ifndef EL_ITERATEDLINKEDLIST_H
#define EL_ITERATEDLINKEDLIST_H

using namespace std;

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType> {
private:
public:
    ListIterator() { ptr = NULL; }

    //ListIterator(ValueType* p) { ptr = p; }
    ListIterator(Element<ValueType>* p) { ptr = p; }

    ListIterator(const ListIterator& it) { ptr = it.ptr; }

    bool operator!=(ListIterator const& other) const {
        return
                ptr != other.ptr;
    }
    bool operator==(ListIterator const& other) const {
        return
                ptr == other.ptr;
    }//need for BOOST_FOREACH
    Element<ValueType>& operator*() {
        return *ptr;
    }

    ListIterator& operator++() {
        ptr = ptr->getNext();
        return
                *this;
    }

    ListIterator& operator++(int v) {
        auto copy = ptr;
        ptr = ptr->getNext();
        return *copy;
    }

    ListIterator& operator--() {
        ptr = ptr->getNext();
        return
                *this;
    }

    ListIterator& operator--(int v) {
        auto copy = ptr;
        ptr = ptr->getNext();
        return *copy;
    }

    ListIterator& operator=(const ListIterator& it) {
        ptr =
                it.ptr;
        return *this;
    }

    ListIterator& operator=(Element<ValueType>* p) {
        ptr = p;
        return *this;
    }

private:
    Element<ValueType>* ptr;
};


template<class T>
class IteratedLinkedList : public LinkedListParent<T> {
public:
    IteratedLinkedList() : LinkedListParent<T>() {
        cout <<
             "\nIteratedLinkedList constructor";
    }

    virtual ~IteratedLinkedList() {
        cout <<
             "\nIteratedLinkedList destructor";
    }

    ListIterator<T> iterator;

    ListIterator<T> begin() {
        ListIterator<T> it =
                LinkedListParent<T>::head;
        return it;
    }

    ListIterator<T> end() {
        ListIterator<T> it =
                LinkedListParent<T>::tail;
        return it;
    }
};

#endif //EL_ITERATEDLINKEDLIST_H
