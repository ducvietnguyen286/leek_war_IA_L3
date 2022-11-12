#include "init.h"
#include "commande.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>

int largeur = 0;

int main(void) {
  int terminer,go,interrupt,tour;/*terminer = Savoir quand la partie est terminée | go = Type de commande | interrupt = Tour du legume(0)/Fruit(1) | tour = 0 si c'est la première action du combattant sinon 1*/
  struct winsize w;/*Recupérer la taille du terminal*/
  char buf;/*Buffer*/
  Champion * tabC = creer_champion();/*Tableau des Champions*/
  Arme * tabA = creer_arme();/*Tableau des armes*/
  Protection * tabP = creer_protection();/*Tableau des protections*/
  Soin * tabS = creer_soin();/*Tableau des Soins*/
  Donnees d;/*On y stocke tous les tbl précédents*/
  char * ch = (char *) malloc(sizeof(char) * 50);/*chaine de car du scanf*/
  Camp *lesFruits, *lesLegumes;/*Les Camps*/
  int min1, min2;/*CE minimum de chaque camp pour jouer*/
  d.tabC = tabC;d.tabA = tabA;d.tabP = tabP;d.tabS = tabS;
debut:
  ioctl(0, TIOCGWINSZ, &w);
  terminer = 0, go = 1, interrupt = 0, tour = 0;

  largeur = w.ws_col - 1;
  /*Création des camps */
  lesFruits = creer_camp(Fruit,"Les Fruits de la mort");
  lesLegumes = creer_camp(Legume,"Les Légumes célestes");

  /*Seuil de crédit minimum pour chaque équipe*/
  min1 = combattant_minimum(d, lesLegumes->t) + arme_minimum(d);
  min2 = combattant_minimum(d, lesFruits->t) + arme_minimum(d);

  printf("\n/!\\ Veuillez ne pas redimenssioner votre fenêtre /!\\\n");
  printf("Largeur : %d\n",largeur);

  printf("\t\tCrédit Initial : %d\n",lesFruits->credit); /*Affichage des crédits initial*/

  /*Tant que l'utilisateur n'a pas fini*/
  while (terminer != 1) {
    if (go == 1) {/*Si le type de Commande == 1 (Commande hors combat*/
      printf(">");
      scanf("%[^\n]",ch);
      terminer = lance_commande(ch,d,lesLegumes,lesFruits,&go, &interrupt);
      ch[0] = '\0';
      if(terminer == -1) {/*La commande fight v versus f retourne -1*/
        continue;
      }
      do {/*Vider le buffer*/
        buf = getchar();
      } while (buf != '\n');
    }
    if (terminer == -2) {/*Si on ne peut pas lancer de combat*/
      terminer = 1;
      continue;
    }
    while (terminer == -1) {/*Tant que l'on est en combat*/
      if (lesLegumes->comb->pv <= 0) { /*Si le combattant des légumes n'a plus de vie*/
        printf("%s a éliminé %s\n",lesFruits->comb->c->nom,lesLegumes->comb->c->nom);
        lesFruits->credit += gain(lesLegumes->credit_combat_used,lesFruits->credit_combat_used);/*Gain du combat*/
        printf("GAIN : %d\n",gain(lesLegumes->credit_combat_used,lesFruits->credit_combat_used));
        terminer = 2;
        go = 1;
        continue;
      }
      else if (lesFruits->comb->pv <= 0) {/*Si le combattant des Fruits n'a plus de vie*/
        printf("%s a éliminé %s\n",lesLegumes->comb->c->nom,lesFruits->comb->c->nom);
        lesLegumes->credit += gain(lesFruits->credit_combat_used,lesLegumes->credit_combat_used);
        printf("GAIN : %d\n",gain(lesFruits->credit_combat_used,lesLegumes->credit_combat_used));
        terminer = 2;
        go =1;
        continue;
      }
      if (lesLegumes->comb->ca <= 0) {/*Si le combattant légume n'a plus de CA*/
        interrupt = 1;/*On change la main*/
        lesLegumes->comb->ca = lesLegumes->comb->ca_initial;/*on reinitialise ces CA*/
      }
      else if (lesFruits->comb->ca <= 0) {/*Sinon si le Fruit n'a plus de CA*/
        interrupt = 0;
        lesFruits->comb->ca = lesFruits->comb->ca_initial;
      }
  	  if(interrupt == 0) {/*Tour du Legume*/
		      printf("tour : %d\n",tour);
          if (tour == 0) {/*Si il commence son tour*/
            tour = 1;
            lesLegumes->comb->ca = lesLegumes->comb->ca_initial;/*on reinitialise ces CA*/
          }
		      printf("%s (%d) >",lesLegumes->comb->c->nom,lesLegumes->comb->ca);
      }
  	  else {
        if (tour == 1) {
          tour = 0;
		      lesFruits->comb->ca = lesFruits->comb->ca_initial;
		      }
          printf("%s (%d) >",lesFruits->comb->c->nom,lesFruits->comb->ca);
      }
      scanf("%[^\n]",ch);
      terminer = lance_commande(ch,d,lesLegumes,lesFruits,&go, &interrupt);
      ch[0] = '\0';
      do {
        buf = getchar();
      } while (buf != '\n');
    }
    if (terminer == 2) {/*Apres un combat*/
      printf("Credit %s : %d\n",lesLegumes->nom,lesLegumes->credit);
      printf("Credit %s : %d\n",lesFruits->nom,lesFruits->credit);
      if (lesLegumes->credit < min1 && lesFruits->credit < min2) {
        printf("Vous êtes ex-aequo !!\n");
        terminer = 1;
      }
    	else if(lesLegumes->credit < min1)/*On verifie si les LEgumes ont assez de CE*/
    	{
    		printf("Le Camp %s n'a pas assez de credit pour le combat\nPERDU!\n",lesLegumes->nom);
    		terminer =1;
    	}else if (lesFruits->credit < min2)
    	{
    		printf("Le Camp %s n'a pas assez de credit pour le combat\nPERDU\n",lesFruits->nom);
    		terminer = 1;
    	}
    }

  }

  printf("Voulez vous recommencer une partie ?(oui/autre)\n");
  scanf("%[^\n]",ch);
  if (strcmp(ch,"oui") == 0) {
    /*free(ch);*/
    do {
      buf = getchar();
    } while (buf != '\n');
    goto debut;
  }

  printf("Aurevoir à bientôt pour des prochains combats !\n");

  return 1;

}
