#ifndef EL_DD_H
#define EL_DD_H

template<class T>
class DD : public D<T>
{
public:

    Element<T>* push(T value)
    {
        auto element = new Element<T>(value);
        LinkedListParent<T>::num += 1;

        if (!IteratedLinkedList<T>::head)
        {
            IteratedLinkedList<T>::tail = element;
            IteratedLinkedList<T>::head = element;
            return element;
        }

        Element<T>* t = IteratedLinkedList<T>::head;

        if (t->getValue() > value) {
            IteratedLinkedList<T>::head = element;
            element->setNext(t);
            t->setPrevious(element);
            return element;
        }

        while (t != NULL) {
            if (t->getValue() > value) {
                break;
            }

            t = t->getNext();
        }

        if (!t) {
            IteratedLinkedList<T>::end()->setNext(element);
            (*element).setPrevious(&(*IteratedLinkedList<T>::end()));
            IteratedLinkedList<T>::tail = element;
            return element;
        }

        element->setPrevious(t->getPrevious());
        element->setNext(&(*t));

        t->getPrevious()->setNext(element);
        t->setPrevious(element);

        return element;
    }
};

#endif //EL_DD_H
