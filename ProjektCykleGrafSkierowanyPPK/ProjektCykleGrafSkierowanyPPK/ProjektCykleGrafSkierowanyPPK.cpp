#include "MainHeader.h"
// funkcja do wykrywania cykli
void dfs_cycle(int u, int p, int color[], int parent[], int& cyclenumber)
{
    // juz całkowicie odwiedzony wierzcholek
    if (color[u] == 2) {
        return;
    } 
    // wierzcholek widziany, ale nie calkowice odwiedzony, cykl wykryty
    // "backtrack" w oparciu o rodzica w celu odnalezienia cyklu
    // backtracking -> algorytm z nawrotami
    if (color[u] == 1) {
        vector<int> v;
        cyclenumber++;
        int cur = p;
        v.push_back(cur);
        while (cur != u) {
            cur = parent[cur];
            v.push_back(cur);
        }
        cycles.push_back(v);
        return;
    }
    parent[u] = p;

    // czesciowo odwiedzony
    color[u] = 1;

    // dfs na grafie
    for (int v : graph[u]) {
        // jesli nie zostal odwiedzony
        if (v == parent[u]) {
            continue;
        }
        dfs_cycle(v, u, color, parent, cyclenumber);
    }
    // calkowicie odwiedzony
    color[u] = 2;
}
// funkcja do wypisywania cykli na ekranie
void printCycles(int& cyclenumber)
{
    if (ind == 1) {
        if (cyclenumber != 0) {
            for (int i = 0; i < cyclenumber; i++) {
                cout << "Cykl." << i + 1 << ": ";
                for (int x : cycles[i])
                    cout << x << " ";
                cout << endl;
            }
        }
        else {
            cout << "Graf jest acykliczny" << endl;
        }
    }
}

// funkcja do odczytu danych z pliku, z uwzglednieniem zalozenie do tego jak dane w pliku maja wygladac
void readData(const string& fileName, unordered_map<int, vector<int>>& graph) {
    ifstream input(fileName);
    if (!input.is_open()&& ind2 == 1) {
        ind = 0;
        cout << "Nie mozna otworzyc pliku: " << fileName << endl;
        cout << "Jesli pod dwukropku nie widzisz nazwy pliku to sprawdz czy uzyles poprawnych argumentow. Uzyj argumentu -h by uzyskac pomoc" << endl;
        return;
    }
    string line;
    while (getline(input, line)) {
        int u, v;
        char op;
        ind = 1;
        stringstream iss(line);
        iss >> u >> op >> v;

        if (op == '>') {
            graph[u].push_back(v);
        }
        else if (op == '<') {
            graph[v].push_back(u);
        }
        else {
            cout << "Niepoprawny znak operatora: " << op << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    string plikwejscie;
    for (int i = 0; i < argc; i++) {
        string spr = argv[i];
        if (spr == "-i") plikwejscie = argv[i + 1];
        else if (spr == "-h") { 
            ind2 = 0;
            cout << "poprawna struktura komendy to: nazwa_programu.exe -i nazwa_pliku_tekstowego.txt" << endl; }
    }
    readData(plikwejscie, graph); // wczytanie danych z pliku
    int color[N];  //tablica kolorow potrzebnych do kolorowania grafu
    int parent[N]; //tablica przechowujaca rodzica wierzcholka
    int cyclenumber = 0; //liczba znalezionych cykli
    dfs_cycle(1, 0, color, parent, cyclenumber); //wywolanie funkcji dfs w celu oznaczenia cykli
    printCycles(cyclenumber); //wypisanie cykli na ekranie

    /*
    Kilka przykladowych kombinacji na, ktorych testowane dzialanie programu
    1 > 2
    2 < 3
    3 > 4
    2 > 4
    1 < 3
    4 > 5
    5 > 1
    5 > 2
    Prawidlowa odpowiedz:
    Cykl.1: 5 4 2 1
    Cykl.2: 5 4 2
    Uzyskany wynik:
    Cykl.1: 5 4 2 1
    Cykl.2: 5 4 2
    

    1 > 2
    2 > 3
    3 > 4
    1 < 3
    4 > 1
    Prawidlowa odpowiedz:
    Cykl.1: 4 3 2 1
    Cykl.2: 3 2 1
    Uzyskany wynik:
    Cykl.1: 4 3 2 1
    Cykl.2: 3 2 1


    1 > 2
    2 > 3
    3 > 4
    1 < 3
    4 > 6
    1 < 6
    5 < 4
    5 > 2
    Prawidlowa odpowiedz:
    Cykl.1: 6 4 3 2 1
    Cykl.2: 5 4 3 2
    Cykl.3: 3 2 1
    Uzyskany wynik:
    Cykl.1: 6 4 3 2 1
    Cykl.2: 5 4 3 2
    Cykl.3: 3 2 1


    1 > 2
    2 > 3
    3 > 4
    1 > 4
    Prawidlowa odpowiedz:
    Graf jest acykliczny
    Uzyskany wynik:
    Graf jest acykliczny
    */
}