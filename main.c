/** بِسْمِ الله مَجْرَاهَا وَ مُرْسَاهَا */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
 int minute;
 int heure;
 int jour;
} Horaire ;

typedef struct {
 int id;
 Horaire horaireDateSouhaite;
 Horaire dureeHeureMinute;
 int typeActivite;
 int idZoneSrc;
 int idZoneDest;
 int idLigne;
 int sens;
} Activite ;

typedef struct {
 int cin;
 int idZoneHabitat;
 int idZoneTravail;
 int idZoneCourante;
 int intentionVoyage;
 int idLigneCourante;
 int sensCourant;
 int idZoneDest;
 int nombreActivites;
 Activite activites[8];
} Personne ;

typedef struct {
 int id;
 int row;
 int column;
 int nombrePersonnes;
 Personne personnes[100];
} Zone ;

typedef struct {
 int row;
 int column;
 int codeRue;
} Subdivision ;

typedef struct {
 int idZoneSrc;
 int idZoneDest;
 int distance;
 Horaire dureeApproximative;
 int nombresubdivisions;
 Subdivision parcours[20];
} Troncon ;

typedef struct {
 int id;
 int nombreZones;
 int idZones[10];
} Ligne ;

typedef struct {
 int id;
 int idLigne;
 int sens;
 Horaire horaireDateDepart;
} Tache ;

typedef struct {
 int zoneSrc;
 int zoneDest;
 int idLigne;
 int sens;
 int idBus;
 Horaire dateVente;
 int distance;
 int prix;
} Ticket ;

typedef struct {
 int id;
 int idZoneCourante;
 int row;
 int column;
 int enRoute;
 int idLigneCourante;
 int sensCourant;
 int nombreTaches;
 Tache taches[10];
 int nombrePassagers;
 Personne passagers[50];
 int nombreTickets;
 Ticket tickets[250];
} Bus ;

typedef struct {
 int rue;
 int zone;
 int bus;
} caseCarte ;

//chargement de fichier zone

void chargerZones(Zone zones[], int *nombreZones)
{
    FILE *fic =fopen("zones.txt", "r");
    int i=0;
    while (!feof(fic)) {
        fscanf(fic, "%d %d %d", &zones[i].id, &zones[i].row, &zones[i].column);
        i++;
    }
    *nombreZones=i;
    fclose(fic);
}

//afficher de tableau zone

void afficherZones(Zone zones[], int nombreZones)
{
    printf("\nle contenu du tableau zone :\n");
    for(int i=0; i<nombreZones; i++){
        printf("%d %d %d \n",zones[i].id, zones[i].row, zones[i].column);
    }
    printf("\n");
}

//sauvgarder dans le nouveau fichier zone

void sauvegarderZones(Zone zones[], int nombreZones, char* nomFichier)
{
    FILE *fic =fopen(nomFichier, "w");
    for(int i=0; i<nombreZones; i++){
        fprintf(fic, "%d %d %d", zones[i].id, zones[i].row, zones[i].column);
        if (i < nombreZones - 1) {
            fprintf(fic, "\n");
        }
    }
    fclose(fic);
}

//chargement de fichier ligne

void chargerLignes(Ligne lignes[], int *nombreLignes)
{
    FILE *fic =fopen("lignes.txt", "r");
    int i=-1, j ,nbligne=0;
    while (!feof(fic)) {
        if(nbligne==0){
            i++;
            fscanf(fic, "%d %d", &lignes[i].id, &lignes[i].nombreZones);
            nbligne=lignes[i].nombreZones;
            j=0;
        }
        else{
            fscanf(fic, "%d", &lignes[i].idZones[j]);
            j++;
            nbligne--;
        }
    }
    *nombreLignes=i+1;
    fclose(fic);
}

//afficher le tableau ligne

void afficherLignes(Ligne lignes[], int nombreLignes)
{
    printf("\nle contenu du tableau ligne :\n");
    for(int i=0; i<nombreLignes; i++){
        printf("%d %d\n", i, lignes[i].nombreZones);
        for (int j = 0; j < lignes[i].nombreZones; j++) {
            printf("%d \n", lignes[i].idZones[j]);
        }
        printf("\n");
    }
}

//sauvgarder dans le nouveau fichier ligne

void sauvegarderLignes(Ligne lignes[],int nombreLignes, char* nomFichier)
{
    FILE *fic =fopen(nomFichier, "w");
    for(int i=0; i<nombreLignes; i++){
        fprintf(fic, "%d %d", i, lignes[i].nombreZones);
        for (int j = 0; j < lignes[i].nombreZones; j++) {
            fprintf(fic, "\n%d", lignes[i].idZones[j]);
        }
    }
    fclose(fic);
}

//chargement de fichier troncon

