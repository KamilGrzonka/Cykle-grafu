#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;
const int N = 100000;
/**@param ind zmienna pomocnicza sluzaca do kontroli kieyd dana funckja ma wyswietlic zawartosc na ekranie, a kiedy nie (sluzy to do zachowania porzadku na ekranie konsli)*/
int ind;			//zmienne pomocniecze sluzaczego do tereminowanie kiedy dana funckja ma wyswietlac zawartosc na ekranie, a kiedy nie (sluzy to do zachowania porzadku na ekranie konsoli)
/**@param ind2 zmienna pomocnicza sluzaca do kontroli kieyd dana funckja ma wyswietlic zawartosc na ekranie, a kiedy nie (sluzy to do zachowania porzadku na ekranie konsli)*/
int ind2 = 1;
//zrobic dokumnetacje w doxygenie
/**graph przechowuje informacje odczytane z pliku na temat wierzcholkow i ich relacji*/
unordered_map<int, vector<int>> graph;
/**cycles przechowuje informacje na temat cykli*/
vector<vector<int>> cycles;
/**Funkcja dfs_cycle jest odpowiedzialna za znaleznie wszystkich cykli w grafie skierowanym, wykorzystuje do tego algorytm przeszukiwania w glab dfs
@param u wierzcholek poczatkowy 
@param p rodzic wierzcholka
@param color[] tablica kolorow
@param parent [] tablica rodzicow
@param cyclenumber liczba znalezionych cykli*/
void dfs_cycle(int u, int p, int color[], int parent[], int& cyclenumber);
/**Funkcja printCycles jest odpowiedzialna za wyswietlenie znalezionych cykli na ekranie konsoli oraz za poinformowanie o ewentualnej acyklicznosci grafu*/
void printCycles(int& cyclenumber);
/**Funkcja readData jest odpowiedzialna za odczytanie danych na temat grafu z pliku tekstowego*/
void readData(const string& fileName, unordered_map<int, vector<int>>& graph);