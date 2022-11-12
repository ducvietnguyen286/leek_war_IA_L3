#include "commande.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int verifier_entier(char *ch) {
  while (*ch != '\0') {
    if (!isdigit(*ch)) {
      return 0;
    }
    ch++;
  }
  return 1;
}

int lance_commande(char *cmd, Donnees d, Camp *c1, Camp *c2, int * go, int *interrupt) {
  int x,sz;
  char *ch;
  if (*go == 1){
	  if (strcmp(cmd,"show vegetables") == 0) {
		show_vegetables(d.tabC);
	  }
	  else if (strncmp(cmd,"show vegetable i",15) == 0 ) {
		sz = strlen(cmd) - 15;
		ch = (char *) malloc(sizeof(char)*(sz+1));
		ch[0] = '\0';
		strncpy(ch,cmd+15,sz);
		if (!verifier_entier(ch)) printf("ERREUR 'show vegetable i' i->int\n");
		else {
		  x = atoi(ch);
		  show_vegetables_i(d.tabC,x);
		}
	  }
	  else if (strcmp(cmd,"show fruits") == 0) {
		show_fruits(d.tabC);
	  }
	  else if (strncmp(cmd,"show fruit i",11) == 0 ) {
		sz = strlen(cmd) - 11;
		ch = (char *) malloc(sizeof(char)*(sz+1));
		ch[0] = '\0';
		strncpy(ch,cmd+11,sz);
		if (!verifier_entier(ch)) printf("ERREUR 'show fruit i' i->int\n");
		else {
		  x = atoi(ch);
		  show_fruits_i(d.tabC,x);
		}
	  }
	  else if (strcmp(cmd,"show weapons") == 0) {
		show_weapons(d.tabA);
	  }
	  else if (strncmp(cmd,"show weapon i",12) == 0 ) {
		sz = strlen(cmd) - 12;
		ch = (char *) malloc(sizeof(char)*(sz+1));
		ch[0] = '\0';
		strncpy(ch,cmd+12,sz);
		if (!verifier_entier(ch)) printf("ERREUR 'show weapon i' i->int\n");
		else {
		  x = atoi(ch);
		  show_weapons_i(d.tabA,x);
		}
	  }
	  else if (strcmp(cmd,"show protections") == 0) {
		show_protections(d.tabP);
	  }
	  else if (strncmp(cmd,"show protection i",16) == 0 ) {
		sz = strlen(cmd) - 16;
		ch = (char *) malloc(sizeof(char)*(sz+1));
		ch[0] = '\0';
		strncpy(ch,cmd+16,sz);
		if (!verifier_entier(ch)) printf("ERREUR 'show protection i' i->int\n");
		else {
		  x = atoi(ch);
		  show_protections_i(d.tabP,x);
		}
	  }
	  else if (strcmp(cmd,"show cares") == 0) {
		show_care(d.tabS);
	  }
	  else if (strncmp(cmd,"show care i",10) == 0 ) {
		sz = strlen(cmd) - 10;
		ch = (char *) malloc(sizeof(char)*(sz+1));
		ch[0] = '\0';
		strncpy(ch,cmd+10,sz);
		if (!verifier_entier(ch)) printf("ERREUR 'show care i' i->int\n");
		else {
		  x = atoi(ch);
		  show_care_i(d.tabS,x);
		}
	  }
	  else if (strcmp(cmd,"exit") == 0) {
		return 1;
	  }
	  else if (strcmp(cmd,"fight v versus f") == 0) {
		*go = 2;
		return fight(c1,c2,d);
	  }
	  else {
		printf("COMMANDE INVALIDE !\n");
      }
  }
  /*COMMANDE DE COMBAT*/
  else if (*go == 2)
  {
	  if(strcmp(cmd,"show") == 0)
	  {
		  if(*interrupt == 0){
			  show(c1);
		}else
		{
			show(c2);
		}
	  }
	  else if(strcmp(cmd,"end") == 0) {
      if (*interrupt == 1) {
        *interrupt = 0;
        c1->comb->estPortee = 0;
      }
      else {
        *interrupt = 1;
        c2->comb->estPortee = 0;
      }
    }
    else if(strncmp(cmd,"move forward n",12) == 0) {
      sz = strlen(cmd);
      if ((sz == 12) || (sz == 13 && cmd[12] == ' ')) {
        move_forward(c1->comb,c2->comb,1,*interrupt);
        affiche_combat(c1,c2);
      }
      else if (sz == 13 && cmd[12] != ' ') printf("COMMANDE INVALIDE EH\n");
      else {
        if(sz > 13) {
          sz-=13;
          ch = (char*) malloc(sizeof(char)*sz+1);
          ch[0] = '\0';
          strncpy(ch,cmd+13,sz);
          if (!verifier_entier(ch)) printf("ERREUR 'move forward n' n->int\n");
          else {
            x = atoi(ch);
            move_forward(c1->comb,c2->comb,x,*interrupt);
            affiche_combat(c1,c2);
          }
        }
      }
    }
    else if(strncmp(cmd,"move backward n",13) == 0) {
      sz = strlen(cmd);
      if ((sz == 13) || (sz == 14 && cmd[13] == ' ')) {
        move_backward(c1->comb,c2->comb,1,*interrupt);
        affiche_combat(c1,c2);
      }
      else if (sz == 14 && cmd[13] != ' ') printf("COMMANDE INVALIDE EH\n");
      else {
        if(sz > 14) {
          sz-=14;
          ch = (char*) malloc(sizeof(char)*sz+1);
          ch[0] = '\0';
          strncpy(ch,cmd+14,sz);
          if (!verifier_entier(ch)) printf("ERREUR 'move backward n' n->int\n");
          else {
            x = atoi(ch);
            move_backward(c1->comb,c2->comb,x,*interrupt);
            affiche_combat(c1,c2);
          }
        }
      }
    }
    else if(strncmp(cmd,"use weapon n",10) == 0) {
      sz = strlen(cmd);
      srand(time(NULL));
      if ((sz == 10) || (sz == 11 && cmd[10] == ' ')) {
        if (*interrupt) use_weapon(c2->comb,c1->comb,1,*interrupt);
        else use_weapon(c1->comb,c2->comb,1,*interrupt);
        affiche_combat(c1,c2);
      }
      else if (sz == 11 && cmd[10] != ' ') printf("COMMANDE INVALIDE EH\n");
      else {
        if(sz > 11) {
          sz-=11;
          ch = (char*) malloc(sizeof(char)*sz+1);
          ch[0] = '\0';
          strncpy(ch,cmd+11,sz);
          if (!verifier_entier(ch)) printf("ERREUR 'use weapon n' n->int\n");
          else {
            x = atoi(ch);
            if (*interrupt) use_weapon(c2->comb,c1->comb,x,*interrupt);
            else use_weapon(c1->comb,c2->comb,x,*interrupt);
            affiche_combat(c1,c2);
          }
        }
      }
    }
    else if (strcmp(cmd,"use protection") == 0) {
      if (*interrupt == 0) use_protection(c1->comb);
      else use_protection(c2->comb);
    }
    else if (strncmp(cmd,"use care n",8) == 0) {
      sz = strlen(cmd);
      srand(time(NULL));
      if ((sz == 8) || (sz == 9 && cmd[8] == ' ')) {
        if (*interrupt) use_care(c2,1);
        else use_care(c1,1);
      }
      else if (sz == 9 && cmd[8] != ' ') printf("COMMANDE INVALIDE\n");
      else {
        sz-=9;
        ch = (char*) malloc(sizeof(char)*sz+1);
        ch[0]='\0';
        strncpy(ch,cmd+9,sz);
        if (!verifier_entier(ch)) printf("ERREUR 'use care n' n->int\n");
        else {
          x = atoi(ch);
          if (*interrupt) use_care(c2,x);
          else use_care(c1,x);
        }
      }
    }
	  else {
      printf("COMMANDE INVALIDE !\n");
    }
    return -1;
  }

  return 0;
}

