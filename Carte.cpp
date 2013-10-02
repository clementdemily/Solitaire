

#include "Carte.h"

namespace tp
{

/**
 * \fn Carte::Carte(Sorte p_sorte, Valeur p_valeur)
 *
 * \param[in] p_sorte la sorte de la nouvelle carte
 * \param[in] p_valeur la valeur de la nouvelle carte
 */
Carte::Carte(Sorte p_sorte, Valeur p_valeur)
  : m_sorte(p_sorte), m_valeur(p_valeur)
{
  
}

/**
 * \fn Sorte Carte::reqSorte() const
 *
 * \return la sorte de la carte
 */
inline Sorte Carte::reqSorte() const
{
  return m_sorte;
}

/**
 * \fn Valeur Carte::reqValeur() const
 *
 * \return la valeur de la carte
 */
inline Valeur Carte::reqValeur() const
{
  return m_valeur;
}

/**
 * \fn bool Carte::estSuivante(const Carte &p_carte) const
 *
 * \param[in] p_carte la carte a superposer a la carte courante
 *
 * \return VRAI si la carte donnee peut etre superposee a la carte courante dans une pile
 */

bool Carte::estSuivante(const Carte &p_carte) const
{
  return (m_sorte == p_carte.m_sorte && p_carte.m_valeur - m_valeur == 1);
}

/**
 * \fn bool Carte::peutEmpiler(const Carte &p_carte) const
 *
 * \param[in] p_carte la carte a superposer a la carte courante
 *
 * \return vrai si la carte donee peut etre superposee a la carte courante dans une colonne
 */
bool Carte::peutEmpiler(const Carte &p_carte) const
{
  return ((m_valeur - p_carte.m_valeur == 1) && !((m_sorte == PIQUE || m_sorte == TREFLE) ^ (p_carte.m_sorte == COEUR || p_carte.m_sorte == CARREAU)));
}

/**
 * \fn std::ostream &operator<<(std::ostream &p_os, const Carte &p_carte)
 *
 * \param[in] p_os le flux de sortie
 * \param[in] p_carte la carte a envoyer au flux de sortie
 *
 * \retour une reference sur le flux de sortie
 */
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
