#include <stdio.h>

// Les différentes structures :

typedef enum {FAUX, VRAI} Booleen;

typedef struct{
  int numLogem;
  int m2;
  int locataire;
}Logement;

typedef struct {
  char nom[31];
  char prenom[31];
  int revenus;
  int nbPersFoyer;
  int valide;
  int nbPoints;
  int numero;
}Personne;

typedef struct {
  Personne identite;
  int logement;
}Locataire;

typedef struct maillon {
  Personne val;
  struct maillon* suiv;
}Maillon;

typedef struct {
  Maillon* tete;
  Maillon* queue;
}File;

typedef struct {
  File demandes;
  int tlog;
  Logement tabLogem[10];
}TypeLogem;

// Menu :
/**
  \brief Affiche du menu et demande le choix de l'utilisateur
  \return le choix de l'utilisateur
*/
int affichMenu(void);

/**
  \brief Menu qui appelle les différentes fonction selon ce que retourne la fonction affichMenu
*/
void menu(void);

/**
  \brief Sous-menu de la partie logement qui affiche un menu, demande ce que veux faire l'utilisateur et appelle la bonne fonction 
  \param *t2 Pointeur sur la structure d'un type de logement
  \param *t3 Pointeur sur la structure d'un type de logement
  \param *t4 Pointeur sur la structure d'un type de logement
  \param *t5 Pointeur sur la structure d'un type de logement
  \param *t6 Pointeur sur la structure d'un type de logement
*/
void sousMenuLogem(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6);
/**
  \brief Sous-menu de la partie locataire qui affiche un menu, demande ce que veux faire l'utilisateur et appelle la bonne fonction 
  \param tabLoc Tableau des locataires
  \param tlogLoc Taille logique du tableau des locataires
  \param nomFich Nom du fichier des locataires 
  \param tmaxLoc Nombre maximal de locataires
*/
void sousMenuLoc(Locataire tabLoc[], char* nomFich, int tmaxLoc, int tlogLoc);

/**
  \brief Sous-menu de la partie demande qui affiche un menu, demande ce que veux faire l'utilisateur et appelle la bonne fonction 
  \param *t2 Pointeur sur la structure d'un type de logement
  \param *t3 Pointeur sur la structure d'un type de logement
  \param *t4 Pointeur sur la structure d'un type de logement
  \param *t5 Pointeur sur la structure d'un type de logement
  \param *t6 Pointeur sur la structure d'un type de logement
  \param tabLoc Tableau des locataires
  \param tlogLoc Taille logique du tableau des locataires
  \param tabPers Tableau des personnes
  \param tlogpers Taille logique du tableau des personnes
  \param tmaxPers Nombre maximal de personnes 
*/
void sousMenuDem(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6, Locataire tabLoc[], int* tlogLoc, Personne **tabPers, int* tlogPers, int* tmaxPers);





// Partie Logement :

/**
  \brief Chargement des structures des type de logements
  \param *t2 Pointeur sur la structure d'un type de logement
  \param *t3 Pointeur sur la structure d'un type de logement
  \param *t4 Pointeur sur la structure d'un type de logement
  \param *t5 Pointeur sur la structure d'un type de logement
  \param *t6 Pointeur sur la structure d'un type de logement
  \param taillemax Taille maximale des tableaux des logements
*/
void chargementLogem(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6,int taillemax);

/**
  \brief Ajoute un nouveau logement 
  \param *t2 Pointeur sur la structure d'un type de logement
  \param *t3 Pointeur sur la structure d'un type de logement
  \param *t4 Pointeur sur la structure d'un type de logement
  \param *t5 Pointeur sur la structure d'un type de logement
  \param *t6 Pointeur sur la structure d'un type de logement
*/
void ajouterLogem(TypeLogem* t2,TypeLogem* t3,TypeLogem* t4,TypeLogem* t5,TypeLogem* t6);

/**
  \brief Affiche tout les logements
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void affichToutLogem(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6);

/**
  \brief Affiche tout les logements disponibles
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void affichLogemDispo(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6);

/**
  \brief Recherche un logement
  \param type Type du logement recherché
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
  \param numLogem Numéro du logement recherché
  \return La position d'un logement ou -1 si il n"existe pas
*/
int rechLogem(char type[],TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6,int numLogem);

/**
  \brief Supprime un logement existant
  \param *t2 Pointeur sur la structure d'un type de logement
  \param *t3 Pointeur sur la structure d'un type de logement
  \param *t4 Pointeur sur la structure d'un type de logement
  \param *t5 Pointeur sur la structure d'un type de logement
  \param *t6 Pointeur sur la structure d'un type de logement
*/
void supprLogem(TypeLogem* t2,TypeLogem* t3,TypeLogem* t4,TypeLogem* t5,TypeLogem* t6);

/**
  \brief Sauvegarde les modifications dans un fichier
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void sauvegarde(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6);





// Partie Locataire :


/**
  \brief permet de lire une personne dans un fichier
  \param fe fichier ouvert en lecture
  \return la personne lue
*/
Personne lirePers(FILE *fe);

/**
  \brief chargement du fichier de personnes dans un tableau de pointeurs sur personnes
  \param nomFich nom du fichier à ouvrir
  \param tabPers tableau de pointeurs sur personnes
  \param tmax taille physique du tableau
  \return la taille logique du tableau
*/
int chargeTabPers(char *nomFich, Personne **tabPers, int tmax);

/**
  \brief vérifie si une personne est valide
  \param pers personne à vérifier
  \return si la personne est valide ou non
*/
Booleen verifPers(Personne pers);