void show_vegetables(Champion * tab) {
  int i;
  Champion c;
  printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\  LES LEGUMES  /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
  printf("ID | NOM\t| FORCE\t| RESISTANCE\t| PV\t| CE\n");
  for (i  = 0; i < NB_CHAMPION; i++) {
    c = tab[i];
    if (c.t == Legume) {
      printf("%d  | %s\t| %d\t| %d\t\t| %d\t| %d\n",c.id,c.nom,c.force,c.resistance,c.pv,c.ce);
    }
  }
  printf("\n");
}

void show_vegetables_i(Champion * tab, int i) {
  int j = 0,trouve = 0;
  Champion c;
  while (!trouve && j < NB_CHAMPION) {
    c = tab[j];
    if (c.t == Legume && c.id == i) {
      trouve = 1;
    }
    else j++;
  }
  if (trouve) {
    printf("LEGUME n°%d : %s | Force : %d | Résistance : %d | PV : %d | CE : %d\n\n",i,c.nom,c.force,c.resistance,c.pv,c.ce);
  }
  else {
    printf("Légume n°%d inexistant !\n",i);
  }
}

void show_fruits(Champion * tab) {
  int i;
  Champion c;
  printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\  LES FRUITS  /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
  printf("ID| NOM\t\t| FORCE\t| RESISTANCE\t| PV\t| CE\n");
  for (i  = 0; i < NB_CHAMPION; i++) {
    c = tab[i];
    if (c.t == Fruit) {
      printf("%d | %s\t| %d\t| %d\t\t| %d\t| %d\n",c.id,c.nom,c.force,c.resistance,c.pv,c.ce);
    }
  }
  printf("\n");
}

