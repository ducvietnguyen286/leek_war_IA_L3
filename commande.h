#include "init.h"
void show_vegetables(Champion * tab);
void show_vegetables_i(Champion * tab, int i);
void show_fruits(Champion * tab);
void show_fruits_i(Champion * tab, int i);
void show_weapons(Arme * tab);
void show_weapons_i(Arme * tab, int i);
void show_protections(Protection * tab);
void show_protections_i(Protection * tab, int i);
void show_care(Soin * tab);
void show_care_i(Soin * tab, int i);
void affiche_combat(Camp *c1, Camp *c2);
int verifier_entier(char *ch);
int fight(Camp *c1, Camp *c2, Donnees d);
Combattant * selection(Camp *c, Donnees d);
int choix_id(Donnees d,char c);
int combattant_minimum(Donnees d, Type type);
int arme_minimum(Donnees d);
void show(Camp *c);
void move_forward(Combattant *c1, Combattant *c2, int pas, int interrupt);
void move_backward(Combattant *c1, Combattant *c2, int pas, int interrupt);
void use_weapon(Combattant *c1, Combattant *c2, int nb, int interrupt);
void use_protection(Combattant *comb);
void use_care(Camp *c, int nb);
int lance_commande(char *cmd, Donnees d, Camp *c1, Camp *c2, int *go, int * interrupt);
int Round(float nb);
int gain(int cePerdant, int ceGagnant);
