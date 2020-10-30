// Context.h
// Fichier de class Context pour le système de gestion de détenus.
// Contentant de la méchanism du programme.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include "Biblio.h"

// ##############################
// afficherEnTete()
// Afficher le titre, auteur, et nombre de détenus dans la liste.
// ##############################
void Context::afficherEnTete()
{
	char coinHG = (char)201;
	char coinHD = (char)187;
	char coinBG = (char)200;
	char coinBD = (char)188;
	char ligneH = (char)205;
	char ligneV = (char)186;

	system("cls");
	setlocale(LC_ALL, "C");
	cout << coinHG;
	for (int i = 0; i < 48; i++)
		cout << ligneH;
	cout << coinHD << endl;
	cout << ligneV << "                                                " << ligneV << endl;
	cout << ligneV << "  Les productions Harley Lounsbury inc          " << ligneV << endl;
	cout << ligneV << "                                                " << ligneV << endl;
	cout << ligneV << "     Syst\x8Ame de suivi de d\x82tenus                " << ligneV << endl;
	cout << ligneV << "                                                " << ligneV << endl;
	cout << coinBG;
	for (int i = 0; i < 48; i++)
		cout << ligneH;
	cout << coinBD << endl;
	setlocale(LC_ALL, "");
	cout << "Liste contenant " << ListeDetenus.G_nbElements() << " détenu(s)" << endl;

	return;
}

// ##############################
// menuPrincipal()
// Afficher le menu principale, saisier le choix de l'utilisateur.
// ##############################
char Context::menuPrincipal()
{
	afficherEnTete();
	char Choix;
	cout << "\n\nMenu principal:\n\n";
	cout << "\tA-Ajouter\n";
	if (ListeDetenus.G_nbElements() > 0)
	{
		cout << "\tF-aFficher\n";
		cout << "\tM-Modifier\n";
		cout << "\tT-Trier\n";
		cout << "\tS-Supprimer\n";
		cout << "\tV-Vider\n\n";
	}
	cout << "\tQ-Quitter\n";
	cout << "\t\tVotre choix:";
   cin >> Choix;
   if (ListeDetenus.G_nbElements() == 0)
   {
      while (!(toupper(Choix) == 'A' || toupper(Choix) == 'Q' ))
      {
         cout << "Vous devez ajouter des détenus à la liste." << endl;
         cout << "\t\tVotre choix:";
         cin >> Choix;
      }
   }

	return toupper(Choix);
}

// ##############################
// menuAjouter()
// Afficher le menu pour ajouter des détenus à la liste.
// ##############################
void Context::menuAjouter()
{
	char Choix;
	Choix = menuCharger();
	while (Choix != 'Q')
	{
		switch (toupper(Choix))
		{
		case 'D': 
			chargerDetenus(); 
			break;
		case 'P': 
			chargerPiecesDossiers(); 
			break;
		case 'Q': 
			return;
		default: 
			break;
		}
		Choix = menuCharger();
	}
}

// ##############################
// menuCharger()
// Afficher le menu de chargement, saisir le choix de l'utilisateur.
// ##############################
char Context::menuCharger()
{
	afficherEnTete();
	char Choix;
	cout << "\n\nChargement de\n\n";
	cout << "\tD-Détenus\n";
	if (ListeDetenus.G_nbElements() > 0)
		cout << "\tP-Pièces aux dossiers\n";
	cout << "\tQ-menu Principal\n";

	cout << "\t\tVotre choix:";
	cin >> Choix;

   if (ListeDetenus.G_nbElements() == 0)
   {
      while (!(toupper(Choix) == 'D' || toupper(Choix) == 'Q'))
      {
         cout << "Vous devez ajouter des détenus à la liste." << endl;
         cout << "\t\tVotre choix:";
         cin >> Choix;
      }
   }

	return toupper(Choix);
}

// ##############################
// chargerDetenus()
// saisir le nom du fichier de donnes de détenus, importer les détenus. 
// ##############################
void Context::chargerDetenus()
{
	string nomFichier;

	afficherEnTete();
	cout << "\n\nAjout de détenus à partir d'un fichier\n\n";
	cout << "Fichier à charger:";
	cin >> nomFichier;

	cout << "-- Chargement de " << nomFichier << " en cours ...\n";
	
	// Importation du fichier.
	int nbChargements = importerDetenus(nomFichier);
	cout << "-- " << nbChargements << " détenus chargés. Chargement terminé.\n\n";

	system("pause");

	return;
}

// ##############################
// importerDetenus(string fichierIn)
// importer ligne par ligne les données de détenus, ajouter à la liste si toutes les critères de champs sont correct. 
// ##############################
int Context::importerDetenus(string fichierIn)
{
	ifstream FicIn(fichierIn);
	string ligneCourante;
	int compteurLigne = 0;
	int compteurChargements = 0;
	Parseur<Detenu> ParDet(";", NB_CHAMPS_DETENU);

	while (FicIn.good())
	{
		getline(FicIn, ligneCourante);
		compteurLigne++;

		if (ligneCourante[0] != '#' && ligneCourante != "")
		{
			string valeurs[NB_CHAMPS_DETENU];
			try
			{
				analyserLigneDetenu(ligneCourante, compteurLigne, fichierIn);
				ParDet.Decouper(ligneCourante, valeurs);
				valeurs[1] = formatterNom(valeurs[1]);
				valeurs[2] = formatterNom(valeurs[2]);
				if (valeurs[13] == "")
					valeurs[13] = "0";
				ListeDetenus.Ajouter(ParDet.Instancier(valeurs));
				compteurChargements++;
			}
			catch (Exception e)
			{
				e.Afficher();
				cout << "Voulez-vous poursuivre le chargement? (o/n)";
				if (_getch() == 'n')
				{
					cout << endl;
					FicIn.close();
					return compteurChargements;
				}
				cout << endl;
			}
		}
	}

	FicIn.close();

	return compteurChargements;
}

