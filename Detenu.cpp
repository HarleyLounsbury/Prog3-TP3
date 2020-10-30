// Detenu.cpp
// Fichier de d�finitions pour le syst�me de gestion de d�tenus.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include "Biblio.h"

// ##############################
// Constructeur - param�tr�
// Prend un tableau de string de valeurs. 
// ##############################
Detenu::Detenu(string valeurs[])
{
	mat = valeurs[0];
	prenom = valeurs[1];
	nom = valeurs[2];
	sexe = valeurs[3];
	anneeNaiss = valeurs[4];
	moisNaiss = valeurs[5];
	jourNaiss = valeurs[6];
	anneeDet = valeurs[7];
	moisDet = valeurs[8];
	jourDet = valeurs[9];
	anneeCon = valeurs[10];
	moisCon = valeurs[11];
	jourCon = valeurs[12];
	duree = valeurs[13];
	anneeDec = valeurs[14];
	moisDec = valeurs[15];
	jourDec = valeurs[16];

	dateLiberation = 0;
}

// ##############################
// calculePeine()
// retourne la dur�e de la peine formatt�: "X jours (Y ans, Z jours)" - X = total jours, Y = Le nombre d'ann�es, Z = le nombre de jours restant.
// retourne simplement "(<1 ans)" si c'est moins d'un ans.
// ##############################
string Detenu::calculePeine()
{
	if (duree == "")
		return "";
	double nbAnnees;
	nbAnnees = stoi(duree);
	if (nbAnnees / 365 >= 1)
		return " jours (" + to_string((int)(nbAnnees / 365.24)) + " ans, " + to_string((int)nbAnnees % 365) + " jours)";

	return "(<1 ans)";
}

// ##############################
// calculeAge()
// retourne l'�ge en nombre d'ann�es complet�e depuis la naissance. 
// ##############################
int Detenu::calculeAge()
{
	// Struct de type tm pour stock� les donn�es du temps syst�me.
	tm TempsSysteme;
	// Pour chercher le temps syst�me, en secondes.
	time_t TempsMaintenant;

	time(&TempsMaintenant);
	// Convertir le temps actuel en type tm.
	localtime_s(&TempsSysteme, &TempsMaintenant);

	return TempsSysteme.tm_year - stoi(anneeNaiss) + 1900;
}

// ##############################
// Afficher()
// afficher l'information pertinent sur une ligne.
// ##############################
void Detenu::Afficher()
{
	cout << left;
	cout << setw(7) << mat;
	cout << setw(21) << prenom;
	cout << setw(21) << nom;
	cout << setw(6) << sexe;
	cout << setw(4) << anneeNaiss << "-" << setw(2) <<  moisNaiss << "-" << setw(3) << jourNaiss;
	cout << setw(4) << anneeDet << "-" << setw(2) << moisDet << "-" << setw(3) << jourDet;
	cout << setw(4) << anneeCon << "-" << setw(2) << moisCon << "-" << setw(3) << jourCon;
	if (duree == "0")
		cout << setw(6) << "";
	else
		cout << setw(6) << duree;
	cout << setw(4) << anneeDec << "-" << setw(2) << moisDec << "-" << setw(2) << jourDec;
	cout << endl;
}

// ##############################
// Afficher(bool unique)
// Afficher un d�tenu en mode unique. 
// ##############################
void Detenu::Afficher(bool unique)
{
	cout << "\n\nInformations du d�tenu " << mat << ":\n\n";
	cout << "-------------------------------------------\n";
	cout << "\tNom:\t\t\t\t" << nom << endl;
	cout << "\tPr�nom:\t\t\t\t" << prenom << endl;
	cout << "\t�ge:\t\t\t\t" << calculeAge() << endl;
	cout << "\tSexe:\t\t\t\t" << sexe << endl;
	cout << "\tD�but d�tention:\t\t\t" << anneeDet << "-" << moisDet << "-" << jourDet << endl;
	cout << "\tComdamnation:\t\t\t" << anneeCon << "-" << moisCon << "-" << jourCon << endl;
	cout << "\tDur�e de la peine:\t\t";
	if (duree == "0")
		cout << "";
	else
		cout << duree;
	cout << calculePeine() << endl;
	cout << "\tD�c�s:\t\t\t\t" << anneeDec << "-" << moisDec << "-" << jourDec << endl;
	cout << "\tPi�ces � son dossier:\t\t" << piecesDossier.G_nbElements() << endl;
	cout << "-------------------------------------------\n";
}

// ##############################
// Exporter(ostream& of) 
// envoyer les donn�es s�par�s d'un ; dans le flux.
// ##############################
void Detenu::Exporter(ostream& of)
{
	of << mat << ";";
	of << prenom << ";";
	of << nom << ";";
	of << sexe << ";";
	of << anneeNaiss << ";";
	of << moisNaiss << ";";
	of << jourNaiss << ";";
	of << anneeDet << ";";
	of << moisDet << ";";
	of << jourDet << ";";
	of << anneeCon << ";";
	of << moisCon << ";";
	of << jourCon << ";";
	if (duree == "0")
		of << ";";
	else
		of << duree << ";";
	of << anneeDec << ";";
	of << moisDec << ";";
	of << jourDec << ";";
	of << endl;

	return;
}

