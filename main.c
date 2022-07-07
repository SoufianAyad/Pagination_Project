#include <stdio.h>
#include <stdlib.h>
#include <string.h>



 struct page{
	int adr;
	struct page *page_suivante;
};

 struct prog{
	char nom[20];
	int taille;
    struct page *page_prog;
	struct prog *prog_suivant;
};

//APPEL DES FCTS
struct page * creation_espace(struct page *p);
void afficher_espace(struct page* p);
int trouver_nombrePages(int t);
int Nombre_Element(struct page* pv);
struct page * creation_page(struct page *p, int t);
void afficher_page(struct page* pv);
struct prog* charger_prgm(struct prog * pgm,char l[],int taille,struct page*p);
struct page* supprimer_pages_charges(struct page *p,int taille);
struct prog* creation_programme(struct page* pg, struct prog* s,char n[] ,int t);
void afficher_prog(struct prog *p);
void afficher_prog_pages(struct prog *p);
void afficher_pages_prog(struct prog *p,char l[]);
struct prog * supprimer_prog(struct prog *pgm, char l[]);
struct page* fusionner(struct page* p,struct page* pg);
int Avoir_taille(struct prog *p,char l[]);
struct page* Avoir_listepages(struct prog *p,char l[]);
struct page * supprimerElementEnFin(struct page * pg);
int chercher(struct prog *p,char l[]);
void formater(char nom[20]);
char*  etat_memoire(struct prog *listeProg);



struct page * creation_espace(struct page *p){
        struct page* nouveau = NULL;
        nouveau=(struct page*)(malloc(sizeof(struct page)));
        nouveau->adr=1;
        nouveau->page_suivante=NULL;
        p->page_suivante=nouveau;
    for (int i =2; i<=26; i++){
        struct page * courant = NULL;
        courant=(struct page*)(malloc(sizeof(struct page)));
        courant->adr=i;
        courant->page_suivante=NULL;
        nouveau->page_suivante=courant;
        nouveau= nouveau->page_suivante;
    }
  return p;
}

void afficher_espace(struct page* p){

     while(p->page_suivante->page_suivante!=NULL){
         printf(" %d  ", p->page_suivante->adr);
         p=p->page_suivante;
    }
}

int trouver_nombrePages(int taille){
int nbr_pages;
    nbr_pages= (taille/100);
        if (taille%100!=0)
        {
           nbr_pages=nbr_pages+1;
        }
  return nbr_pages ;
}


int Nombre_Element(struct page* p){
  int n=0;
  while(p->page_suivante->page_suivante!=NULL){
         n=n+1;
         p=p->page_suivante;}
 return n;
}

struct page * creation_page(struct page *p, int t){
  struct page * pg = NULL;
	pg=(struct page*)(malloc(sizeof(struct page)));

	pg->adr=0;
	pg->page_suivante=NULL;
	struct page * nouveau = NULL;
	nouveau=(struct page*)(malloc(sizeof(struct page)));
    nouveau->adr=p->page_suivante->adr;
    nouveau->page_suivante=NULL;
    pg->page_suivante=nouveau;

    for(int i=2; i<=t+1; i++){
        struct page * courant = NULL;
        courant=(struct page*)(malloc(sizeof(struct page)));
        courant->adr=p->page_suivante->page_suivante->adr;
        courant->page_suivante=NULL;
        nouveau->page_suivante=courant;
        nouveau= nouveau->page_suivante;
        p=p->page_suivante;

    	}
   return pg;
}

void afficher_page(struct page* pv){
     while(pv->page_suivante->page_suivante!=NULL){
         printf(" %d ", pv->page_suivante->adr);
         pv=pv->page_suivante;
    }
}


struct page * supprimer_pages_charges(struct page *pr,int taille){
      struct page *nouveau;
      for (int i=0; i<taille ;i++){
       nouveau=pr->page_suivante;
       pr->page_suivante=pr->page_suivante->page_suivante;
        free(nouveau);
       }
  return pr;
}


void afficher_prog(struct prog *p){
     while(p!=NULL){
        printf("-----------------# %s \n",p->nom);
        p=p->prog_suivant;
    }
}

void afficher_prog_pages(struct prog *p){
     while(p!=NULL){
        printf("-----------------# %s  :",p->nom);
        afficher_page(p->page_prog);
        printf("\n");
        p=p->prog_suivant;
    }
}

struct prog* creation_programme(struct page* pg, struct prog* s,char n[] ,int t){
   struct prog* p;
   p = (struct prog*)malloc(sizeof(struct prog));
   strcpy(p->nom,n);
   p->taille=t;
   p->page_prog = pg;
   p->prog_suivant= s;
 return p;
}

