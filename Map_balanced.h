#ifndef EL_MAP_BALANCED_H
#define EL_MAP_BALANCED_H

using namespace std;

class Iterator_Exception : public exception {
public:
    Iterator_Exception(string *msg) : exception() { }
};
// само бинарное дерево поиска
template<class K, class T>
class Map_balanced {
protected:
    // корень, начало и конец
    Node_m<K, T> *root;
    Node_m<K, T> *begin_, *end_;

    // разность высот поддеревьев левого и правого
    virtual int bfactor(Node_m<K, T> *p) {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        return (hr - hl);
    }

    // тут мы фиксируем высоту дерева минимальную
    virtual void fixHeight(Node_m<K, T> *p) {
        int hl = 0;
        int hr = 0;
        if (p->getLeft() != NULL)
            hl = p->getLeft()->getHeight();
        if (p->getRight() != NULL)
            hr = p->getRight()->getHeight();
        p->setHeight((hl > hr ? hl : hr) + 1);
    }

    // правый поворот для балансировки
    virtual Node_m<K, T> *RotateRight(Node_m<K, T> *p) // правый поворот вокруг p
    {
        Node_m<K, T>* q = p->getLeft();
        p->setLeft(q->getRight());
        q->setRight(p);

        if (p != root) {
            if (p->getParent()->getKey() > p->getKey()) // p->getParent
                p->getParent()->setLeft(q);
            else p->getParent()->setRight(q);
        }
        else root = q;

        q->setParent(p->getParent());
        p->setParent(q);
        if (p->getLeft() != NULL) p->getLeft()->setParent(p);

        fixHeight(p);
        fixHeight(q);
        return q;
    }

    // левый поворот
    virtual Node_m<K, T> *RotateLeft(Node_m<K, T> *q) // левый поворот вокруг p
    {
        Node_m<K, T>* p = q->getRight();
        q->setRight(p->getLeft());
        p->setLeft(q);

        if (q != root) {
            if (q->getParent()->getKey() > q->getKey()) // p->getParent
                q->getParent()->setLeft(p);
            else q->getParent()->setRight(p);
        }
        else root = p;

        p->setParent(q->getParent());
        q->setParent(p);
        if (q->getRight() != NULL) q->getRight()->setParent(q);

        fixHeight(q);
        fixHeight(p);
        return p;
    }

    // сама логика балансировки через повороты
    virtual Node_m<K, T> *Balance(Node_m<K, T> *p) // балансировка узла p
    {
        fixHeight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->getRight()) < 0) RotateRight(p->getRight());
            return RotateLeft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->getLeft()) > 0) RotateLeft(p->getLeft());
            return RotateRight(p);
        }
        return p; // балансировка не нужна
    }

    // рекурсивный push потому что push жлемента должен быть быстрыйвроед как O(log n)
    virtual Node_m<K, T> *push_R(Node_m<K, T> *n, Node_m<K, T> *Current) {
        if (n == NULL) return NULL;
        if (root == NULL) {
            root = n;
            return n;
        }

        if (Current->getKey() > n->getKey()) {
            //идем влево
            if (Current->getLeft() != NULL)
                Current->setLeft(push_R(n, Current->getLeft()));
            else
                Current->setLeft(n);
            Current->getLeft()->setParent(Current);
        }
        if (Current->getKey() < n->getKey()) {
            //идем вправо
            if (Current->getRight() != NULL)
                Current->setRight(push_R(n, Current->getRight()));
            else
                Current->setRight(n);
            Current->getRight()->setParent(Current);
        }
        if (Current->getKey() == n->getKey())
            ;

        if (Current != NULL)
            return Balance(Current);

        return n;
    }

    // Поиск по ключу
    virtual Node_m<K, T> *Find_R_Key(K key, Node_m<K, T> *Current) {
        // база рекурсии
        if (Current == NULL) return NULL;

        if (Current->getKey() == key) return Current;

        // рекурсивный вызов
        if (Current->getKey() > key) return Find_R_Key(key, Current->getLeft());

        if (Current->getKey() < key) return Find_R_Key(key, Current->getRight());
    }