// ##############################
// analyserLigneDetenu(string ligne, int numLigne, string nomFich)
// analyser le ligne qu'on essaie de importer. THROW object de classe Exception si erreur.
// ##############################
void Context::analyserLigneDetenu(string ligne, int numLigne, string nomFich)
{
	Parseur<Detenu> ParseTemp(";", NB_CHAMPS_DETENU);
	
	// 1. NOMBRE DE CHAMPS TROP PETIT
	if (ParseTemp.CompteurChamp(ligne) < NB_CHAMPS_DETENU)
		throw Exception(1, nomFich, numLigne);

	// 2. NOMBRE DE CHAMPS TROP GRAND
	if (ParseTemp.CompteurChamp(ligne) > NB_CHAMPS_DETENU)
		throw Exception(2, nomFich, numLigne);

	string tempVals[NB_CHAMPS_DETENU];
	ParseTemp.Decouper(ligne, tempVals);

	// 3. UN CHAMP QUI EST TROP PETIT (certains peut étre vide, par contre.
	int longueursMin[NB_CHAMPS_DETENU] = { EXACTE_MATRICULE,  // Matricule
										MIN_PRENOM,		// Prénom
										MIN_NOM,		// Nom
										EXACTE_SEXE,	// Sexe (M ou F)
										EXACTE_ANNEE,	// Année de naissance (AAAA)
										EXACTE_MOIS,	// Mois de naissance (MM)
										EXACTE_JOUR,	// Jour de naissance (JJ)
										EXACTE_ANNEE,	// Année de début de détention
										EXACTE_MOIS,	// Mois de début de détention
										EXACTE_JOUR,	// Jour de début de détention	
										0,				// Année de condamnation (AAAA) (peut être vide, dans le cas qu'il n'a pas encore été condamné.)
										0,				// Mois de condamnation (MM) (peut être vide, dans le cas qu'il n'a pas encore été condamné.)
										0,				// Jour de condamnation (JJ) (peut être vide, dans le cas qu'il n'a pas encore été condamné.)
										0,		// Durée de la peine (en nombre de jours, il n'a peut-etre pas encore sa sentence.)
										0,				// Année de déces (AAAA) (peut être vide, dans le cas qu'il est encore en vie.)
										0,				// Mois de déces (MM) (peut être vide, dans le cas qu'il est encore en vie.)
										0, };			// Jour de déces (JJ) (peut être vide, dans le cas qu'il est encore en vie.)
	int indiceChamp = ParseTemp.ValiderMinLongeurChamps(NB_CHAMPS_DETENU, longueursMin, tempVals);
	if (indiceChamp != -1)
	{
		switch (indiceChamp)
		{
		case 0:
			throw Exception(3, nomFich, numLigne, "matricule");
			break;
		case 1:
			throw Exception(3, nomFich, numLigne, "nom");
			break;
		case 2:
			throw Exception(3, nomFich, numLigne, "prenom");
			break;
		case 3:
			throw Exception(3, nomFich, numLigne, "sexe");
			break;
		case 4:
			throw Exception(3, nomFich, numLigne, "année de naissance");
			break;
		case 5:
			throw Exception(3, nomFich, numLigne, "mois de naissance");
			break;
		case 6:
			throw Exception(3, nomFich, numLigne, "jour de naissance");
			break;
		case 7:
			throw Exception(3, nomFich, numLigne, "année de début de détention");
			break;
		case 8:
			throw Exception(3, nomFich, numLigne, "mois de début de détention");
			break;
		case 9:
			throw Exception(3, nomFich, numLigne, "jour de début de détention");
			break;
		case 10:
			throw Exception(3, nomFich, numLigne, "année de condamnation");
			break;
		case 11:
			throw Exception(3, nomFich, numLigne, "mois de condamnation");
			break;
		case 12:
			throw Exception(3, nomFich, numLigne, "jour de condamnation");
			break;
		case 13:
			throw Exception(3, nomFich, numLigne, "durée de la peine");
			break;
		case 14:
			throw Exception(3, nomFich, numLigne, "année de déces");
			break;
		case 15:
			throw Exception(3, nomFich, numLigne, "mois de déces");
			break;
		case 16:
			throw Exception(3, nomFich, numLigne, "jour de déces");
			break;
		default:
			break;
		}
	}

	// 4. UN CHAMP QUI DÉPASSE LE LONGUEUR MAXIMUM
	int longueursMax[NB_CHAMPS_DETENU] = { EXACTE_MATRICULE,  // Matricule
									    MAX_PRENOM,		// Prénom
										MAX_NOM,		// Nom
										EXACTE_SEXE,	// Sexe (M ou F)
										EXACTE_ANNEE,	// Année de naissance (AAAA)
										EXACTE_MOIS,	// Mois de naissance (MM)
										EXACTE_JOUR,	// Jour de naissance (JJ)
										EXACTE_ANNEE,	// Année de début de détention
										EXACTE_MOIS,	// Mois de début de détention
										EXACTE_JOUR,	// Jour de début de détention	
										EXACTE_ANNEE,	// Année de condamnation (AAAA)
										EXACTE_MOIS,	// Mois de condamnation (MM)
										EXACTE_JOUR,	// Jour de condamnation (JJ)
										MAX_DUREE,		// Durée de la peine (en nombre de jours, mais pour le longueur, 6 est en masse)
										EXACTE_ANNEE,	// Année de déces (AAAA)
										EXACTE_MOIS,	// Mois de déces (MM)
										EXACTE_JOUR, };	// Jour de déces (JJ)
		indiceChamp = ParseTemp.ValiderMaxLongeurChamps(NB_CHAMPS_DETENU, longueursMax, tempVals);
	if (indiceChamp != -1)
	{
		switch (indiceChamp)
		{
		case 0:
			throw Exception(4, nomFich, numLigne, "matricule");
			break;
		case 1:
			throw Exception(4, nomFich, numLigne, "nom");
			break;
		case 2:
			throw Exception(4, nomFich, numLigne, "prenom");
			break;
		case 3:
			throw Exception(4, nomFich, numLigne, "sexe");
			break;
		case 4:
			throw Exception(4, nomFich, numLigne, "année de naissance");
			break;
		case 5:
			throw Exception(4, nomFich, numLigne, "mois de naissance");
			break;
		case 6:
			throw Exception(4, nomFich, numLigne, "jour de naissance");
			break;
		case 7:
			throw Exception(4, nomFich, numLigne, "année de début de détention");
			break;
		case 8:
			throw Exception(4, nomFich, numLigne, "mois de début de détention");
			break;
		case 9:
			throw Exception(4, nomFich, numLigne, "jour de début de détention");
			break;
		case 10:
			throw Exception(4, nomFich, numLigne, "année de condamnation");
			break;
		case 11:
			throw Exception(4, nomFich, numLigne, "mois de condamnation");
			break;
		case 12:
			throw Exception(4, nomFich, numLigne, "jour de condamnation");
			break;
		case 13:
			throw Exception(4, nomFich, numLigne, "durée de la peine");
			break;
		case 14:
			throw Exception(4, nomFich, numLigne, "année de déces");
			break;
		case 15:
			throw Exception(4, nomFich, numLigne, "mois de déces");
			break;
		case 16:
			throw Exception(4, nomFich, numLigne, "jour de déces");
			break;
		default:
			break;
		}
	}

	// 5. FORMAT DE CHAMP ERRONÉ (matricule)
	if (tempVals[0].length() != EXACTE_MATRICULE)
		throw Exception(5, nomFich, numLigne);

	// 6. FORMAT DE CHAMP ERRONÉ (sexe)
	if (tempVals[3] != "M" && tempVals[3] != "F")
		throw Exception(6, nomFich, numLigne);
		
	// 7. FORMAT DE CHAMP ERRONÉ (date)
	if (!Detenu::validerDate(tempVals[4], tempVals[5], tempVals[6]))
		throw Exception(7, nomFich, numLigne);

	// 8. FORMAT DE CHAMP ERRONÉ (durée de la peine)
	if (tempVals[13].find_first_not_of("0123456789") != -1)
		throw Exception(8, nomFich, numLigne);

	// 9. VALEUR DE CHAMP ERRONÉ (mortalité avant naissance);
	if (tempVals[14] + tempVals[15] + tempVals[16] != "")
		if ((tempVals[4] + tempVals[5] + tempVals[6]) > (tempVals[14] + tempVals[15] + tempVals[16]))
			throw Exception(9, nomFich, numLigne);

	// 10. VALEUR DE CHAMP ERRONÉ (mortalité avant détention)
	if (tempVals[14] + tempVals[15] + tempVals[16] != "")
		if ((tempVals[7] + tempVals[8] + tempVals[9]) > (tempVals[14] + tempVals[15] + tempVals[16]))
			throw Exception(10, nomFich, numLigne);

	// 11. VALEUR DE CHAMP ERRONÉ (doublon de matricule)
	Noeud<Detenu>* pCourant = nullptr;
	if (ListeDetenus.G_pPremier() != nullptr)
	{
		pCourant = ListeDetenus.G_pPremier();
		while (pCourant)
		{
			if (pCourant->G_pInfo()->G_matricule() == tempVals[0])
				throw Exception(11, nomFich, numLigne);
			pCourant = pCourant->G_pProchain();
		}
	}

	return;
}

