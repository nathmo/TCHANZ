/*!
  \file   calendrier.cc
  \author RB
  \date   Fevrier 2019
  \brief  Implémentation du module "calendrier"
*/

#include <cstdlib>      // pour la fonction abs()
#include "calendrier.h"
#include "difference.h"

static	int jours_depuis_debut(int jour, int mois, int annee);

/* 
   Cette fonction retourne le nombre de jours ecoules depuis le
   1er janvier 1600.
   
   Elle n'est pas visible en dehors de ce module grace à static
*/

static int jours_depuis_debut(int jour, int mois, int annee)
{
	int i,
	total = 0;

	for (i=1600; i < annee; i++)
		total += jours_par_an (i);
  
	for (i=1; i < mois; i++)
		total += jours_par_mois (i, annee);
  
	return total + jour - 1;
}

int jours_entre_deux_dates(int jour_1, int mois_1, int annee_1,
			               int jour_2, int mois_2, int annee_2)
{
  return abs(jours_depuis_debut(jour_1, mois_1, annee_1) -
	         jours_depuis_debut(jour_2, mois_2, annee_2));
}
