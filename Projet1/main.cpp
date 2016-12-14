#include "SBTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

int main() {

	ifstream file("dictionnaire.txt", std::ios::in);

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
	while (reponse != 'q') {
		cout << "pour quitter entrez : q" << endl;
		cin >> reponse;
	}
	return EXIT_SUCCESS;
}