// ##############################
// formatterNomss(string nom)
// Formatter un nom (ou autre string) en "Abcde"
// ##############################
string Context::formatterNom(string nom)
{
	string nomFormatte = nom;
	nomFormatte[0] = toupper(nomFormatte[0]);
	for (int i = 1; i < nom.length(); i++)
	{
		nomFormatte[i] = tolower(nom[i]);
		if (nom[i - 1] == '-')
			nomFormatte[i] = toupper(nom[i]);
	}
	return nomFormatte;
}

// ##############################
// Init()
// Méthode publique pour partir le programme. 
// ##############################
void Context::Init()
{
	afficherEnTete();
	char Choix;
	do
	{
		Choix = menuPrincipal();
		switch (toupper(Choix))
		{
		case 'A': 
			menuAjouter(); 
			break;
		case 'M':
			modifier(); 
			break;
		case 'T': 
			trier(); 
			break;
		case 'S': 
			supprimer(); 
			break;
		case 'V': 
			vider();
			break;
		case 'F': 
			afficher(); 
			break;
		default: 
			break;
		}
	} while (Choix != 'Q');

	return;
}

// ##############################
// Déstructeur
// Vider la liste - libérer de la mémoire allouée dynamiquement.
// ##############################
Context::~Context()
{
	ListeDetenus.Vider();
}

