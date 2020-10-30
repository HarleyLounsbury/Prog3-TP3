// Exception.cpp
// Fichier de classe Exception - g�re les messages pour des erreurs communs. 
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include "Biblio.h"

// ##############################
// Constructeur - param�tr�
// Pour des dates
// ##############################
Exception::Exception(int code)
{
	codeErreur = code;
	message = "Format de date invalide.";
}

// ##############################
// Constructeur - param�tr�
// Pour des donn�es erron�es
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
		message += "matricule erron�.\n";
		break;
	case 6:
		message += "sexe erron�.\n";
		break;
	case 7:
		message += "date erron�.\n";
		break;
	case 8:
		message += "Dur�e de peine erron�.\n";
		break;
	case 9:
		message += "date de d�ces ne peut �tre avant la date de naissance.\n";
		break;
	case 10:
		message += "date de d�ces ne peut �tre avant la date de d�but de d�tention.\n";
		break;
	case 11:
		message += "doublon de matricule.\n";
		break;
	default:
		break;
	}
}

// ##############################
// Constructeur - param�tr�
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
