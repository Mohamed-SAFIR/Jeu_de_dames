struct erg{
	int joueur; /*0 ou 1*/
	char statut; /*d ou p ou espace si elle est vide*/
};
typedef struct erg piece_t;

struct erg1{
	int x;
	int y;
};
typedef struct erg1 position_t;

struct erg3{
	struct erg3* suivant;  /* il reste les infos sur les eventuelle  */
	struct erg3* preced;
	position_t* cp;     /*pour stocker tout les position intermidiares  la position initiale est cp[0] et finale cp[k] */
	int n;          /* pour stocker la langueure du tableau et exactement pour savoir la derniere position cp[k-1]*/
	int promotion;             /* si y a promotion 1   sinon 0*/   
};	
typedef struct erg3 mouvement_t;

struct erg4{
	mouvement_t* debut;
	mouvement_t* fin;
	int taille;
};
typedef struct erg4 liste_mouv_t;

struct erg6{
	piece_t tab[10][10];
	struct erg6* suivant;
	struct erg6* precedent;
};
typedef struct erg6 configuration_t;

struct erg7{
	configuration_t* debut;
	configuration_t* fin;
	int taille;
	int nbpj0;
	int nbpj1;
};
typedef struct erg7 lis_config;

struct erg5{
	piece_t plateau[10][10];
	liste_mouv_t* lis_coup_joue; 
	lis_config* lis_configur;         
	int joueur;
};
typedef struct erg5 partie_t;

void aff_noy(partie_t* partie,int x,int y);      /* on l utilise dans fonction afficher */	
piece_t piece_creer(int a,char c);
int piece_joueur(piece_t piec1);
piece_t piece_identifier(char x);
char piece_caracter(piece_t piec1);
void piece_afficher(piece_t piec1);
int case_vide(partie_t* partie,int x,int y);
void modifier_case(partie_t* partie,piece_t piec,int x,int y);	
void afficher_plateau(partie_t* partie);
void modifier_damier(partie_t* partie,position_t init,position_t finale);
mouvement_t* creer_mouv();
void ajouter_mouv(partie_t* partie,mouvement_t* mouv);
void supprimer_elem_mouv(partie_t* partie);
partie_t* partie_creer();
void modifier_damier(partie_t* partie,position_t a,position_t b);
configuration_t* creer_configuration();
void ajouter_config(partie_t* partie,configuration_t* conf);
void supprimer_elem_conf(partie_t* partie);
position_t saisie_case();
int saut_pion(partie_t* partie,position_t b);
int saut_dame(partie_t *partie,position_t b);
void conf_tab(partie_t* partie,configuration_t* conf);		 
int deplacement_valide(partie_t* partie,position_t dep,position_t arr);
void changer_joueur(partie_t* partie);
void annuler_mouvement(partie_t* partie);
void partie_jouer(partie_t* partie);
void partie_detruire(partie_t* partie);

partie_t * partie_charger(char * chemin);
void partie_sauvegarder(partie_t * partie, char * chaine);











