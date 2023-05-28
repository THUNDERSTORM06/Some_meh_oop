#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "console.h"
#include "biblioteca.h"
#include "carte_repo.h"
#include "validator.h"

void adaugaCateva(Biblioteca& ctr) {
	ctr.addCarte("Maitreyi", "Mircea Eliade", "biografic", 1933);
	ctr.addCarte("Maitreyi", "Mircea", "bio", 1933);
	ctr.addCarte("Ferma animalelor", "George Orwell", "istoric", 2000);
	ctr.addCarte("Lolita", "Vladimir Nabokov", "romantic", 1989);
	ctr.addCarte("Micul print", "Antoine de Saint-Exupery", "best", 1998);
	ctr.addCarte("Fluturi", "Irina Binder", "romantic", 2016);
}
/*
3. Biblioteca
Creati o aplicatie care permite :
- gestiunea unei liste de carti. Carte : titlu, autor, gen, anul aparitiei
- adaugare DAP, stergere DAP, modificare DAP si afisare carti DAP
- cautare carte DAP
- filtrare carti dupa : titlu  Dap, anul aparitiei Dap
- sortare carti dupa titlu, autor, anul aparitiei + gen DAP
*/

void testAll() {
	testeRepo();
	testCtr();
	testValidator();
}

int main() {
	testAll();
	CarteRepo rep;
	CarteValidator val;
	Biblioteca ctr{ rep,val };
	adaugaCateva(ctr);//adaug cateva carti
	ConsoleUI ui{ ctr };
	ui.start();

	//_CrtDumpMemoryLeaks();

}