#include "sae.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- Menu (Les deux) ----------------

int affichMenu(void) {

  int choix;

  printf("=======================================\n");
  printf("MENU PRINCIPAL\n");
  printf("=======================================\n");
  printf("0)\tQuitter\n");
  printf("---------------------------------------\n");
  printf("1)\tGérer les logements\n");
  printf("2)\tGérer les locataires\n");
  printf("3)\tGérer les demandes de logement\n");
  printf("=======================================\n");
  printf("Choix :\t");
  scanf("%d", &choix);
  printf("\n\n");
  return choix;
}

void menu(void) {

  int tlogPers, tmaxPers=100;
  Personne *tabPers[100];
  char nomFichPers[31] = "../demandesEnregistrement.don";
  
  Locataire *tabLoc;
  char nomFichLoc[31] = "../locataires.don";
  int choix, tmaxLoc, tlogLoc;

  int taillemax=10;
  TypeLogem t2,t3,t4,t5,t6;

  tlogPers = chargeTabPers(nomFichPers, tabPers, tmaxPers);
  if (tlogPers < 0) {
    printf("Erreur lors du chargement\n");
    exit(1);
  }
  
  chargementLogem(&t2,&t3,&t4,&t5,&t6,taillemax);
  
  tabLoc = chargementLocataires(&tlogLoc, nomFichLoc, &tmaxLoc);
  if (tlogLoc < 0) {
    printf("Erreur lors du chargement du tableau des locataires\n");
    return;
  }

  choix = affichMenu();
  if (choix == 0) return;
  else if (choix == 1) {
    sousMenuLogem(&t2,&t3,&t4,&t5,&t6);
  }
  else if (choix == 2) {
    sousMenuLoc(tabLoc, nomFichLoc, tmaxLoc, tlogLoc);
  }
  else if (choix == 3) {
    sousMenuDem(&t2,&t3,&t4,&t5,&t6,tabLoc, &tlogLoc,tabPers, &tlogPers, &tmaxPers);
  }
  else printf("Choix inconnu\n");
  menu();

  free(tabLoc);
}

void sousMenuLogem(TypeLogem *t2,TypeLogem *t3,TypeLogem *t4,TypeLogem *t5,TypeLogem *t6){

  int choix;

  printf("============================================\n");
  printf("GESTION DES LOGEMENTS\n");
  printf("============================================\n");
  printf("0)\tRevenir en arrière\n");
  printf("--------------------------------------------\n");
  printf("1)\tAjouter un logement\n");
  printf("2)\tSupprimer un logement\n");
  printf("3)\tAfficher tous les logements\n");
  printf("4)\tAfficher les logements disponibles\n");
  printf("============================================\n");
  printf("Choix :\t");
  scanf("%d", &choix);
  printf("\n\n");

  if (choix == 0) return;
  else if (choix == 1) {
    ajouterLogem(t2,t3,t4,t5,t6);
    sauvegarde(*t2,*t3,*t4,*t5,*t6);
  }
  else if (choix == 2) {
    supprLogem(t2,t3,t4,t5,t6);
    sauvegarde(*t2,*t3,*t4,*t5,*t6);
  }
  else if (choix == 3) {
    affichToutLogem(*t2,*t3,*t4,*t5,*t6);
  }
  else if (choix == 4) {
    affichLogemDispo(*t2,*t3,*t4,*t5,*t6);
  }
  else printf("Choix inconnu\n");
}

void sousMenuLoc(Locataire tabLoc[], char* nomFich, int tmax, int tlog) {

  int choix, pos;

  printf("================================\n");
  printf("GESTION DES LOCATAIRES\n");
  printf("================================\n");
  printf("0)\tRevenir en arrière\n");
  printf("--------------------------------\n");
  printf("1)\tAfficher les locataires\n");
  printf("2)\tRechercher un locataire\n");
  printf("================================\n");
  printf("Choix :\t");
  scanf("%d%*c", &choix);
  printf("\n\n");

  if (choix == 0) return;
  else if (choix == 1) {
    affichLoc(tabLoc, tlog);
  }
  else if (choix == 2) {
    pos = rechercheLoc(tabLoc, tlog);
    affich1Loc(tabLoc[pos]);
    printf("====================================================================\n\n\n");
  }
  else printf("Choix inconnu\n");

  tabLoc = triLoc(tabLoc, tlog);
  sauvegardeLoc(tabLoc, tlog, nomFich);
}

