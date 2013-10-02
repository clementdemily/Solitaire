

#ifndef	__CARTE_H
# define __CARTE_H

#include <iostream>

#ifndef __COLOR__
  #define BLACK  "\033[22;30m"
  #define RED  "\033[22;31m"
  #define GREEN  "\033[22;32m"
  #define YELLOW  "\033[22;33m"

  #define RESETCOLOR "\033[0m"
#endif

namespace tp
{

enum Sorte
{
  PIQUE = 0,
  COEUR,
  CARREAU,
  TREFLE,
};

enum Valeur
{
  AS = 0,
  DEUX,
  TROIS,
  QUATRE,
  CINQ,
  SIX,
  SEPT,
  HUIT,
  NEUF,
  DIX,
  VALET,
  DAME,
  ROI,
};

class Carte
{
 public:
  Carte(Sorte = PIQUE, Valeur = AS);

 public:
  Sorte reqSorte() const;
  Valeur reqValeur() const;

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
