// PieceDossier.h
// Fichier en-t�te de r�f�rences pour le syst�me de gestion de d�tenus.
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