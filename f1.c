
#include <stdio.h>
#include <stdlib.h>
#include "f1.h"
#include <string.h>


piece_t piece_creer(int a,char c)
{
	piece_t piec1;
	piec1.joueur=a;
	piec1.statut=c;
  return(piec1);
}

int piece_joueur(piece_t piec1)
{
	return(piec1.joueur);
}

piece_t piece_identifier(char x)   /*Il faut verifier que x soit: p , P, d, D */
{
	piece_t p;
		p.statut=x;
	       if(x=='d' || x=='p')
			p.joueur=0;
	       else
			p.joueur=1;
	return(p);
}
char piece_caracter(piece_t piec1)
{
	return(piec1.statut);
}

void piece_afficher(piece_t piec1)
{
	printf("%c",piec1.statut);
}

/****************************************************************************/

int case_vide(partie_t* partie,int x,int y)    /* elle prend un pointeur vers unr partie comme argument, donc une adresse*/
{
	piece_t* l=&((*partie).plateau[x][y]);     /*si le statut egale a un espace donc la case est vide */
	if((*l).statut==' ')
	      return 1;        /*renvoie 1 si  elle est vide*/
    return 0;             /*renvoie 0 si elle est occupee*/
}

void modifier_case(partie_t* partie,piece_t piec,int x,int y)
{
	(*partie).plateau[x][y].joueur=piec.joueur;       /*les testes pour eviter  les erreur lors de la saisie par l utlisteur  ou si la case n est pas vide on le verifie dans le main*/
	(*partie).plateau[x][y].statut=piec.statut;       /* les changement sur les liste chainee on le fait dans cette fonction  pas dans le main */
}
	


void ajouter_mouv(partie_t* partie,mouvement_t* mouv)    /* le nouveau element on l ajoute au debut de la liste*/
{
	mouvement_t* m=partie->lis_coup_joue->debut;
	partie->lis_coup_joue->debut=mouv;

	if(partie->lis_coup_joue->taille==0)             /*le mouv passee en argument  ses deux pointeurs sont initialises a  NULL*/
		partie->lis_coup_joue->fin=mouv;
	else
	  {
	         mouv->suivant= m;
		 m->preced= mouv;
	  }
       partie->lis_coup_joue->taille++;
}

void supprimer_elem_mouv(partie_t* partie)
 {
	mouvement_t* m=partie->lis_coup_joue->debut;
	if(partie->lis_coup_joue->taille==1)
	  {
		partie->lis_coup_joue->fin=NULL;
		partie->lis_coup_joue->debut=NULL;
	  }
	if(partie->lis_coup_joue->taille>1)
	  {
		partie->lis_coup_joue->debut->suivant->preced=NULL;
		partie->lis_coup_joue->debut=m->suivant;

	  }
	partie->lis_coup_joue->taille--;
  free(m);
}	


void ajouter_config(partie_t* partie,configuration_t* conf)
{
	configuration_t* c=partie->lis_configur->debut;
	partie->lis_configur->debut=conf;
	

	if(partie->lis_configur->taille==0)
	       partie->lis_configur->fin=conf;
	else
	  {
		conf->suivant=c;
		c->precedent=conf;
	  }
  partie->lis_configur->taille++;
  
}

void supprimer_elem_conf(partie_t* partie)
 {
	configuration_t* conf=partie->lis_configur->debut;
	if(partie->lis_configur->taille==1)
	  {
		partie->lis_configur->fin=NULL;
		partie->lis_configur->debut=NULL;
	  }
	if(partie->lis_configur->taille>1)
	  {
		partie->lis_configur->debut->suivant->precedent=NULL;
		partie->lis_configur->debut=conf->suivant;
	  }
	partie->lis_configur->taille--;
  free(conf);
 }