void show_fruits_i(Champion * tab, int i) {
  int j = 0,trouve = 0;
  Champion c;
  while (!trouve && j < NB_CHAMPION) {
    c = tab[j];
    if (c.t == Fruit && c.id == i) {
      trouve = 1;
    }
    else j++;
  }
  if (trouve)  printf("FRUIT n°%d : %s | Force : %d | Résistance : %d | PV : %d | CE : %d\n\n",i,c.nom,c.force,c.resistance,c.pv,c.ce);
  else {
    printf("Fruit n°%d inexistant !\n",i);
  }
}

void show_weapons(Arme * tab) {
  int i;
  Arme a;
  printf("/\\/\\/\\/\\  LES ARMES  /\\/\\/\\/\\\n");
  printf("ID| NOM\t\t\t| CE\t| CA\t| DEGATS| PORTEE\n");
  for (i  = 0; i < NB_ARME; i++) {
    a = tab[i];
    printf("%d | %s\t| %d\t| %d\t| %d-%d\t| %d\n",a.id,a.nom,a.ce,a.ca,a.degMin,a.degMax,a.portee);
  }
  printf("\n");
}

void show_weapons_i(Arme * tab, int i) {
  int j = 0, trouve = 0;
  Arme a;
  while (!trouve && j < NB_ARME) {
    if (tab[j].id == i) {
      trouve = 1;
    }
    else j++;
  }
  if (trouve) {
    a = tab[j];
    printf("Arme n°%d : %s | CE : %d | CA : %d | Dégât : %d-%d | Portée : %d\n",a.id,a.nom,a.ce,a.ca,a.degMin,a.degMax,a.portee);
  }
  else {
    printf("Arme n°%d inexistante !\n",i);
  }
  printf("\n");
}

void show_protections(Protection * tab) {
  int i;
  Protection p;
  printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\ LES PROTECTIONS /\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
  printf("ID| NOM\t\t\t| CE\t| CA\t| PROBABILITE\n");
  for (i  = 0; i < NB_PROTECTION; i++) {
    p = tab[i];
    printf("%d | %s\t| %d\t| %d\t| %d%%\n",p.id,p.nom,p.ce,p.ca,p.proba);
  }
  printf("\n");
}