void sousMenuDem(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6, Locataire tabLoc[], int *tlogLoc, Personne **tabPers, int* tlogPers, int* tmaxPers) {

  int choix;

  chargementDemandes(t2,t3,t4,t5,t6);

  printf("========================================\n");
  printf("GESTION DES DEMANDES DE LOGEMENT\n");
  printf("========================================\n");
  printf("0)\tRevenir en arrière\n");
  printf("----------------------------------------\n");
  printf("1)\tEnregistrer une demande\n");
  printf("2)\tAfficher les demandes\n");
  printf("3)\tTraiter les demandes en attente\n");
  printf("========================================\n");
  printf("Choix :\t");
  scanf("%d", &choix);
  printf("\n\n");

  if (choix == 0) return;
  else if (choix == 1){
    creerDemande(*t2,*t3,*t4,*t5,*t6,tabPers, tlogPers, tmaxPers);
  }
  else if (choix == 2){
    afficherToutesFiles(*t2,*t3,*t4,*t5,*t6);
  } 
  else if (choix == 3){
    traitDemandes(*t2,*t3,*t4,*t5,*t6, tabLoc, tlogLoc);
  }
  else printf("Choix inconnu\n");
}








// ---------------- Logements (Alexis) ----------------

void chargementLogem(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6,int taillemax){
  
  char type[3];
  FILE *fe;

  fe=fopen("../logements.don","r");
  if(fe==NULL){
    printf("Fichier introuvable\n");
    return;
  }

  (t2->tlog)=0;
  (t3->tlog)=0;
  (t4->tlog)=0;
  (t5->tlog)=0;
  (t6->tlog)=0;

  fscanf(fe,"%s ",type);

  while(!feof(fe)){

    if(strcmp(type,"T2")==0){
      if((t2->tlog)==taillemax){
        printf("Tableau trop petit - 2\n");
        fclose(fe);
        return;
      }
      fscanf(fe,"%d %d %d ", &t2->tabLogem[t2->tlog].numLogem, &t2->tabLogem[t2->tlog].m2, &t2->tabLogem[t2->tlog].locataire);
      (t2->tlog)++;
    }

    else if(strcmp(type,"T3")==0){
      if((t3->tlog)==taillemax){
        printf("Tableau trop petit - 3\n");
        fclose(fe);
        return;
      }
      fscanf(fe,"%d %d %d ",&t3->tabLogem[t3->tlog].numLogem,&t3->tabLogem[t3->tlog].m2, &t3->tabLogem[t3->tlog].locataire);
      (t3->tlog)++;
    }

    else if(strcmp(type,"T4")==0){
      if((t4->tlog)==taillemax){
        printf("Tableau trop petit - 4\n");
        fclose(fe);
        return;
      }
      fscanf(fe,"%d %d %d ",&t4->tabLogem[t4->tlog].numLogem,&t4->tabLogem[t4->tlog].m2, &t4->tabLogem[t4->tlog].locataire);
      (t4->tlog)++;
    }

    else if(strcmp(type,"T5")==0){
      if((t5->tlog)==taillemax){
        printf("Tableau trop petit - 5\n");
        fclose(fe);
        return;
      }
      fscanf(fe,"%d %d %d ",&t5->tabLogem[t5->tlog].numLogem,&t5->tabLogem[t5->tlog].m2, &t5->tabLogem[t5->tlog].locataire);
      (t5->tlog)++;
    }

    else{
      if((t6->tlog)==taillemax){
        printf("Tableau trop petit - 6\n");
        fclose(fe);
        return;
      }
      fscanf(fe,"%d %d %d ",&t6->tabLogem[t6->tlog].numLogem,&t6->tabLogem[t6->tlog].m2, &t6->tabLogem[t6->tlog].locataire);
      (t6->tlog)++;
    }
    fscanf(fe,"%s ",type);
  }
  fclose(fe);
}

