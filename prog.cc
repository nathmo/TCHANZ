/*!
  \file   prog.cc
  \author RB
  \date   Fevrier 2019
  \brief  Implémentation du module principal avec la fonction main().
          ce programme calcule le nombre de jours entre 2 dates
*/

#include <iostream>
#include "calendrier.h"
#include "difference.h"

using namespace std;

#define START_YEAR 1600

// fonction utilitaire visible seulement dans ce module
static	void saisie_date(int& jour, int& mois, int& annee);

 
int main (void)
{  
	cout << "Ce programme calcule le nombre de jours"
	        " separant deux dates." << endl;
	cout << "Attention: les dates doivent etre "
			"posterieures au 1er jan. 1600." << endl;
  
	cout << "Première date" << endl;
	int jour_1(0), mois_1(0), annee_1(0);
	saisie_date(jour_1, mois_1, annee_1);
  
 	cout << "Seconde date" << endl;
	int jour_2(0), mois_2(0), annee_2(0);
	saisie_date(jour_2, mois_2, annee_2);
  
	// Calcul et affichage du resultat.
	cout << "Le nombre de jours separant ces deux dates est : ";
	cout << jours_entre_deux_dates(jour_1, mois_1, annee_1,
					               jour_2, mois_2, annee_2) << endl;
  
	return 0; // optionnel
}


static void saisie_date(int& jour, int& mois, int& annee)
{
	bool do_again(true);
	do 
    {
		cout << "Entrez une date [jj mm aaaa]: ";
		cin  >> jour >> mois >> annee;
      
		if (!date_valable(jour, mois, annee) || (annee < START_YEAR))
		{
			cout << "Cette date n'est pas valable!" << endl ;
		}
		else 
			do_again= false; 
    } while(do_again);

}

