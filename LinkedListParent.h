#ifndef EL_LINKEDLISTPARENT_H
#define EL_LINKEDLISTPARENT_H

using namespace std;

template<class T>
class LinkedListParent {
protected:
    //достаточно хранить начало и конец
    Element<T>* head;
    Element<T>* tail;
    //для удобства храним количество элементов
    int num;
public:
    virtual int Number() { return num; }

    virtual Element<T>* getBegin() { return head; }

    virtual Element<T>* getEnd() { return tail; }

    LinkedListParent() {
        //конструктор без параметров
        cout << "\nParent constructor";
        head = NULL;
        num = 0;
    }

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление

    virtual Element<T>* push(T value) = 0;

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление

    virtual Element<T>* pop() = 0;

    virtual ~LinkedListParent() {
        //деструктор - освобождение памяти
        cout << "\nParent destructor";
    }

    //получение элемента по индексу - какова асимптотическая оценка этого действия?

    virtual Element<T>* operator[](int i) {
        //индексация
        if (i < 0 || i > num) return NULL;
        int k = 0;
        //ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
        Element<T>* cur = head;
        for (k = 0; k < i; k++) {
            cur = cur->getNext();
        }
        return cur;
    }

    template<class K>
    friend ostream& operator<<(ostream& ustream, LinkedListParent<K>& obj);

    template<class K>
    friend istream& operator>>(istream& ustream, LinkedListParent<K>& obj);
};

template<class T>
ostream& operator<<(ostream& ustream, LinkedListParent<T>& obj) {
    if (typeid(ustream).name() == typeid(ofstream).name()) {
        ustream << obj.num << "\n";
        for (Element<T>* current = obj.getBegin(); current !=
                                                   NULL; current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }
    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (Element<T>* current = obj.getBegin(); current != NULL;
         current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue()
                << "\n";
    return ustream;
}

template<class T>
istream& operator>>(istream& ustream, LinkedListParent<T>&
obj) {
    //чтение из файла и консоли совпадают
    int len;
    ustream >> len;
    //здесь надо очистить память под obj, установить obj.num = 0
    double v = 0;
    for (int i = 0; i < len; i++) {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

#endif //EL_LINKEDLISTPARENT_H
