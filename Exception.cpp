// Exception.cpp
// Fichier de classe Exception - gère les messages pour des erreurs communs. 
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include "Biblio.h"

// ##############################
// Constructeur - paramétré
// Pour des dates
// ##############################
Exception::Exception(int code)
{
	codeErreur = code;
	message = "Format de date invalide.";
}

// ##############################
// Constructeur - paramétré
// Pour des données erronées
// ##############################
Exception::Exception(int code, string nomFichier, int ligne)
{
	codeErreur = code;
	message += "Erreur ";
	message += codeErreur;
	message += ": ";
	message += "Erreur: ";
	message += nomFichier;
	message += " ligne ";
	message += to_string(ligne);
	message += ": ";
	switch (codeErreur)
	{
	case 1:
		message += "nombre de champs trop grands.\n";
		break;
	case 2:
		message += "nombre de champs trop petits.\n";
		break;
	case 5:
		message += "matricule erroné.\n";
		break;
	case 6:
		message += "sexe erroné.\n";
		break;
	case 7:
		message += "date erroné.\n";
		break;
	case 8:
		message += "Durée de peine erroné.\n";
		break;
	case 9:
		message += "date de déces ne peut être avant la date de naissance.\n";
		break;
	case 10:
		message += "date de déces ne peut être avant la date de début de détention.\n";
		break;
	case 11:
		message += "doublon de matricule.\n";
		break;
	default:
		break;
	}
}

// ##############################
// Constructeur - paramétré
// Pour des champs de taille trop grande/petite.
// ##############################
Exception::Exception(int code, string nomFichier, int ligne, string champ)
{
	codeErreur = code;
	message += "Erreur ";
	message += codeErreur;
	message += ": ";
	message += nomFichier;
	message += " ligne ";
	message += to_string(ligne);
	message += ": ";
	switch (codeErreur)
	{
	case 3:
		message += "taille de champ \"" + champ + "\" trop petite.\n";
		break;
	case 4:
		message += "taille de champ \"" + champ + "\" trop grande.\n";
		break;
	default:
		break;
	}
}

void Exception::Afficher()
{
	cout << message;
	return;
}