void show_protections_i(Protection * tab, int i) {
  int j = 0, trouve = 0;
  Protection p;
  while (!trouve && j < NB_PROTECTION) {
    if (tab[j].id == i) {
      trouve = 1;
    }
    else j++;
  }
  if (trouve) {
    p = tab[j];
    printf("Protection n°%d : %s | CE : %d | CA : %d | Probabilité : %d%%\n",p.id,p.nom,p.ce,p.ca,p.proba);
  }
  else {
    printf("Protection n°%d inexistante !\n",i);
  }
  printf("\n");
}

void show_care(Soin * tab) {
  int i;
  Soin s;
  printf("/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\  LES SOINS  /\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n");
  printf("ID| NOM\t\t\t| CE\t| CA\t| VOLUMES\t| EFFET\n");
  for (i  = 0; i < NB_SOIN; i++) {
    s = tab[i];
    printf("%d | %s\t| %d\t| %d\t| %d\t\t| %d-%d\n",s.id,s.nom,s.ce,s.ca,s.volume,s.effetMin,s.effetMax);
  }
  printf("\n");
}

void show_care_i(Soin * tab, int i) {
  int j = 0, trouve = 0;
  Soin s;
  while (!trouve && j < NB_SOIN) {
    if (tab[j].id == i) {
      trouve = 1;
    }
    else j++;
  }
  if (trouve) {
    s = tab[j];
    printf("Soin n°%d : %s | CE : %d | CA : %d | Volume : %d | Effet : %d-%d\n",s.id,s.nom,s.ce,s.ca,s.volume,s.effetMin,s.effetMax);
  }
  else {
    printf("Soin n°%d inexistante !\n",i);
  }
  printf("\n");
}

int choix_id(Donnees d,char c){
  int taille,i=-2,fini = 0;
  char buf;
  if (c == 'l') taille = NB_LEGUME;
  else if (c=='f') taille = NB_FRUIT;
  else if (c=='a') taille = NB_ARME;
  else if (c=='p') taille = NB_PROTECTION;
  else if (c=='s') taille = NB_SOIN;
  while (!fini) {
    printf("\tEntrer l'id : ");
    scanf("%d",&i);
    buf = getchar();
    while (buf!='\n') {
      buf = getchar();
    }
    if ( i <= taille && i > 0) fini = 1;
    if ( (c == 'p' || c == 's') && (i == -1)) fini = 1;
  }
  return i;
}

int acheter_ca(int credit) {
  int x = -1,fini = 0;
  char buf;
  do {
    printf("Nombre de CA voulu : ");
    scanf("%d",&x);
    buf = getchar();
    while (buf !='\n') {
      buf = getchar();
    }
    if (x >= 0 && credit - x >= 0) fini = 1;
  } while (!fini);
  return x;
}

int Round(float nb){
	int entier = (int)nb;
	float decimale = nb - (float)entier;
	if(decimale >= 0.5) return entier+1;
	return entier;
}

int combattant_minimum(Donnees d, Type type){
	int i, min_combattant;
	if (type == Legume)
	{
		min_combattant = d.tabC[0].ce;
		for(i = 1; i < NB_LEGUME; i++) {
			if (d.tabC[i].ce < min_combattant) min_combattant = d.tabC[i].ce;
		}
	}else{
		min_combattant = d.tabC[NB_LEGUME].ce;
		for(i = NB_LEGUME+1; i < NB_CHAMPION; i++) {
			if (d.tabC[i].ce < min_combattant) min_combattant = d.tabC[i].ce;
		}
	}
	return min_combattant;
}

int arme_minimum(Donnees d){
	int i, min_arme = d.tabA[0].ce;
	for(i = 1; i < NB_ARME; i++) {
		if (d.tabA[i].ce < min_arme) min_arme = d.tabA[i].ce;
	}
	return min_arme;
}

