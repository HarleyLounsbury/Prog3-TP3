// Noeud.h
// Fichier template de classe Noeud
//
// Auteur: Harley Lounsbury
// Date: 2019-11-01


// ##############################
// Structure de la classe.
// ##############################
template <class T>
class Noeud {
private:
	T* pInfo;
	Noeud<T>* pProchain;
	Noeud<T>* pPrecedent;

public:
	Noeud(T* pGenerique);
	T* G_pInfo() { return pInfo; }
	Noeud* G_pProchain() { return pProchain; }
	Noeud* G_pPrecedent() { return pPrecedent; }
	void S_pProchain(Noeud* pP) { pProchain = pP; }
	void S_pPrecedent(Noeud* pP) { pPrecedent = pP; }
	~Noeud();
};	

// ##############################
// Constructeur
// ##############################
template <class T>
Noeud<T>::Noeud(T* pGenerique)
{
	pInfo = pGenerique;
	pProchain = nullptr;
	pPrecedent = nullptr;
}

// ##############################
// Déstructeur
// ##############################
template <class T>
Noeud<T>::~Noeud()
{
	delete pInfo;
}