void ajouterLogem(TypeLogem* t2,TypeLogem* t3,TypeLogem* t4,TypeLogem* t5,TypeLogem* t6){

  char type[3];
  int m2,test=0,numLogem;

  printf("===================================================\n");
  printf("AJOUTER UN LOGEMENT\n");
  printf("===================================================\n");

  printf("Numéro du nouveau logement : ");
  scanf("%d",&numLogem);
  while(numLogem<=0){
    printf("Erreur : Numéro incorrect. Veuillez retaper :\nNuméro du logement : ");
    scanf("%d",&numLogem);
  }

  printf("Nombre de m2 : ");
  scanf("%d",&m2);
  while(m2<=0){
    printf("Erreur : Superficie incorrecte. Veuillez retaper :\nNombre de m2 : ");
    scanf("%d",&m2);
  }
  
  printf("Type de logement (format : T2) : ");
  scanf("%s%*c",type);

  while(test!=1){

    if(strcmp(type,"T2")==0){
      t2->tabLogem[t2->tlog].numLogem=numLogem;
      t2->tabLogem[t2->tlog].m2=m2;
      t2->tabLogem[t2->tlog].locataire=0;
      (t2->tlog)++;
      test=1;
    }

    else if(strcmp(type,"T3")==0){
      t3->tabLogem[t3->tlog].numLogem=numLogem;
      t3->tabLogem[t3->tlog].m2=m2;
      t3->tabLogem[t3->tlog].locataire=0;
      (t3->tlog)++;
      test=1;
    }

    else if(strcmp(type,"T4")==0){
      t4->tabLogem[t4->tlog].numLogem=numLogem;
      t4->tabLogem[t4->tlog].m2=m2;
      t4->tabLogem[t4->tlog].locataire=0;
      (t4->tlog)++;
      test=1;
    }

    else if(strcmp(type,"T5")==0){
      t5->tabLogem[t5->tlog].numLogem=numLogem;
      t5->tabLogem[t5->tlog].m2=m2;
      t5->tabLogem[t5->tlog].locataire=0;
      (t5->tlog)++;
      test=1;
    }

    else if(strcmp(type,"T6")==0){
      t6->tabLogem[t6->tlog].numLogem=numLogem;
      t6->tabLogem[t6->tlog].m2=m2;
      t6->tabLogem[t6->tlog].locataire=0;
      (t6->tlog)++;
      test=1;
    }

    else{
      printf("Erreur : Type incorrect. Veuillez retaper :\nType de logement (format : T2) : ");
      scanf("%s%*c",type);
    }
  }

  printf("--------------------------------------------------------------------\n");
  printf("Logement ajouté\n");
  printf("====================================================================\n\n\n");

}

void affichToutLogem(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6){

  int i=0;

  printf("=====================================================================\n");
  printf("LISTE DE TOUT LES LOGEMENTS\n");
  printf("=====================================================================\n");
  printf("    Numéro du logement\t|  Nombre de mètre carrés\t|  Locataire\n");
  printf("---------------------------------------------------------------------\n");

  while(i!=(t2.tlog)){
    printf("T2) %d\t\t\t|  %d\t\t\t\t|  %d\n",t2.tabLogem[i].numLogem,t2.tabLogem[i].m2, t2.tabLogem[i].locataire);
    i++;
  }

  i=0;
  while(i!=(t3.tlog)){
    printf("T3) %d\t\t\t|  %d\t\t\t\t|  %d\n",t3.tabLogem[i].numLogem,t3.tabLogem[i].m2, t3.tabLogem[i].locataire);
    i++;
  }

  i=0;
  while(i!=(t4.tlog)){
    printf("T4) %d\t\t\t|  %d\t\t\t\t|  %d\n",t4.tabLogem[i].numLogem,t4.tabLogem[i].m2, t4.tabLogem[i].locataire);
    i++;
  }

  i=0;
  while(i!=(t5.tlog)){
    printf("T5) %d\t\t\t|  %d\t\t\t\t|  %d\n",t5.tabLogem[i].numLogem,t5.tabLogem[i].m2, t5.tabLogem[i].locataire);
    i++;
  }

  i=0;
  while(i!=(t6.tlog)){
    printf("T6) %d\t\t\t|  %d\t\t\t\t|  %d\n",t6.tabLogem[i].numLogem,t6.tabLogem[i].m2, t6.tabLogem[i].locataire);
    i++;
  }

  printf("=====================================================================\n\n\n");
}

void affichLogemDispo(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6){
  
  int i=0;

  printf("=====================================================================\n");
  printf("LISTE DES LOGEMENTS DISPONIBLES\n");
  printf("=====================================================================\n");
  printf("    Numéro du logement\t|  Nombre de mètre carrés\t|  Locataire\n");
  printf("---------------------------------------------------------------------\n");

  while(i!=(t2.tlog)){
    if(t2.tabLogem[i].locataire==0){
      printf("T2) %d\t\t\t|  %d\t\t\t\t|  %d\n",t2.tabLogem[i].numLogem,t2.tabLogem[i].m2, t2.tabLogem[i].locataire);
    }
    i++;
  }

  i=0;
  while(i!=(t3.tlog)){
    if(t3.tabLogem[i].locataire==0){
      printf("T3) %d\t\t\t|  %d\t\t\t\t|  %d\n",t3.tabLogem[i].numLogem,t3.tabLogem[i].m2, t3.tabLogem[i].locataire);
    }
    i++;
  }

  i=0;
  while(i!=(t4.tlog)){
    if(t4.tabLogem[i].locataire==0){
      printf("T4) %d\t\t\t|  %d\t\t\t\t|  %d\n",t4.tabLogem[i].numLogem,t4.tabLogem[i].m2, t4.tabLogem[i].locataire);
    }
    i++;
  }

  i=0;
  while(i!=(t5.tlog)){
    if(t5.tabLogem[i].locataire==0){
      printf("T5) %d\t\t\t|  %d\t\t\t\t|  %d\n",t5.tabLogem[i].numLogem,t5.tabLogem[i].m2, t5.tabLogem[i].locataire);
    }i++;
  }

  i=0;
  while(i!=(t6.tlog)){
    if(t6.tabLogem[i].locataire==0){
    printf("T6) %d\t\t\t|  %d\t\t\t\t|  %d\n",t6.tabLogem[i].numLogem,t6.tabLogem[i].m2, t6.tabLogem[i].locataire);
    }
    i++;
  }
  printf("=====================================================================\n\n\n");

}

