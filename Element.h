#ifndef EL_ELEMENT_H
#define EL_ELEMENT_H

using namespace std;

template<class T>
class Element {//элемент связного списка
private:
    //указатель на предыдущий и следующий элемент
    Element* next;
    Element* prev;
    //информация, хранимая в поле
    T field;
public:
    Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
    {
        field = value;
        next = next_ptr;
        prev = prev_ptr;
    }

    //доступ к полю *next
    virtual Element* getNext() { return next; }

    virtual void setNext(Element* value) { next = value; }

    //доступ к полю *prev
    virtual Element* getPrevious() { return prev; }

    virtual void setPrevious(Element* value) { prev = value; }

    //доступ к полю с хранимой информацией field
    virtual T getValue() { return field; }

    virtual void setValue(T value) { field = value; }

    template<class K>
    friend ostream& operator<<(ostream& ustream, Element<K>& obj);
};

#endif