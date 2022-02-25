/*!
  \file   calendrier.cc
  \author RB
  \date   Fevrier 2019
  \brief  Implémentation du module "calendrier"
*/

#include <iostream>
#include "calendrier.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
int annee_est_bissextile(int annee)
{
	if((annee % 400) == 0)
		return true;
	else if((annee % 100) == 0)
		return false;
	else
		return ((annee % 4) == 0);
}

///////////////////////////////////////////////////////////////////////
int jours_par_mois (int mois, int annee)
{ 
	switch (mois)
    {
    case 4 :
    case 6 :
    case 9 :
    case 11: 
		return 30;      
    case 1 :
    case 3 :
    case 5 :
    case 7 :
    case 8 :
    case 10:
    case 12: 
		return 31;      
    case 2 : 
		return annee_est_bissextile (annee) ? 29 : 28;      
    default: 
		cout << "Erreur: je ne connais pas le mois "
		     << mois << endl;
		return 0;
    }
}

//////////////////////////////////////////////////////////////////////
int jours_par_an(int annee)
{ 
  return annee_est_bissextile (annee) ? 366 : 365;
}

//////////////////////////////////////////////////////////////////////
int date_valable(int jour, int mois, int annee)
{ 
  if ((mois < 1) || (mois > 12))
    return 0;

  if ((jour < 1) || (jour > jours_par_mois (mois, annee)))
    return 0;
  
  return 1;    /* oui, la date est valable */
}