public:
    // обьявляем итератор пока что абстрактно
    class tree_iterator;

    virtual Node_m<K, T> *getRoot() { return root; }

    // конструкторы
    Map_balanced() {
        root = NULL;
    }

    // этот конструктор нужен для нормальной работы итератора,
    // надо ввести максимально маленький и максимально большой ключи - это будут end_ и begin_
    Map_balanced(K k1, K k2) {
        root = NULL;
        begin_ = new Node_m<K, T>(k1);
        end_ = new Node_m<K, T>(k2);
        push_R(begin_, root);
        push_R(end_, root);
    }

    virtual Node_m<K, T> *push(Node_m<K, T> *N) {
        return push_R(N, root);
    }

    // функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual Node_m<K, T> *push(K k, T n) {
        auto *N = new Node_m<K, T>;
        N->setData(n);
        N->setKey(k);
        return push(N);
    }

    // удаление элемента
    virtual Node_m<K, T> *remove(K key, Node_m<K, T> *Current) {
        if (Current == NULL)
            return Current;

        if (key < Current->getKey())
            Current->setLeft(remove(key, Current->getLeft()));
        else if (key > Current->getKey())
            Current->setRight(remove(key, Current->getRight()));
        else if (Current->getLeft() != NULL && Current->getRight() != NULL) {
            Current->setKey(Min(Current->getRight())->getKey());
            Current->setRight(remove(Current->getKey(), Current->getRight()));
        }
        else {
            if (Current->getLeft() != NULL)
                Current = Current->getLeft();
            else if (Current->getRight() != NULL)
                Current = Current->getRight();
            else
                Current = NULL;
        }
        return Current;
    }

    // поиск по ключу такой же как в привате уже забыл зачем мне их 2...
    virtual Node_m<K, T> *FindKey(K key, Node_m<K, T> *Current) {
        //база рекурсии
        if (Current == NULL) return NULL;
        if (Current->getKey() == key) return Current;
        //база рекурсии
        if (Current->getKey() > key)
            return FindKey(key,Current->getLeft());
        if (Current->getKey() < key)
            return FindKey(key,Current->getRight());
    }

    virtual Node_m<K, T> *Min(Node_m<K, T> *Current = NULL) {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getLeft() != NULL)
            Current = Current->getLeft();
        return Current;
    }

    virtual Node_m<K, T> *Max(Node_m<K, T> *Current = NULL) {
        //максимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getRight() != NULL)
            Current = Current->getRight();
        return Current;
    }

    // а теперь самое веселое - подкласс итератора
    tree_iterator begin() {
        // получаем такой begin потому что при перечислении элементов должен быть обработан последний
        // лучше никогда не делать вывод элементов с конца, потому что не выводится самый левый)
        // но петрусевич не заметил хихиихих
        auto it = begin_->getParent();
        return it;
    }

    tree_iterator end() {
        auto it = end_;
        return it;
    }

    class tree_iterator {
    protected:
        Node_m<K, T> *ptr; // указатель на текущий эелмент
    public:
        tree_iterator() { ptr = NULL; }

        tree_iterator(Node_m<K, T> *p) { ptr = p; }

        tree_iterator(const tree_iterator &it) { ptr = it.ptr; }

        // нужны min и max такие же как в дереве для всяких перегруженных операторов
        Node_m<K, T> *Min(Node_m<K, T> *Current = NULL) {
            if (ptr == NULL) return NULL;
            if (Current == NULL)
                Current = ptr;
            while (Current->getLeft() != NULL)
                Current = Current->getLeft();
            return Current;
        }

        Node_m<K, T> *Max(Node_m<K, T> *Current = NULL) {
            if (ptr == NULL) return NULL;
            if (Current == NULL)
                Current = ptr;
            while (Current->getRight() != NULL)
                Current = Current->getRight();
            return Current;
        }

        const Node_m<K, T> operator++(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the Node_m");

            if (ptr->getRight() != NULL)
                ptr = Min(ptr->getRight());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Node_m<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() < ptr->getKey())
                    current = current->getParent();
                if (current->getKey() > ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Node_m<K, T> operator++() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the Node_m");

            if (ptr->getRight() != NULL)
                ptr = Min(ptr->getRight());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Node_m<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() < ptr->getKey())
                    current = current->getParent();
                if (current->getKey() > ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        const Node_m<K, T> &operator--(int) {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the Node_m");

            if (ptr->getLeft() != NULL)
                ptr = Max(ptr->getLeft());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Node_m<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() > ptr->getKey())
                    current = current->getParent();
                if (current->getKey() < ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Node_m<K, T> &operator--() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the Node_m");

            if (ptr->getLeft() != NULL)
                ptr = Max(ptr->getLeft());
            else {
                if (ptr->getParent() == NULL)
                    return *ptr;

                Node_m<K, T> *current = ptr->getParent();

                while (current->getParent() != NULL && current->getKey() > ptr->getKey())
                    current = current->getParent();
                if (current->getKey() < ptr->getKey())
                    ptr = current;
            }
            return *ptr;
        }

        Node_m<K, T> &operator*() {
            if (ptr == NULL)
                throw Iterator_Exception((string *) "iterator is not bound to the Node_m");
            return *ptr;
        }

        bool operator!=(const tree_iterator &it) { return ptr != it.ptr; }

        bool operator==(const tree_iterator &it) { return ptr == it.ptr; }
    };

    template<class K1, class T1>
    friend ostream &operator<< (ostream &out, Map_balanced<K1, T1> t);
};

// функция вывода, никто не знает, но на самом деле она с костылём
template<class K1, class T1>
ostream &operator<< (ostream &out, Map_balanced<K1 ,T1> Tree_) {
    auto it = Tree_.begin();
    while (it != Tree_.end()) {
        out << *it << " ";
        it++;
    }
    return out;
}

#endif //EL_MAP_BALANCED_H
