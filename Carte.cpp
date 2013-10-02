

#include "Carte.h"

namespace tp
{

Carte::Carte(Sorte p_sorte, Valeur p_valeur)
  : m_sorte(p_sorte), m_valeur(p_valeur)
{
  
}

inline Sorte Carte::reqSorte() const
{
  return m_sorte;
}

inline Valeur Carte::reqValeur() const
{
  return m_valeur;
}

bool Carte::estSuivante(const Carte &p_carte) const
{
  return (m_sorte == p_carte.m_sorte && p_carte.m_valeur - m_valeur == 1);
}

bool Carte::peutEmpiler(const Carte &p_carte) const
{
  return ((m_valeur - p_carte.m_valeur == 1) && !((m_sorte == tp::PIQUE || m_sorte == tp::TREFLE) ^ (p_carte.m_sorte == tp::COEUR || p_carte.m_sorte == tp::CARREAU)));
}

std::ostream &operator<<(std::ostream &p_os, const Carte &p_carte)
{
  static std::string s_sorte[] = 
  {
    "PI",
    "CO",
    "CA",
    "TR",
  };
  static std::string s_valeur[] = 
  {
    "AS",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "V",
    "D",
    "R",
  };
  
  p_os << s_valeur[(int)p_carte.reqValeur()] << "'" << s_sorte[(int)p_carte.reqSorte()];

  return p_os;
}

};
