#include <iostream>

#include "Element.h"
#include "LinkedListParent.h"
#include "IteratedLinkedList.h"

#include "D.h"
#include "DD.h"

#include "Node_m.h"
#include "Map_balanced.h"

#include "Multimap_balanced.h"

#include "sportsman.h"
#include "locality.h"

using namespace std;

int main() {
    /*тут пишешь просто работу с контейнером Map_balanced как и в прошлых практиках
     * что-то примерно такое // Спортсмены
    Sportsman
            sp1("Gregory", "Demchenko", "Russia", "Voleyball", 19, 2),
            sp2("Alexey", "Avgust", "Belarus", "Tennis", 21, 4),
            sp3("Xiao", "Lin", "China", "Skiing", 27, 9),
            sp4("John", "Lenon", "Britain", "Football", 32, 4),
            sp5("Ayanami", "Rei", "Japan", "Archery", 14, 10),
            sp6("Polnaref", "Jian Piere", "France", "Athletics", 18, 8),
            sp7("Peter", "Lindemann", "Germany", "Tennis", 38, 16),
            sp8("Glen", "Quagmire", "USA", "Athletics", 30, 6),
            sp9("Mathew", "Bellamy", "Britain", "Voleyball", 27, 6),
            sp10("Anatoly", "Annin", "Russia", "Chess", 41, 22);

    // Имена спортсменов
    string
        name1 = "Gregory Demchenko",
        name2 = "Alexey Avgust",
        name3 = "Xiao Lin",
        name4 = "John Lenon",
        name5 = "Ayanami Rei",
        name6 = "Polnaref Jian Piere",
        name7 = "Peter Lindemann",
        name8 = "Glen Quagmire",
        name9 = "Mathew Bellamy",
        name10 = "Anatoly Annin";

    // Создаем наше дерево передавая элемент begin_ и end_
    Map<string , Sportsman> T("AAAAAAAAAAAAAAAA", "ZZZZZZZZZZZZZZZZ");

    T.push(name1, sp1);
    T.push(name2, sp2);
    T.push(name3, sp3);
    T.push(name4, sp4);
    T.push(name5, sp5);
    T.push(name6, sp6);
    T.push(name7, sp7);
    T.push(name8, sp8);
    T.push(name9, sp9);
    T.push(name10, sp10);

    // Вывод дерева
    print(T);

    // Удаляем элемент по ключу name7 = "Peter Lindemann"
    T.Remove(name7, T.getRoot());
    cout << "Дерево после удаления name7 = \"Peter Lindemann\"\n";
    print(T);

    // Находим элемент c ключом name3 = "Xiao Lin"
    Element<string , Sportsman> *el = T.FindKey(name3, T.getRoot());
    cout << "\nЭлемент name3 = \"Xiao Lin\"\n\n" << *el << endl;
    return 0;*/


    //-----------------------------------------------------------------------------------

    // вот пример 2.5
    /*Multimap_Tree<string, Sportsman> mp("zzzzzzzzzzz", "aaaaaaaaaa");

    mp.push(name1, sp1);
    mp.push(name2, sp2);
    mp.push(name3, sp3);
    mp.push(name4, sp4);
    mp.push(name5, sp5);
    // Добавим спортсмена с ключом который уже существует
    mp.push(name4, sp4);
    mp.push(name6, sp6);
    mp.push(name7, sp7);
    mp.push(name8, sp8);
    mp.push(name9, sp9);
    mp.push(name10, sp10);

    // Поиск по ключу используя []
    cout << "\n---------\n" << *mp["John Lenon"] << endl;

    print(mp);

    D_Stack<Sportsman> result;

    result.push(mp[name1]->getData());
    result.push(mp[name2]->getData());
    result.push(mp[name3]->getData());
    result.push(mp[name4]->getData());
    result.push(mp[name5]->getData());
    result.push(mp[name6]->getData());
    result.push(mp[name7]->getData());
    result.push(mp[name8]->getData());
    result.push(mp[name9]->getData());
    result.push(mp[name10]->getData());

    cout << result;*/


    return 0;
}