struct prog* charger_prgm(struct prog * pgm,char l[],int taille,struct page *p){
  if(taille<=0){
     printf("----------!!!taille insuportable!!!! \n");
  }
  else{
       struct page * nv = NULL;
       int t=trouver_nombrePages(taille);
       int n=Nombre_Element(p);
       int v=chercher(pgm,l);
  if(v==0){
      if (t>n){
         printf("----------!!!Memoire pleine!!! \n");
      }
    else{
          struct page * Pg = NULL;
	      Pg=(struct page*)(malloc(sizeof(struct page)));
          Pg=creation_page(p, t);
          struct page * nv = NULL;
        nv=(struct page*)(malloc(sizeof(struct page)));
        nv=supprimer_pages_charges(p,t);
         printf("\n");
         if (pgm==NULL){
            pgm=creation_programme(Pg,NULL,l,t);
            printf("--------------le programme a ete bien enregistre \n");
         }
         else{
            struct prog *tmp;
            tmp=(struct prog*)(malloc(sizeof(struct prog)));
            tmp=pgm;
            while(tmp->prog_suivant != NULL){

                 tmp = tmp->prog_suivant;
            }
           tmp->prog_suivant = creation_programme(Pg,NULL,l,t);
           printf("--------------le programme a ete bien enregistre \n");
         }
       }
   }
  else{
    printf("----------!!!!ce programme existe deja!!!! ");
  }
  }
 return pgm;
}

void afficher_pages_prog(struct prog *p,char l[]){

    while(p!=NULL){

         if(strcmp(l,p->nom)==0){
         afficher_page(p->page_prog);
          }
         p=p->prog_suivant;
    }
}

int chercher(struct prog *p,char l[]){
   int v=0;
    while(p!=NULL){

         if(strcmp(l,p->nom)==0){
             v=1;
          }
         p=p->prog_suivant;
    }
  return v;
}

struct page* Avoir_listepages(struct prog *p,char l[]){

  struct prog * tmp = (struct prog * ) malloc(sizeof(struct prog * ));
  tmp = p;
  while (tmp) {
    if (strcmp(tmp->nom, l) == 0) {
      return tmp->page_prog;
    }
    tmp = tmp->prog_suivant;
  }
}

struct prog * supprimer_prog(struct prog *pgm, char l[]){
    if(pgm == NULL)
        return NULL;
    if(strcmp(l,pgm->nom)==0)
    {
        struct prog* tmp = pgm->prog_suivant;
        free(pgm);
        tmp = supprimer_prog(tmp, l);
        return tmp;
    }
    else
    {
        pgm->prog_suivant = supprimer_prog(pgm->prog_suivant,l);
        return pgm;
    }
 }

struct page* fusionner(struct page* p,struct page* pg)
{
    struct page* temp1=p;
    struct page* temp2=pg;

      if(temp1==NULL)
      {
         return temp2;
      }
      else if(temp2==NULL)
      {
         return temp1;
      }
      else if ((temp1->adr) <= (temp2->adr))
     {
          temp1->page_suivante = fusionner(temp1->page_suivante,temp2);
          return(temp1);
     }
      else
     {
         temp2->page_suivante = fusionner(temp1,temp2->page_suivante);
          return(temp2);
     }
}


struct page * supprimerElementEnFin(struct page * pg)
{
    if(pg == NULL)
        return NULL;
    if(pg->page_suivante == NULL)
    {
        free(pg);
        return NULL;
    }

    struct page* tmp = pg;
    struct page* ptmp = pg;
    while(tmp->page_suivante != NULL)
    {
        ptmp = tmp;
        tmp = tmp->page_suivante;
    }
    ptmp->page_suivante= NULL;
    free(tmp);
    return pg;
}

/*************Affichage*****************/

char*  etat_memoire(struct prog *listeProg){

    struct prog *p;
    p=listeProg;

    char T[25][10]={"--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--","--"};

    while(p!=NULL){
              struct page *temp;
               temp=p->page_prog;
                while(temp->page_suivante->page_suivante!=NULL){

                temp=temp->page_suivante;

                int j=temp->adr;
                strcpy(T[j-1],p->nom);
            }
            temp=NULL;

            p=p->prog_suivant;
    }


   printf("\n\t+************************+\n\t");
   printf("|\t\t\t\t\t\t\t\t     |\n");
   printf("\t|\t\t\t   Memoire Centrale   \t\t\t     |\n");
   printf("\t|\t\t\t\t\t\t\t\t     |\n");
   printf("\t+****++****++****++****++****+\n\t");
    for (int i=0;i<5;i++){
        formater(T[i]);
    }
    printf("\n");
    printf("\t+****++****++****++****++****+\n\t");
    for (int i=5;i<10;i++){
        formater(T[i]);
    }
    printf("\n");
    printf("\t+****++****++****++****++****+\n\t");
    for (int i=10;i<15;i++){
        formater(T[i]);
    }
    printf("\n");
   printf("\t+****++****++****++****++****+\n\t");
    for (int i=15;i<20;i++){
        formater(T[i]);
    }
    printf("\n");
    printf("\t+****++****++****++****++****+\n\t");
    for (int i=20;i<25;i++){
        formater(T[i]);
    }
    printf("\n");
    printf("\t+****++****++****++****++****+\n\t");

    return T;
}


