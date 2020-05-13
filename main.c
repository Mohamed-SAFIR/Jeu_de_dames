#include<stdio.h>
#include<stdlib.h>
#include "jeu.h"

int main() 	
{
	partie_t* partie=partie_creer();
	afficher_plateau(partie);
	
	
	partie_jouer(partie);
  partie_detruire(partie);
	
  return EXIT_SUCCESS;
}
