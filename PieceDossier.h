// PieceDossier.h
// Fichier en-tête de références pour le système de gestion de détenus.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
class PieceDossier
{
private:
	string matricule;
	string date;
	string type;
	string contenu;

public:
	PieceDossier(string valeurs[]);
	void Afficher();
	static void AfficherEnTete();
};