void chargerTroncons(Troncon troncons[], int *nombreTroncons)
{
    FILE *fic =fopen("troncons.txt", "r");
    int i = -1, j ,nbsub=0;
    while (!feof(fic)) {
        if(nbsub==0){
            i++;
            fscanf(fic, "%d %d %d %d %d %d %d", &troncons[i].idZoneSrc, &troncons[i].idZoneDest, &troncons[i].distance,
            &troncons[i].dureeApproximative.jour, &troncons[i].dureeApproximative.heure, &troncons[i].dureeApproximative.minute, &troncons[i].nombresubdivisions);
            nbsub= troncons[i].nombresubdivisions;
            j=0;
        }
        else{
            fscanf(fic, "%d %d %d", &troncons[i].parcours[j].row, &troncons[i].parcours[j].column, &troncons[i].parcours[j].codeRue);
            j++;
            nbsub--;
        }
    }
    *nombreTroncons=i+1;
    fclose(fic);
}

//affichage de tableau troncon

void afficherTroncons(Troncon troncons[], int nombreTroncons)
{
    printf("\nle contenu du tableau troncons :\n");
    for(int i=0; i<nombreTroncons; i++){
        printf("%d %d %d %d %d %d %d\n", troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance,
        troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure, troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);
        for (int j = 0; j < troncons[i].nombresubdivisions; j++) {
            printf("%d %d %d\n", troncons[i].parcours[j].row, troncons[i].parcours[j].column, troncons[i].parcours[j].codeRue);
        }
    }
}

//sauvegarde de nouveau fichier troncons

void sauvegarderTroncons(Troncon troncons[], int nombreTroncons, char* nomFichier)
{
    FILE *fic =fopen(nomFichier, "w");
    for(int i=0; i<nombreTroncons; i++){
        if (i > 0) {
            fprintf(fic, "\n");
        }
        fprintf(fic, "%d %d %d %d %d %d %d", troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance,
        troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure, troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);
        for (int j = 0; j < troncons[i].nombresubdivisions; j++) {
            fprintf(fic ,"\n%d %d %d", troncons[i].parcours[j].row, troncons[i].parcours[j].column, troncons[i].parcours[j].codeRue);
        }
    }
    fclose(fic);
}

//chargement de fichier flottebus

void chargerFlotteBus(Bus flotteBus[], int *nombreBus)
{
    FILE *fic =fopen("flotteBus.txt", "r");
    int i = -1, j ,nbtache=0;
    while (!feof(fic)) {
        if(nbtache==0){
            i++;
            fscanf(fic, "%d %d %d %d %d %d %d %d", &flotteBus[i].id, &flotteBus[i].idZoneCourante, &flotteBus[i].row, &flotteBus[i].column, &flotteBus[i].enRoute, &flotteBus[i].idLigneCourante, &flotteBus[i].sensCourant, &flotteBus[i].nombreTaches);
            nbtache= flotteBus[i].nombreTaches;
            j=0;
        }
        else{
            fscanf(fic, "%d %d %d %d %d %d", &flotteBus[i].taches[j].id, &flotteBus[i].taches[j].idLigne, &flotteBus[i].taches[j].sens, &flotteBus[i].taches[j].horaireDateDepart.jour, &flotteBus[i].taches[j].horaireDateDepart.heure, &flotteBus[i].taches[j].horaireDateDepart.minute);
            j++;
            nbtache--;
        }
    }
    *nombreBus=i;
    fclose(fic);
}

//affichage de tableau flottebus

void afficherFlotteBus(Bus flotteBus[], int nombreBus)
{
    printf("\nle contenu du tableau flottebus :\n");
    for(int i=0; i<nombreBus; i++){
        printf("%d %d %d %d %d %d %d %d\n", flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute, flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);
        for (int j = 0; j < flotteBus[i].nombreTaches; j++) {
            printf("%d %d %d %d %d %d\n", flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens, flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure, flotteBus[i].taches[j].horaireDateDepart.minute);
        }
    }
}

//sauvegarde de nouveau fichier flotteBus

void sauvegarderFlotteBus(Bus flotteBus[], int nombreBus, char* nomFichier){
    FILE *fic =fopen(nomFichier, "w");
    for(int i=0; i<nombreBus; i++){
        fprintf(fic ,"%d %d %d %d %d %d %d %d", flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute, flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);
        for (int j = 0; j < flotteBus[i].nombreTaches; j++) {
            fprintf(fic ,"\n%d %d %d %d %d %d", flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens, flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure, flotteBus[i].taches[j].horaireDateDepart.minute);
        }
        if (i < nombreBus - 1) {
            fprintf(fic, "\n");
        }
    }
    fclose(fic);
}

//Affecter personne a une zone

void affecterPersonneZone(Zone zones[], Personne pers)
{
    zones[pers.idZoneHabitat].personnes[zones[pers.idZoneHabitat].nombrePersonnes]=pers;
    zones[pers.idZoneHabitat].nombrePersonnes++;
}

//Le module recherche sens

