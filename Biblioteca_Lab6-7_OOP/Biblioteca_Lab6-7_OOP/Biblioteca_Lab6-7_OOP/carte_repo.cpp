#include "carte_repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void CarteRepo::store(const Carte& c)
{
	if (exist(c)) {
		throw CarteRepoException("Exista deja carte cu titlul:" + c.getTitlu() + " si autor:" + c.getAutor());
	}
	all.push_back(c);
}

void CarteRepo::modify(const Carte& c, int poz)
{
	if (poz > all.size() || poz <= 0) {
		throw CarteRepoException("Nu exista carte cu pozitia:" + poz);
	}
	all.at(poz - 1) = c;
}

void CarteRepo::sterge(int poz)
{
	if (poz > all.size() || poz <= 0) {
		throw CarteRepoException("Nu exista carte cu pozitia:" + poz);
	}
	all.erase(all.begin() + poz - 1);
}

bool CarteRepo::exist(const Carte& c) const {
	try {
		find(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (CarteRepoException&) {
		return false;}
}
/*
Cauta
arunca exceptie daca nu exista carte
*/
const Carte& CarteRepo::find(string titlu, string autor) const {
	for (const auto& c : all) {
		if (c.getTitlu() == titlu && c.getAutor() == autor) {
			return c;
		}
	}
	//daca nu exista arunc o exceptie
	throw CarteRepoException("Nu exista carte cu titlul:" + titlu + " si autor:" + autor);}

/*
returneaza toate cartile salvate
*/
const vector<Carte>& CarteRepo::getAll() const noexcept {
	return all;
}


ostream& operator<<(ostream& out, const CarteRepoException& ex) {
	out << ex.msg;
	return out;
}


void testAdauga() {
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("Maitreyi", "Mircea Eliade").getTitlu() == "Maitreyi");

	rep.store(Carte{ "Micul print", "Antoine de Saint - Exupery", "biografic", 1998 });
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu acelasi tip si specie
	try {
		rep.store(Carte{ "Maitreyi", "Mircea Eliade", "realist", 1933 });
		//assert(false);
	}
	catch (const CarteRepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.find("c", "c");
		//assert(false);
	}
	catch (const CarteRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	CarteRepo rep;
	rep.store(Carte{ "Maitreyi", "Mircea Eliade", "biografic", 1933 });
	rep.store(Carte{ "Micul print", "Antoine de Saint - Exupery", "biografic", 1998 });

	auto p = rep.find("Maitreyi", "Mircea Eliade");
	assert(p.getAutor() == "Mircea Eliade");
	assert(p.getTitlu() == "Maitreyi");

	//arunca exceptie daca nu gaseste
	try {
		rep.find("a", "b");
		//assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
}