void aff_noy(partie_t* partie,int x,int y)
{
		if((x%2==0 && y%2==0)||(x%2!=0 && y%2!=0))
			printf("   ");
		else{
			if(case_vide(partie,x,y)==1)
				printf(" . ");
			else
			  {
			       if(partie->plateau[x][y].joueur==0)
				{
				    if(partie->plateau[x][y].statut=='p')	
				      printf(" p ");
				    if(partie->plateau[x][y].statut=='d')
				      printf(" d ");
				}
			       if(partie->plateau[x][y].joueur==1)
				{
				    if(partie->plateau[x][y].statut=='P')	
				      printf(" P ");
				    if(partie->plateau[x][y].statut=='D')
				      printf(" D ");
			        }
		          }
		   }
}

void afficher_plateau(partie_t* partie)
{
	printf("\n\n\n");
	int i,j;
	printf("                                  0  1  2  3  4  5  6  7  8  9");
	printf("\n\n");
		for(i=0;i<10;i++)
		  {
			if(i<=3)
			     printf("          joueur 1--->        %d  ",9-i);
			if(i>3 && i<6)
			     printf("                              %d  ",9-i);
			
			if(i>=6 && i<=9)
			     printf("          joueur 0--->        %d  ",9-i);
                     for(j=0;j<=9;j++)
			aff_noy(partie,i,j);
                     printf("\n");
		}
	printf("\n");
 } 

/* dans la fonction passee on traiter un deplassement simple ou complexe et les deplacements des dames , on a supprime les pions capturees et on a ajoueter tous ca a la liste chainnee des mouvemnts (coup jouee)*/
 


                                                                                           
partie_t* partie_creer()
 {
	int i,j;
	partie_t* partie=malloc(sizeof(partie_t));
     for(i=0;i<=3;i++)
	for(j=0;j<10;j++)
	  {
		(*partie).plateau[i][j].joueur=1;
		(*partie).plateau[i][j].statut='P';
	  }
     for(i=4;i<6;i++)
	for(j=0;j<10;j++)
	  {
		(*partie).plateau[i][j].statut=' ';
		(*partie).plateau[i][j].joueur=-1;
	  }

     for(i=6;i<10;i++)
	for(j=0;j<10;j++)
	  {
		(*partie).plateau[i][j].joueur=0;
		(*partie).plateau[i][j] .statut='p';    
          }
	partie->lis_coup_joue=malloc(sizeof(liste_mouv_t)); 	 /*initialise la liste des coup joue*/
	partie->lis_coup_joue->debut=NULL;
	partie->lis_coup_joue->fin=NULL;
	partie->lis_coup_joue->taille=0;
	partie->lis_configur=malloc(sizeof(lis_config));  	/*initialise la liste des configurations*/
	partie->lis_configur->debut=NULL;
        partie->lis_configur->fin=NULL;
	partie->lis_configur->taille=0;
	partie->lis_configur->nbpj1=20;
	partie->lis_configur->nbpj0=20;
	configuration_t* c=creer_configuration();
	for(i=0;i<10;i++)
	   for(j=0;j<10;j++)
		c->tab[i][j]=partie->plateau[i][j];
	ajouter_config(partie,c);
	
	
	
  return(partie);
 }

void changer_joueur(partie_t* partie)
{
	if(partie->joueur==1)
		partie->joueur=0;
	else
		partie->joueur=1;
     
}


position_t saisie_case()
{
	position_t p;
	int a,b;
	int valide=0;
	while(valide==0)
	  {
		printf("  X =    Y= \n");
	        scanf("%d %d",&a,&b);
		a=9-a;
		if(a>9 || a<0 || b>9 || b<0 || (a%2!=0 && b%2!=0) || (a%2==0 && b%2==0))
			printf(" ERREUR vos coordonneés sont fausses !  \n");
		else{
			p.x=a;
			p.y=b;
			valide=1;
		    }
         }	
    return(p);
}

