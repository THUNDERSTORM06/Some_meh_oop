#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Carte {
	std::string titlu;
	std::string autor;
	std::string gen;
	int an;
public:
	Carte(const string t, const string aut, const string g, int a) :titlu{ t }, autor{ aut }, gen{ g }, an{ a }{}

	/*Pet(const Pet& ot):type{ ot.type }, species{ ot.species }, price{ ot.price } {
		cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}*/


	string getTitlu() const {
		return titlu;
	}
	string getAutor() const {
		return autor;
	}
	string getGen() const {
		return gen;
	}
	int getAn() const noexcept {
		return an;
	}
};
/*
Compara dupa titlu
returneaza true daca c1.titlu e mai mic decat c2.titlu
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);

/*
Compara dupa autor
returneaza true daca c1.autor e mai mic decat c2.autor
*/
bool cmpAutor(const Carte& c1, const Carte& c2);