Combattant *selection(Camp *c, Donnees d) {
  Combattant *comb = (Combattant*) malloc(sizeof(Combattant));
  extern int largeur;
  int x = -1, arme_min = arme_minimum(d);
  printf("A votre tour %s :\n\n",c->nom);
  printf("\tCrédit disponible : %d\n\n",c->credit_combat);
  printf("\t###\tCHOIX DU CHAMPION\t###\n\n");

  c->credit_combat_used = c->credit_combat;

  if (c->t == Fruit) {
    show_fruits(d.tabC);
    do {
      if (x != -1) printf("T'es Pauvre mec ! Choisis en un moins chère ;)\n");
      x = choix_id(d,'f') - 1;
    } while (c->credit_combat - d.tabC[NB_LEGUME+x].ce < arme_min);
    c->credit_combat -= d.tabC[NB_LEGUME+x].ce;
    printf("Champion choisi : %s\n",d.tabC[NB_LEGUME+x].nom);
    comb->c = &d.tabC[NB_LEGUME+x];
    comb->pos = largeur;
  }
  else {
    show_vegetables(d.tabC);
    do {
      if (x != -1) printf("T'es Pauvre mec ! Choisis en un moins chère ;)\n");
      x = choix_id(d,'l') - 1;
    } while (c->credit_combat - d.tabC[x].ce < arme_min);
    c->credit_combat -= d.tabC[x].ce;
    printf("Champion choisi : %s\n\n",d.tabC[x].nom);
    comb->c = &d.tabC[x];
    comb->pos = 0;
  }
  comb->pv = comb->c->pv;


  printf("\t###\tCHOIX DE L'ARME\t###\n\n");
  printf("\tCredit disponible : %d\n",c->credit_combat);
  x= -1;
  show_weapons(d.tabA);
  do {
    if (x != -1) printf("Prend une arme moins chère !\n");
    x = choix_id(d,'a') - 1;
  } while (c->credit_combat - d.tabA[x].ce < 0);
  c->credit_combat -= d.tabA[x].ce;
  printf("Arme choisie : %s\n\n",d.tabA[x].nom);
  comb->a = &d.tabA[x];

  printf("\t###\tCHOIX DE LA PROTECTION\t###\n\n");
  printf("\tCrédit disponible : %d\n",c->credit_combat);
  comb->p = NULL;
  x = -1;
  show_protections(d.tabP);
  if(c->credit_combat > 0){
  do {
    if (x != -1) printf("Prends une protection moins chère ou bien n'en prends pas !\n");
    x = choix_id(d,'p') - 1;/*x prend l'indice à laquelle l'élément se situe dans le tableau*/
    if (x == -2) break;/*Si le user a entrer -1 il ne prend rien*/
  } while (c->credit_combat - d.tabP[x].ce < 0);
  if (x != -2) {
    c->credit_combat -= d.tabP[x].ce;
    printf("Protection choisie : %s\n\n",d.tabP[x].nom);
    comb->p = &d.tabP[x];
  }
  else {
	  printf("Protection choisie : Aucune \n\n");
  }
  }
  else printf("Vous n'avez pas assez de CA pour se procurer une protection\n");

  printf("\t###\tCHOIX DU SOIN\t###\n\n");
  printf("\tCrédit disponible : %d\n",c->credit_combat);
  comb->s = NULL;
  comb->nbSoins = 0;
  x = -1;
  show_care(d.tabS);
  if(c->credit_combat > 0){
  do {
    if (x != -1) printf("Prends du soins moins chère ou bien n'en prend pas !\n");
    x = choix_id(d,'s') - 1;
    if (x == -2) break;
  } while (c->credit_combat - d.tabS[x].ce < 0);
  if (x != -2) {
    c->credit_combat -= d.tabS[x].ce;
    printf("Soin choisi : %s\n\n",d.tabS[x].nom);
    comb->s = &d.tabS[x];
    comb->nbSoins = comb->s->volume;
  }
  else printf("Soin choisi : Aucun\n\n");
  }
  else printf("Vous n'avez pas assez de CA pour se procurer un soin\n");

  if(c->credit_combat > 0){
	printf("\tCrédit disponible : %d\n",c->credit_combat);
	printf("\t###\tAcheter des CA ? (Actuellement : %d)\t###\n\n",CREDIT_ACTION);
	x = acheter_ca(c->credit_combat);
	comb->ca=CREDIT_ACTION + x;/*Augmentre les CA en fonction du nombre de CA acheté en plus*/
	c->credit_combat-=x;/*Retire le crédit utilisé pour acheter les CA*/
	} else {
		comb->ca=CREDIT_ACTION;
		printf("Il ne vous reste plus de credit_combat pour acheter de CA\n");
	}
	printf("Total de CA : %d\n",comb->ca);
	c->credit+=c->credit_combat;/*On ajoute les crédits restant au total de crédits*/
  c->credit_combat_used-=c->credit_combat;/*On met a jour le nombre de crédit utlisé pour le combat*/
	printf("Crédit non dépensé : %d ==> Crédit total : %d\n",c->credit_combat,c->credit);

	comb->ca_initial = comb->ca;

  comb->estPortee = 0;/*Le Combatant ne porte pas sa protection*/
  return comb;
}

