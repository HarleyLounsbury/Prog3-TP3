// Context.h
// Context est la classe qui contient la liste de detenus. 
// 
// Auteur: Harley Lounsbury
// Date: 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
class Context
{
private:
	Liste<Detenu> ListeDetenus;

	void afficherEnTete();
	char menuPrincipal();

	void menuAjouter();
	char menuCharger();
	void chargerDetenus();
	int importerDetenus(string fichierIn);
	void analyserLigneDetenu(string ligne, int numLigne, string nomFich);
	string formatterNom(string nom);

	void afficher();
	char menuAfficher();
	void afficherListeComplete(string option, bool pageParPage);
	void afficherUnDetenu();
	void affichageTermine();

	void modifier();
	char menuModifier(Noeud<Detenu>* pDetenu);
	void modifierDate(Noeud<Detenu>* pDetenu, string dateAModifier);

	void afficherListeFiltree(string option);
	void filtreEtAffiche(string option, string filtre, string filresUtilises);

	void trier();
	char menuTrier();
	void trierListe(string Critere, string Ordre);

	char confirmation(string msg);
	void messageDeConfirmation();

	void supprimer();
	void vider();

	string dateMaintenantConcatine(string separateur = "");

	void chargerPiecesDossiers();
	int importerDossiers(string nomFichier, int& rejets);
	void analyserLigneDossier(string ligneCourante);
	char optionOuiNon(string phrase);
	void ajouterPieceAuDossier(Noeud<Detenu>* pDetenu);
	char menuTypeDePiece();

public:
	void Init();
	~Context();
};