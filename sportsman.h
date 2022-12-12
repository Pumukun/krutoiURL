#ifndef EL_SPORTSMAN_H
#define EL_SPORTSMAN_H

class sportsman
{
public:
    int count_medals;
    int age;
    std::string surname;
    std::string name;
    sportsman()
    {
        count_medals = 0;
        age = 0;
        surname = " ";
        name = " ";
    }
    sportsman& operator=(const sportsman& it)
    {
        count_medals = it.count_medals;
        age = it.age;
        surname = it.surname;
        name = it.name;
        return *this;
    }
    sportsman(int cm, int a, std::string sn, std::string n)
    {
        count_medals = cm;
        age = a;
        surname = sn;
        name = n;
    }
    friend ostream& operator<<(std::ostream& s, const sportsman& it);
};

ostream& operator<<(ostream& s, const sportsman& v)
{
    s << v.count_medals << " " << v.age << " " << v.surname << " " << v.name << endl;
    return s;
}

bool sort_(sportsman s1, sportsman s2)
{
    if (s1.count_medals != s2.count_medals)
    {
        return s1.count_medals < s2.count_medals;
    }
    if (s1.age != s2.age)
    {
        return s1.age < s2.age;
    }
    if (s1.surname != s2.surname) {
        int i = 0;
        while (i < s1.surname.size() || i < s2.surname.size())
        {
            if (s1.surname[i] != s2.surname[i])
                return s1.surname[i] > s2.surname[i];
            i++;
        }
    }
    if (s1.name != s2.name) {
        int i = 0;
        while (i < s1.name.size() || i < s2.name.size())
        {
            if (s1.name[i] != s2.name[i])
                return s1.name[i] > s2.name[i];
            i++;
        }
    }
}

#endif //EL_SPORTSMAN_H