int rechLogem(char type[],TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6,int numLogem){
  int i;
  if(strcmp(type,"T2")==0){
    for(i=0;i<t2.tlog;i++){
      if(t2.tabLogem[i].numLogem==numLogem){
        return i;
      }
    }
    return -1;
  }
  else if(strcmp(type,"T3")==0){
    for(i=0;i<t3.tlog;i++){
      if(t3.tabLogem[i].numLogem==numLogem){
        return i;
      }
    }
    return -1;
  }
  else if(strcmp(type,"T4")==0){
    for(i=0;i<t4.tlog;i++){
      if(t4.tabLogem[i].numLogem==numLogem){
        return i;
      }
    }
    return -1;
  }
  else if(strcmp(type,"T5")==0){
    for(i=0;i<t5.tlog;i++){
      if(t5.tabLogem[i].numLogem==numLogem){
        return i;
      }
    }
    return -1;
  }
  else if(strcmp(type,"T6")==0){
    for(i=0;i<t6.tlog;i++){
      if(t6.tabLogem[i].numLogem==numLogem){
        return i;
      }
    }
    return -1;
  }
  else{
    printf("Type inconnu");
    return -1;
  } 
}

void supprLogem(TypeLogem* t2,TypeLogem* t3,TypeLogem* t4,TypeLogem* t5,TypeLogem* t6){

  int i,numLogem,posi;
  char type[3];

  printf("==============================================\n");
  printf("SUPPRIMER UN LOGEMENT\n");
  printf("==============================================\n");

  printf("Numéro du logement à supprimer : ");
  scanf("%d",&numLogem);
  while(numLogem<=0){
    printf("Erreur : Numéro incorrect. Veuillez retaper :\nNuméro du logement : ");
    scanf("%d",&numLogem);
  }

  printf("Type du logement (format : T2) : ");
  scanf("%s%*c",type);
  posi=rechLogem(type,*t2,*t3,*t4,*t5,*t6,numLogem);

  if(posi==-1){
    printf("Logement inconnu\n");
  }

  else{
    if(strcmp(type,"T2")==0){
      for(i=posi;i<t2->tlog;i++){
        t2->tabLogem[i]=t2->tabLogem[i+1];
      }
      (t2->tlog)--;
    }
    else if(strcmp(type,"T3")==0){
      for(i=posi;i<t3->tlog;i++){
        t3->tabLogem[i]=t3->tabLogem[i+1];
      }
      (t3->tlog)--;
    }
    else if(strcmp(type,"T4")==0){
      for(i=posi;i<t4->tlog;i++){
        t4->tabLogem[i]=t4->tabLogem[i+1];
      }
      (t4->tlog)--;
    }
    else if(strcmp(type,"T5")==0){
      for(i=posi;i<t5->tlog;i++){
        t5->tabLogem[i]=t5->tabLogem[i+1];
      }
      (t5->tlog)--;
    }
    else{
      for(i=posi;i<t6->tlog;i++){
        t6->tabLogem[i]=t6->tabLogem[i+1];
      }
      (t6->tlog)--;
    }
    printf("----------------------------------------------\n");
    printf("Logement supprimé\n");
    printf("==============================================\n\n\n");
  }
}

void sauvegarde(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6){

  FILE *fs;
  int i;

  fs=fopen("Logement.txt","w");

  for(i=0;i<t2.tlog;i++){ 
    fprintf(fs,"T2 %d %d %d\n",t2.tabLogem[i].numLogem,t2.tabLogem[i].m2,t2.tabLogem[i].locataire);
  }

  for(i=0;i<t3.tlog;i++){ 
    fprintf(fs,"T3 %d %d %d\n",t3.tabLogem[i].numLogem,t3.tabLogem[i].m2,t3.tabLogem[i].locataire);
  }

  for(i=0;i<t4.tlog;i++){ 
    fprintf(fs,"T4 %d %d %d\n",t4.tabLogem[i].numLogem,t4.tabLogem[i].m2,t4.tabLogem[i].locataire);
  }

  for(i=0;i<t5.tlog;i++){ 
    fprintf(fs,"T5 %d %d %d\n",t5.tabLogem[i].numLogem,t5.tabLogem[i].m2,t5.tabLogem[i].locataire);
  }

  for(i=0;i<t6.tlog;i++){ 
    fprintf(fs,"T6 %d %d %d\n",t6.tabLogem[i].numLogem,t6.tabLogem[i].m2,t6.tabLogem[i].locataire);
  }

  fclose(fs);
}