void affiche_combat(Camp *c1, Camp *c2) {
  int i=0;
  extern int largeur;
  Champion * champ1 = c1->comb->c;
  Champion * champ2 = c2->comb->c;
  printf("\tPV %s : %d/%d\tPV %s : %d/%d\n\n",champ1->nom,c1->comb->pv,champ1->pv,champ2->nom,c2->comb->pv,champ2->pv);
  printf("\tPOS : %d\tPOS : %d\n\n",c1->comb->pos,c2->comb->pos);
  while (i < c1->comb->pos) {
    printf("_");
    i++;
  }
  printf("X");
  i++;
  while(i < c2->comb->pos) {
    printf("_");
    i++;
  }
  printf("O");
  i++;
  while(i<= largeur) {
    printf("_");
    i++;
  }
  printf("\n\n");
}

int fight(Camp *c1, Camp *c2, Donnees d) {
	int min1 = combattant_minimum(d, c1->t) + arme_minimum(d);
	int min2 = combattant_minimum(d, c2->t) + arme_minimum(d);
	if(c1->credit < min1)
	{
		printf("Le Camp %s n'a pas assez de credit pour le combat\n",c1->nom);
		return -2;
	}else if (c2->credit < min2)
	{
		printf("Le Camp %s n'a pas assez de credit pour le combat\n",c2->nom);
		return -2;
	}
	else
	{
	  Combattant *comb1;
	  Combattant *comb2;
	  int credit_combat = CREDIT_COMBAT;

	  /*On détermine le nombre de crédit attribué pour le tour*/
	  if(c1->credit < CREDIT_COMBAT) {
		  credit_combat = c1->credit;
	  }
	  if (c2->credit < credit_combat) {
		  credit_combat = c2->credit;
		}

	  c1->credit_combat = credit_combat;
    c1->credit -= c1->credit_combat;
	  c2->credit_combat = credit_combat;
	  c2->credit -= c2->credit_combat;

	  printf("\n##\n######\t\tFIGHT\t\t######\n\n");
    printf("CREDIT LEGUME : %d\n",c1->credit+credit_combat);
    printf("CREDIT FRUIT : %d\n",c2->credit+credit_combat);
	  comb1 = selection(c1, d);
	  c1->comb = comb1;
	  printf("\n\n\n");
	  comb2 = selection(c2, d);
	  c2->comb = comb2;
	  printf("Combattant 1 : %s | %s | CA : %d\n",comb1->c->nom,comb1->a->nom,comb1->ca);
	  printf("Combattant 2 : %s | %s | CA : %d\n",comb2->c->nom,comb2->a->nom,comb2->ca);
	  printf("QUE LE COMBAAAT COMMEEENNNNCE !\n\n");
	  affiche_combat(c1,c2);
  }
  return -1;
}