void formater(char nom[20]) {

  char
  var [20] = "";
  int b = strlen(nom);
  if (b == 12) {
    printf("|%s|", nom);
    //system("PAUSE");
  } else {
    int m = 12 - strlen(nom);
    int i;
    for (i = 0; i < m / 2; i++) {
      var [i] = ' ';
    }
    for (i = m / 2; i < b + m / 2; i++) {
      var [i] = nom[i - m / 2];
    }
    for (i = b + m / 2; i < b + m; i++) {
      var [i] = ' ';
    }

    printf("|%s|",
      var);

  }

}


int main()
{

    char choix[15];
    int t;
    char n[15];
    int taille;
    struct page * p = NULL;
    struct page *pg;
    struct prog *pgm=NULL;
	p=(struct page*)(malloc(sizeof(struct page)));
	p->adr=0;
    p->page_suivante=NULL;
    p=creation_espace(p);



	system("cls");
    system("COLOR 71");
    system("COLOR 71");
    system("cls");
    printf("\n\n");
    printf("\n\t\t\t\t\t\t    Bonjour (^_^) !!\n\t\t\t\t\t   Gestion de la memoire par pagination\n ");


 while (strcmp(choix,"9")!=0) {



    printf("                                                       ~ MENU ~                      \n");
    printf("                                               1 . Charger un programme en MC           \n");
    printf("                                               2 . Afficher les pages vides             \n");
    printf("                                               3 . Afficher la liste des programmes en MC \n");
    printf("                                               4 . chercher un programme               \n");
    printf("                                               5 . Afficher les programme par pages    \n");
    printf("                                               6 . Terminer l'execution d'un programme \n");
    printf("                                               7 . Afficher la memoire centrale        \n");
    printf("                                               8 . Vider la memoire                    \n");
    printf("                                               9 . Quitter                             \n");


		printf("\n--------> Veuillez schoisir une option: ");
		scanf("%s", &choix);
		printf("\n");


		if (strcmp(choix,"1") == 0) {

			printf("--------> Veuillez saisir le nom du programme a charger: ");
			scanf("%s", &n);
			printf("--------> veuillez saisir la taille de ce programme: ");
			scanf("%d", &taille);

            pgm=charger_prgm(pgm,n, taille, p);
		}
		else if (strcmp(choix,"2") == 0) {
            int l=Nombre_Element(p);
         if(l==0){
            printf("\n----------Aucune page vide n'existe dans la memoire !!!! \n\n");
         }
         else{
           printf("\n----------Les pages vides dans la memoire : \n\n");
            afficher_espace(p);
            printf("\n");
         }
		}
		else if (strcmp(choix,"3") == 0) {

            int s=Nombre_Element(p);
            if(s==25){
                printf("\n");
                printf("----------la memoire est vide !!!");
                printf("\n");
            }
            else{
                printf ("\n----------La lise des programmes : \n");
                afficher_prog(pgm);
                printf("\n");
            }
		}
		else if (strcmp(choix,"4") == 0) {
            printf("--------> Veuillez saisir le nom du programme a afficher: ");
			scanf("%s", &n);
            int v=chercher(pgm,n);
           if(v==0){
                printf("\n");
             printf("----------Ce programme n'existe pas !!!!\n");

           }
           else{
              printf("\n");
              printf("\n----------Les pages du programme %s : \n\n",n);
              printf("\t    ");
              afficher_pages_prog(pgm,n);
              printf("\n");
           }

		}
		else if (strcmp(choix,"5") == 0) {
		    int s=Nombre_Element(p);
                if(s==25){
                printf("\n");
                printf("--------!!!la memoire est vide!!!-------");
                printf("\n");
            }
            else{
               printf("\n----------La Liste des programmes : \n");
               afficher_prog_pages(pgm);
            }

		}
		else if (strcmp(choix,"6") == 0) {

			printf("--------> Veuillez saisir le nom du programme a supprimer: ");
			scanf("%s", &n);
           int v=chercher(pgm,n);
          if(v==0){
             printf("----------Ce programme n'existe pas !!!!!\n");
          }
          else{
            pg=Avoir_listepages(pgm,n);
            pg=supprimerElementEnFin(pg);
            pgm=supprimer_prog(pgm, n);
            printf("--------le programme a ete bien supprime-------\n");
            p=fusionner(p->page_suivante,pg);
          }
		}
		else if (strcmp(choix,"7") == 0) {
        etat_memoire(pgm);
		}
		else if(strcmp(choix,"8")==0){
            if(pgm==NULL){
                printf("La m%cmoire est d%cja vide !!!!",130,138);
            }
            else{
                while(pgm!=NULL){
                pg=Avoir_listepages(pgm,pgm->nom);
                pg=supprimerElementEnFin(pg);
                pgm=supprimer_prog(pgm, pgm->nom);
                p=fusionner(p->page_suivante,pg);
		    }
		    printf("La m%cmoire a bien %ct%c vid%c ",130,130,130,130);
            }

		}
		else {

            printf(" !!!!!!!! veuillez saisir un numero depuis le menu !!!!!!! \n");

		}
}
 printf("\n\n ~~~~ Merci pour avoir utilise ce programme (^_^) a tres bientot ~~~~  \n\n");
return 0;
}
