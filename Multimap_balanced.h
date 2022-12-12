#ifndef EL_MULTIMAP_BALANCED_H
#define EL_MULTIMAP_BALANCED_H

template<class K, class T>
class Multimap_Tree : public Map_balanced<K, T> {
protected:
public:
    // просто наследуем конструкторы
    Multimap_Tree() : Map_balanced<K, T>() {}

    Multimap_Tree(K k1, K k2) : Map_balanced<K, T>(k1, k2) {}

    Node_m<K, T> *push_R(Node_m<K, T> *n, Node_m<K, T> *Current) override {
        if (n == NULL) return NULL;
        if (Map_balanced<K, T>::root == NULL) {
            Map_balanced<K, T>::root = n;
            return n;
        }

        if (Current->getKey() > n->getKey()) {
            //идем влево
            if (Current->getLeft() != NULL)
                Current->setLeft(Multimap_Tree<K, T>::push_R(n, Current->getLeft()));
            else
                Current->setLeft(n);
            Current->getLeft()->setParent(Current);
        }
        // push() отличается тем что тут <= то есть равные элементы просто добавляем вправо,
        // но это очень опасно, потому что не всегда все добавляется правильно иногда он уходит в бесконечную рекурсию,
        // потом в мейне я вставлю рабочий вариант добавления
        if (Current->getKey() <= n->getKey()) {
            //идем вправо
            if (Current->getRight() != NULL)
                Current->setRight(Map_balanced<K, T>::push_R(n, Current->getRight()));
            else
                Current->setRight(n);
            Current->getRight()->setParent(Current);
        }

        if (Current != NULL)
            return Map_balanced<K, T>::Balance(Current);

        return n;
    }

    Node_m<K, T> *push(K k, T n) override {
        auto *N = new Node_m<K, T>(k, n);
        return Multimap_Tree<K, T>::push_R(N, Map_balanced<K, T>::root);
    }
    // единственное что петрус требует это возвращать не один элемент а несколько если по одинаковым ключам их несколько
    Node_m<K, T> *operator[](K key) {
        Node_m<K, T> *result;
        result = Map_balanced<K, T>::FindKey(key, Map_balanced<K, T>::root);
        return result;
    }
};
// тут тоже забавный принт :)
template<class K, class T>
void print(Multimap_Tree<K, T> Tree) {
    auto it = Tree.begin();
    while (it != Tree.end()) {
        cout << *it << " ";
        it++;
    }
}

#endif //EL_MULTIMAP_BALANCED_H
