#pragma once

#include "Carte.h"
#include "carte_repo.h"
#include <string>
#include <vector>

#include <functional>
#include "validator.h"

using std::vector;
using std::function;

class Biblioteca {
	CarteRepo& rep;
	CarteValidator& val;

	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 Carte, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Carte)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<Carte> generalSort(bool (*maiMicF)(const Carte&, const Carte&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar cartile care trec de filtru (fct(carte)==true)
	*/
	vector<Carte> filtreaza(function<bool(const Carte&)> fct);
public:
	Biblioteca(CarteRepo& rep, CarteValidator& val) :rep{ rep }, val{ val } {
	}
	//nu permitem copierea de obiecte Biblioteca
	Biblioteca(const Biblioteca& ot) = delete;
	/*
	 returneaza toate cartile in ordinea in care au fost adaugate
	*/
	const vector<Carte>& getAll() noexcept {
		return rep.getAll();
	}
	/*
	Adauga o noua carte
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addCarte(const string& titlu, const string& autor, const string& gen, int an);

	/*
	Modifica o carte
	Arunca exceptie daca: nu se poate modificaa, nu este valid, pozitia e invalida
	*/
	void modifyCarte(const string& titlu, const string& autor, const string& gen, int an, int poz);

	/*
	Sterge o carte
	Arunca exceptie daca: nu se poate sterge, pozitia e invalida
	*/
	void deleteCarte(int poz);

	/*
	Sorteaza dupa titlu
	*/
	vector<Carte> sortByTitlu();

	/*
	Sorteaza dupa autor
	*/
	vector<Carte> sortByAutor();

	/*
	Sorteaza dupa gen si dupa an
	*/
	vector<Carte> sortByGenAn();

	/*
	returneaza doar cartile cu an mai mic decat cel dat
	*/
	vector<Carte> filtrareAnMaiMic(int an);

	/*
	returneaza doar cartile cu acelasi titlu
	*/
	vector<Carte> filtrareTitlu(const string& titlu);

	/*
	cauta o carte dupa autor si titlu
	*/
	const Carte& cautare(const string& titlu, const string& autor);

};

void testCtr();