// ---------------- Personnes (Lilian) ----------------

Personne lirePers(FILE *fe) {

  Personne pers;

  fscanf(fe, "%s %s %d %d %d ", pers.nom, pers.prenom, &pers.revenus, &pers.nbPersFoyer, &pers.valide);
  return pers;
}

void affichPers(Personne p) {

  printf("%s\t%s\t%d\t%d\t%d\n\n", p.nom, p.prenom, p.revenus, p.nbPersFoyer, p.valide);
}

int chargeTabPers(char *nomFich, Personne *tabPers[], int tmax) {

  FILE* fe;
  Personne pers;
  int i=0;

  fe = fopen(nomFich, "r");
  if (fe == NULL) {
    printf("Problème d'ouverture du fichier %s\n", nomFich);
    return -1;
  }

  pers = lirePers(fe);
  
  while (!feof(fe)) {
    
    if (i == tmax) {
	printf("Tableau trop petit\n");
	return -3;
      }
    
    if(verifPers(pers) == VRAI) {
      tabPers[i] = (Personne*) malloc (sizeof(Personne));
      if (tabPers[i] == NULL) {
	printf("Problème sur malloc d'une case\n");
	fclose(fe);
	libereTab(tabPers, i);
	return -2;
      }

      *tabPers[i] = pers;
      i++;
    }
    
    pers = lirePers(fe);
  }
  fclose(fe);
  return i;
}

Booleen verifPers(Personne pers) {

  int plafond;

  if (pers.valide == FAUX) return FAUX;
  
  if (pers.nbPersFoyer == 1) plafond = 20966;
  else if (pers.nbPersFoyer == 2) plafond = 27968;
  else if (pers.nbPersFoyer == 3) plafond = 33670;
  else if (pers.nbPersFoyer == 4) plafond = 40648;
  else if (pers.nbPersFoyer == 5) plafond = 47618;
  else if (pers.nbPersFoyer == 6) plafond = 53891;
  else plafond = 53891 + ((pers.nbPersFoyer-6)*6011);

  if (pers.revenus > plafond) return FAUX;
  else return VRAI;
}

void attributionPoints(Personne *p) {

  int nbPoints=0;
  char res;
  
  printf("Personne handicapée ? (o/n) ");
  scanf("%c%*c", &res);
  if (res=='o') {
    nbPoints=nbPoints+30;
  }

  printf("Personne victime de violences ? (o/n) ");
  scanf("%c%*c", &res);
  if (res=='o') {
    nbPoints=nbPoints+15;
  }

  printf("Personne hébergée ou logée temporairement ? (o/n) ");
  scanf("%c%*c", &res);
  if (res=='o') {
    nbPoints=nbPoints+15;
  }

  printf("Personne sans aucun logement ou menacée d'expulsion ? (o/n) ");
  scanf("%c%*c", &res);
  if (res=='o') {
    nbPoints=nbPoints+10;
  }

  printf("Personne logée dans un logement isalubre ou dangereux ? (o/n) ");
  scanf("%c%*c", &res);
  if (res=='o') {
    nbPoints=nbPoints+8;
  }

  p->nbPoints = nbPoints;
}


Personne** ajouterPers(Personne **tabPers, int *tlog, int *tmax) {

  Personne *p;

  p = (Personne*) malloc (sizeof(Personne));
  if (p==NULL) {
    printf("Erreur malloc\n");
    exit(1);
  }

  printf("Nom / Prénom : ");
  scanf("%s / %s", p->nom, p->prenom);

  printf("Nombre de personnes dans le foyer : ");
  scanf("%d", &p->nbPersFoyer);

  printf("Revenus du foyer : ");
  scanf("%d", &p->revenus);

  p->valide = 1;
  
  if (verifPers(*p) == FAUX) {
    printf("Désolé, cette personne ne correspond pas à nos critères de validité.\n");
    exit(1);
  }
  else {
    attributionPoints(p);
  
    printf("Numéro du locataire : ");
    scanf("%d", &p->numero);
    }

  tabPers[*tlog]=p;
  (*tlog)++;
  return tabPers;
}

void libereTab(Personne **tabPers, int taille) {

  int i;

  for(i=0 ; i<taille ; i++) {
    free(tabPers[i]);
  }
}