void modifier_damier(partie_t* partie,position_t a,position_t b)  /*supposons ce delacement est valide*/
{
	int i,j,n,rep;
	position_t po,c;
	partie->plateau[b.x][b.y].joueur=partie->plateau[a.x][a.y].joueur;
	partie->plateau[b.x][b.y].statut=partie->plateau[a.x][a.y].statut;
	partie->plateau[a.x][a.y].statut=' ';
	partie->plateau[a.x][a.y].joueur=-1;

	mouvement_t* mouv=creer_mouv();
	configuration_t* conf=creer_configuration();

	mouv->cp[0]=a;   		/*on ainitialise le tableau a une taille de 2 */
	mouv->cp[1]=b;
	
	
	if(partie->joueur==1 && b.x==9)    /*on a initiliser le champs joueur du mouvement et on a rendu la piece damme si elle a atteint la derniere ligne*/ 
	  {
		partie->plateau[b.x][b.y].statut='D';
		/*m->promotion=1;*/
	  }
	if(partie->joueur==0 && b.x==0)
	  {
		partie->plateau[b.x][b.y].statut='d';
		/*m->promotion=1;*/
	          
	  }
	n=abs(a.x-b.x);  /* on effectue la capture pour pion ou pour damme*/
   /* if(n<=1)
	{
		ajouter_config(partie,config); on ajoute le maillon (configuration) a la liste des configuration
        } */
	

    if(n>1)
     {
	if(a.x>b.x)     /*figure 1 et 2 */
	  {
		if(a.y<b.y){  /*figure 1*/
		   for(i=1;i<=n;i++){
		       if(piece_joueur(partie->plateau[a.x-i][a.y+i])!=partie->joueur)
		         {
					partie->plateau[a.x-i][a.y+i].statut=' ';
					partie->plateau[a.x-i][a.y+i].joueur=-1;
					mouv->promotion=1;
					if(partie->joueur==1)
					{	
						partie->lis_configur->nbpj0--;
					}
					else{
						partie->lis_configur->nbpj1--;
					}
					
							
			  }
		    } 
			
			 
						
               }
                if(a.y>b.y){    /*figure 2*/
		   for(i=1;i<=n;i++){
		       if(piece_joueur(partie->plateau[a.x-i][a.y-i])!=partie->joueur)
			{
				partie->plateau[a.x-i][a.y-i].statut=' ';
				partie->plateau[a.x-i][a.y-i].joueur=-1;
				mouv->promotion=1;
				if(partie->joueur==1)
				{	
					partie->lis_configur->nbpj0--;
				}
				else{
					partie->lis_configur->nbpj1--;
				}
				/*conf_tab(partie,config);*/
					/*ajouter_config(partie,config);*/
			}
		    }
		
			
			
		}
         } 
	 if(a.x<b.x) /* figure 3 et 4*/
	  {
		if(a.y<b.y){  /* figure 3*/
		     for(i=1;i<=n;i++){
		       if(piece_joueur(partie->plateau[a.x+i][a.y+i])!=partie->joueur)
			{
					partie->plateau[a.x+i][a.y+i].statut=' ';
					partie->plateau[a.x+i][a.y+i].joueur=-1;
					mouv->promotion=1;
					if(partie->joueur==1)
					{	
						partie->lis_configur->nbpj0--;
					}
					else{
						partie->lis_configur->nbpj1--;
					}
					/*conf_tab(partie,config);*/
					/*ajouter_config(partie,config);*/
			}
		      }
		   
		}	
			
	  
		if(a.y>b.y){
		     for(i=1;i<=n;i++){ 	   /*figure 4*/
		       if(piece_joueur(partie->plateau[a.x+i][a.y-i])!=partie->joueur)
			{
					partie->plateau[a.x+i][a.y-i].statut=' ';
					partie->plateau[a.x+i][a.y-i].joueur=-1;
					mouv->promotion=1;
					if(partie->joueur==1)
					{	
						partie->lis_configur->nbpj0--;
					}
					else{
						partie->lis_configur->nbpj1--;
					}
					/*conf_tab(partie,config);*/
					/*ajouter_config(partie,config);*/
			}
		     }
			
			
	
		   }
	}
    }
	
                               /*pour verifier si  il peut continuer*/
		if(saut_pion(partie,b)==1)
			printf(" la faute est dans saut \n");

			              if((partie->plateau[b.x][b.y].statut=='p')||(partie->plateau[b.x][b.y].statut=='P'))
					  {
  /*a verifier qui n est pas devenue dame */    while(saut_pion(partie,b)==1 && (abs(b.x-a.x)>1) )
						  {
							/*printf(" pour confirmer le coup appuyer sur 7 sinon sur 8\n");
					         	scanf("%d",&rep);
							if(rep!=7)
							  {
								annuler_mouvement(partie);
							  }*/
							afficher_plateau(partie);
							printf("   vous pouvez capturer encore!   saisissez la cordonnée d'arriver \n");
							c=a;
							a=b;
							b=saisie_case();
							if(deplacement_valide(partie,a,b)==1 && (abs(b.x-a.x)>1))
							  {
								mouv->cp=realloc(mouv->cp,(n+1)*sizeof(position_t));
								mouv->cp[n]=b;
								mouv->n++;
								modifier_damier(partie,a,b);
								afficher_plateau(partie);
								
								
							 }
							else
							  {
								printf(" vous devez capturer !!!\n");
								b=a;
								a=c;
							  }
						};
					   printf("c'est bon t as terminé on passe au joueur suivant\n");
					 }
					if((partie->plateau[b.x][b.y].statut=='D') || (partie->plateau[b.x][b.y].statut=='d'))
					  {
						while(saut_dame(partie,b)==1)
						  {
							printf("pour confirmer appuyer sur 7 sinon sur 8\n");
								scanf("%d",&rep);
								if(rep!=7)
								  {
									annuler_mouvement(partie);
								  }
							afficher_plateau(partie);
							printf("vous pouvez capturer encore!   saisissez la cordonnée d'arriver \n");
							c=a;
							a=b;
							b=saisie_case();
							if(deplacement_valide(partie,a,b)==1)
							  {
								mouv->cp=realloc(mouv->cp,(n+1)*sizeof(position_t));
								mouv->cp[n]=b;
								mouv->n++;
								modifier_damier(partie,a,b);
								afficher_plateau(partie);
								
							  }
							else
							  {
								printf(" vous devez capturer !!!\n");
								b=a;
								a=c;
							  }
						  };
						 printf("c'est bon t as terminé on passe au joueur suivant\n");
					  }
        conf_tab(partie,conf);
	
	ajouter_config(partie,conf);
	
	ajouter_mouv(partie,mouv);
		

 }	



