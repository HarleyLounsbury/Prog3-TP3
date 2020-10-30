// Liste.h
// Fichier de class Liste
// Liste est une usine de Liste, c'est-à-dire une liste doublement chaînée générique.
// Liste a fini comme une hybride: les méthodes de lignes 31 à 41 inclusivement sont particulier aux objets de la classe Detenu.
// Par Harley Lounsbury
// 2019-11-01

// ##############################
// Structure de la classe.
// ##############################
template <class T>
class Liste
{
private:
	Noeud<T>* pPremier;
	Noeud<T>* pDernier;
	int nbElements;

public:
	Liste();
	void Ajouter(T* pGenerique);
	int G_nbElements();
	void Afficher();
	void Afficher(int NombreALaFois);
	void Exporter(ostream& of);
	void Vider();
	Noeud<T>* G_pPremier();
	Liste operator+=(Liste);

	// Méthodes pour gérer une liste d'objets de classe Detenu.
	Noeud<T>* EstPresent(string mat);
	void Supprimer(string mat);
	Liste& Trier(string critere, string ordre);

	void InsererParNomCroiss(T* pGenerique);
	void InsererParNomDecroiss(T* pGenerique);
	void InsererParMatriculeCroiss(T* pGenerique);
	void InsererParMatriculeDecroiss(T* pGenerique);
	void InsererParPeineCroiss(T* pGenerique);
	void InsererParPeineDecroiss(T* pGenerique);
	void InsererParAgeCroiss(T* pGenerique);
	void InsererParAgeDecroiss(T* pGenerique);
};

// ##############################
// Liste() - Constructeur par défaut.
// ##############################
template <class T>
Liste<T>::Liste()
{
	pPremier = nullptr;
	pDernier = nullptr;
	nbElements = 0;
}


// ##############################
// Ajouter(T* pGenerique) - Ajouter des éléments à la liste. Par défaut, ceci est en pile.
// ##############################
template <class T>
void Liste<T>::Ajouter(T* pGenerique)
{
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	if (pPremier == nullptr)
	{
		pDernier = pNeoNoeud;
		pPremier = pNeoNoeud;
		nbElements++;
		return;
	}

	Noeud<T>* pCourant;

	pCourant = pPremier;
	pPremier->S_pPrecedent(pNeoNoeud);
	pPremier = pNeoNoeud;
	pPremier->S_pProchain(pCourant);

	nbElements++;

	return;
}

// ##############################
// G_nbElements() - retourne le nombre d'éléments dans la liste.
// ##############################
template<class T>
int Liste<T>::G_nbElements()
{
	return nbElements;
}

// ##############################
// Afficher la liste.
// Objets dans la liste doivent avoir une fonction publique Afficher()
// ##############################
template <class T>
void Liste<T>::Afficher()
{
	Noeud<T>* pCourant = pPremier;
	while (pCourant)
	{
		pCourant->G_pInfo()->Afficher();

		pCourant = pCourant->G_pProchain();
	}

	return;
}

// ##############################
// Afficher(int nombreALaFois) - afficher dans le console un nombre d'éléments, puis prend un pause.
// Objets dans la liste doivent avoir une fonction publique Afficher()
// ##############################
template<class T>
void Liste<T>::Afficher(int nombreALaFois)
{
	Noeud<T>* pCourant = pPremier;
	int compteur = 0;
	while (pCourant)
	{
		pCourant->G_pInfo()->Afficher();
		compteur++;
		if (compteur % nombreALaFois == 0)
		{
			system("pause");
			pCourant->G_pInfo()->AfficherEnTete();
		}
		pCourant = pCourant->G_pProchain();

	}

	return;
}

// ##############################
// Exporter(ostream& of) - pour exporter la liste en entière
// Objets dans la liste doivent avoir une fonction publique Exporter()
// ##############################
template<class T>
void Liste<T>::Exporter(ostream& of)
{
	Noeud<T>* pCourant = pPremier;
	while (pCourant)
	{
		pCourant->G_pInfo()->Exporter(of);

		pCourant = pCourant->G_pProchain();
	}

	return;
}

