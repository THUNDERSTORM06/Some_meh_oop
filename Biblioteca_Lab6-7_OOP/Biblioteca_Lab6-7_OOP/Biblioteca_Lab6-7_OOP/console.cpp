#include "console.h"

#include "carte.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using namespace std;

void ConsoleUI::tipareste(const vector<Carte>& books) {
	cout << "Lista de carti:\n";
	int i = 0;
	for (const auto& carte : books) {
		i++;
		cout << i << ") Titlu: " << carte.getTitlu() << "; Autor: " << carte.getAutor() << "; Gen: " << carte.getGen() << "; An: " << carte.getAn() << '\n';
	}
	cout << "Sfarsit lista carti\n";
}

void ConsoleUI::meniuUI() {
	cout << "Meniu:\n";
	cout << "1. Adauga\n2. Tipareste\n3. Sorteaza dupa titlu\n";
	cout << "4. Sorteaza dupa autor\n5. Sorteaza dupa gen + an\n6. Filtrare an\n";
	cout << "7. Filtrare dupa titlu\n8. Cauta\n9. Modifica\n";
	cout << "10. Sterge\n0. Iesire\n";
	cout << "Dati comanda : ";
}

void ConsoleUI::adaugaUI() {
	string t, autor, g;
	int an;
	cin.sync();
	cin.get();
	cout << "Dati titlul:";
	getline(cin, t);
	cout << "Dati autorul:";
	getline(cin, autor);
	cout << "Dati genul:";
	getline(cin, g);
	cout << "Dati anul:";
	cin >> an;
	ctr.addCarte(t, autor, g, an);
	cout << "***Adaugat cu succes!\n";
}

void ConsoleUI::filtrareUI(int cmd) {
	if (cmd == 6)
	{
		cout << "Dati an maxim:";
		int an;
		cin >> an;
		tipareste(ctr.filtrareAnMaiMic(an));
	}
	else {
		cout << "Dati titlu pt filtrat:";
		string titlu;
		cin >> titlu;
		tipareste(ctr.filtrareTitlu(titlu));
	}
}

void ConsoleUI::cautareUI() {
	string titlu, autor;
	cin.sync();
	cin.get();
	cout << "Dati titlul de cautat:";
	getline(cin, titlu);
	cout << "Dati autorul:";
	getline(cin, autor);
	
	Carte carte = ctr.cautare(titlu, autor);
	cout << "Cartea gasita: " << "Titlu: " << carte.getTitlu() << "; Autor: " << carte.getAutor() << "; Gen: " << carte.getGen() << "; An: " << carte.getAn() << '\n';
}

void ConsoleUI::modificaUI() {
	string t, autor, g;
	int an, poz;
	cin.sync();
	cin.get();
	cout << "Dati pozitia cartii de modificat:";
	cin >> poz;
	cin.sync();
	cin.get();
	cout << "Dati titlul:";
	getline(cin, t);
	cout << "Dati autorul:";
	getline(cin, autor);
	cout << "Dati genul:";
	getline(cin, g);
	cout << "Dati anul:";
	cin >> an;
	ctr.modifyCarte(t, autor, g, an, poz);
	cout << "***Modificat cu succes!\n";
}

void ConsoleUI::stergeUI() {
	int poz;
	cin.sync();
	cin.get();
	cout << "Dati pozitia cartii de sters:";
	cin >> poz;
	
	ctr.deleteCarte(poz);
	cout << "***Sters cu succes!\n";
}

void ConsoleUI::start() {
	while (true) {
		meniuUI();

		int cmd;
		cin >> cmd;
		if (!isdigit(cmd)){
			try {
				switch (cmd) {
				case 1:
					adaugaUI();
					break;
				case 2:
					tipareste(ctr.getAll());
					break;
				case 3:
					tipareste(ctr.sortByTitlu());
					break;
				case 4:
					tipareste(ctr.sortByAutor());
					break;
				case 5:
					tipareste(ctr.sortByGenAn());
					break;
				case 6:
					filtrareUI(cmd);
					break;
				case 7:
					filtrareUI(cmd);
					break;
				case 8:
					cautareUI();
					break;
				case 9:
					modificaUI();
					break;
				case 10:
					stergeUI();
					break;
				case 0:
					return;
				default:
					cout << "Comanda invalida\n";
				}
			}
			catch (const CarteRepoException& ex) {
				cout << ex << '\n';
			}
			catch (const ValidateException& ex) {
				cout << ex << '\n';
			}
		}
		else {
			break;
		}
	}
}