// ##############################
// afficher()
// partir au menu choisi par l'utilisateur.
// ##############################
void Context::afficher()
{
	char Choix;
	afficherEnTete();
	Choix = menuAfficher();

	while (Choix != 'Q')
	{
		switch (Choix)
		{
		case 'L':
			afficherListeComplete("ecran", false);
			break;
		case 'E':
			afficherListeComplete("ecran", true);
			break;
		case 'C':
			afficherListeComplete("fichier", false);
			break;
		case 'F':
			afficherListeFiltree("");	
			break;
		case 'I':
			afficherListeFiltree("fichier");
			break;
		case 'U':
			afficherUnDetenu();
			break;
		default:
			break;
		}
		Choix = menuAfficher();
	}
}

// ##############################
// menuAfficher()
// menu d'options d'affichage.
// ##############################
char Context::menuAfficher()
{
	afficherEnTete();
	char Choix;
	cout << "\n\nAffichage\n\n";
	cout << "Options d'affichage:\n\n";
	cout << "\tÀ l'écran\n\n";
	cout << "\t\tL-Liste complète\n";
	cout << "\t\tE-Liste complète, un Ecran à la fois\n";
	cout << "\t\tF-Liste Filtrée\n\n";
	cout << "\t\tU-Un seul détenu\n\n";
	cout << "\tDans un fichier\n\n";
	cout << "\t\tC-liste Complète\n";
	cout << "\t\tI-lISte filtrée\n\n";
	cout << "\t\tQ-retour au menu Principal\n";

	cout << "\t\tVotre choix:";
	cin >> Choix;

	return toupper(Choix);
}

// ##############################
// afficherListeComplete(string option, bool pageParPage)
// afficher la liste au complet, soit en entière, soit page par page (25 par page).
// ##############################
void Context::afficherListeComplete(string option, bool pageParPage)
{
	string FicOut;
	afficherEnTete();
	if (!pageParPage)
	{
		if (option == "fichier")
		{
			cout << "Nom du fichier qui recevra la liste:";
			cin >> FicOut;
			ofstream fichier(FicOut, ios::app);
			cout << "Ecriture de la liste complète en cours...\n";
			Detenu::AfficherEnTeteFichier(fichier);
			ListeDetenus.Exporter(fichier);
			cout << "Écriture de " << ListeDetenus.G_nbElements() << " détenus dans le fichier " << FicOut << "\n";
			fichier.close();
		}
		if (option == "ecran")
		{
			Detenu::AfficherEnTete();
			ListeDetenus.Afficher();
		}
	}
	else
	{
		Detenu::AfficherEnTete();
		ListeDetenus.Afficher(25);
	}

	affichageTermine();

	return;
}

// ##############################
// afficherUnDetenu()
// affichage d'un détenu unique.
// ##############################
void Context::afficherUnDetenu()
{
	string matricule;
	afficherEnTete();
	cout << "\n\nAffichage d'un seul détenu\n\n";
	cout << "Matricule à afficher:";
	cin >> matricule;

	Noeud<Detenu>* pDetenu = ListeDetenus.EstPresent(matricule);
	if (pDetenu)
		pDetenu->G_pInfo()->Afficher(true);
	else
		cout << "Numéro de matricule invalide." << endl;

	char Choix;
	if (pDetenu && pDetenu->G_pInfo()->G_pDossier()->G_pPremier())
	{
		Choix = optionOuiNon("Afficher les pièces à son dossier");
		switch (toupper(Choix))
		{
		case 'O': 
			PieceDossier::AfficherEnTete();
			//pDetenu->G_pInfo()->G_pDossier()->Afficher();
			break;
		default:
			break;
	}
	}
	system("pause");
}

// ##############################
// affichageTermine()
// signaler la fin de l'affichage.
// ##############################
void Context::affichageTermine()
{
	cout << "\n\t----------FIN---------------\n\n\n";
	system("pause");

	return;
}

// ##############################
// modifier()
// modifier des informations d'un détenu.
// ##############################
void Context::modifier()
{
	char Choix;
	string matricule;

	afficherEnTete();
	cout << "\n\nModifications des informations d'un détenu\n\n";
	cout << "Matricule du détenu:";
	cin >> matricule;

	Noeud<Detenu>* pDet = ListeDetenus.EstPresent(matricule);
	if (pDet)
	{
		Choix = menuModifier(pDet);

		switch (Choix)
		{
		case 'C': 
			modifierDate(pDet, "condamnation"); 
			break;
		case 'D': 
			modifierDate(pDet, "deces");
			break;
		case 'P': 
			ajouterPieceAuDossier(pDet); 
			break;
		default: 
			break;
		}
	}
	else
	{
		cout << "Numéro de matricule invalide." << endl;
		return;
	}
	return;
}

// ##############################
// menuModifier(Noeud<Detenu>* pDetenu)
// saisir choix de l'utilisateur et retourner la caractère corréspondante.
// ##############################
char Context::menuModifier(Noeud<Detenu>* pDetenu)
{
	char Choix;
	afficherEnTete();

	cout << "\n\nInformations du détenu " << pDetenu->G_pInfo()->G_matricule() << ":\n\n";
	pDetenu->G_pInfo()->Afficher(true);

	cout << "\tModifier:\n\n";
	cout << "\t\tC-Condamnation\n";
	cout << "\t\tD-Décès\n";
	cout << "\t\tP-Ajouter une pièce au dossier\n";
	cout << "\t\tQ-retour au menu précédent\n";
	cout << "\t\tVotre choix:";
	cin >> Choix;

	return toupper(Choix);
}

