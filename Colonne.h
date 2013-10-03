/**
 * \file Colonne.h
 * \brief Classe définissant une colonne de carte
 * \author Nathan Irjud
 * \version 1.0
 * \date octobre 2013
 */


#ifndef __COLONNE_CARTES_H
# define __COLONNE_CARTES_H

#include <iostream>

#include "Carte.h"
#include "Liste.h"

namespace tp
{

/**
 * \class ColonneCartes
 *
 * \brief classe representant une colonne de cartes du jeu solitaire
 *
 *  La classe gere une colonne de cartes selon les regles du jeu solitaire ainsi
 *  que les interactions entre plusieurs colonnes.
 */	
class ColonneCartes
{
 public:
  ColonneCartes();

 public:
  int getNbCartesVisibles() const;
  const Liste<Carte> &reqLesCartes() const;

 public:
  void initColonneCartes(Liste<Carte> &p_listeCartes);
  void ajoute(const Carte &p_carte);
  void deplacePaquet(ColonneCartes &p_destination, int p_nombreCartes);
  void supprimerDerniereCarte();
  
 public:
  friend std::ostream &operator<<(std::ostream &p_os, const ColonneCartes &p_colonneCartes);

 private:
  Liste<Carte> m_lesCartes;
  int m_nbCartesVisibles;
};

};

#endif /* !__COLONNE_CARTES_H */
