// Biblio.h
// Fichier en-tête de références pour le système de gestion de détenus.
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <ctime>

using namespace std;

#include "Noeud.h"
#include "Liste.h"
#include "PieceDossier.h"
#include "Detenu.h"
#include "Exception.h"
#include "Parseur.h"
#include "Context.h"

const int NB_CHAMPS_DETENU = 17;
const int NB_CHAMPS_DOSSIER = 4;

// Longueurs de champs de détenus.
const int EXACTE_MATRICULE = 6;
const int MIN_PRENOM = 1;
const int MAX_PRENOM = 20;
const int MIN_NOM = 1;
const int MAX_NOM = 20;
const int EXACTE_SEXE = 1;
const int EXACTE_ANNEE = 4;
const int EXACTE_MOIS = 2;
const int EXACTE_JOUR = 2;
const int MIN_DUREE = 1;
const int MAX_DUREE = 6;