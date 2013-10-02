

#include "Colonne.h"

namespace tp
{

ColonneCartes::ColonneCartes()
  : m_nbCartesVisibles(0)
{

}

int ColonneCartes::getNbCartesVisibles() const
{
  return m_nbCartesVisibles;
}

const Liste<Carte> &ColonneCartes::reqLesCartes() const
{
  return m_lesCartes;
}

void ColonneCartes::initColonneCartes(Liste<Carte> &p_listeCartes)
{
  m_lesCartes = p_listeCartes;
  if (m_lesCartes.taille() > 0)
    m_nbCartesVisibles = 1;
}

void ColonneCartes::ajoute(const Carte &p_carte)
{
  if (m_lesCartes.taille() == 0 || m_lesCartes.element(1).peutEmpiler(p_carte))
  {
    m_lesCartes.ajouter(p_carte, 1);
    ++m_nbCartesVisibles;
  }
  else
    throw std::runtime_error("ajoute() : Impossible d'ajouter dans la colonne");
}

void ColonneCartes::deplacePaquet(ColonneCartes &p_destination, int p_nombreCartes)
{
  if (p_nombreCartes > 0 && p_nombreCartes <= m_nbCartesVisibles
      && (p_destination.m_lesCartes.taille() == 0 || p_destination.m_lesCartes.element(1).peutEmpiler(m_lesCartes.element(p_nombreCartes))))
    for (int i = 0; p_nombreCartes != i; --p_nombreCartes)
    {
      p_destination.ajoute(m_lesCartes.element(p_nombreCartes));
      m_lesCartes.enleverPos(p_nombreCartes);
      --m_nbCartesVisibles;
    }
  else
    throw std::runtime_error("deplacePaquet() : Deplacement impossible");
}

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

std::ostream &operator<<(std::ostream &p_os, const ColonneCartes &p_colonneCartes)
{
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