void show(Camp *c) {
	printf("Details equipements combattant\n");
	printf("Combattant : %s, PV : %d\n",c->comb->c->nom, c->comb->pv);
	printf("Arme : %s, Degat : %d-%d, CA : %d\n",c->comb->a->nom,c->comb->a->degMin,c->comb->a->degMax,c->comb->a->ca);
  if (c->comb->p != NULL) {
    printf("Protection : %s, Proba : %d%%, CA : %d\n",c->comb->p->nom,c->comb->p->proba,c->comb->p->ca);
  }
  else printf("Protection : Aucune\n");
  if (c->comb->s != NULL) {
    printf("Soins : %s, Effet : %d-%d, Restant : %d, CA : %d\n",c->comb->s->nom,c->comb->s->effetMin,c->comb->s->effetMax,c->comb->nbSoins,c->comb->s->ca);
  }
  else printf("Soins : Aucun\n");
}

void move_forward(Combattant *comb1, Combattant *comb2,int pas,int interrupt) {
  if (interrupt == 0) {
    if (comb1->pos + pas < comb2->pos) {
      if (comb1->ca - pas < 0) {
        printf("## Pas assez de CA pour aller %d pas\n",pas);
      }
      else {
        comb1->pos+=pas;
        comb1->ca-=pas;
      }
    }
    else {
      printf("##Impossible d'avancer aussi loin\n");
    }
  }
  else {
    if (comb2->pos - pas > comb1->pos) {
      if (comb2->ca - pas < 0) {
        printf("## Pas assez de CA pour aller a %d pas\n",pas);
      }
      else {
        comb2->pos-=pas;
        comb2->ca-=pas;
      }
    }
    else printf("##Impossible d'avancer aussi loin\n");
  }
}

void move_backward(Combattant *comb1, Combattant *comb2,int pas,int interrupt) {
  extern int largeur;
  if (interrupt == 0) {/*Si c'est le tour du combattant 1*/
    if (comb1->pos - pas >= 0) {/*Si il peut reculer*/
      if (comb1->ca - (2*pas) < 0) {/*Si il n'a pas assez de CA pour reculer*/
        printf("## Pas assez de CA pour aller %d pas\n",pas);
      }
      else {
        comb1->pos-=pas;/*On modifie sa position*/
        comb1->ca-= (2*pas);/*On modifie ses CA*/
      }
    }
    else {
      printf("##Impossible d'avancer aussi loin\n");
    }
  }
  else {/*Sinon si c'est le tour du combattant 2*/
    if (comb2->pos + pas <= largeur) {/*Si il peut reculer*/
      if (comb2->ca - (2*pas) < 0) {/*Si il n'a assez de CA pour reculer*/
        printf("## Pas assez de CA pour aller a %d pas\n",pas);
      }
      else {
        comb2->pos+=pas;/*On modifie sa position*/
        comb2->ca-= (2*pas);/*On modifie ses CA*/
      }
    }
    else printf("##Impossible d'avancer aussi loin\n");
  }
}

void sub_use_weapon(Combattant *comb1, Combattant *comb2,int nb, int interrupt) {
	int atteint,probaProtec,total = 0, contrer = 0;
	float force, resistance;
	while (nb > 0) {/*Pour chaque tir*/
		  comb1->ca -= comb1->a->ca;/*On decremente le cout en CA d'un tir*/
		  atteint = ((rand() % (comb1->a->degMax - comb1->a->degMin + 1)) + comb1->a->degMin);/*On défini le nombre de dégât */
		  force = (100+(float)comb1->c->force)/100;/*La force du combattant 1*/
		  resistance = (100-(float)comb2->c->resistance)/100;/*La résistance du combattant 2*/
		  atteint = Round(force*atteint);/*On multiplie les dégât par la force de combattant 1*/
		  atteint = Round(resistance*atteint);/*Puis on multiplie les dégât obtenue précédement par la résistance de combattant 2*/

		  if (comb2->estPortee) {/*Si le combattant 2 a une protection et qu'il l'a porte*/
			probaProtec = (rand()% 100);/*Probabilité que le coup porté le touche*/
			  if (probaProtec < comb2->p->proba) {/*Si ca ne le touche pas*/
				contrer += atteint;/*On ajoute les degats du coup au nombre de degat contré*/
			  }
			  else {/*Si cela le touche*/
				total += atteint;/*On augmente les dégât recu*/
			  }
		  }
		  else {/*Si le combattant 2 n'a pas de protection*/
			total +=atteint;
		  }
		  nb--;
		}
		comb2->pv -= total;/*On enlève les dégât total au combattant 2*/
		if (comb2->estPortee) printf("%s a contrer %d dégâts grâce à sa protection\n",comb2->c->nom,contrer);
		printf("%s a infligé %d dégats à %s avec %s\n",comb1->c->nom,total,comb2->c->nom,comb1->a->nom);
}

