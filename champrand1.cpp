// champrand1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

enum dmg_type { heavy_ad, ad, ap, heavy_ap, hybrid, truedmg, supp};
enum health_type { tank, bruiser, squishy };
enum rol { top, jungle, mid, adc, support };

struct champ {
    string name;
    dmg_type damage;
    health_type tankiness;
    vector<bool> posiciones;
};

//implementar com map<champname, champinfo>?
vector <champ> roster;
int allchamps;

int rol_to_enum(string llegit) {
    if (llegit == "top") return 0;
    if (llegit == "jgl") return 1;
    if (llegit == "mid") return 2;
    if (llegit == "adc") return 3;
    if (llegit == "sup") return 4;
    return -1;
}

bool llegeix_campions(string filename) {

    //hay que implementar que dmg y health sean vector bool solo k me da pereza ahora mismo.
    //un champ puede tener multiples builds (blitz hard ap squishy // normal ap tank incluso ad bruiser somehow broken champ)
    //tambien caldria implementar algo k relacione las builds(si blitz va ap k el juego reconozca k es squishy)
    ifstream fin;

    //Cada linea ha de contener esta info separada por espacios: 
    //nombre del champ
    //dmg type - had 1,ad 2,ap 3,hap 4,hyb 5,true 6, support 7
    //health type - tk 1 br 2 sq 3
    // numero de rols del champ
    //rol - top jgl mid adc sup   (pot tenir mes d'un rol) (separats per un espai)

    fin.open(filename);
    if (!fin.is_open()) return false;

    //map con <nombre, posicion en el vector> no estaria bien?
    //serviria para poder poner compañeros con buena o mala sinergia para
    //tocar los pesos a la hora de randomizar
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
            temp.damage = supp;
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

        
        for (int i = 0; i < 5; ++i) {
            if (rol[i] == '1') temp.posiciones.push_back(true);
            else temp.posiciones.push_back(false);
        }

        roster.push_back(temp);

    }
    allchamps = roster.size();
    return true;
}


void escriu_rol_pool(int r) { //r -> 0-4   top-supp
    int champ_counter = 0;
    switch (r) {
        case 0:
            cout << "all top champs:" << endl;
            break;
        case 1:
            cout << "all jungle champs:" << endl;
            break;
        case 2:
            cout << "all mid champs:" << endl;
            break;
        case 3:
            cout << "all adc champs:" << endl;
            break;
        case 4:
            cout << "all support champs:" << endl;
            break;
    }
    for (int i = 0; i < allchamps; ++i) {
        if (roster[i].posiciones[r]) {
            cout << roster[i].name << endl;
            ++champ_counter;
        }
    }
    cout << champ_counter << " champs" << endl << endl;
}

void comp_maker() {//prioritat amb vector de punters a sets?

    vector <pair <set <string>::iterator, int>> ordre;
    set <string> c_top;
    set <string> c_jgl;
    set <string> c_mid;
    set <string> c_adc;
    set <string> c_sup;

    for (int i = 0; i < allchamps; ++i) {
        if (roster[i].posiciones[0]) c_top.insert(roster[i].name);
        if (roster[i].posiciones[1]) c_jgl.insert(roster[i].name);
        if (roster[i].posiciones[2]) c_mid.insert(roster[i].name);
        if (roster[i].posiciones[3]) c_adc.insert(roster[i].name);
        if (roster[i].posiciones[4]) c_sup.insert(roster[i].name);
    }
    ordre.push_back(make_pair(c_top.begin(), c_top.size()));
    ordre.push_back(make_pair(c_jgl.begin(), c_jgl.size()));
    ordre.push_back(make_pair(c_mid.begin(), c_mid.size()));
    ordre.push_back(make_pair(c_adc.begin(), c_adc.size()));
    ordre.push_back(make_pair(c_sup.begin(), c_sup.size()));

    cout << "di en que orden quieres que se generen los picks. top/jgl/mid/adc/sup" << endl;
    string allegir;
    string equip[5];
    srand(time(NULL));

    for (int i = 0; i < 5; ++i) {
        cin >> allegir;
        int omplir = rol_to_enum(allegir);
        int aleatori = rand() % ordre[omplir].second;
        for (int j = 0; j < aleatori; ++j) ++ordre[omplir].first;
        equip [omplir] = *(ordre[omplir].first);
        c_top.erase(equip[omplir]);
        c_jgl.erase(equip[omplir]);
        c_mid.erase(equip[omplir]);
        c_adc.erase(equip[omplir]);
        c_sup.erase(equip[omplir]);
    }
    cout << "top: " << equip[0] << endl << "jungle: " << equip[1] << endl << "mid: " << equip[2] << endl
         << "adc: " << equip[3] << endl << "support: " << equip[4] << endl << endl;

    
}



int main(){   
   

    if (!llegeix_campions("pool.txt")) {
        cout << "el archivo no se ha podido abrir" << endl;
        exit(1);
    }
    string lectura = "";
    cin >> lectura;
    while (lectura != "close") {
        if (lectura == "llistar") {
            cin >> lectura;
            int enviar = rol_to_enum(lectura);
            if (enviar != -1) escriu_rol_pool(enviar);
            else cout << "input erroneo: escribir 'llistar top/jgl/mid/adc/sup'" << endl << endl; 
        }

        else if (lectura == "comp") {
            comp_maker();
        }



        cin >> lectura;
    }
      


}
