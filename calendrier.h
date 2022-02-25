/*!
  \file   calendrier.h
  \author RB
  \date   Fevrier 2019
  \brief  Interface du module "calendrier"
*/

/*!
  \brief Cette fonction retourne 1 si l'annee passee en argument est
  bissextile, et 0 sinon.
*/
int annee_est_bissextile(int annee);

/*!
  \brief Cette fonction retourne le nombre de jours dans le mois d'une
  annee, en tenant compte du fait que celle-ci peut etre bissextile.
*/
int jours_par_mois(int mois, int annee);

/*!
  \brief Cette fonction retourne le nombre de jours dans une annee.
*/
int jours_par_an(int annee);

/*!
  \brief Cette fonction retourne 1 si la date est valable, et 0 sinon.
*/
int date_valable(int jour, int mois, int annee);
