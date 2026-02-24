#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <regex>
#include <chrono>
#include <time.h>
#include <thread>
#include "fonction.cpp"
#include "api.h"
/*
popen =
- fgets
*/

using namespace std;

// fonction de récupération automatique

int main() {
    // intégration des acsents ==>
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // recupérateur 300 ==>
    string choix;
    do
    {    
        system("color 4");
        string sortie;
        string operateur;
        cout << "" << endl
        << ",,,,,,,,,,,,,,,,,,,,,,,,$$$$" << endl
        << ",,,,,,,,,,,,,,,,,,,,,,,,$$$$" << endl
        << ",,,,,,,,,,,$$$$$$$$$$$$$$$$$" << endl
        << ",,,,,,,$$$$$$$$$$$$$$$$$$$$$$" << endl
        << ",,,,,$$$$$$$,,,,,$$$$,,,,$$$$$$$$" << endl
        << ",,,$$$$$$,,,,,,,,,$$$$,,,,,,,,$$$$$$$" << endl
        << ",,$$$$$$,,,,,,,,,,$$$$,,,,,,,,,,$$$$$$" << endl
        << ",,$$$$$$,,,,,,,,,,$$$$" << endl
        << ",,$$$$$$,,,,,,,,,,$$$$" << endl
        << ",,,$$$$$$,,,,,,,,,$$$$" << endl
        << ",,,,$$$$$$$$,,,,$$$$" << endl
        << ",,,,,,$$$$$$$$$$$$$$$" << endl
        << "V3.2.6 by PhilØ" << endl
        << "=============================================" << endl;
        cout << "(ecrire wifi/wifiauto) Bienvenue dans le récupérateur 3000 = ";
        cin >> operateur;
        system("cls;")
        if (operateur == "wifi") {
            bool verif = true;
            do
            {
            espace();
            system("netsh wlan show profile | findstr \"utilisateurs\"");
            string nomwifi;
            cout << "Nom du Wifi = ";
            cin.ignore();
            getline(cin, nomwifi);
            espace();
            string commande = "netsh wlan show profile name=\"" + nomwifi +
                            "\" key=clear | findstr \"Contenu\"";
            int result = system(commande.c_str());
            (void)result;
            ofstream fichierentrer("data.txt");
            fichierentrer << nomwifi << " = " << result;
            espace();
            if(result == 1){
                cout << "/!\\ entrer invalide, vérifier les majuscules, %\\ interdit" << endl;
                verif = false;
            }else if (result == 0){}
            
            } while (verif == false);
        }else if(operateur == "wifiauto"){
            extract();
            cout << "Tout a été enregistrer dans le fichier : data.txt" << endl;
        }
        cout << "Nouvelle entrer (OUI/NON) ? = ";
        cin >> choix;
        if(choix == "oui"){
            system("clear");
        }
        } while (choix == "oui");
        return 0;
    }