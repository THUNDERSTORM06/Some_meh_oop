#pragma once
#include "Carte.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class CarteRepo {
	vector<Carte> all;
	/*
	metoda privata verifica daca exista deja c in repository
	*/
	bool exist(const Carte& c) const;
public:
	CarteRepo() = default;
	//nu permitem copierea de obiecte
	CarteRepo(const CarteRepo& ot) = delete;
	/*
	Salvare pet
	arunca exceptie daca mai exista o carte cu acelasi titlu si autor
	*/
	void store(const Carte& c);

	/*
	Cauta
	arunca exceptie daca nu exista carte
	*/
	const Carte& find(string type, string species) const;

	/*
	returneaza toate cartile salvate
	*/
	const vector<Carte>& getAll() const noexcept;

	/*
	Modifica o carte sau arunca exceptie
	*/
	void modify(const Carte& c, int poz);

	/*
	Sterge o carte sau arunca exceptie
	*/
	void sterge(int poz);

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class CarteRepoException {
	string msg;
public:
	CarteRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const CarteRepoException& ex);
};

ostream& operator<<(ostream& out, const CarteRepoException& ex);

void testeRepo();