int saut_pion(partie_t* partie,position_t b)   /* pour savoir la possibilite de capturer*/
{
	if( (b.x-1>=0) && (b.y+1<10) && (b.x-1<10) && (b.y+1>=0) && partie->plateau[b.x-1][b.y+1].joueur!=partie->joueur && partie->plateau[b.x-1][b.y+1].joueur!=-1)
	 {
		if((b.x-2>=0) && (b.y+2<10) && (b.x-2<10) && (b.y+2>=0) && (case_vide(partie,b.x-2,b.y+2)==1) )
		{
			printf(" f1\n");
			return 1;
		}
	 }	

	
	if( (b.x-1>=0) && (b.y-1<10) && (b.x-1<10) && (b.y-1>=0) && (partie->plateau[b.x-1][b.y-1].joueur!=partie->joueur) && (partie->plateau[b.x-1][b.y-1].joueur!=-1))
	 {
		if( (b.x-2>=0) && (b.y-2<10) && (b.x-2<10) && (b.y-2>=0) && (case_vide(partie,b.x-2,b.y-2)==1) )
		{
			printf(" f2\n");
			return 1;
		}
	 }	


	if( (b.x+1>=0) && (b.y+1<10) && (b.x+1<10) && (b.y+1>=0) && partie->plateau[b.x+1][b.y+1].joueur!=partie->joueur && partie->plateau[b.x+1][b.y+1].joueur!=-1)
	 {
		if( (b.x+2>=0) && (b.y+2<10) && (b.x+2<10) && (b.y+2>=0) && (case_vide(partie,b.x+2,b.y+2)==1))
		{
			printf(" f3\n");
			return 1;
		}
	 }	



	if( (b.x+1>=0) && (b.y-1<10) && (b.x+1<10) && (b.y-1>=0) && partie->plateau[b.x+1][b.y-1].joueur!=partie->joueur && partie->plateau[b.x+1][b.y-1].joueur!=-1)
	 {
		if( (b.x+2>=0) && (b.y-2<10) && (b.x+2<10) && (b.y-2>=0) && (case_vide(partie,b.x+2,b.y-2)==1))
		{
			printf("f4\n");
			return 1;
		}
	 }	
		
	return 0;
}

		
int saut_dame(partie_t *partie,position_t b)  /* pour savoir la possibilite de capturer dans les 4 diagonales*/
{
	int i;
	for(i=1;i<10;i++)
	{
		if( (b.x-i>=0) && (b.x-i<10) && (b.y+i>=0) && (b.y+i<10) )
			if( (partie->plateau[b.x-i][b.y+i].joueur!= partie->joueur) && (b.x-i-1<10) && (b.x-i-1>=0) && (b.y+i+1<10) && (b.y+i+1>=0) && (case_vide(partie,b.x-i-1,b.y+i+1)==1) && (partie->plateau[b.x-i][b.y+i].joueur!=-1 ))	
				return 1;
	} 


	for(i=1;i<10;i++)
	{
		if( (b.x-i>=0) && (b.x-i<10) && (b.y-i>=0) && (b.y-i<10) )
			if( (partie->plateau[b.x-i][b.y-i].joueur!= partie->joueur) && (b.x-i-1<10) && (b.x-i-1>=0) && (b.y-i-1<10) && (b.y-i-1>=0) && (case_vide(partie,b.x-i-1,b.y-i-1)==1) && (partie->plateau[b.x-i][b.y-i].joueur!=-1))	
				return 1;
	} 


	for(i=1;i<10;i++)
	{
		if( (b.x+i>=0) && (b.x+i<10) && (b.y+i>=0) && (b.y+i<10) )
			if( (partie->plateau[b.x+i][b.y+i].joueur!= partie->joueur) && (b.x+i+1<10) && (b.x+i+1>=0) && (b.y+i+1<10) && (b.y+i+1>=0) && (case_vide(partie,b.x+i+1,b.y+i+1)==1) && (partie->plateau[b.x+i][b.y+i].joueur!=-1))	
				return 1;
	} 


	for(i=1;i<10;i++)
	{
		if( (b.x+i>=0) && (b.x+i<10) && (b.y-i>=0) && (b.y-i<10) )
			if( (partie->plateau[b.x+i][b.y-i].joueur!= partie->joueur) && (b.x+i+1<10) && (b.x+i+1>=0) && (b.y-i-1<10) && (b.y-i-1>=0) && (case_vide(partie,b.x+i+1,b.y-i-1)==1) && (partie->plateau[b.x+i][b.y-i].joueur!=-1 ))	
				return 1;
	} 

	return 0;
}

    

