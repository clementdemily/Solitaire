

#ifndef	__CARTE_H
# define __CARTE_H

#include <iostream>
#include <string>

#ifndef __COLOR__
  const std::string BLACK = "\033[22;30m";
  const std::string RED = "\033[22;31m";
  const std::string GREEN = "\033[22;32m";
  const std::string YELLOW = "\033[22;33m";

  const std::string RESETCOLOR = "\033[0m";
#endif /* !__COLOR__ */

namespace tp
{

/**
 * \enum Sorte
 * \brief la sorte de la carte
 */
enum Sorte
{
  PIQUE = 0, /** pique */
  COEUR, /** coeur */
  CARREAU, /** carreau */
  TREFLE, /** trefle */
};

/**
 * \enum Valeur
 * \brief la valeur de la carte
 */
enum Valeur
{
  AS = 0, /** as */
  DEUX, /** 2 */
  TROIS, /** 3 */
  QUATRE, /** 4 */
  CINQ, /** 5 */
  SIX, /** 6 */
  SEPT, /** 7 */
  HUIT, /** 8 */
  NEUF, /** 9 */
  DIX, /** 10 */
  VALET, /** valet */
  DAME, /** dame */
  ROI, /** roi */
};

/**
 * \class Carte
 *
 * \brief classe representant une carte a jouer
 *
 *  La classe gere une carte a jouer et les regles du solitaires
 *  pour les relations entre elles.
 */
class Carte
{
 public:
  Carte(Sorte = PIQUE, Valeur = AS);

 public:
  Sorte reqSorte() const;
  Valeur reqValeur() const;
  void asgSorte(Sorte);
  void asgValeur(Valeur);

 public:
  bool estSuivante(const Carte &) const;
  bool peutEmpiler(const Carte &) const;

 public:
  friend std::ostream &operator<<(std::ostream &, const Carte &);

 private:
  Sorte m_sorte;
  Valeur m_valeur;
};

};


#endif /* !__CARTE_H */