int rechercherLigneSens(int idZoneSrc, int idZoneDest, Ligne lignes[], int nombreLignes) {
    for (int i = 0; i < nombreLignes; i++) {
        int src = -1, dest = -1;
        for (int j = 0; j < lignes[i].nombreZones; j++) {
            if (lignes[i].idZones[j] == idZoneSrc) {
                src = j;
            } else if (lignes[i].idZones[j] == idZoneDest) {
                dest = j;
            }
        }
        if (src != -1 && dest != -1) {
            if(src < dest){
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    return -1;
}

//generer des personnes

void genererPersonne(Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes)
{
    srand(time(NULL));
    Personne pers;

    for(int i=0;i<300;i++){
        pers.cin=i+1;
        pers.idZoneHabitat=rand()%10;
        do{
           pers.idZoneTravail=rand()%10;
        }while(pers.idZoneHabitat==pers.idZoneTravail);
        pers.idZoneCourante=pers.idZoneHabitat;
        pers.intentionVoyage=0;
        pers.idLigneCourante=-1;
        pers.sensCourant=-1;
        pers.idZoneDest=pers.idZoneTravail;
        pers.nombreActivites=3;
        //ACTIVITE 1
        pers.activites[0].id=0;
        pers.activites[0].horaireDateSouhaite.jour=0;
        pers.activites[0].horaireDateSouhaite.heure=6+rand()%3;
        pers.activites[0].horaireDateSouhaite.minute=0;
        pers.activites[0].dureeHeureMinute.jour=0;
        pers.activites[0].dureeHeureMinute.heure=8;
        pers.activites[0].dureeHeureMinute.minute=0;
        pers.activites[0].typeActivite=1;
        pers.activites[0].idZoneSrc=pers.idZoneHabitat;
        pers.activites[0].idZoneDest=pers.idZoneTravail;
        pers.activites[0].idLigne=0;
        pers.activites[0].sens=rechercherLigneSens(pers.activites[0].idZoneSrc, pers.activites[0].idZoneDest, lignes, nombreLignes);
        //ACTIVITE 2
        pers.activites[1].id=1;
        pers.activites[1].horaireDateSouhaite.jour=0;
        pers.activites[1].horaireDateSouhaite.heure=6+rand()%3;
        pers.activites[1].horaireDateSouhaite.minute=0;
        pers.activites[1].dureeHeureMinute.jour=0;
        pers.activites[1].dureeHeureMinute.heure=8;
        pers.activites[1].dureeHeureMinute.minute=0;
        pers.activites[1].typeActivite=2;
        pers.activites[1].idZoneSrc=pers.idZoneTravail;
        do{
            pers.activites[1].idZoneDest=rand()%10;
        }while(pers.activites[1].idZoneDest==pers.idZoneTravail || pers.activites[1].idZoneDest==pers.idZoneHabitat);
        pers.activites[1].idLigne=0;
        pers.activites[1].sens=rechercherLigneSens(pers.activites[1].idZoneSrc, pers.activites[1].idZoneDest, lignes, nombreLignes);
        //ACTIVITE 3
        pers.activites[2].id=2;
        pers.activites[2].horaireDateSouhaite.jour=0;
        pers.activites[2].horaireDateSouhaite.heure=6+rand()%3;
        pers.activites[2].horaireDateSouhaite.minute=0;
        pers.activites[2].dureeHeureMinute.jour=0;
        pers.activites[2].dureeHeureMinute.heure=8;
        pers.activites[2].dureeHeureMinute.minute=0;
        pers.activites[2].typeActivite=0;
        pers.activites[2].idZoneSrc=pers.activites[1].idZoneDest;
        pers.activites[2].idZoneDest=pers.idZoneHabitat;
        pers.activites[2].idLigne=0;
        pers.activites[2].sens=rechercherLigneSens(pers.activites[2].idZoneSrc, pers.activites[2].idZoneDest, lignes, nombreLignes);
        affecterPersonneZone(zones, pers);
    }
}

//Affichage personnes

void afficherPersonnes(Zone zones[], int nombreZones)
{
    printf("\nle contenu du tableau zone PERSONNES:\n");
    for(int i=0; i<nombreZones; i++){
        printf("la zone %d \n",i);
        for(int j=0; j<zones[i].nombrePersonnes; j++){
            printf("    le personne %d \n",j);
            printf("    %d %d %d %d %d %d %d %d %d \n",
            zones[i].personnes[j].cin,
            zones[i].personnes[j].idZoneHabitat,
            zones[i].personnes[j].idZoneTravail,
            zones[i].personnes[j].idZoneCourante,
            zones[i].personnes[j].intentionVoyage,
            zones[i].personnes[j].idLigneCourante,
            zones[i].personnes[j].sensCourant,
            zones[i].personnes[j].idZoneDest,
            zones[i].personnes[j].nombreActivites);
            for(int c=0; c<3; c++){
                printf("        l'activite %d \n",c);
                printf("        %d %d %d %d %d %d %d %d %d %d %d %d \n",
                       zones[i].personnes[j].activites[c].id,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.jour,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.heure,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.minute,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.jour,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.heure,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.minute,
                       zones[i].personnes[j].activites[c].typeActivite,
                       zones[i].personnes[j].activites[c].idZoneSrc,
                       zones[i].personnes[j].activites[c].idZoneDest,
                       zones[i].personnes[j].activites[c].idLigne,
                       zones[i].personnes[j].activites[c].sens);
            }
        }
        printf("\n");
    }
}

//Sauvegarde Persones dans sauvPersonnes.txt

void sauvegarderPersonnes(Zone zones[], int nombreZones, char* nomFichier)
{
    FILE *fic =fopen(nomFichier, "w");
    for(int i=0; i<nombreZones; i++){
        for(int j=0; j<zones[i].nombrePersonnes; j++){
            if (!(i == 0 && j == 0)) {
                fprintf(fic, "\n");
            }
            fprintf(fic,"%d %d %d %d %d %d %d %d %d",
            zones[i].personnes[j].cin,
            zones[i].personnes[j].idZoneHabitat,
            zones[i].personnes[j].idZoneTravail,
            zones[i].personnes[j].idZoneCourante,
            zones[i].personnes[j].intentionVoyage,
            zones[i].personnes[j].idLigneCourante,
            zones[i].personnes[j].sensCourant,
            zones[i].personnes[j].idZoneDest,
            zones[i].personnes[j].nombreActivites);
            for(int c=0; c<3; c++){
                fprintf(fic,"\n%d %d %d %d %d %d %d %d %d %d %d %d",
                       zones[i].personnes[j].activites[c].id,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.jour,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.heure,
                       zones[i].personnes[j].activites[c].horaireDateSouhaite.minute,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.jour,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.heure,
                       zones[i].personnes[j].activites[c].dureeHeureMinute.minute,
                       zones[i].personnes[j].activites[c].typeActivite,
                       zones[i].personnes[j].activites[c].idZoneSrc,
                       zones[i].personnes[j].activites[c].idZoneDest,
                       zones[i].personnes[j].activites[c].idLigne,
                       zones[i].personnes[j].activites[c].sens);
            }
        }
    }
    fclose(fic);
}

//Charger Persones dans le tableau zone depuis personnesSauv.txt

void chargerPersonnes(Zone zones[], int* nombreZones, char* nomFichier)
{
    FILE *fic = fopen(nomFichier, "r");
    Personne pers;
    int nbact = 0;
    int c = 0;
    while (!feof(fic)) {
        if (nbact == 0) {
            fscanf(fic, "%d %d %d %d %d %d %d %d %d",
                    &pers.cin,
                    &pers.idZoneHabitat,
                    &pers.idZoneTravail,
                    &pers.idZoneCourante,
                    &pers.intentionVoyage,
                    &pers.idLigneCourante,
                    &pers.sensCourant,
                    &pers.idZoneDest,
                    &pers.nombreActivites);
            nbact = pers.nombreActivites;
            c = 0;
        }
        else {
            fscanf(fic,"%d %d %d %d %d %d %d %d %d %d %d %d",
                    &pers.activites[c].id,
                    &pers.activites[c].horaireDateSouhaite.jour,
                    &pers.activites[c].horaireDateSouhaite.heure,
                    &pers.activites[c].horaireDateSouhaite.minute,
                    &pers.activites[c].dureeHeureMinute.jour,
                    &pers.activites[c].dureeHeureMinute.heure,
                    &pers.activites[c].dureeHeureMinute.minute,
                    &pers.activites[c].typeActivite,
                    &pers.activites[c].idZoneSrc,
                    &pers.activites[c].idZoneDest,
                    &pers.activites[c].idLigne,
                    &pers.activites[c].sens);
            c++;
            nbact--;
            if (nbact == 0) {
                affecterPersonneZone(zones, pers);
            }
        }
    }
    fclose(fic);
}

//Remplissage Totale

void remplissageComplet(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int *nombreZones, int *nombreLignes, int *nombreTroncons, int *nombreBus)
{
    chargerZones(zones, nombreZones);
    chargerLignes(lignes, nombreLignes);
    chargerTroncons(troncons, nombreTroncons);
    chargerFlotteBus(flotteBus, nombreBus);
}

//Affichage Totale

void affichageComplet(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    afficherZones(zones, nombreZones);
    afficherLignes(lignes, nombreLignes);
    afficherTroncons(troncons, nombreTroncons);
    afficherFlotteBus(flotteBus, nombreBus);
    afficherPersonnes(zones, nombreZones);
}

//Sauvegarde Totale

void sauvegardeComplete(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus, char *nomFichier)
{
    sauvegarderZones(zones, nombreZones, "zones_sauv.txt");
    sauvegarderLignes(lignes, nombreLignes, "lignes_sauv.txt");
    sauvegarderTroncons(troncons,nombreTroncons, "tronconsSauv.txt");
    sauvegarderFlotteBus(flotteBus, nombreBus, "flotteBusSauv.txt");
    sauvegarderPersonnes(zones, nombreZones, "personnesSauv.txt");
}

//calcule distance

int calculerDistance(int idZoneSrc, int idZoneDest, Ligne lignes[], Troncon troncons[], int nombreLignes, int nombreTroncons) {
    if(rechercherLigneSens(idZoneSrc, idZoneDest, lignes, nombreLignes) == -1)
        return -1;
    int dist = 0;
    if(rechercherLigneSens(idZoneSrc, idZoneDest, lignes, nombreLignes) == 1) {
        int aux = idZoneSrc;
        idZoneSrc = idZoneDest;
        idZoneDest = aux;
    }
    for (int i = 0; i < nombreTroncons; i++) {
        if (troncons[i].idZoneSrc == idZoneSrc) {
            for (int j = i; j < nombreTroncons && troncons[j].idZoneSrc != idZoneDest; j++) {
                dist += troncons[j].distance;
            }
        }
    }
    return dist;
}

//initialisation carte

void initialiserCarte(caseCarte cartegeo[20][20], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    for( int l=0; l<20 ; l++){
        for( int c=0; c<20 ; c++){
            cartegeo[l][c].rue=0;
            cartegeo[l][c].zone=-1;
            cartegeo[l][c].bus=-1;
        }
    }
    for( int i=0; i<nombreZones ; i++){
        int r=zones[i].row;
        int p=zones[i].column;
        cartegeo[r][p].zone=zones[i].id;
    }
    for( int i=0; i<nombreTroncons ; i++){
        for( int j=0; j<troncons[i].nombresubdivisions ; j++){
            int r=troncons[i].parcours[j].row;
            int p=troncons[i].parcours[j].column;
            cartegeo[r][p].rue=troncons[i].parcours[j].codeRue;
        }
    }
    for( int i=0; i<nombreBus ; i++){
        int r=flotteBus[i].row;
        int p=flotteBus[i].column;
        if(cartegeo[r][p].bus==-1)
            cartegeo[r][p].bus=flotteBus[i].id;
        else
            cartegeo[r][p].bus=100;
    }
}

//AFFICHAGE Carte

void afficherCarteGeo(caseCarte cartegeo[20][20] , Zone zones[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    for(int a=0; a<=20; a++){
        if(a<1)
            printf("    ");
        else{
            if(a<11)
                printf(" %d  ",a-1);
            else{
                if(a<20)
                    printf(" %d ",a-1);
                else
                    printf(" %d \n",a-1);
            }
        }
    }
    for(int a=0; a<=20; a++){
        if(a<1)
            printf("    ");
        else{
            if(a<20)
                printf("----");
            else
                printf("----\n");
        }
    }
    for(int l=0; l<20; l++){
        if(l<10)
            printf("  %d|",l);
        else
            printf(" %d|",l);
        for(int c=0; c<20; c++){
            if(cartegeo[l][c].zone != -1 && cartegeo[l][c].bus==-1){
                if(zones[cartegeo[l][c].zone].nombrePersonnes>9)
                    {printf("%dZ%d",zones[cartegeo[l][c].zone].nombrePersonnes,cartegeo[l][c].zone);}
                else
                    {printf(" %dZ%d",zones[cartegeo[l][c].zone].nombrePersonnes,cartegeo[l][c].zone);}
            }
            else if(cartegeo[l][c].zone!=-1 && cartegeo[l][c].bus!=-1){
                if(cartegeo[l][c].bus<100)
                    {printf("Z%db%d",cartegeo[l][c].zone,cartegeo[l][c].bus);}
                else
                    {printf("Z%dbM",cartegeo[l][c].zone);}
            }
            else if(cartegeo[l][c].bus!=-1){
                if(cartegeo[l][c].bus<100)
                {
                    if(flotteBus[cartegeo[l][c].bus].nombrePassagers>9)
                        printf("%db%d",flotteBus[cartegeo[l][c].bus].nombrePassagers,cartegeo[l][c].bus);
                    else
                        printf(" %db%d",flotteBus[cartegeo[l][c].bus].nombrePassagers,cartegeo[l][c].bus);
                }
                else
                    printf("[bM]");
            }
            else if(cartegeo[l][c].rue==3)
                printf("%c%c%c%c",205,205,205,205);
            else if(cartegeo[l][c].rue==12)
                printf("  %c ",186);
            else if(cartegeo[l][c].rue==5)
                printf("%c%c%c ",205,205,187);
            else if(cartegeo[l][c].rue==6)
                printf("  %c%c",201,205);
            else if(cartegeo[l][c].rue==9)
                printf("%c%c%c ",205,205,188);
            else if(cartegeo[l][c].rue==15)
                printf("%c%c%c%c",205,205,206,205);
            else
                printf("    ");
            if(c==19)
                printf("|");
        }
        printf("\n");
    }
    for(int p=0; p<=20; p++){
        if(p<1)
            printf("    ");
        else{
            if(p<20)
                printf("----");
            else
                printf("----\n");
        }
    }
}

//Détermination du numéro de la tâche

int numTacheSuivante(Horaire horaireCourant, int idBusCourant, Bus flotteBus[])
{
    for(int j=0 ; j<flotteBus[idBusCourant].nombreTaches ; j++){
        if(flotteBus[idBusCourant].taches[j].horaireDateDepart.jour==horaireCourant.jour
           && flotteBus[idBusCourant].taches[j].horaireDateDepart.heure==horaireCourant.heure
           && flotteBus[idBusCourant].taches[j].horaireDateDepart.minute==horaireCourant.minute){
            return(flotteBus[idBusCourant].taches[j].id);
        }
    }
    return -1;
}

//Déplacement Bus

void deplacerBus(caseCarte cartegeo[20][20], int idBusCourant, Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus, Horaire horaireCourant)
{
    int i=0,dest;
    while (flotteBus[idBusCourant].idZoneCourante != lignes[0].idZones[i])
    {
        i++;
    }
    if (flotteBus[idBusCourant].sensCourant == 0)
        dest = i + 1;
    else
        dest = i - 1;

    int tron = 0,sub=0;
    if (flotteBus[idBusCourant].sensCourant == 0)
    {
        while ((tron < nombreTroncons) && ((flotteBus[idBusCourant].idZoneCourante != troncons[tron].idZoneSrc) || (lignes[0].idZones[dest] != troncons[tron].idZoneDest)))
            tron++;
    }
    else
    {
        while ((tron < nombreTroncons) && ((flotteBus[idBusCourant].idZoneCourante != troncons[tron].idZoneDest) || (lignes[0].idZones[dest] != troncons[tron].idZoneSrc)))
            tron++;
    }

    while ((sub < troncons[tron].nombresubdivisions) && ((troncons[tron].parcours[sub].row != flotteBus[idBusCourant].row) || (troncons[tron].parcours[sub].column != flotteBus[idBusCourant].column)))
    {
        sub++;
    }

    //sens 0
    if(flotteBus[idBusCourant].sensCourant==0){
        if(sub==troncons[tron].nombresubdivisions){
            //l'emplacement de bus est une zone
            int z=0;
            while(z<nombreZones && flotteBus[idBusCourant].idZoneCourante!=zones[z].id)
                z++;
            if(flotteBus[idBusCourant].row==zones[z].row && flotteBus[idBusCourant].column==zones[z].column){
                int r,c;
                r=troncons[tron].parcours[0].row;
                c=troncons[tron].parcours[0].column;
                cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                //Z%dBM***
                if(cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus==100)
                    cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=100;
                else
                    cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
            }
        }
        else {
            if(sub<troncons[tron].nombresubdivisions-1){
                int r,c;
                r=troncons[tron].parcours[sub+1].row;
                c=troncons[tron].parcours[sub+1].column;
                //[BM]****
                if(cartegeo[r][c].bus==-1)
                    cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                else
                    cartegeo[r][c].bus=100;
                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
            }
            else{
                int s=0;
                while(s<nombreZones && (lignes[0].idZones[dest]!=zones[s].id)){
                    s++;
                }
                int r,c;
                r=zones[s].row;
                c=zones[s].column;
                cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
                flotteBus[idBusCourant].idZoneCourante=zones[s].id;
                if(tron==nombreTroncons-1 && sub==troncons[nombreTroncons-1].nombresubdivisions-1){
                    flotteBus[idBusCourant].enRoute=0;
                }
            }
        }
    }
    //sens 1
    else{
        if(sub==troncons[tron].nombresubdivisions){
            //l'emplacement de bus est une zone
            int z=0;
            while(z<nombreZones && flotteBus[idBusCourant].idZoneCourante!=zones[z].id)
                z++;
            if(flotteBus[idBusCourant].row==zones[z].row && flotteBus[idBusCourant].column==zones[z].column){
                int r,c;
                r=troncons[tron].parcours[troncons[tron].nombresubdivisions-1].row;
                c=troncons[tron].parcours[troncons[tron].nombresubdivisions-1].column;
                cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                //Z%dBM***
                if(cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus==100)
                    cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=100;
                else
                    cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
            }
        }
        else {
            if(sub>0){
                int r,c;
                r=troncons[tron].parcours[sub-1].row;
                c=troncons[tron].parcours[sub-1].column;
                //[BM]****
                if(cartegeo[r][c].bus==-1)
                    cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                else
                    cartegeo[r][c].bus=100;
                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
            }
            else{
                int s=0;
                while(s<nombreZones && (lignes[0].idZones[dest]!=zones[s].id)){
                    s++;
                }
                int r,c;
                r=zones[s].row;
                c=zones[s].column;
                cartegeo[r][c].bus=flotteBus[idBusCourant].id;
                cartegeo[flotteBus[idBusCourant].row][flotteBus[idBusCourant].column].bus=-1;
                flotteBus[idBusCourant].row = r;
                flotteBus[idBusCourant].column = c;
                flotteBus[idBusCourant].idZoneCourante=zones[s].id;
                if(tron==0 && sub==0){
                    flotteBus[idBusCourant].enRoute=0;
                }
            }
        }
    }
}

//LE DEPLACEMENT D'UNE PERSONNE D'UN TABLEAU A UN AUTRE
void deplacerPersonne(Personne src[], Personne dest[], int indicePersonneSrc, int *nombrePersonnesSrc, int *nombrePersonnesDest)
{
    // Ajoutez la personne au tableau de destination
    dest[*nombrePersonnesDest] = src[indicePersonneSrc];
    (*nombrePersonnesDest)++;

    // Supprimez la personne du tableau source en décalant les éléments restants
    for (int i = indicePersonneSrc; i < *nombrePersonnesSrc - 1; i++) {
        src[i] = src[i + 1];
    }

    // Réduisez le nombre de personnes dans le tableau source
    (*nombrePersonnesSrc)--;
}

//MISE A JOUR PERSONNE UNE ZONE

void majPersonnesUneZone(Horaire horaireCourant, Zone zones[], int idZone)
{
    for(int j=0 ; j<zones[idZone].nombrePersonnes ; j++){
        for(int i=0; i<zones[idZone].personnes[j].nombreActivites; i++){
            if(zones[idZone].personnes[j].activites[i].horaireDateSouhaite.jour==horaireCourant.jour
               && zones[idZone].personnes[j].activites[i].horaireDateSouhaite.heure==horaireCourant.heure
               && zones[idZone].personnes[j].activites[i].horaireDateSouhaite.minute==horaireCourant.minute){
                zones[idZone].personnes[j].intentionVoyage=1;
                zones[idZone].personnes[j].idZoneCourante=zones[idZone].personnes[j].activites[i].idZoneSrc;
                zones[idZone].personnes[j].idZoneDest=zones[idZone].personnes[j].activites[i].idZoneDest;
                zones[idZone].personnes[j].idLigneCourante=zones[idZone].personnes[j].activites[i].idLigne;
                zones[idZone].personnes[j].sensCourant=zones[idZone].personnes[j].activites[i].sens;
            }
        }
    }
}

//MISE A JOUR PERSONNE TOUTES ZONES

void majPersonnesToutesZones(Horaire horaireCourant, Zone zones[], int nombreZones)
{
    for(int i=0; i<nombreZones; i++){
        majPersonnesUneZone(horaireCourant, zones, i);
    }
}

/****** TICKET ******/

//calcule prix ticket
int calculerPrixTicket(int x)
{
    if(x>=1 && x<=30)
        return 300;
    else if(x>30 && x<=60)
        return 600;
    else
        return 900;
}

//vente ticket
Ticket venteTicket(Horaire horaireVente, int idZoneSrc, int idZoneDest, int idLigne, int sens, Ligne lignes[], Troncon troncons[], int nombreLignes, int nombreTroncons, int idBus)
{
    Ticket tick;
    tick.zoneSrc=idZoneSrc;
    tick.zoneDest=idZoneDest;
    tick.idLigne=idLigne;
    tick.sens=sens;
    tick.idBus=idBus;
    tick.dateVente=horaireVente;
    tick.distance=calculerDistance(idZoneSrc, idZoneDest, lignes, troncons, nombreLignes, nombreTroncons);
    tick.prix=calculerPrixTicket(tick.distance);
    return tick;
}

//deplacement et reinitialisation ticket

void deplacerEtReinitialiserTicketsBus(Bus flotteBus[], int nombreBus, Ticket tickets[]) {
    int nombreTotalTicket=0;
    for (int i = 0; i < nombreBus; i++) {
        for (int j = 0; j < flotteBus[i].nombreTickets; j++) {
            if (nombreTotalTicket < 10000) {
                tickets[nombreTotalTicket] = flotteBus[i].tickets[j];
                nombreTotalTicket++;
            }
        }
        // Réinitialiser les tickets dans les bus
        flotteBus[i].nombreTickets = 0;
    }
}

/******************************/

//EMBARQUER PERSONNE

void embarquerPersonnes(Zone zones[], Bus flotteBus[] , int idZone, int idBus, Horaire horaireCourant, Ligne lignes[] , Troncon troncons[] , int nombreLignes, int nombreTroncons)
{
    int nbEmbarquant=0;
    for(int i=0; i<zones[idZone].nombrePersonnes; i++){
        if(zones[idZone].personnes[i].intentionVoyage==1
           && zones[idZone].personnes[i].idLigneCourante==flotteBus[idBus].idLigneCourante
           && zones[idZone].personnes[i].sensCourant==flotteBus[idBus].sensCourant){
                deplacerPersonne(zones[idZone].personnes, flotteBus[idBus].passagers, i, &zones[idZone].nombrePersonnes, &flotteBus[idBus].nombrePassagers);
                flotteBus[idBus].tickets[flotteBus[idBus].nombreTickets] = venteTicket(horaireCourant, zones[idZone].personnes[i].idZoneCourante, zones[idZone].personnes[i].idZoneDest, zones[idZone].personnes[i].idLigneCourante, zones[idZone].personnes[i].sensCourant, lignes , troncons , nombreLignes, nombreTroncons, i);
                (flotteBus[idBus].nombreTickets)++;
                    nbEmbarquant++;
           }
    }
}

//DEBARQUER PERSONNE

void debarquerPersonnes(Zone zones[], Bus flotteBus[] , int idZone, int idBus, Horaire horaireCourant)
{
    int nbDebarquant=0;
    for(int i=0; i<flotteBus[idBus].nombrePassagers; i++){
        if(flotteBus[idBus].passagers[i].idZoneDest==idZone){
            deplacerPersonne(flotteBus[idBus].passagers, zones[idZone].personnes, i, &flotteBus[idBus].nombrePassagers, &zones[idZone].nombrePersonnes);
            nbDebarquant++;
        }
    }
    majPersonnesUneZone(horaireCourant, zones, idZone);
}

//Calcule de gain

int calculerGainNet(Bus flotteBus[], int nombreBus, Ligne lignes[], int nombreLignes)
{
    int gain=0;
    for(int i=0; i<nombreBus; i++){
        for(int j=0; j<flotteBus[i].nombreTickets; j++)
            gain+=flotteBus[i].tickets[j].prix;
    }
    return gain;
}

//Affichage statistique

void afficherStatistiques(Bus flotteBus[], int nombreBus, Ligne lignes[], int nombreLignes)
{
    printf("\n");
    for(int i=0; i<nombreBus; i++){
        int gain=0;
        for(int j=0; j<flotteBus[i].nombreTickets; j++)
            gain+=flotteBus[i].tickets[j].prix;
        printf("le gain net de bus %d est : %d\n",i,gain);
    }
    printf("Le gain net total est %d\n",calculerGainNet(flotteBus, nombreBus, lignes, nombreLignes));
}

//Sauvegarde rapport

void sauvegarderRapport(char* nomFichier, Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    FILE *fic =fopen("rapportSauv.txt", "w");
    for(int i=0; i<nombreBus; i++){
        int gain=0;
        for(int j=0; j<flotteBus[i].nombreTickets; j++)
            gain+=flotteBus[i].tickets[j].prix;
        fprintf(fic,"%d ",i);
        fprintf(fic,"%d\n",gain);
    }
    fprintf(fic,"%d",calculerGainNet(flotteBus, nombreBus, lignes, nombreLignes));
    fclose(fic);
}

//Dérouler

void deroulerSemaine(caseCarte cartegeo[20][20], Ticket tickets[], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus,char* nomFichier)
{
    Horaire now;
    initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
    int v;
    int x=0;
    printf("\n\nRemarque:Le statistique est a la fin de jeu\n\nVotre choix: ");

    for(int j=0; j<6; j++){
        for(int h=6; h<=22; h++){
            for(int m=0; m<=59; m++){
                now.jour=j;
                now.heure=h;
                now.minute=m;
                majPersonnesToutesZones(now, zones, nombreZones);
                printf("\nnow(J%d) %dH:%dm\n\n",j,h,m);
                afficherCarteGeo(cartegeo , zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);

                for(int i=0; i<nombreBus; i++){
                    if(flotteBus[i].enRoute==0){
                        int k=numTacheSuivante( now, i, flotteBus);
                        if(k > -1){
                            flotteBus[i].enRoute=1;
                            flotteBus[i].sensCourant=flotteBus[i].taches[k].sens;
                            flotteBus[i].idLigneCourante=flotteBus[i].taches[k].idLigne;
                        }
                    }
                    if((flotteBus[i].row==zones[flotteBus[i].idZoneCourante].row) && (flotteBus[i].column==zones[flotteBus[i].idZoneCourante].column) && flotteBus[i].enRoute==1){
                        embarquerPersonnes( zones, flotteBus, zones[flotteBus[i].idZoneCourante].id, i, now, lignes, troncons, nombreLignes, nombreTroncons);
                        debarquerPersonnes( zones, flotteBus, zones[flotteBus[i].idZoneCourante].id, i, now);
                    }
                    if(flotteBus[i].enRoute==1){
                        deplacerBus(cartegeo, i, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons , nombreBus, now);
                        sauvegardeComplete(zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus, nomFichier);
                    }
                }

                //Le deroullement en plusieurs vitesse

                 if(x==0){
                    do{
                        printf("1 - minute par minute\n2 - par 10 minutes\n3 - par heure\n4 - par 4 heures\n5 - par jour\n\n");
                        printf("\nPreciser la vitesse de deroulement :\n");
                        scanf("%d",&v);
                    }while(v<1 || v>5);
                 }
                 x++;
                 if (v == 1) {
                     x = 0;
                 } else if (v == 2) {
                     if (x == 10)
                         {x = 0;}
                 } else if (v == 3) {
                     if (x == 60)
                         {x = 0;}
                 } else if (v == 4) {
                     if (x == 240)
                         {x = 0;}
                 } else if (v == 5) {
                     if (x == 720)
                         {x = 0;}
                 }

                /***************************************/
                if(h == 12 && m == 59){
                    afficherStatistiques(flotteBus, nombreBus, lignes, nombreLignes);
                    sauvegarderRapport(nomFichier, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
                    deplacerEtReinitialiserTicketsBus(flotteBus, nombreBus, tickets);
                    return;
                }
                /***************************************/
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    caseCarte cartegeo[20][20];
    Zone zones[10];
    Bus flotteBus[10];
    Ligne lignes[1];
    Troncon troncons[9];
    Ticket tickets[10000];
    printf("----Bienvenu tout le monde----!\n");
    int nombreZones,nombreLignes,nombreTroncons,nombreBus;
    char nomFichier[30];

    printf("*****MENU*****\n");
    printf("1-Nouveau jeu\n");
    printf("2-Charger jeu\n");
    int choix;
    printf("Choisir votre choix :");
    scanf("%d", &choix);

    if (choix==1)
    {
        remplissageComplet(zones, lignes, troncons, flotteBus, &nombreZones, &nombreLignes, &nombreTroncons, &nombreBus);
        genererPersonne(zones, nombreZones, lignes, nombreLignes);
        initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
        deroulerSemaine(cartegeo, tickets, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus,nomFichier);
    }
    else if(choix==2){
        remplissageComplet(zones, lignes, troncons, flotteBus, &nombreZones, &nombreLignes, &nombreTroncons, &nombreBus);
        chargerPersonnes(zones, &nombreZones, "personnesSauv.txt");
        initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
        deroulerSemaine(cartegeo, tickets, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus,nomFichier);
    }
    else{
        printf("choix invalide !!");
    }

    return 0;
}
