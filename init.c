#include "init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

champ champs = {{"Haricot","Légume","10","10","40","5"},
                {"Fenouil","Légume","12","15","40","7"},
                {"Poireau","Légume","15","20","60","10"},
                {"Aubergine","Légume","20","20","60","15"},
                {"Courgette","Légume","20","25","80","20"},
                {"Carotte","Légume","25","25","80","25"},
                {"Banane","Fruit","10","10","40","5"},
                {"Kiwi","Fruit","12","15","40","7"},
                {"Poire","Fruit","15","20","60","10"},
                {"Pomme","Fruit","20","20","60","15"},
                {"Ananas","Fruit","20","25","80","20"},
                {"Durian","Fruit","25","25","80","25"}};


arme armes = {{"Eplucheur Laser","2","1","1","2","2"},
              {"Mandoline Sonique","5","3","1","3","3"},
              {"Couperet Laser","10","5","2","6","5"},
              {"Hachoir Neuronique","20","7","4","9","7"},
              {"Mixeur Blaster","30","10","7","12","11"}};

protection protections = {{"Casque-Egouttoir","1","2","25"},
                          {"Casque-Entonnoir","3","4","40"},
                          {"Woklier","5","6","60"},
                          {"Tablier-Armure","10","8","80"}};

soin soins = {{"Humus-Neutronique","1","5","4","2","4"},
              {"Compost-Protonique","5","10","3","5","8"},
              {"Engrais-Ionique","7","15","2","8","12"}};

Champion * creer_champion(void) {
  Champion *tab = (Champion*) malloc(sizeof(Champion)*NB_CHAMPION);
  int i, id_fruit = 1, id_legume = 1;
  for(i = 0; i < NB_CHAMPION; i++) {
	Champion c;
	c.nom = champs[i][NOM_C];
	c.force = atoi(champs[i][FORCE_C]);
	c.resistance = atoi(champs[i][RESISTANCE_C]);
	c.pv = atoi(champs[i][PV_C]);
	c.ce = atoi(champs[i][CE_C]);
	if (strcmp(champs[i][TYPE_C],"Légume") == 0) {
		c.t = Legume;
		c.id = id_legume++;
	}
	else {
		c.t = Fruit;
		c.id = id_fruit++;
	}
	tab[i] = c;
  }
  return tab;
}

Arme * creer_arme(void){
  Arme *tab = (Arme*) malloc(sizeof(Arme)*NB_ARME);
  int i;
  for(i = 0; i < NB_ARME; i++) {
    Arme a;
    a.id = i + 1;
    a.nom = armes[i][NOM_A];
    a.ce = atoi(armes[i][CE_A]);
    a.ca = atoi(armes[i][CA_A]);
    a.degMin = atoi(armes[i][DEGMIN_A]);
    a.degMax = atoi(armes[i][DEGMAX_A]);
    a.portee = atoi(armes[i][PORTEE_A]);
    tab[i] = a;
  }
  return tab;
}

Protection * creer_protection(void) {
  Protection * tab = (Protection *) malloc(sizeof(Protection)*NB_PROTECTION);
  int i;
  for (i = 0; i < NB_PROTECTION; i++) {
    Protection p;
    p.id = i + 1;
    p.nom = protections[i][NOM_P];
    p.ce = atoi(protections[i][CE_P]);
    p.ca = atoi(protections[i][CA_P]);
    p.proba = atoi(protections[i][PROBA_P]);
    tab[i] = p;
  }
  return tab;
}

Soin * creer_soin(void) {
  Soin * tab = (Soin *) malloc(sizeof(Soin)*NB_SOIN);
  int i;
  for (i = 0; i < NB_SOIN; i++) {
    Soin s;
    s.id = i + 1;
    s.nom = soins[i][NOM_S];
    s.ce = atoi(soins[i][CE_S]);
    s.ca = atoi(soins[i][CA_S]);
    s.volume = atoi(soins[i][VOLUME_S]);
    s.effetMin = atoi(soins[i][EFFET_MIN_S]);
    s.effetMax = atoi(soins[i][EFFET_MAX_S]);
    tab[i] = s;
  }
  return tab;
}

Camp * creer_camp(Type t, char *nom) {
  Camp *c =(Camp*) malloc(sizeof(Camp));
  c->t = t;
  c->credit = CREDIT_INITIAL;
  c->nom = nom;
  c->credit_combat = 0;
  return (c);
}