// ---------------- Locataires (Lilian) ----------------

Locataire lireLoc(FILE *fe) {

  Locataire loc;

  fscanf(fe, "%s %s %d %d %d %d %d %d", loc.identite.nom, loc.identite.prenom, &loc.identite.revenus, &loc.identite.nbPersFoyer, &loc.identite.valide, &loc.identite.nbPoints, &loc.identite.numero, &loc.logement);

  return loc;
}

Locataire* chargementLocataires(int * tLog, char* nomFich, int *tmax) {

  FILE *fe;
  Locataire loc;
  Locataire* tabLoc;
  int i=0;

  *tmax = 25;
  
  tabLoc = (Locataire*) malloc (sizeof(Locataire)*(*tmax));
  if (tabLoc == NULL) {
    printf("Problème malloc\n");
    exit(1);
  }

  fe = fopen(nomFich, "r");
  if (fe == NULL) {
    printf("Problème d'ouverture du fichier %s\n", nomFich);
    free(tabLoc);
    exit(1);
  }
  
  loc = lireLoc(fe);

  while (!feof(fe)) {

    if (i == *tmax) {
      reall(&tabLoc, tmax);
    }
    tabLoc[i] = loc;
    i++;
    loc = lireLoc(fe);
  }

  *tLog = i;
  return tabLoc;
}

void reall(Locataire** tabLoc, int *taille) {

  Locataire *tabTemp;
  *taille = *taille + 25;

  tabTemp = (Locataire*) realloc (*tabLoc, *taille * sizeof(Locataire));
  if (tabTemp == NULL) {
    printf("Problème sur le realloc\n");
    return;
  }
  else *tabLoc = tabTemp;
}

int comparerNomPrenom(char* nom1, char* prenom1, char* nom2, char* prenom2) {

  char nomPrenom1[100];
  char nomPrenom2[100];

  strcpy(nomPrenom1, nom1);
  strcat(nomPrenom1, prenom1);

  strcpy(nomPrenom2, nom2);
  strcat(nomPrenom2, prenom2);

  return (strcmp(nomPrenom1, nomPrenom2));
}

Locataire* triLoc(Locataire tabLoc[], int taille) {

  Locataire tmp;
  int i, cpt=0, cmp;

  for (i=0 ; i<taille-1 ; i++) {
    cmp = comparerNomPrenom(tabLoc[i].identite.nom, tabLoc[i].identite.prenom, tabLoc[i+1].identite.nom, tabLoc[i+1].identite.prenom);
    if (cmp > 0 ) {
      tmp = tabLoc[i];
      tabLoc[i] = tabLoc[i+1];
      tabLoc[i+1] = tmp;
      cpt++;
    }
  }
  if (cpt > 0) triLoc(tabLoc, taille-1);

  return tabLoc;
}

void affich1Loc(Locataire loc) {

  if (strlen(loc.identite.nom) < 8) {
    printf("%s\t\t\t%s\t\t%d\t\t\t%d\n", loc.identite.nom, loc.identite.prenom, loc.identite.numero, loc.logement);
    return;
  }
  printf("%s\t\t%s\t\t%d\t\t\t%d\n", loc.identite.nom, loc.identite.prenom, loc.identite.numero, loc.logement);

}

void affichLoc(Locataire tabLoc[], int taille) {

  int i;
  printf("===================================================================================\n");
  printf("Nom\t\t\tPrénom\t\tNuméro de locataire\tNuméro du logement\n");
  printf("-----------------------------------------------------------------------------------\n");
  for (i=0 ; i<taille ; i++) {
    affich1Loc(tabLoc[i]);
  }
  printf("===================================================================================\n\n\n");
}

int rechercheLoc(Locataire tabLoc[], int taille) {

  int numero;
  int deb = 0, fin = taille-1, m;

  printf("====================================================================\n");
  printf("Numéro du locataire : ");
  scanf("%d", &numero);
  printf("--------------------------------------------------------------------\n");
  
  while (deb <= fin) {
    m = (deb+fin)/2;

    if (tabLoc[m].identite.numero == numero) {
      return m;
    }
    else if (numero < tabLoc[m].identite.numero)
      fin = m-1;
    else
      deb = m+1;
  }
  return deb;
}