/**
  \brief affiche une personne
  \param p personne à afficher
*/
void affichPers(Personne p);  

/**
  \brief attribue des points à une personne selon certains critères
  \param p personne à qui on doit affecter les points
*/
void attributionPoints(Personne *p);

/**
  \brief libere le tableau de personnnes de la mémoire
  \param tabPers tableau à libérer
  \param taille taille logique du tableau
*/
void libereTab(Personne **tabPers, int taille);

/**
  \brief ajoute une personne dans le tableau
  \param tabPers tableau de personne
  \param tlog taille logique du tableau
  \param tmax taille physique du tableau
  \return
*/
Personne** ajouterPers(Personne** tabPers, int *tlog, int *tmax);


/**
  \brief lit un locataire dans un fichier
  \param fe fichier dans lequel lire
  \return le locataire lu
*/
Locataire lireLoc(FILE *fe);

/**
  \brief charge le fichier de locataires dans un tableau
  \param tlog taille logique du tableau
  \param nomFich nom du fichier de locataires
  \param tmax taille physique du tableau
  \return un tableau de locataires
*/
Locataire* chargementLocataires(int *tLog, char* nomFich, int *tmax);

/**
  \brief réalloue un tableau de locataire plus grand
  \param tabLoc tableau de locataire à réallouer
  \param taille taille logique du tableau
*/
void reall(Locataire* tabLoc[], int *taille);

/**
  \brief compare les noms et prénoms de 2 personnes (par ordre alphabétique)
  \param nom1 nom de la première personne
  \param prenom1 prenom de la première personne
  \param nom2 nom de la deuxième personne
  \param prenom2 prenom de la deuxieme personne
  \return le résultat de la comparaison
*/
int comparerNomPrenom(char* nom1, char* prenom1, char* nom2, char* prenom2);

/**
  \brief tri le tableau des locataires par ordre alphabétiques de leurs noms puis de leur prénoms
  \param tabLoc tableau de locataires à trier
  \param taille taille logique du tableau
  \return le tableau de locataire trié
*/
Locataire* triLoc(Locataire tabLoc[], int taille);

/**
  \brief affiche un locataire
  \param loc locataire à afficher
*/
void affich1Loc(Locataire loc);

/**
  \brief affiche tous les locataires du tableau
  \param tabLoc tableau de locataires
  \paramtaille taille logique du tableau
*/
void affichLoc(Locataire tabLoc[], int taille);

/**
  \brief recherche un locataire dans un tableau de locataires trié
  \param tabLoc tableau de locataire trié
  \param taille taille logique du tableau
  \return position du loataire dans le tableau
*/
int rechercheLoc(Locataire tabLoc[], int taille);

/**
  \brief sauvegarde le tableau des locataires dans le fichier
  \param tabLoc tableau de locataires
  \param tlog taille logique du tableau
  \param nomFich nom du fichier dans lequel sauvegarder
*/
void sauvegardeLoc(Locataire tabLoc[], int tlog, char *nomFich);





// Partie Demande :

/**
  \brief Affiche toute les demandes
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void affichDemandes(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6);

/**
  \brief Permet de savoir si une file est vide
  \param demandes File que l'on teste
  \return Si la file est vide ou non
*/
Booleen estFileVide(File demandes);

/**
  \brief Attribue les logement disponibles aux premières demandes dans la file
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void traitDemandes(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6, Locataire tabLoc);

/**
  \brief Ajoute une nouvelle demande dans la file des demandes
  \param t2 Structure d'un type de logement
  \param t3 Structure d'un type de logement
  \param t4 Structure d'un type de logement
  \param t5 Structure d'un type de logement
  \param t6 Structure d'un type de logement
*/
void creerDemande(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6,Personne *tabPers);

/**
  \brief Insert une demande dans la file des demandes à la bonne position
  \param demandes File des demandes
  \param pers Personne à ajouter dans cette file
*/
void insetionFile(File demandes, Personne pers);

/**
  \brief Ajoute une personne à la file
  \param f File 
  \param nom Nom de la personne à ajouter 
  \param prenom Prenom de la personne à ajouter 
  \param num Numéro de la personne à ajouter 
  \return La file avec le nouvelle personne
*/
File enfiler(File f,char nom[], char prenom[],int num);

/**
   \brief Charge les demandes dans des files
   \param t2 Structure d'un type de logement
   \param t3 Structure d'un type de logement
   \param t4 Structure d'un type de logement
   \param t5 Structure d'un type de logement
   \param t6 Structure d'un type de logement
*/
void chargementDemandes(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6);

/**
   \brief affiche la file d'un type de logement
   \param demandes file des demandes d'un type de logement
*/
void affich1File(File demandes);

/**
   \brief affiche toutes les files d'attentes de logement
   \param t2 Structure d'un type de logement
   \param t3 Structure d'un type de logement
   \param t4 Structure d'un type de logement
   \param t5 Structure d'un type de logement
   \param t6 Structure d'un type de logement
*/
void afficherToutesFiles(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6);

/**
  \brief Insère une personne en tete
  \param m maillon dans lequel insérer
  \param p personne a ajouter
  \return le maillon après insertion
*/
Maillon* insererEnTete(Maillon* m, Personne p);

/**
  \brief permet d'insérer de façon triée dans une file (enfin je crois)
  \param m maillon dans lequel insérer
  \param p personne a ajouter  
  \return le maillon après insertion
*/
Maillon* insererTriee(Maillon* m, Personne p);