// ##############################
// G_pPremier() - retourne le pointer vers le premier Noeud<T>
// ##############################
template<class T>
Noeud<T>* Liste<T>::G_pPremier()
{
	return pPremier;
}

// ##############################
// operator+=(Liste<T> lParam) - surcharge de l'opérateur +=. Pratique pour fusionner deux listes.
// La fonction ne prend pas en charge le possibilité de doublons une fois fusionnés, car chaque objet peut en avoir de la critère particulière pour être identiques. 
// ##############################
template <class T>
Liste<T> Liste<T>::operator+=(Liste<T> lParam)
{
	Noeud<T>* pCourant = lParam.pPremier;
	while (pCourant)
	{
		Ajouter(new T(*(pCourant->G_pInfo())));
		pCourant = pCourant->G_pProchain();
	}

	return *this;
}

// ##############################
// Vider() - vider la liste, libérer de la mémoire allouée dynamiquement.
// ##############################
template<class T>
void Liste<T>::Vider()
{
	Noeud<T>* pCourant = pPremier;

	while (pCourant)
	{
		Noeud<T>* pSupprimer = pCourant;
		pCourant = pCourant->G_pProchain();
		delete pSupprimer;
	}
	pPremier = nullptr;
	pDernier = nullptr;
	nbElements = 0;
}

// ########################################################################################################################
// FONCTIONS POUR UNE LISTE DE LA CLASSE DETENU
// ########################################################################################################################

// ##############################
// Trouver un detenu selon son matricule. Cette fonction est particulier pour fonctionner avec une liste de type Detenu.
// ##############################
template<class T>
Noeud<T>* Liste<T>::EstPresent(string mat)
{
	Noeud<T>* pCourant = pPremier;
	while (pCourant)
	{
		if (pCourant->G_pInfo()->G_matricule() == mat)
			return pCourant;
		pCourant = pCourant->G_pProchain();
	}

	return nullptr;
}

// ##############################
// Trouver un detenu selon son matricule. Cette fonction est particulier pour fonctionner avec une liste de type Detenu.
// ##############################
template <class T>
Liste<T>& Liste<T>::Trier(string critere, string ordre)
{
	Liste listeTmp;
	Noeud<T>* pCourant = pPremier;

	while (pCourant)
	{
		if (critere == "Nom" && ordre == "croissant")
			listeTmp.InsererParNomCroiss(pCourant->G_pInfo());
		if (critere == "Nom" && ordre == "décroissant")
			listeTmp.InsererParNomDecroiss(pCourant->G_pInfo());
		if (critere == "Matricule" && ordre == "croissant")
			listeTmp.InsererParMatriculeCroiss(pCourant->G_pInfo());
		if (critere == "Matricule" && ordre == "décroissant")
			listeTmp.InsererParMatriculeDecroiss(pCourant->G_pInfo());
		if (critere == "Age" && ordre == "croissant")
			listeTmp.InsererParAgeCroiss(pCourant->G_pInfo());
		if (critere == "Age" && ordre == "décroissant")
			listeTmp.InsererParAgeDecroiss(pCourant->G_pInfo());
		if (critere == "Durée de peine" && ordre == "croissant")
			listeTmp.InsererParPeineCroiss(pCourant->G_pInfo());
		if (critere == "Durée de peine" && ordre == "décroissant")
			listeTmp.InsererParPeineDecroiss(pCourant->G_pInfo());

		pCourant = pCourant->G_pProchain();
	}
	*this = listeTmp;
	return *this;
}

