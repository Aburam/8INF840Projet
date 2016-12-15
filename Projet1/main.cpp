#include "SBTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

int main() {

	ifstream file("dictionnaire2.txt", std::ios::in);

	string text;

	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			text += line;
		}
		file.close();
		
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	SBTree sbtree = SBTree(text, 25, 8);
	char reponse = 0;
	sbtree.display();
	while (reponse != 'q') {
		cout << "pour quitter entrez : q" << endl;
		cout << "pour afficher la structure de donnees, entrez : d" << endl;
		cout << "pour inserer un nouveau mot, entrez : i" << endl;
		cout << "pour rechercher un suffix entrez : r" << endl;
		cout << "pour rechercher une sous-chaine ou la chaine elle-meme, entrez : s" << endl;
		cin >> reponse;

		switch (reponse) {
			case 'd': {
				sbtree.display();
				break;
			}
			case 'i': {
				cout << "quelque mot voulez-vous rajouter" << endl;
				string newReponse;
				cin >> newReponse;
				sbtree.insert(newReponse);
				break;
			}
			case 'r': {
				cout << "quelque suffix voulez-vous rechercher" << endl;
				string newReponse;
				cin >> newReponse;
				sbtree.seekSuffix(newReponse);
				break;
			}
			case 's': {
				cout << "quelque sous-chaine voulez-vous rechercher" << endl;
				string newReponse;
				cin >> newReponse;
				sbtree.seek(newReponse);
			}
		}
	}
	return EXIT_SUCCESS;
}