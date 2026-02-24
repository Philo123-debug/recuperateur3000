#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <regex>
#include <chrono>
#include <time.h>
#include <thread>

using namespace std;

void espace(){
    cout << "=============================================" << endl;
}

void extract(){
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
    _pclose(pipe2);
    // cout << liste;
    cout << pile.top() << " = " << liste << endl;
    ofstream fichierentrer("data.txt", ios::app);
    fichierentrer << pile.top() << " = " << liste << endl;
    pile.pop();
    this_thread::sleep_for(chrono::milliseconds(40));
    } while (!pile.empty());
}