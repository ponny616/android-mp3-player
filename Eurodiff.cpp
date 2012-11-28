// Eurodiff.cpp: ���������� ����� ����� ��� ����������� ����������.
// origin

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
// ����� �� ������ �����
class Cities
{

public:
    unsigned int coins;
    unsigned int recipientCount;

unsigned int portions;
};
// ������������ ���������� �������
Cities Euro[40+2][40+2];
unsigned int recipientCount[40+2][40+2];


class �ountry
{
public:
        std::string name; // �������� ������
        unsigned int X1; // ����������
    unsigned int X2;
        unsigned int Y1;
    unsigned int Y2;
        int DayMax;   // ���������� ���� ��� ���������� ��������
        bool Complete; // ���� ����������
        // ���������� ��������� ��� ��������� ����������
        bool operator<(const �ountry j) const
        {
                if(DayMax == j.DayMax)
                        return(( strcmp(name.c_str(), j.name.c_str())<0 ) ? true : false);
                return (DayMax<j.DayMax);

        }


};

/**
 * ������� ��� ��������� for_each ��� ��������� � ������ ������ ������
 */
void SubcoinofSity(�ountry & l_country)
{

    for(unsigned int x = l_country.X1; x <= l_country.X2; ++x)
                for(unsigned int y = l_country.Y1; y <=l_country.Y2; ++y)
                {
                    Euro[x][y].portions = Euro[x][y].coins/1000;

                    Euro[x][y].coins-= Euro[x][y].portions*recipientCount[x][y];
                }
}

/**
 * ������� ��� ��������� for_each ��� ���������� ������ ������ �������
 */
void AddcointoSity(�ountry & l_country)
{
    for(unsigned int x = l_country.X1; x <= l_country.X2; ++x)
                for(unsigned int y = l_country.Y1; y <=l_country.Y2; ++y)
                {
                    Euro[x][y].coins+= Euro[x+1][y].portions + Euro[x-1][y].portions
                            + Euro[x][y+1].portions+ Euro[x][y-1].portions;
                }

}

/**
 * ������� ��� ��������� for_each ��� �������� ���������� ������� ��� ������� ������
 */
void recipientCountmake(�ountry & l_country)
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
 * ������� ��� ��������� for_each ��� ���������� ���������� ������� ��� ������� ������
 */
void initCountries(�ountry & l_country)
{

        l_country.Complete = false;

}

/**
 * ������ ������ �� ����� ��� ��������� for_each
 */
void print(�ountry & l_country)
{
        std::cout << l_country.name <<"  "<< l_country.DayMax <<std::endl;

}
/**
 *
 * @param in           ������� ����� �� �����
 * @param countryCount ���������� �����
 */

void processCase(istream& in, unsigned int countryCount)
{
// ��������� ���������� ��� ���������� �������
        �ountry Temp;
        Temp.DayMax = 0;
        Temp.Complete = false;
        // ������ �����
        std::vector<�ountry> countries;
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



                    // ��������� ������������� ����� � ������������� �������� ����� ������
                          std::for_each(countries.begin(),countries.end(),initCountries);

                          for(unsigned int x = countries[i].X1; x <= countries[i].X2; ++x)
                            for(unsigned int y = countries[i].Y1; y <= countries[i].Y2; ++y)
                                  {

                                          Euro[x][y].coins = 1000000;

                                  }

							// ��������, ������� ��������� ��� ������ ����������� ��������
							
                                    do
                                    {


                                           // �������� ��������� �� ������ �������� ������� ����
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
                                                                  // ���� ���� �� � ����� ������ ��� �����, �� ������ ������ �� ���������
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
															// ������ ���������� ����, ���� ��������������� ���������� ���� ���� ������
															// �� ��������, �� �������� ������ ����������
                                                          countries[c].DayMax = (countries[c].DayMax>day)?countries[c].DayMax:day;
                                                          }

                                                   }
                                    }
                                                                 // ����������� ���������� �����, ������� ���������� �������� ������� � �� ����������
                                                                               std::for_each(countries.begin(),countries.end(),SubcoinofSity);


                                                                 // ���������� � ������ ����� ������������ ���������� ����� �������
                                                                               std::for_each(countries.begin(),countries.end(),AddcointoSity);
                                            // �������� ��� ������ ��������� �� ����������� ��������
                                          if(Count == countries.size())
                                                  break;

                                    }
                                    while(++day);
        }
// �������� STL ��� ����������
        std::sort(countries.begin(),countries.end());
        // �������� ������ �� ����� ������ ������ ������
        std::for_each(countries.begin(),countries.end(),print);



}


int main(int argc, char *argv[])
{

// �������� ����� � �����
        std::string data = argv[0];
        data.erase(data.end()-12,data.end()); // ��������� �������� ���������
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