void conf_tab(partie_t* partie,configuration_t* conf)
{
	int i,j; 
		for(i=0;i<10;i++)
		    for(j=0;j<10;j++)
			conf->tab[i][j]=partie->plateau[i][j];
}





int deplacement_valide(partie_t * partie, position_t dep, position_t arr)
{
	int i,n;
	int k=0;
	n=abs(arr.x-dep.x);

	if((partie->plateau[arr.x][arr.y].statut!=' ') || (partie->plateau[dep.x][dep.y].joueur!=partie->joueur) || (partie->plateau[dep.x][dep.y].statut==' ') || (dep.x==arr.x && dep.y==arr.y) || (dep.x==arr.x) )
	{	
		return 0;
	//voir si la piece lui appartient et que la case d arriver et libre et que casedepart n est pas vide
	}
	
	if(partie->joueur==0)
	{
		if(partie->plateau[dep.x][dep.y].statut=='p')
		{	
			if(n>2)
			{
				return 0; //car c'est un pion
			}
			if(n==2)  //donc y a une capture , on verifie que la case entre dep et arr est pour l adversse
			{
				if((dep.x > arr.x) && (arr.y>dep.y)) //1
				{
					if(partie->plateau[dep.x-1][dep.y+1].joueur==1)
					{
						return 1;
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))   //2
				{
					if(partie->plateau[dep.x-1][dep.y-1].joueur==1)
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))   //3
				{
					if(partie->plateau[dep.x+1][dep.y-1].joueur==1)
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))    //4
				{
					if(partie->plateau[dep.x+1][dep.y+1].joueur==1)
					{
						return 1;
					}
				}
				return 0; 
			}
			if(n==1)
			{
				/*if(saut_pion(partie,dep)==1)
				{
					return 0;
				}
				else 
				{*/
					if (dep.x>arr.x)
					{
						return 1;
					}
					else 
					{
						return 0;
					}
				/*}*/
			}
		// voir s'il s'agit bien d'une dame
			if(partie->plateau[arr.x][arr.y].statut=='d')
			{
				if((dep.x>arr.x) && (dep.y<arr.y)) //figure1
				{ //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x-i>=0) && (dep.x-i<10) && (dep.y+i>=0) && (dep.y+i<10))
						{
							if(partie->plateau[dep.x-i][dep.y+i].joueur==0)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))  //figure2
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x-i>=0) && (dep.x-i<10) && (dep.y-i>=0) && (dep.y-i<10))
						{
							if(partie->plateau[dep.x-i][dep.y-i].joueur==0)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))  //figure3
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x+i>=0) && (dep.x+i<10) && (dep.y+i>=0) && (dep.y+i<10))
						{
							if(partie->plateau[dep.x+i][dep.y+i].joueur==0)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))   //figure4
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x+i>=0) && (dep.x+i<10) && (dep.y-i>=0) && (dep.y-i<10))
						{
							if(partie->plateau[dep.x+i][dep.y-i].joueur==0)
							{
								return 0;
							}
						}
					}
				}
					// etape deux
				
				if((dep.x>arr.x) && (dep.y<arr.y))  //figure1
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x-i>=0) && (dep.x-i<10) && (dep.y+i>=0) && (dep.y+i<10) )
						{
							if(partie->plateau[dep.x-i][dep.y+i].joueur==1) //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))  //figure2
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x-i>=0) && (dep.x-i<10) && (dep.y-i>=0) && (dep.y-i<10) )
						{
							if(partie->plateau[dep.x-i][dep.y-i].joueur==1)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))  //figure3
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x+i>=0) && (dep.x+i<10) && (dep.y+i>=0) && (dep.y+i<10) )
						{
							if(partie->plateau[dep.x+i][dep.y+i].joueur==1)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))  //figure4
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x+i>=0) && (dep.x+i<10) && (dep.y-i>=0) && (dep.y-i<10) )
						{
							if(partie->plateau[dep.x+i][dep.y-i].joueur==1)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					} 
				       if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}

				// etape 3
				

				/*if (saut_dame(partie,dep)==1)
				{
					if(n==1)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}*/
			}
		}
	}
		// autre joueur

	if(partie->joueur==1)
	{
		if(partie->plateau[dep.x][dep.y].statut=='P')
		{	
			if(n>2)
			{
				return 0; //car c'est un pion
			}
			if(n==2)  //donc y a une capture , on verifie que la case entre dep et arr est pour l adversse
			{
				if((dep.x >arr.x) && (arr.y>dep.y)) //1
				{
					if(partie->plateau[dep.x-1][dep.y+1].joueur==0)
					{
						return 1;
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))   //2
				{
					if(partie->plateau[dep.x-1][dep.y-1].joueur==0)
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))   //3
				{
					if(partie->plateau[dep.x+1][dep.y-1].joueur==0)
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))    //4
				{
					if(partie->plateau[dep.x+1][dep.y+1].joueur==0)
					{
						return 1;
					}
				}
				return 0; 
			}
			if(n==1)
			{
				/*if(saut_pion(partie,dep)==1)
				{
					return 0;
				}
				else 
				{*/
					if (dep.x<arr.x)
					{	
						return 1;
					}
					else 
					{
						return 0;
					}
				//}
			}
		 // voir s'il s'agit bien d'une dame
			if(partie->plateau[arr.x][arr.y].statut=='D')
			{
				if((dep.x>arr.x) && (dep.y<arr.y)) //figure1
				{ //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x-i>=0) && (dep.x-i<10) && (dep.y+i>=0) && (dep.y+i<10))
						{
							if(partie->plateau[dep.x-i][dep.y+i].joueur==1)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))  //figure2
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x-i>=0) && (dep.x-i<10) && (dep.y-i>=0) && (dep.y-i<10))
						{
							if(partie->plateau[dep.x-i][dep.y-i].joueur==1)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))  //figure3
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x+i>=0) && (dep.x+i<10) && (dep.y+i>=0) && (dep.y+i<10))
						{
							if(partie->plateau[dep.x+i][dep.y+i].joueur==1)
							{
								return 0;
							}
						}
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))   //figure4
				{  //pour voir si il y a ses propres pieces dans son chemin si oui on renvoie 0 sinon on continu avec les tests
					for(i=1;i<n;i++)
					{	
						if((dep.x+i>=0) && (dep.x+i<10) && (dep.y-i>=0) && (dep.y-i<10))
						{
							if(partie->plateau[dep.x+i][dep.y-i].joueur==1)
							{
								return 0;
							}
						}
					}
				}
					// etape deux
				
				if((dep.x>arr.x) && (dep.y<arr.y))  //figure1
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x-i>=0) && (dep.x-i<10) && (dep.y+i>=0) && (dep.y+i<10) )
						{
							if(partie->plateau[dep.x-i][dep.y+i].joueur==0) //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x>arr.x) && (dep.y>arr.y))  //figure2
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x-i>=0) && (dep.x-i<10) && (dep.y-i>=0) && (dep.y-i<10) )
						{
							if(partie->plateau[dep.x-i][dep.y-i].joueur==0)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y<arr.y))  //figure3
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x+i>=0) && (dep.x+i<10) && (dep.y+i>=0) && (dep.y+i<10) )
						{
							if(partie->plateau[dep.x+i][dep.y+i].joueur==0)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					}
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}
				if((dep.x<arr.x) && (dep.y>arr.y))  //figure4
				{
					for(i=1;i<n;i++)
					{
						if( (dep.x+i>=0) && (dep.x+i<10) && (dep.y-i>=0) && (dep.y-i<10) )
						{
							if(partie->plateau[dep.x+i][dep.y-i].joueur==0)  //pour voir si ya plus d'une piece appartien a l'adversse dans son chemin il renvoie0 sinon on continue le test 
							{
								k=k+1;	
							}
							if(k>=2)
							{
								return 0;
							}
						}
						
					} 
					if(k==1)  //si entre le depp et l'arr ya une seul piece d'adverse donc y a une capture on renvoie 1
					{
						return 1;
					}
				}

				// etape 3
				

				/*if(saut_dame(partie,dep)==1)
				{
					if(n==1)
					{
						return 0;
					}
					else
					{
						return 1;
					}
				}*/
			}
		}
	}
}