// ##############################
// modifierDate(Noeud<Detenu>* pDetenu, string dateAModifier)
// modifier une date au dossier.
// ##############################
void Context::modifierDate(Noeud<Detenu>* pDetenu, string dateAModifier)
{
	string dateVals[3];
	string tampon = "-";
	char Choix;

	afficherEnTete();
	if (dateAModifier == "condamnation")
		cout << "\nDate de condamnation pour matricule " << pDetenu->G_pInfo()->G_matricule() << ":";
	if (dateAModifier == "deces")
		cout << "\nDate de déces pour matricule " << pDetenu->G_pInfo()->G_matricule() << ":";
	try
	{
		string nouvDate;
		cin >> nouvDate;
		Parseur<string> ParDet("-", 3);
		if (ParDet.CompteurChamp(nouvDate) + 1 != 3)
			throw Exception(12);

		dateVals[0] = nouvDate.substr(0, 4);
		dateVals[1] = nouvDate.substr(5, 2);
		dateVals[2] = nouvDate.substr(8, 2);

		Choix = confirmation("Confirmer les changements");
		switch (toupper(Choix))
		{
		case 'C': 
			if (dateAModifier == "condamnation")
				pDetenu->G_pInfo()->S_dateCondamnation(dateVals);
			if (dateAModifier == "deces")
				pDetenu->G_pInfo()->S_dateDeces(dateVals);
			messageDeConfirmation();
			break;
		default:
			break;
		}
	}
	catch (Exception e) 
	{
		e.Afficher();
	}
	

	return;
}

// ##############################
// afficherListeFiltree(string option)
// afficher le menu de filtres.
// ##############################
void Context::afficherListeFiltree(string option)
{
	string ListeFiltre;
	afficherEnTete();
	cout << "\n\nFiltres possibles pour l'affichage\n\n";
	cout << "\t\tSexe            :\t M (masculin)      ou F (féminin)\n";
	cout << "\t\tVivant          :\t V (vivant)        ou D (décédé)\n";
	cout << "\t\tCondamné        :\t C (condamné)      ou P (en procès)\n";
	cout << "\t\tLibéré          :\t L (libéré)        ou I (incarcéré)\n";
	cout << "\t\t%Peine complétée:\t + (Plus du tiers) ou - (moins du tiers)\n\n";
	cout << "\t\tQ-retour au menu affichage\n";

	cout << "\t\tVotre choix de filtres:";
	getline(cin, ListeFiltre);
	getline(cin, ListeFiltre);

	string ListeFiltreUP;
	for (unsigned int i = 0; i < ListeFiltre.length(); i++)
	{
		ListeFiltreUP += toupper(ListeFiltre[i]);
	}

	string FiltreUtilises;
	if (ListeFiltreUP.find('Q') != -1)
		return;
	if (ListeFiltreUP.find('M') != -1)
		FiltreUtilises += "Masculins ";
	if (ListeFiltreUP.find('F') != -1)
		FiltreUtilises += "Féminins ";
	if (ListeFiltreUP.find('V') != -1)
		FiltreUtilises += "Vivants ";
	if (ListeFiltreUP.find('D') != -1)
		FiltreUtilises += "Décédés ";
	if (ListeFiltreUP.find('L') != -1)
		FiltreUtilises += "Libérés ";
	if (ListeFiltreUP.find('I') != -1)
		FiltreUtilises += "Incarcérés ";
	if (ListeFiltreUP.find('C') != -1)
		FiltreUtilises += "Condamnés ";
	if (ListeFiltreUP.find('P') != -1)
		FiltreUtilises += "En procès ";
	if (ListeFiltreUP.find('+') != -1)
		FiltreUtilises += "Plus du 1/3 ";
	if (ListeFiltreUP.find('-') != -1)
		FiltreUtilises += "Moins du 1/3 ";

	filtreEtAffiche(option, ListeFiltreUP, FiltreUtilises);
}

