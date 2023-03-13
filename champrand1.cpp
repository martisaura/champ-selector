// champrand1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

enum dmg_type { heavy_ad, ad, ap, heavy_ap, hybrid, truedmg, support};
enum health_type { tank, bruiser, squishy };
enum rol { top, jungle, mid, adc, support };

struct champ {
    string name;
    dmg_type damage;
    health_type tankiness;
    vector<bool> posiciones;
};

vector <champ> roster;

int main()
{   //hay que implementar que dmg y health sean vector bool solo k me da pereza ahora mismo.
    //un champ puede tener multiples builds (blitz hard ap squishy // normal ap tank incluso ad bruiser somehow broken champ)
    //tambien caldria implementar algo k relacione las builds(si blitz va ap k el juego reconozca k es squishy)
    ifstream fin;

    //Cada linea ha de contener esta info separada por espacios: 
    //nombre del champ
    //dmg type - had 1,ad 2,ap 3,hap 4,hyb 5,true 6, support 7
    //health type - tk 1 br 2 sq 3
    // numero de rols del champ
    //rol - top jgl mid adc sup   (pot tenir mes d'un rol) (separats per un espai)

    fin.open("pool.txt");
    if (!fin.is_open()) cout << "reetar" << endl;



    string nom;
    string rol(5, false);
    int dano, vida;
    while (fin >> nom >> dano >> vida >> rol) {


        champ temp;
        temp.name = nom;

        switch (dano) {
            case 1:
                temp.damage = heavy_ad;
                break;
            case 2:
                temp.damage = ad;
                break;
            case 3:
                temp.damage = ap;
                break;
            case 4:
                temp.damage = heavy_ap;
                break;
            case 5:
                temp.damage = hybrid;
                break;
            case 6:
                temp.damage = truedmg;
                break;
            case 7:
                temp.damage = support;
                break;
        }

        switch (vida) {
            case 1:
                temp.tankiness = tank;
                break;
            case 2:
                temp.tankiness = bruiser;
                break;
            case 3:
                temp.tankiness = squishy;
                break;
        }

        if (rol[0] == '1') temp.posiciones.push_back(top);
        else if (rol[1] == '1')  temp.posiciones.push_back(jungle);
        else if (rol[2] == '1')  temp.posiciones.push_back(mid);
        else if (rol[3] == '1')  temp.posiciones.push_back(adc);
        else if (rol[4] == '1') temp.posiciones.push_back(support);

        roster.push_back(temp);

    }

    for (int i = 0; i < roster.size(); ++i) cout << roster[i].name << endl;
    cout << roster.size() << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