void sauvegardeLoc(Locataire tabLoc[], int tlog, char *nomFich) {

  FILE *fs;
  int i;

  fs = fopen(nomFich, "w");
  if (fs == NULL) {
    printf("Problème d'ouverture du fichier %s\n", nomFich);
    return;
  }

  for (i=0 ; i<tlog ; i++) {
    fprintf(fs, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", tabLoc[i].identite.nom, tabLoc[i].identite.prenom, tabLoc[i].identite.revenus, tabLoc[i].identite.nbPersFoyer, 1, tabLoc[i].identite.nbPoints, tabLoc[i].identite.numero, tabLoc[i].logement);
  }

  fclose(fs);
}








//  ---------------- Demandes (Les deux) ----------------

void chargementDemandes(TypeLogem *t2,TypeLogem* t3,TypeLogem *t4,TypeLogem* t5,TypeLogem* t6){
  
  char type[3],nom[31],prenom[31];
  int num;
  FILE *fe;

  fe=fopen("../demandes.don","r");
  if(fe==NULL){
    printf("Fichier introuvable\n");
    return;
  }

  t2->demandes.tete=NULL;
  t3->demandes.tete=NULL;
  t4->demandes.tete=NULL;
  t5->demandes.tete=NULL;
  t6->demandes.tete=NULL;

  fscanf(fe,"%s ",type);

  while(!feof(fe)){

    if(strcmp(type,"T2")==0){
      fscanf(fe,"%s %s %d ",nom,prenom,&num);
      t2->demandes=enfiler(t2->demandes,nom,prenom,num);
    }

    else if(strcmp(type,"T3")==0){
      fscanf(fe,"%s %s %d ",nom,prenom,&num);
      t3->demandes=enfiler(t3->demandes,nom,prenom,num);
    }

    else if(strcmp(type,"T4")==0){
      fscanf(fe,"%s %s %d ",nom,prenom,&num);
      t4->demandes=enfiler(t4->demandes,nom,prenom,num);
    }

    else if(strcmp(type,"T5")==0){
      fscanf(fe,"%s %s %d ",nom,prenom,&num);
      t5->demandes=enfiler(t5->demandes,nom,prenom,num);
    }

    else{
      fscanf(fe,"%s %s %d ",nom,prenom,&num);
      t6->demandes=enfiler(t6->demandes,nom,prenom,num);
    }
    fscanf(fe,"%s ",type);
  }
  fclose(fe);
}
 
File enfiler(File f,char nom[], char prenom[],int num){
  Maillon * tmp;
  tmp=(Maillon*)malloc(sizeof(Maillon));
  if(tmp==NULL){
    printf("Probleme allocation mémoire\n");
    return f;
  } 
  strcpy(tmp->val.nom,nom);
  strcpy(tmp->val.prenom,prenom);
  tmp->val.numero=num;
  tmp->suiv=NULL;
  if(estFileVide(f)){
    f.tete=tmp;
  }
  f.queue=tmp;
  return f;
}

Booleen estFileVide(File demandes){
  if(demandes.tete==NULL) return VRAI;
  return FAUX;
}

void traitDemandes(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6, Locataire tabLoc[], int *tlogLoc){

  int i;

  if(!estFileVide(t2.demandes)==0){
    for(i=0;i<t2.tlog;i++){
      if(t2.tabLogem[i].locataire==0){
        t2.tabLogem[i].locataire=t2.demandes.tete->val.numero;
        tabLoc[*tlogLoc].logement=t2.tabLogem[i].numLogem;
        tabLoc[*tlogLoc].identite=t2.demandes.tete->val;
        (*tlogLoc)++;
        printf("Logement n°%d attribué à la personne n°%d\n",t2.tabLogem[i].numLogem, tabLoc[(*tlogLoc)-1].identite.numero);
      }
    }
  }

  if(!estFileVide(t3.demandes)==0){
    for(i=0;i<t3.tlog;i++){
      if(t3.tabLogem[i].locataire==0){
        t3.tabLogem[i].locataire=t3.demandes.tete->val.numero;
        tabLoc[*tlogLoc].logement=t3.tabLogem[i].numLogem;
        tabLoc[*tlogLoc].identite=t3.demandes.tete->val;
        (*tlogLoc)++;
        printf("Logement n°%d attribué à la personne n°%d\n",t3.tabLogem[i].numLogem, tabLoc[(*tlogLoc)-1].identite.numero);
      }
    }
  }

  if(!estFileVide(t4.demandes)==0){
    for(i=0;i<t4.tlog;i++){
      if(t4.tabLogem[i].locataire==0){
        t4.tabLogem[i].locataire=t4.demandes.tete->val.numero;
        tabLoc[*tlogLoc].logement=t4.tabLogem[i].numLogem;
        tabLoc[*tlogLoc].identite=t4.demandes.tete->val;
        (*tlogLoc)++;
        printf("Logement n°%d attribué à la personne n°%d\n",t4.tabLogem[i].numLogem, tabLoc[(*tlogLoc)-1].identite.numero);
      }
    }
  }

  if(!estFileVide(t5.demandes)==0){
    for(i=0;i<t5.tlog;i++){
      if(t5.tabLogem[i].locataire==0){
        t5.tabLogem[i].locataire=t5.demandes.tete->val.numero;
        tabLoc[*tlogLoc].logement=t5.tabLogem[i].numLogem;
        tabLoc[*tlogLoc].identite=t5.demandes.tete->val;
        (*tlogLoc)++;
        printf("Logement n°%d attribué à la personne n°%d\n",t5.tabLogem[i].numLogem, tabLoc[(*tlogLoc)-1].identite.numero);
      }
    }
  }

  if(!estFileVide(t6.demandes)==0){
    for(i=0;i<t6.tlog;i++){
      if(t6.tabLogem[i].locataire==0){
        t6.tabLogem[i].locataire=t6.demandes.tete->val.numero;
        tabLoc[*tlogLoc].logement=t6.tabLogem[i].numLogem;
        tabLoc[*tlogLoc].identite=t6.demandes.tete->val;
        (*tlogLoc)++;
        printf("Logement n°%d attribué à la personne n°%d\n",t6.tabLogem[i].numLogem, tabLoc[(*tlogLoc)-1].identite.numero);
      }
    }
  }
}

File defiler(File f) {

  Maillon* tmp;

  if (estFileVide(f)) {
    printf("File vide\n");
    exit(1);
  }

  tmp = f.tete;
  if(f.tete == f.queue) {
    f.tete = NULL;
    f.queue = NULL;
  }
  else {
    f.tete = tmp->suiv;
  }
  return f;
}

void creerDemande(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6,Personne **tabPers, int* tlog, int* tmax){

  int numPers;
  char type[3];

  printf("Numéro de la personne (ou 0 si pas enregisté): ");
  scanf("%d",&numPers);

  if(numPers==0){
    tabPers = ajouterPers(tabPers, tlog, tmax);
  }

  printf("Type de logment demandé (Format: T2): ");
  scanf("%s",type);

  if(strcmp(type,"T2")==0){
    insertionFile(t2.demandes,*tabPers[numPers]);
  }

  else if(strcmp(type,"T3")==0){
    insertionFile(t3.demandes,*tabPers[numPers]);
  }

  else if(strcmp(type,"T4")==0){
    insertionFile(t4.demandes,*tabPers[numPers]);
  }

  else if(strcmp(type,"T5")==0){
    insertionFile(t5.demandes,*tabPers[numPers]);
  }

  else{
    insertionFile(t6.demandes,*tabPers[numPers]);
  }

  printf("Demande ajoutée à la liste\n");
}


Maillon* insererEnTete(Maillon* m, Personne p) {

  Maillon* tmp;

  tmp = (Maillon*) malloc(sizeof(Maillon));
  if(tmp == NULL) {
    printf("Erreur malloc\n");
    exit(1);
  }

  tmp->val = p;
  tmp->suiv = m;
  m = tmp;
  return m;
}


Maillon* insererTriee(Maillon* m, Personne p) {

  if(m == NULL) {
    m = insererEnTete(m, p);
  }
  else {
    if(p.nbPoints < m->val.nbPoints) {
      m = insererEnTete(m, p);
    }
    m->suiv = insererTriee(m->suiv, p);
  }
  return m;
}


File insertionFile(File demandes, Personne pers){

  if(estFileVide(demandes)) {
    demandes.tete = insererEnTete(demandes.tete, pers);
  }
  else {
    if(pers.nbPoints < demandes.tete->val.nbPoints) {
      demandes.tete = insererEnTete(demandes.tete, pers);
    }
    else {
      demandes.tete->suiv = insererTriee(demandes.tete->suiv, pers);
    }
  }
  return demandes;
}


void affich1File(File demandes) {

  Maillon* tmp = demandes.tete;

  while(tmp!=NULL) {
    printf("%s\t%s\t%d\t///\t", tmp->val.nom, tmp->val.prenom, tmp->val.numero);
    tmp = tmp->suiv;
  }
}


void afficherToutesFiles(TypeLogem t2,TypeLogem t3,TypeLogem t4,TypeLogem t5,TypeLogem t6) {

  printf("\n\n");
  printf("File d'attente pour les T2 : ");
  affich1File(t2.demandes);

  printf("\n\n==================================================\n");
  printf("File d'attente pour les T3 : ");
  affich1File(t3.demandes);

  printf("\n\n==================================================\n");
  printf("File d'attente pour les T4 : ");
  affich1File(t4.demandes);

  printf("\n\n==================================================\n");
  printf("File d'attente pour les T5 : ");
  affich1File(t5.demandes);

  printf("\n\n==================================================\n");
  printf("File d'attente pour les T6 : ");
  affich1File(t6.demandes);
  printf("\n\n");
}