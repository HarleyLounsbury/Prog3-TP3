// PieceDossier.cpp 
// Fichier de classe PieceDossier.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include "Biblio.h"

// ##############################
// Constructeur - paramétré
// Prend un tableau de string de valeurs. 
// ##############################
PieceDossier::PieceDossier(string valeurs[])
{
	matricule = valeurs[0];
	date = valeurs[1];
	type = valeurs[2];
	contenu = valeurs[3];
}

// ##############################
// Afficher()
// afficher les détails à l'écran.
// ##############################
void PieceDossier::Afficher()
{
	cout << date << " " << type << " " << contenu << endl;
	return;
}

// ##############################
// AfficherEnTete()
// Méthode statique pour afficher l'en-tête de pièces au dossier.
// ##############################
void PieceDossier::AfficherEnTete()
{
	cout << "Date       Type Contenu" << endl;
	return;
}