template<class T>
void Liste<T>::Supprimer(string mat)
{
	if (pPremier == nullptr)
		return;

	Noeud<T>* pAnterieur = nullptr;
	Noeud<T>* pSuivant = nullptr;
	Noeud<T>* pADetruire = EstPresent(mat);

	if (pADetruire)
	{
		pAnterieur = pADetruire->G_pPrecedent();
		pSuivant = pADetruire->G_pProchain();
		if (pAnterieur)
			pAnterieur->S_pProchain(pSuivant);
		else
			//Supprimer le 1er noeud de la liste
			pPremier = pSuivant;

		if (pSuivant)
			pSuivant->S_pPrecedent(pAnterieur);
		else
			//Supprimer le dernier noeud de la liste
			pDernier = pAnterieur;
		nbElements--;
		delete pADetruire;
		return;
	}

	return;
}

// ##############################
// Méthodes pour insérer dans une liste de classe Detenu, selon le besoin. Leurs appels se font dans Trier()
// ##############################
template<class T>
void Liste<T>::InsererParNomCroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}
	 
	if (pNeoNoeud->G_pInfo()->G_nom() < pPremier->G_pInfo()->G_nom())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_nom() < pCourant->G_pProchain()->G_pInfo()->G_nom())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParNomDecroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (pNeoNoeud->G_pInfo()->G_nom() > pPremier->G_pInfo()->G_nom())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_nom() > pCourant->G_pProchain()->G_pInfo()->G_nom())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParMatriculeCroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (pNeoNoeud->G_pInfo()->G_matricule() < pPremier->G_pInfo()->G_matricule())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_matricule() < pCourant->G_pProchain()->G_pInfo()->G_matricule())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParMatriculeDecroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (pNeoNoeud->G_pInfo()->G_matricule() > pPremier->G_pInfo()->G_matricule())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_matricule() > pCourant->G_pProchain()->G_pInfo()->G_matricule())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParPeineCroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (stoi(pNeoNoeud->G_pInfo()->G_duree()) < stoi(pPremier->G_pInfo()->G_duree()))
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (stoi(pNeoNoeud->G_pInfo()->G_duree()) < stoi(pCourant->G_pProchain()->G_pInfo()->G_duree()))
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParPeineDecroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (stoi(pNeoNoeud->G_pInfo()->G_duree()) > stoi(pPremier->G_pInfo()->G_duree()))
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (stoi(pNeoNoeud->G_pInfo()->G_duree()) > stoi(pCourant->G_pProchain()->G_pInfo()->G_duree()))
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParAgeCroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (pNeoNoeud->G_pInfo()->G_dateNaissConcatine() > pPremier->G_pInfo()->G_dateNaissConcatine())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_dateNaissConcatine() > pCourant->G_pProchain()->G_pInfo()->G_dateNaissConcatine())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}

template<class T>
void Liste<T>::InsererParAgeDecroiss(T* pGenerique)
{
	nbElements++;
	Noeud<T>* pNeoNoeud = new Noeud<T>(pGenerique);

	//Inserer dans une liste vide
	if (pPremier == nullptr)
	{
		pPremier = pNeoNoeud;
		pDernier = pNeoNoeud;
		return;
	}

	if (pNeoNoeud->G_pInfo()->G_dateNaissConcatine() < pPremier->G_pInfo()->G_dateNaissConcatine())
	{
		//Inserer en premier
		pPremier->S_pPrecedent(pNeoNoeud);
		pNeoNoeud->S_pProchain(pPremier);
		pPremier = pNeoNoeud;
		return;
	}
	Noeud<T>* pCourant = pPremier;
	while (pCourant->G_pProchain())
	{
		if (pNeoNoeud->G_pInfo()->G_dateNaissConcatine() < pCourant->G_pProchain()->G_pInfo()->G_dateNaissConcatine())
		{
			//Insérer au millieu
			pNeoNoeud->S_pProchain(pCourant->G_pProchain());
			pNeoNoeud->S_pPrecedent(pCourant);
			pCourant->G_pProchain()->S_pPrecedent(pNeoNoeud);
			pCourant->S_pProchain(pNeoNoeud);
			return;
		}
		pCourant = pCourant->G_pProchain();
	}
	//Inserer à la fin
	pNeoNoeud->S_pPrecedent(pDernier);
	pDernier->S_pProchain(pNeoNoeud);
	pDernier = pNeoNoeud;

	return;
}