// ##############################
// filtreEtAffiche(string option, string filtre, string filtresUtilises)
// filtre la liste, afficher. 
// Optimisation v6
//
// v1 - 1 filtre à la fois
// v2, v3 - filtre par dessus filtre, avec doublons.
// v4 - filtre par dessus filtre, sans doublons.
// v5 - filtre avec analyse croisé pour combiné les filtres - fonctionnelle, mais le temps réquise était perceptible. (~4 secondes pour 500 détenus. Exponentiel, À 10000 détenus c'est devenu impossible.)
// ##############################
void Context::filtreEtAffiche(string option, string filtre, string filtresUtilises)
{
	Liste<Detenu> listeFiltree;
	Noeud<Detenu>* pDet = ListeDetenus.G_pPremier();

	Liste<Detenu> listeSexe;
	Liste<Detenu> listeVivantMort;
	Liste<Detenu> listeLibereIncarcere;
	Liste<Detenu> listeCondamneEnProces;
	Liste<Detenu> listePlusMoinsTier;

	afficherEnTete();

	// Appliquer les filtres en ajoutant le détenu à la liste du critère.
	while (pDet)
	{
		if (filtre.find('M') != -1 && pDet->G_pInfo()->G_sexe() == "M" && listeSexe.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeSexe.Ajouter(pDet->G_pInfo());
		if (filtre.find('F') != -1 && pDet->G_pInfo()->G_sexe() == "F" && listeSexe.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeSexe.Ajouter(pDet->G_pInfo());

		if (filtre.find('V') != -1 && pDet->G_pInfo()->G_dateDecesConcatine() == "" && listeVivantMort.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeVivantMort.Ajouter(pDet->G_pInfo());
		if (filtre.find('D') != -1 && pDet->G_pInfo()->G_dateDecesConcatine() != "" && listeVivantMort.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeVivantMort.Ajouter(pDet->G_pInfo());

		if (filtre.find('L') != -1 && pDet->G_pInfo()->EstLibere() && listeLibereIncarcere.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeLibereIncarcere.Ajouter(pDet->G_pInfo());
		if (filtre.find('I') != -1 && (!pDet->G_pInfo()->EstLibere()) && pDet->G_pInfo()->G_dateCondamnationConcatine() != "" && listeLibereIncarcere.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeLibereIncarcere.Ajouter(pDet->G_pInfo());

		if (filtre.find('C') != -1 && pDet->G_pInfo()->G_dateCondamnationConcatine() != "" && listeCondamneEnProces.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeCondamneEnProces.Ajouter(pDet->G_pInfo());
		if (filtre.find('P') != -1 && pDet->G_pInfo()->G_dateCondamnationConcatine() == "" && listeCondamneEnProces.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listeCondamneEnProces.Ajouter(pDet->G_pInfo());

		if (filtre.find('+') != -1 
			&& !pDet->G_pInfo()->EstLibere() 
			&& stod(pDet->G_pInfo()->JoursRestants()) / stod(pDet->G_pInfo()->G_duree()) < (1.0 / 3.0)
			&& listePlusMoinsTier.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listePlusMoinsTier.Ajouter(pDet->G_pInfo());

		if (filtre.find('-') != -1 
			&& !pDet->G_pInfo()->EstLibere()
			&& stod(pDet->G_pInfo()->JoursRestants()) / stod(pDet->G_pInfo()->G_duree()) > (1.0 / 3.0)
			&& listeFiltree.EstPresent(pDet->G_pInfo()->G_matricule()) == nullptr)
			listePlusMoinsTier.Ajouter(pDet->G_pInfo());

		pDet = pDet->G_pProchain();
	}

	// Pour multiple filtres, dés qu'on trouve que le detenu n'est pas dans la liste, il est éliminé.
	// Le détenu doit se trouver dans TOUTES les listes qui ont été populés.
	if (filtre.length() > 1)
	{
		pDet = ListeDetenus.G_pPremier();
		bool ajouter;

		while (pDet)
		{
			ajouter = true;
			if (listeSexe.G_pPremier() && !listeSexe.EstPresent(pDet->G_pInfo()->G_matricule()))
				ajouter = false;
			if (listeVivantMort.G_pPremier() && !listeVivantMort.EstPresent(pDet->G_pInfo()->G_matricule()))
				ajouter = false;
			if (listeLibereIncarcere.G_pPremier() && !listeLibereIncarcere.EstPresent(pDet->G_pInfo()->G_matricule()))
				ajouter = false;
			if (listeCondamneEnProces.G_pPremier() && !listeCondamneEnProces.EstPresent(pDet->G_pInfo()->G_matricule()))
				ajouter = false;
			if (listePlusMoinsTier.G_pPremier() && !listePlusMoinsTier.EstPresent(pDet->G_pInfo()->G_matricule()))
				ajouter = false;

			if (ajouter == true)
				listeFiltree.Ajouter(pDet->G_pInfo());

			pDet = pDet->G_pProchain();
		}
	}
	else
	{
		// 1 filtre. 
		if (filtre.find('M') == -1 || filtre.find('F') == -1)
			listeFiltree += listeSexe;
		if (filtre.find('V') == -1 || filtre.find('D') == -1)
			listeFiltree += listeVivantMort;
		if (filtre.find('L') == -1 || filtre.find('I') == -1)
			listeFiltree += listeLibereIncarcere;
		if (filtre.find('C') == -1 || filtre.find('P') == -1)
			listeFiltree += listeCondamneEnProces;
		if (filtre.find('+') == -1 || filtre.find('-') == -1)
			listeFiltree += listePlusMoinsTier;
	}

	// Envoyer au fichier, quitte la fonction.
	if (option == "fichier")
	{
		string FicOut;
		afficherEnTete();
		cout << "Nom du fichier qui recevra la liste:";
		cin >> FicOut;
		ofstream fichier(FicOut, ios::app);

		Detenu::AfficherEnTeteFichier(fichier);
		listeFiltree.Exporter(fichier);
		cout << "Ecriture de la liste filtrée en cours...\n";
		cout << "Écriture de " << listeFiltree.G_nbElements() << " détenus dans le fichier " << FicOut << "\n";
		system("pause");
		fichier.close();
		messageDeConfirmation();
		return;
	}

	// Afficher la liste, populé de détenus qui respecte la critère de filtre(s).
	cout << "Filtre appliqué: " << filtresUtilises << endl;
	Detenu::AfficherEnTete();
	listeFiltree.Afficher();

	system("pause");
	return;
}

// ##############################
// trier()
// trier (en appelant la fonction avec les bons paramétres) selon le choix de l'utilisateur.
// ##############################
void Context::trier()
{
	char Choix;
	Choix = menuTrier();
	if (Choix != 'Q')
	{
		switch (Choix)
		{
		case '1':
			trierListe("Matricule", "croissant"); 
			break;
		case '2': 
			trierListe("Matricule", "décroissant");
			break;
		case '3': 
			trierListe("Nom", "croissant");
			break;
		case '4': 
			trierListe("Nom", "décroissant");
			break;
		case '5': 
			trierListe("Age", "croissant"); 
			break;
		case '6': 
			trierListe("Age", "décroissant"); 
			break;
		case '7':
			trierListe("Durée de peine", "croissant"); 
			break;
		case '8': 
			trierListe("Durée de peine", "décroissant"); 
			break;
		default: break;
		}
	}
	return;
}

// ##############################
// menuTrier()
// Menu options pour trier la liste.
// ##############################
char Context::menuTrier()
{
	char Choix;

	afficherEnTete();
	cout << "\n\nTri de la liste des abonnements\n\n";
	cout << "\tTrier par:\n\n";
	cout << "\t\t1-Matricule (.:)\n";
	cout << "\t\t2-Matricule (:.)\n";
	cout << "\t\t3-Nom  (.:)\n";
	cout << "\t\t4-Nom  (:.)\n";
	cout << "\t\t5-Age (.:)\n";
	cout << "\t\t6-Age (:.)\n";
	cout << "\t\t7-Durée de peine (.:)\n";
	cout << "\t\t8-Durée de peine (:.)\n\n";
	cout << "\t\tQ-retour au menu Principal\n";

	cout << "\t\tVotre choix:";
	cin >> Choix;

	return toupper(Choix);
}

// ##############################
// trierListe(string Critere, string Ordre)
// afficher le processus de trier, message de completion. 
// ##############################
void Context::trierListe(string Critere, string Ordre)
{
	afficherEnTete();
	cout << "\n\nTri " << Ordre << " selon " << Critere << " en cours ...";
	ListeDetenus.Trier(Critere, Ordre);
	cout << "\nTri complété\n";
	cout << "---------------------------------------------\n\n";

	system("pause");

	return;
}

// ##############################
// confirmation(string msg)
// afficher le message de confirmation formatté
// ##############################
char Context::confirmation(string msg)
{
	char Choix;
	cout << "\t" << msg << "\n\n";
	cout << "\t\tC-Confirmer\n";
	cout << "\t\tA-ou autre touches pour Annuler\n";

	cout << "\t\tVotre choix:";
	cin >> Choix;
	return toupper(Choix);
}

// ##############################
// messageDeConfirmation()
// afficher un message de confirmation générique.
// ##############################
void Context::messageDeConfirmation()
{
	afficherEnTete();
	cout << "\n\n\t-*-*-*-*Opération traitée avec succès-*-*-*-*\n\n\n";

	system("pause");

	return;
}

// ##############################
// supprimer()
// supprimer un détenu de la liste selon par matricule.
// ##############################
void Context::supprimer()
{
	string matricule;
	char Choix;
	afficherEnTete();

	cout << "\n\n\n\tMatricule à supprimer:";
	cin >> matricule;

	Noeud<Detenu>* pDet = ListeDetenus.EstPresent(matricule);

	if (pDet)
	{
		cout << "-------------------------------------------\n";
		cout << "\n\nInformations du détenu " << matricule << ":\n\n";
		cout << "-------------------------------------------\n";
		pDet->G_pInfo()->Afficher(true);
	}
	else
	{
		cout << "Numéro de matricule invalide." << endl;
		return;
	}

	Choix = confirmation("Voulez vous le supprimer?");
	switch (toupper(Choix))

	{
	case 'C':
		ListeDetenus.Supprimer(matricule);
		if (!ListeDetenus.EstPresent(matricule))
			messageDeConfirmation();
		break;
	default:
		break;
	}
}

// ##############################
// vider()
// vider la liste.
// ##############################
void Context::vider()
{
	char Choix;
	afficherEnTete();
	cout << "\n\n\t";
	Choix = confirmation("Êtes-vous sûr de vouloir vider la liste?");

	switch (toupper(Choix))
	{
	case 'C':
		ListeDetenus.Vider();
		messageDeConfirmation();
		break;
	default:
		break;
	}
}

// ##############################
// dateMaintenantConcatine(string separateur)
// retourner la date d'aujourd'hui en YYYYMMJJ par défaut ou, par exemple, YYYY-MM-JJ, si paramétre est spécifié.
// ##############################
string Context::dateMaintenantConcatine(string separateur)
{
	// Struct de type tm pour stocké les données du temps système.
	tm TempsSysteme;
	// Pour chercher le temps système, en secondes.
	time_t TempsMaintenant;

	time(&TempsMaintenant);
	// Convertir le temps actuel en type tm.
	localtime_s(&TempsSysteme, &TempsMaintenant);
	cout << TempsSysteme.tm_mon << endl;

	return to_string(TempsSysteme.tm_year + 1900) + separateur 
		+ (to_string(TempsSysteme.tm_mon).length() == 1 ? "0" + to_string(TempsSysteme.tm_mon) : to_string(TempsSysteme.tm_mon)) + separateur 
		+ (to_string(TempsSysteme.tm_mday).length() == 1 ? "0" + to_string(TempsSysteme.tm_mday) : to_string(TempsSysteme.tm_mday));
}

// ##############################
// chargerPiecesDossiers()
// charger les pièces au dossier.
// ##############################
void Context::chargerPiecesDossiers()
{
	string nomFichier;

	afficherEnTete();
	cout << "\n\nAjout de pièces aux dossiers des détenus à partir d'un fichier\n\n";
	cout << "Fichier à charger:";
	cin >> nomFichier;


	cout << "-- Chargement de " << nomFichier << " en cours ...\n";

	// Importation du fichier.
	int nbRejets = 0;
	int nbChargements = importerDossiers(nomFichier, nbRejets);
	cout << "-- " << nbChargements << " pièces chargées\n";
	if (nbRejets > 0)
		cout << "-- " << nbRejets << " pièces rejetées (sans détenu)\n";
	cout << "Chargement terminé.\n\n";
	system("pause");
}

// ##############################
// importerDossiers(string nomFichier, int& rejets)
// importer les pièces au dossier, instancier les objets PieceDossier, attacher l'objet à la liste du détenu.
// ##############################
int Context::importerDossiers(string nomFichier, int& rejets)
{
	ifstream FicIn(nomFichier);
	string ligneCourante;
	int compteurLigne = 0;
	int compteurChargements = 0;
	Parseur<PieceDossier> ParDos(";", NB_CHAMPS_DOSSIER);
	Noeud<Detenu>* pDet = nullptr;

	while (FicIn.good())
	{
		getline(FicIn, ligneCourante);
		compteurLigne++;

		if (ligneCourante[0] != '#' && ligneCourante != "")
		{
			string valeurs[NB_CHAMPS_DOSSIER];
			try
			{
				analyserLigneDossier(ligneCourante);
				ParDos.Decouper(ligneCourante, valeurs);

				pDet = ListeDetenus.EstPresent(valeurs[0]);

				if (!pDet)
					throw 1;
				
				pDet->G_pInfo()->G_pDossier()->Ajouter(ParDos.Instancier(valeurs));

				compteurChargements++;

			}
			catch (...)
			{
				rejets++;
			}
		}
	}

	FicIn.close();

	return compteurChargements;
}

// ##############################
// analyserLigneDossier(string ligneCourante)
// ##############################
void Context::analyserLigneDossier(string ligneCourante)
{
	Parseur<Detenu> ParseTemp(";", NB_CHAMPS_DOSSIER);

	// 1. NOMBRE DE CHAMPS TROP PETIT
	if (ParseTemp.CompteurChamp(ligneCourante) < NB_CHAMPS_DOSSIER)
		throw 1;

	// 2. NOMBRE DE CHAMPS TROP GRAND
	if (ParseTemp.CompteurChamp(ligneCourante) > NB_CHAMPS_DOSSIER)
		return;

	string tempVals[NB_CHAMPS_DETENU];
	ParseTemp.Decouper(ligneCourante, tempVals);

	// 3. UN CHAMP QUI EST TROP PETIT (certains peut étre vide, par contre.
	int longueursMin[NB_CHAMPS_DETENU] = { EXACTE_MATRICULE,	// Matricule
										10,						// La Date en YYYY-MM-JJ
										3,						// Type, 3 caractères
										0 };					// Commentaire. Peut-être vide.
	int indiceChamp = ParseTemp.ValiderMinLongeurChamps(NB_CHAMPS_DETENU, longueursMin, tempVals);
	if (indiceChamp != -1)
		throw 1;

	// 4. UN CHAMP QUI DÉPASSE LE LONGUEUR MAXIMUM
	int longueursMax[NB_CHAMPS_DOSSIER] = { EXACTE_MATRICULE,	// Matricule
										10,						// La Date en YYYY-MM-JJ
										3,						// Type, 3 caractères
										140 };					// Commentaire. Max longueur d'un tweet.
	indiceChamp = ParseTemp.ValiderMaxLongeurChamps(NB_CHAMPS_DETENU, longueursMax, tempVals);
	if (indiceChamp != -1)
		throw 1;

	// 5. FORMAT DE CHAMP ERRONÉ (matricule)
	if (tempVals[0].length() != EXACTE_MATRICULE)
		throw 1;

	return;
}

// ##############################
// optionOuiNon(string phrase)
// ##############################
char Context::optionOuiNon(string phrase)
{
	char Choix;
	cout << "Voulez vous " << phrase << "?" << endl;
	cout << "(O)Oui / (N)Non: ";
	cin >> Choix;
	return toupper(Choix);
}

// ##############################
// ajouterPieceAuDossier(Noeud<Detenu>* pDetenu)
// ##############################
void Context::ajouterPieceAuDossier(Noeud<Detenu>* pDetenu)
{
	string commentaire;
	string tampon;
	char Choix;
	string valeurs[4];

	afficherEnTete();
	cout << "\n\nNouvelle pièce au dossier du matricule " << pDetenu->G_pInfo()->G_matricule() << "\n";
	cout << "\nType de pièce:";

	Choix = menuTypeDePiece();

	cout << "\nEntrez le texte de la pièce:";
	getline(cin, tampon);
	getline(cin, commentaire);

	valeurs[0] = pDetenu->G_pInfo()->G_matricule();
	valeurs[1] = dateMaintenantConcatine("-");
	switch (Choix)
	{
	case 'E':
		valeurs[2] = "EJU";
		break;
	case 'I':
		valeurs[2] = "RDI";
		break;
 	case 'C':
		valeurs[2] = "COM";
		break;
	default:
		break;
	}
	valeurs[3] = commentaire;	

	Choix = confirmation("Confirmer la nouvelle pièce");

	switch (toupper(Choix))
	{
	case 'C':
		pDetenu->G_pInfo()->G_pDossier()->Ajouter(new PieceDossier(valeurs));
		messageDeConfirmation();
		break;
	default:break;
	}
}

// ##############################
// menuTypeDePiece()
// ##############################
char Context::menuTypeDePiece()
{
	char Choix;
	cout << "\tE- Etape judiciaire\n";
	cout << "\t\tI- Rapport d'incident\n";
	cout << "\t\tC- Commentaire\n\n";

	cout << "\t\tQ-retour au menu précédent\n";
	cout << "\t\tVotre choix:";
	cin >> Choix;
	return toupper(Choix);
}