void annuler_mouvement(partie_t* partie)
 {
	int i,j,m;
	m=(partie->lis_coup_joue->debut->n);
	supprimer_elem_conf(partie);
	for(i=0;i<10;i++)
	   for(j=0;j<10;j++)
		partie->plateau[i][j]=partie->lis_configur->debut->tab[i][j];
	if(partie->joueur==1)
	 {
		partie->lis_configur->nbpj0= partie->lis_configur->nbpj0+(m-2);      /*on augmente  les pieces capturer pour le joueur adversse si y avais une capture car on a annule le mouvement*/  
	 }
	if(partie->joueur==0)
	 {
		partie->lis_configur->nbpj1=partie->lis_configur->nbpj1+(m-2);       /*on augmente  les pieces capturer pour le joueur adversse si y avais une capture car on a annule le mouvement*/  
	 }
	supprimer_elem_mouv(partie);
 }



		
	 
 	 	
	
void partie_jouer(partie_t* partie)
 {
	int quitter,sauv,confir,rep;
	quitter=0;
	sauv=0;
	partie->joueur=0;
	position_t p1,p2;
	char* s;
	   do{
		do{
			printf("le tour est pour le joueur :%d\n",partie->joueur);
			printf(" saisissez les cordonnées de depart  svp !\n");
			p1=saisie_case();
			printf(" saisissez les cordonnées d'arrivée  svp !\n");
			p2=saisie_case();
		}while(deplacement_valide(partie,p1,p2)==0);
			modifier_damier(partie,p1,p2);
			afficher_plateau(partie);
			printf("pour confirmer appuyer sur 7 \n");
			scanf("%d",&confir);
			
			if(confir==7)
				{
					changer_joueur(partie);	  		
				}
			       else
				{
					annuler_mouvement(partie);
					afficher_plateau(partie);
				}
 			   

			printf(" pour quitter la partie appuyer sur 1 \n");
			scanf("%d",&rep);
			
			if(rep==1)
			 {
				printf("pour sauvegarder 1");
				scanf("%d",&sauv);
				if(sauv==1)
				{
							printf("donnez un nom au fichier svp!\n");
							scanf("%s",s);
							partie_sauvegarder(partie,s);
				}
			}
			

		}while(quitter==0 || partie->lis_configur->nbpj0>0 || partie->lis_configur->nbpj1>0);
	if(partie->lis_configur->nbpj0==0)
	{
		printf(" fin de partie , le joueur 1 a gagné ");
	}
	if(partie->lis_configur->nbpj1==0)
	{
		printf(" fin de partie , le joueur 0 a gagné ");
	}


	
 }
	
