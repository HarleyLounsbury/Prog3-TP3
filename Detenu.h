// Detenu.h
// Fichier en-tête de classe Detenu.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
class Detenu
{
private:
	string mat;
	string prenom;
	string nom;
	string sexe;
	string anneeNaiss;
	string moisNaiss;
	string jourNaiss;
	string anneeDet;
	string moisDet;
	string jourDet;
	string anneeCon;
	string moisCon;
	string jourCon;
	string duree;
	string anneeDec;
	string moisDec;
	string jourDec;

	Liste<PieceDossier> piecesDossier;

	time_t dateLiberation;

	string calculePeine();
	int calculeAge();

public:
	Detenu(string valeurs[]);

	void Afficher();
	void Afficher(bool unique);
	void Exporter(ostream & of);
	static void AfficherEnTete();
	static void AfficherEnTeteFichier(ostream & of);

	string G_matricule();
	void S_dateCondamnation(string vals[]);
	void S_dateDeces(string vals[]);
	string G_nom();
	string G_prenom();
	string G_duree();
	string G_dateNaissConcatine();
	string G_dateDecesConcatine();
	string G_sexe();

	bool EstLibere();
	string G_dateCondamnationConcatine();
	string JoursRestants();

	Liste<PieceDossier>* G_pDossier();
	static bool validerDate(string annee, string mois, string jour);
};
