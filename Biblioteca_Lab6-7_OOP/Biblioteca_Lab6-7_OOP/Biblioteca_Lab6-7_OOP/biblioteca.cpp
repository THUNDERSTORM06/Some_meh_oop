#include "biblioteca.h"
#include <functional>
#include <algorithm>
#include <assert.h>

vector<Carte> Biblioteca::generalSort(bool(*maiMicF)(const Carte&, const Carte&)) {
	vector<Carte> v{ rep.getAll() };//fac o copie	
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Carte aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

/*
Adauga un nou pet
arunca exceptie daca: nu se poate salva, nu este valid
*/
void Biblioteca::addCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu,autor,gen,an };
	val.validate(c);
	rep.store(c);
}

void Biblioteca::modifyCarte(const string& titlu, const string& autor, const string& gen, int an, int poz) {
	Carte c{ titlu,autor,gen,an };
	val.validate(c);
	rep.modify(c, poz);
}

void Biblioteca::deleteCarte(int poz) {
	rep.sterge(poz);
}

/*
Sorteaza dupa tip
*/
vector<Carte> Biblioteca::sortByTitlu() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpTitlu);
	return copyAll;
	//return generalSort(cmpType);
}

/*
Sorteaza dupa species
*/
vector<Carte> Biblioteca::sortByAutor() {
	return generalSort(cmpAutor);
}

/*
Sorteaza dupa gen+an
*/
vector<Carte> Biblioteca::sortByGenAn() {
	return generalSort([](const Carte& c1, const Carte& c2) {
		if (c1.getGen() == c2.getGen()) {
			return c1.getAn() < c2.getAn();
		}
		return c1.getGen() < c2.getGen();
		});
}

vector<Carte> Biblioteca::filtreaza(function<bool(const Carte&)> fct) {
	vector<Carte> rez;
	for (const auto& carte : rep.getAll()) {
		if (fct(carte)) {
			rez.push_back(carte);
		}
	}
	return rez;
}

vector<Carte> Biblioteca::filtrareAnMaiMic(int an) {
	return filtreaza([an](const Carte& c) {
		return c.getAn() <= an;
		});
}

vector<Carte> Biblioteca::filtrareTitlu(const string& titlu) {
	return filtreaza([titlu](const Carte& c) {
		return c.getTitlu() == titlu;
		});
}

const Carte& Biblioteca::cautare(const string& titlu, const string& autor) {
	return rep.find(titlu, autor);
}


/*
vector<Carte> Biblioteca::filtrareAnMaiMic(int an) {
	return filtreaza([=](const Pet& p) {
		return p.getPrice() >= pretMin && p.getPrice() <= pretMax;
		});
}
*/

void testAdaugaCtr() {
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.addCarte("", "", "", - 1);
		//assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce exista deja
	try {
		ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
		//assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testFiltrare() {
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };

	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);
	ctr.addCarte("Micul print", "Antoine de Saint - Exupery", "best", 1998);

	assert(ctr.filtrareAnMaiMic(1940).size() == 2);
	assert(ctr.filtrareAnMaiMic(2000).size() == 3);
	assert(ctr.filtrareTitlu("Maitreyi").size() == 1);
}

void testSortare() {
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016);
	ctr.addCarte("Micul print", "Antoine de Saint - Exupery", "biografic", 1998);
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);

	auto firstC = ctr.sortByTitlu()[0];
	assert(firstC.getTitlu() == "Enigma Otiliei");

	firstC = ctr.sortByAutor()[0];
	assert(firstC.getAutor() == "Antoine de Saint - Exupery");

	firstC = ctr.sortByGenAn()[0];
	assert(firstC.getAn() == 1933);

}

void testModifica()
{
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938);
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016);

	assert(ctr.getAll()[1].getTitlu() == "Fluturi");

	ctr.modifyCarte("Micul print", "Antoine de Saint - Exupery", "biografic", 1998, 2);

	assert(ctr.getAll()[1].getTitlu() == "Micul print");

	try {
		ctr.modifyCarte("", "", "", -1, 1); //vrem sa modificam o carte cu date invalide
		//assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.modifyCarte("Maitreyi", "Mircea Eliade", "biografic", 1933, 7); //vrem sa modificam o carte cu o pozitie inexistenta
		//assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testStergere()
{
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938); //poz 0
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016); //poz 1

	assert(ctr.getAll().size() == 2);
	assert(ctr.getAll()[1].getTitlu() == "Fluturi");

	ctr.deleteCarte(2); //eu cand sterg presupun ca lista mea incepe de la pozitia 1

	assert(ctr.getAll().size() == 1);
	assert(ctr.getAll()[0].getTitlu() == "Enigma Otiliei");

	try {
		ctr.deleteCarte(-1); //vrem sa stergem o carte cu o pozitie inexistenta
		//assert(false);
	}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testCautare()
{
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	ctr.addCarte("Enigma Otiliei", "George Calinescu", "roman realist", 1938); //poz 0
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016); //poz 1

	const Carte Carte_DeCautat = ctr.getAll()[0];
	const Carte Carte_Gasita = ctr.cautare("Enigma Otiliei", "George Calinescu");
	assert(Carte_Gasita.getAutor() == Carte_DeCautat.getAutor());
	assert(Carte_Gasita.getTitlu() == Carte_DeCautat.getTitlu());

	try {
		const Carte Carte_Gasita2 = ctr.cautare("Enigma", "Jeorje");}
	catch (CarteRepoException&) {
		assert(true);
	}
}

void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testModifica();
	testStergere();
	testCautare();
}