mouvement_t* creer_mouv()  /* creer un maillon mouvement et allouer l espace pour le tableau(pour initiale et finale) apres on rajoute intermidiare*/
 {
	mouvement_t* m=malloc(sizeof(mouvement_t));
	m->suivant=NULL;
	m->preced=NULL;
	m->n=2;
	m->cp=malloc(2*sizeof(position_t));
	
    return(m);
}	

configuration_t* creer_configuration()  /*creer un maillon configuration  et initialiser les deux pointeurs*/
{
	configuration_t* c=malloc(sizeof(configuration_t));
	c->suivant=NULL;
	c->precedent=NULL;

     return(c);
}	
		
void partie_detruire(partie_t* partie)
 {
	int i;
	for(i=1;i<=(partie->lis_coup_joue->taille);i++)
	   supprimer_elem_mouv(partie);
	free(partie->lis_coup_joue);

	for(i=1;i<=(partie->lis_configur->taille);i++)
	  supprimer_elem_conf(partie);
	free(partie->lis_configur);
  free(partie);
}

	 
void partie_sauvegarder(partie_t * partie, char * chaine)
{
	int i,j;
	FILE *f;
	char *chemin=malloc(strlen(chaine) + 20 );
	sprintf(chemin,"../plateaux/%s.plt",chaine);
	f=fopen(chemin,"w+");
	if(f!=NULL)
	{
		fprintf(f,"PL\n");
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{
				fprintf(f,"%c ", partie->plateau[i][j].statut);
			}
		}
	}
	fclose(f);	
}

partie_t * partie_charger(char * chemin)
{
	partie_t *partie=partie_creer();
	char entete[3]="";
	FILE * f = fopen(chemin,"r");
	if(f!=NULL)
	{
		int i,j;
		char piece;
		fscanf(f,"%s",entete);
		if(strcmp(entete,"PL") !=0)
		{
			printf("ce n'est pas un fichier .plt\n");
		}
		else
		{
			for(i=0;i<10;i++)
			{
				for(j=0;j<10;j++)
				{
					fscanf(f,"%c",&piece);
					partie->plateau[i][j]=piece_identifier(piece);
				}
				fscanf(f,"%c",&piece);
			}
		}
		fclose(f);
	}
	else
	{
		printf("ya une erreur lors d'enregistrement de votre partie \n");
	}
	return(partie);
}
  











































