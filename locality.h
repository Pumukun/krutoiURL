#ifndef EL_LOCALITY_H
#define EL_LOCALITY_H

using namespace std;

class locality
{
public:
    std::string settlement_name;
    std::string type_of_sett_name;
    int area_code;
    int population_size;
    int area;
    locality()
    {
        settlement_name = ' ';
        type_of_sett_name = ' ';
        area_code = 0;
        population_size = 0;
        area = 0;
    }
    locality& operator=(const locality& it) {
        settlement_name = it.settlement_name;
        type_of_sett_name = it.type_of_sett_name;
        area_code = it.area_code;
        population_size = it.population_size;
        area = it.area;
        return *this;
    }
    friend ostream& operator<<(std::ostream& s, const locality& it);
    locality(std::string s_n, std::string t_of_s_n, int a_c, int p_s, int a)
    {
        settlement_name = s_n;
        type_of_sett_name = t_of_s_n;
        area_code = a_c;
        population_size = p_s;
        area = a;
    }
};

template<class T>
ostream& operator<<(ostream& ustream, Element<T>& obj) {
    ustream << obj.field;
    return ustream;
}

#endif