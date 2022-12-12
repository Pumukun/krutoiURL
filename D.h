#ifndef EL_D_H
#define EL_D_H

template<class T>
class D : public IteratedLinkedList<T>
{
public:
    Element<T>* push(T value)
    {
        Element<T>* element = new Element<T>(value);
        LinkedListParent<T>::num += 1;
        if (!IteratedLinkedList<T>::head)
        {
            IteratedLinkedList<T>::tail = element;
            IteratedLinkedList<T>::head = element;
            return element;
        }

        (*IteratedLinkedList<T>::end()).setNext(element);
        element->setPrevious(&(*IteratedLinkedList<T>::end()));
        IteratedLinkedList<T>::tail = element;
        return &(*IteratedLinkedList<T>::end());
    }
    Element<T>* pop()
    {
        if (!IteratedLinkedList<T>::head)
        {
            return NULL;
        }
        LinkedListParent<T>::num -= 1;
        Element<T>* iter = IteratedLinkedList<T>::head;
        if (!(iter->getNext()))
        {
            IteratedLinkedList<T>::head = NULL;
            return iter;
        }
        Element<T>* it = IteratedLinkedList<T>::tail;
        IteratedLinkedList<T>::tail = it->getPrevious();
        IteratedLinkedList<T>::tail->setNext(NULL);
        return 0;
    }
    Element<T>* push_(T value) {
        auto element = new Element<T>(value);
        LinkedListParent<T>::num += 1;
        if (!IteratedLinkedList<T>::head) {
            IteratedLinkedList<T>::tail = element;
            IteratedLinkedList<T>::head = element;
            return this->getEnd();
        }

        auto tmp = IteratedLinkedList<T>::head;

        if (sort_(tmp->getValue(), value)) {
            tmp->setPrevious(element);
            element->setNext(tmp);
            IteratedLinkedList<T>::head = element;
            return element;
        }

        while (tmp != NULL) {
            if (sort_(tmp->getValue(), value)) {
                break;
            }

            tmp = tmp->getNext();
        }
        if (!tmp) {
            (*IteratedLinkedList<T>::end()).setNext(element);
            (*element).setPrevious(this->getEnd());
            IteratedLinkedList<T>::tail = element;
            return this->getEnd();
        }
        element->setPrevious(tmp->getPrevious());
        element->setNext(&(*tmp));
        tmp->getPrevious()->setNext(element);
        tmp->setPrevious(element);
        return element;
    }
    ~D() {
        Element<T>* t = &(*IteratedLinkedList<T>::head);
        if (!t) { return; }

        if (!t->getNext()) {
            free(t);
            return;
        }

        t = t->getNext();

        while (t) {
            free(t->getPrevious());
            t = t->getNext();
        }

        free(t);
    }
};


#endif