// ##############################
// AfficherEnTete()
// m�thode statique pour afficher un en-t�te � l'�cran.
// ##############################
void Detenu::AfficherEnTete()
{
	cout << left;
	cout << setw(7) << "Mat";
	cout << setw(21) << "Pr�nom";
	cout << setw(21) << "Nom";
	cout << setw(6) << "Sexe";
	cout << setw(11) << "Naissance";
	cout << setw(11) << "Detention";
	cout << setw(11) << "Condamnati";
	cout << setw(6) << "Peine";
	cout << setw(11) << "D�ces";
	cout << endl;
	cout << setw(103) << setfill('-') << "-" << setfill(' ') << endl;

	return;
}

// ##############################
// AfficherEnTeteFichier(ostream& of)
// m�thode statique pour envoyer l'en-t�te dans le flux.
// ##############################
void Detenu::AfficherEnTeteFichier(ostream& of)
{
	of << "#Matricule;Pr�nom;Nom;Sexe;NaisAAAA;Nais-MM;Nais-JJ;D�tention_AAAA;D�tention_MM;D�tention_JJ;Condamnation-AAAA;Condamnation-MM;Condamnation-JJ;Dur�e;D�c�s_AAAA;D�c�s_MM;D�c�s_JJ;\n";
	
	return;
}

// ##############################
// G_matricule()
// retourne le matricule.
// ##############################
string Detenu::G_matricule()
{
	return mat;
}

// ##############################
// S_dateCondamnation(string vals[])
// Mutateur pour la date de condamnation. Prend les trois valeurs dans un tableau en param�tre. 
// ##############################
void Detenu::S_dateCondamnation(string vals[])
{
	anneeCon = vals[0];
	moisCon = vals[1];
	jourCon = vals[2];

	return;
}

// ##############################
// S_dateDeces(string vals[])
// Mutateur pour la date de d�c�s. Prend les trois valeurs dans un tableau en param�tre. 
// ##############################
void Detenu::S_dateDeces(string vals[])
{
	anneeDec = vals[0];
	moisDec = vals[1];
	jourDec = vals[2];

	return;
}

// ##############################
// G_nom()
// retourne le nom
// ##############################
string Detenu::G_nom()
{
	return nom;
}

string Detenu::G_prenom()
{
	return prenom;
}

// ##############################
// G_duree()
// retourne la dur�e de la peine (nombre de jours)
// ##############################
string Detenu::G_duree()
{
	return duree;
}

// ##############################
// G_dateNaissConcatine()
// retourne la date de naissance concatin�e YYYYMMJJ
// ##############################
string Detenu::G_dateNaissConcatine()
{
	return anneeNaiss + moisNaiss + jourNaiss;
}

// ##############################
// G_dateDecesConcatine()
// retourne la date de d�c�s concatin�e YYYYMMJJ
// ##############################
string Detenu::G_dateDecesConcatine()
{
	return anneeDec + moisDec + jourDec;
}

// ##############################
// G_sexe()
// retourne sexe.
// ##############################
string Detenu::G_sexe()
{
	return sexe;
}

// ##############################
// EstLibere()
// Conditions d'�tre lib�r�: detenu(e) est mort, d�tenu(e) n'a pas �t� condamn� (encore? besoin de r�f�rence judiciaire), detenu(e) a termin� sa penitence. 
// ##############################
bool Detenu::EstLibere()
{
	if (G_dateDecesConcatine() != "")
		return true;

	if (G_dateCondamnationConcatine() == "")
		return true;

	struct tm TM;
	time_t condamnationDepuisEpoch;
	time_t maintenant(time(0));

	TM.tm_year = stoi(anneeCon) - 1900;
	TM.tm_mon = stoi(moisCon) - 1;
	TM.tm_mday = stoi(jourCon);
	TM.tm_hour = 0;
	TM.tm_min = 0;
	TM.tm_sec = 0;
	condamnationDepuisEpoch = mktime(&TM);

	dateLiberation = condamnationDepuisEpoch + ((time_t)(stod(duree) * 24 * 60 * 60));

	if (difftime(dateLiberation, maintenant) <= 0)
		return true;

	return false;

}

// ##############################
// G_dateCondamnationConcatine()
// retourne la date de condamnation concatin�e YYYYMMJJ 
// ##############################
string Detenu::G_dateCondamnationConcatine()
{
	return anneeCon + moisCon + jourCon;
}

// ##############################
// JoursRestants()
// retourne le nombre de jours restants de la peine.  
// ##############################
string Detenu::JoursRestants()
{
	if (EstLibere())
		return "0";

	double JoursRestants = (dateLiberation - time(0)) / 60.0 / 60.0 / 24.0;

	return to_string(JoursRestants);
}

// ##############################
// Detenu::G_pDossier()
// retourne l'adresse de la liste de pieces au dossier.
// ##############################
Liste<PieceDossier>* Detenu::G_pDossier()
{
	return &piecesDossier;
}

// ##############################
// validerDate(string annee, string mois, string jour)
// valider que les champs de date sont bien une date valide. 
// ##############################
bool Detenu::validerDate(string annee, string mois, string jour)
{
	int iJour = stoi(jour);
	int iMois = stoi(mois);
	int iAnnee = stoi(annee);

	if (iJour < 1 || iJour > 31 || iMois < 1 || iMois > 12)
		return false;

	if ((iMois == 4 || iMois == 6 || iMois == 9 || iMois == 11) && iJour == 31)
	{
		return false;
	}
	else if ((iMois == 2) && (iAnnee % 4 == 0) && iJour > 29) {
		return false;

	}
	else if ((iMois == 2) && (iAnnee % 4 != 0) && iJour > 28) {
		return false;
	}

	return true;
}

