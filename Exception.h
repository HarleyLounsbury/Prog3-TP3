// Exception.h
// Fichier en-t�te de la classe exception, qui g�re les exceptions et ce qui doit �tre afficher.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
class Exception
{
private:
	int codeErreur;
	string message;
public:
	Exception(int code);
	Exception(int code, string nomFichier, int ligne);
	Exception(int code, string nomFichier, int ligne, string champ);
	void Afficher();
};

// CODES ERREUR:
// 1: Nombre de champs trop grands.
// 2: Nombre de champs trop petits.
// 3: Taille trop petite d'un champ.
// 4: Taille trop grande d'un champ.
// 5: Format de champ erron�(matricule)
// 6: Format de champ erron�(sexe)
// 7: Format de champ erron�(date)
// 8: Format de champ erron�(dur�e de la peine)
// 9: Valeur de champ erron�(mortalit� avant naissance)
// 10: Valeur de champ erron�(mortalit� avant d�tention)
// 11: Valeur de champ erron�(doublon de matricule)
// 12: Format invalide de date.