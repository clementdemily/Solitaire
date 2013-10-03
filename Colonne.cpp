

#include "Colonne.h"

namespace tp
{

/**
 * \fn ColonneCartes::ColonneCartes()
 */
ColonneCartes::ColonneCartes()
  : m_nbCartesVisibles(0)
{

}

/**
 * \fn int ColonneCartes::getNbCartesVisibles() const
 *
 * \return le nombre de cartes visibles
 */
int ColonneCartes::getNbCartesVisibles() const
{
  return m_nbCartesVisibles;
}

/**
 * \fn const Liste<Carte> &ColonneCartes::reqLesCartes() const
 *
 * \return la liste des cartes
 */
const Liste<Carte> &ColonneCartes::reqLesCartes() const
{
  return m_lesCartes;
}

/**
 * \fn void ColonneCartes::initColonneCartes(Liste<Carte> &p_listeCartes)
 *
 * \param[in] p_listeCartes la liste de cartes avec laquelle initialiser la colonne
 */
void ColonneCartes::initColonneCartes(Liste<Carte> &p_listeCartes)
{
  m_lesCartes = p_listeCartes;
  if (m_lesCartes.taille() > 0)
    m_nbCartesVisibles = 1;
}

/**
 * \fn void ColonneCartes::ajoute(const Carte &p_carte)
 *
 * \param[in] p_carte la carte a ajouter a la colonne
 *
 * \pre la carte peut est ajoutee a la colonne d'apres les regles du jeu
 * \exception runtime_error si la carte ne peut pas etre mise sur la colonne
 */
void ColonneCartes::ajoute(const Carte &p_carte)
{
  if ((m_lesCartes.taille() == 0 && p_carte.reqValeur() == ROI)
      || (m_lesCartes.taille() > 0 && m_lesCartes.element(1).peutEmpiler(p_carte)))
  {
    m_lesCartes.ajouter(p_carte, 1);
    ++m_nbCartesVisibles;
  }
  else
    throw std::runtime_error("ajoute() : Impossible d'ajouter dans la colonne");
}

/**
 * \fn void ColonneCartes::deplacePaquet(ColonneCartes &p_destination, int p_nombreCartes)
 *
 * \param[in] p_destination la colonne vers laquelle deplacer les cartes
 * \param[in] p_nombreCartes le nombre de cartes a deplacer
 *
 * \pre les parametres du deplacement doivent etre conformes aux regles du jeu
 * \exception runtime_error si le deplacement n'est pas conforme aux regles
 */
void ColonneCartes::deplacePaquet(ColonneCartes &p_destination, int p_nombreCartes)
{
  if (p_nombreCartes > 0 && p_nombreCartes <= m_nbCartesVisibles
      && ((p_destination.m_lesCartes.taille() == 0 && m_lesCartes.element(p_nombreCartes).reqValeur() == ROI)
        || (p_destination.m_lesCartes.taille() > 0 && p_destination.m_lesCartes.element(1).peutEmpiler(m_lesCartes.element(p_nombreCartes)))))
  {
    for (int i = 0; p_nombreCartes != i; --p_nombreCartes)
    {
      p_destination.ajoute(m_lesCartes.element(p_nombreCartes));
      m_lesCartes.enleverPos(p_nombreCartes);
      --m_nbCartesVisibles;
    }
    if (m_lesCartes.taille() > 0 && m_nbCartesVisibles == 0)
      m_nbCartesVisibles = 1;
  }
  else
    throw std::runtime_error("deplacePaquet() : Deplacement impossible");
}

/**
 * \fn void ColonneCartes::supprimerDerniereCarte()
 */
void ColonneCartes::supprimerDerniereCarte()
{
  if (m_lesCartes.taille() > 0)
  {
    m_lesCartes.enleverPos(1);
    --m_nbCartesVisibles;
    if (m_lesCartes.taille() > 0 && m_nbCartesVisibles == 0)
      ++m_nbCartesVisibles;
  }
}

/**
 * \fn std::ostream &operator<<(std::ostream &p_os, const ColonneCartes &p_colonneCartes)
 *
 * \param[in] p_os le flux de sortie
 * \param[in] p_colonneCartes la colonne a envoyer au flux
 *
 * \return une reference sur le flux de sortie
 */
std::ostream &operator<<(std::ostream &p_os, const ColonneCartes &p_colonneCartes)
{
  if (p_colonneCartes.reqLesCartes().taille() == 0)
    p_os << "-";
  for (int i = p_colonneCartes.reqLesCartes().taille(); i > 0; --i)
  {
    if (i < p_colonneCartes.reqLesCartes().taille())
      p_os << " ";
    if (i > p_colonneCartes.getNbCartesVisibles())
      p_os << "?";
    else
      p_os << p_colonneCartes.reqLesCartes().element(i);
  }

  return p_os;
}

};
