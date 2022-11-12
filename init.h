#ifndef NB_CHAMPION
typedef enum {Legume, Fruit} Type;
typedef struct {
  int id;
  char *nom;
  Type t;
  int force;
  int resistance;
  int pv;
  int ce;
} Champion;

typedef struct {
  int id;
  char *nom;
  int ce;
  int ca;
  int degMin;
  int degMax;
  int portee;
} Arme;

typedef struct {
  int id;
  char *nom;
  int ce;
  int ca;
  int proba;
} Protection;

typedef struct {
  int id;
  char *nom;
  int ce;
  int ca;
  int volume;
  int effetMin;
  int effetMax;
} Soin;


#define CREDIT_ACTION 50
typedef struct {
  Champion *c;
  int pv;
  Arme *a;
  Protection *p;
  int estPortee;
  Soin *s;
  int nbSoins;
  int ca;
  int ca_initial;
  int pos;
} Combattant;


#define CREDIT_INITIAL 1000
#define CREDIT_COMBAT 50
typedef struct {
  Type t;
  char * nom;
  int credit;
  int credit_combat;
  int credit_combat_used;
  Combattant *comb;
} Camp;
Camp * creer_camp(Type t, char *nom);



#define NB_FRUIT 6
#define NB_LEGUME 6
#define NB_CHAMPION (NB_FRUIT + NB_LEGUME)
#define NOM_C 0
#define TYPE_C 1
#define FORCE_C 2
#define RESISTANCE_C 3
#define PV_C 4
#define CE_C 5


typedef char * champ[NB_CHAMPION][6];

Champion * creer_champion(void);

#define NB_ARME 5
#define NOM_A 0
#define CE_A 1
#define CA_A 2
#define DEGMIN_A 3
#define DEGMAX_A 4
#define PORTEE_A 5
typedef char * arme[NB_ARME][6];
Arme * creer_arme(void);

#define NB_PROTECTION 4
#define NOM_P 0
#define CE_P 1
#define CA_P 2
#define PROBA_P 3
typedef char * protection[NB_PROTECTION][4];
Protection * creer_protection(void);

#define NB_SOIN 3
#define NOM_S 0
#define CE_S 1
#define CA_S 2
#define VOLUME_S 3
#define EFFET_MIN_S 4
#define EFFET_MAX_S 5
typedef char * soin[NB_SOIN][6];
Soin * creer_soin(void);

typedef struct {
  Champion * tabC;
  Arme * tabA;
  Protection *  tabP;
  Soin * tabS;
} Donnees;


Combattant * creer_combattant(Champion c, Arme a, Protection p, Soin s);


#endif
