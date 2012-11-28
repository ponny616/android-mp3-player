// Eurodiff.cpp: определяет точку входа для консольного приложения.
// origin

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
// класс на каждый город
class Cities
{

public:
    unsigned int coins;
    unsigned int recipientCount;

unsigned int portions;
};
// максимальное количество городов
Cities Euro[40+2][40+2];
unsigned int recipientCount[40+2][40+2];


class Сountry
{
public:
        std::string name; // название страны
        unsigned int X1; // координаты
    unsigned int X2;
        unsigned int Y1;
    unsigned int Y2;
        int DayMax;   // количество дней для заполнения монетами
        bool Complete; // флаг заполнения
        // перегрузка оператора для алгоритма сортировки
        bool operator<(const Сountry j) const
        {
                if(DayMax == j.DayMax)
                        return(( strcmp(name.c_str(), j.name.c_str())<0 ) ? true : false);
                return (DayMax<j.DayMax);

        }


};

/**
 * функция для алгоритма for_each для вычитания в каждом городе монеты
 */
void SubcoinofSity(Сountry & l_country)
{

    for(unsigned int x = l_country.X1; x <= l_country.X2; ++x)
                for(unsigned int y = l_country.Y1; y <=l_country.Y2; ++y)
                {
                    Euro[x][y].portions = Euro[x][y].coins/1000;

                    Euro[x][y].coins-= Euro[x][y].portions*recipientCount[x][y];
                }
}

/**
 * функция для алгоритма for_each для добавления городу монеты соседей
 */
void AddcointoSity(Сountry & l_country)
{
    for(unsigned int x = l_country.X1; x <= l_country.X2; ++x)
                for(unsigned int y = l_country.Y1; y <=l_country.Y2; ++y)
                {
                    Euro[x][y].coins+= Euro[x+1][y].portions + Euro[x-1][y].portions
                            + Euro[x][y+1].portions+ Euro[x][y-1].portions;
                }

}

/**
 * функция для алгоритма for_each для загрузки количества соседей для каждого города
 */
void recipientCountmake(Сountry & l_country)
{

    for(unsigned int x = l_country.X1; x <= l_country.X2; ++x)
                for(unsigned int y = l_country.Y1; y <=l_country.Y2; ++y)
                {
                        recipientCount[x-1][y]++;
                        recipientCount[x+1][y]++;
                        recipientCount[x][y+1]++;
                        recipientCount[x][y-1]++;
                }
}

/**
 * функция для алгоритма for_each для заполнения количества соседей для каждого города
 */
void initCountries(Сountry & l_country)
{

        l_country.Complete = false;

}

/**
 * печать данных на экран для алгоритма for_each
 */
void print(Сountry & l_country)
{
        std::cout << l_country.name <<"  "<< l_country.DayMax <<std::endl;

}
/**
 *
 * @param in           входной поток от файла
 * @param countryCount количество стран
 */

void processCase(istream& in, unsigned int countryCount)
{
// временная переменная для наполнения вектора
        Сountry Temp;
        Temp.DayMax = 0;
        Temp.Complete = false;
        // вектор стран
        std::vector<Сountry> countries;
    for(unsigned int id=0; id<countryCount; id++) {

                in >> Temp.name >> Temp.X1 >> Temp.Y1 >> Temp.X2>> Temp.Y2;
                countries.push_back(Temp);
         }
      memset(recipientCount, 0, sizeof(recipientCount));
      std::for_each(countries.begin(),countries.end(),recipientCountmake);

        for(unsigned int i = 0; i < countries.size(); ++i)
        {

          int day = 0;
          unsigned int Count = 0;

          memset(Euro, 0, sizeof(Euro));



                    // обнуления заполненности стран и инициализация монетами одной страны
                          std::for_each(countries.begin(),countries.end(),initCountries);

                          for(unsigned int x = countries[i].X1; x <= countries[i].X2; ++x)
                            for(unsigned int y = countries[i].Y1; y <= countries[i].Y2; ++y)
                                  {

                                          Euro[x][y].coins = 1000000;

                                  }

							// алгоритм, который заполняет все страны однотипными монетами
							
                                    do
                                    {


                                           // проверка заполнена ли страна монетами данного типа
                                           // for(unsigned int c = 0; c < countries.size(); ++c)
                                                                 for(unsigned int c = 0; c < countries.size(); ++c)
                                                                 {
                                                  if(!countries[c].Complete)
                                                   {
                                                          countries[c].Complete = true;
                                                     for(unsigned int x = countries[c].X1; x <= countries[c].X2; ++x)
                                                     {
                                                          for(unsigned int y = countries[c].Y1; y <= countries[c].Y2; ++y)
                                                          {
                                                                  // если хотя бы в одном городе нет монет, то значит страна не завершена
                                                                  if(!Euro[x][y].coins)
                                                                  {
                                                                          countries[c].Complete = false;

                                                                          break;

                                                                  }


                                                          }
                                                          if(!countries[c].Complete)
                                                                                                  break;
                                                     }
                                                          if(countries[c].Complete)
                                                          {
                                                          Count++;
															// запись количества дней, если предварительное количество дней было больше
															// за нынешнее, то остается старое количество
                                                          countries[c].DayMax = (countries[c].DayMax>day)?countries[c].DayMax:day;
                                                          }

                                                   }
                                    }
                                                                 // определения количества монет, которые передаются соседним городам с их вычитанием
                                                                               std::for_each(countries.begin(),countries.end(),SubcoinofSity);


                                                                 // добавление в каждый город необходимого количества монет соседей
                                                                               std::for_each(countries.begin(),countries.end(),AddcointoSity);
                                            // проверка все страны заполнены ли однотипными монетами
                                          if(Count == countries.size())
                                                  break;

                                    }
                                    while(++day);
        }
// алгоритм STL для сортировки
        std::sort(countries.begin(),countries.end());
        // Алгоритм вывода на экран данных каждой страны
        std::for_each(countries.begin(),countries.end(),print);



}


int main(int argc, char *argv[])
{

// открытие файла в поток
        std::string data = argv[0];
        data.erase(data.end()-12,data.end()); // вычитание названия программы
        data+="in.txt";
        std::cout<<data<<std::endl;
        ifstream in(data.c_str());
    if( !in.is_open() ) {
        cerr << "ERROR: Can't open file." << endl;
        return 1;
    }

    unsigned int countryCount;

    in >> countryCount;
    for(unsigned int i=1; countryCount > 0; i++) {
        cout << "Case Number " << i << endl;
        processCase(in, countryCount);
        in >> countryCount;
    }

    getchar();

    return 1;
   }