void use_weapon(Combattant *comb1, Combattant *comb2,int nb, int interrupt) {

	if (interrupt) comb1->a->portee*=-1;/*Si c'est le joueur de droite qui tire on inverse la portée de son arme*/

	if(comb1->ca - (comb1->a->ca * nb) < 0) {/*Si il n'a pas assez de CA pour effectuer tout ses tirs*/
		printf("## Pas assez de CA pour utiliser l'arme %d fois\n",nb);
	}
	else if ((interrupt) && (comb1->pos + comb1->a->portee <= comb2->pos)) {/*Sinon si il a assez de portée pour effectuer ses tirs*/
		sub_use_weapon(comb1,comb2,nb,interrupt);
	}
	else if (!(interrupt) && (comb1->pos + comb1->a->portee >= comb2->pos)) {/*Sinon si il a assez de portée pour effectuer ses tirs*/
		sub_use_weapon(comb1,comb2,nb,interrupt);
	}
	else {/*Sinon si il n'a pas assez de portée*/
		printf("==> Le champion %s est hors portée de ton %s\n",comb2->c->nom,comb1->a->nom);
		comb1->ca-= comb1->a->ca * nb;/*On lui enlève ses crédit*/
	}
	if (interrupt) comb1->a->portee*=-1;
	}

void use_protection(Combattant *comb) {
	if(comb->p != NULL){
	  if (comb->estPortee == 0) {
		if (comb->ca - comb->p->ca > 0) {
		  printf("Le champion équipe sa protection !\n");
		  comb->ca-=comb->p->ca;
		  comb->estPortee = 1;
		}
		else printf("Pas assez de CA pour équiper sa protection !\n");
	  }
	  else {
		printf("Il porte déjà sa protection ! \n");
	  }
	}else printf("Tu n'as pas de protection\n");
}

void use_care(Camp *c, int nb) {
  Combattant * comb = c->comb;
  int effet,total = 0;
  if (comb->s != NULL && nb > 0) {/*Si le combattant a du Soins*/
    if (nb <= comb->nbSoins) {/*Si il lui en reste encore assez de soins comparé a nb*/
      if (comb->ca >= (nb * comb->s->ca)) {/*Si il a assez de CA*/
        while (nb > 0 && comb->pv < comb->c->pv) {
          effet = (rand() % (comb->s->effetMax - comb->s->effetMin + 1)) + comb->s->effetMin;
          comb->pv+=effet;/*On ajoute les PV*/
          total += effet;
          comb->nbSoins--;/*On enleve un Soins*/
          comb->ca -= comb->s->ca;/*On enleve les CA*/
          nb--;
        }
        printf("%s a gagner %dPV\n",comb->c->nom,total);
        printf("Soins restant : %d\n",comb->nbSoins);
      }
      else printf("Vous n'avez pas assez de CA\n");
    }
    else {
      if (comb->nbSoins == 0) printf("Tu n'as plus de Soins\n");
      else printf("Il ne vous reste pas assez de Soins pour vous en appliquer %d fois\n",nb);
    }
  }
  else printf("Tu n'as pas de soins !\n");
}

int gain(int cePerdant, int ceGagnant) {
  int gain;
  gain = cePerdant - ceGagnant;
  if (gain < 1) gain = 1;
  return 5*gain;
}
