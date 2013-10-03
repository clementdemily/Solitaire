#include "Solitaire.h"

namespace tp 
{
    /**
       *  \fn Solitaire::Solitaire()
       */
    Solitaire::Solitaire()
    {
      _init();
    }

    /**
     *  \fn Solitaire::Solitaire(const Solitaire& p_cp) throw(std::bad_alloc)
       */
    Solitaire::Solitaire(const Solitaire& p_cp) throw(std::bad_alloc)
    {
      m_talon = p_cp.m_talon;
      for (int i = 0 ; i < 7; i++)
        m_colonnes[i] = p_cp.m_colonnes[i];
      for (int i = 0 ; i < 4; i++)
        m_piles[i] = p_cp.m_piles[i];
    }

    /**
       *  \brief Destructeur
       *
       *  \fn Solitaire::~Solitaire()
       */
    Solitaire::~Solitaire()
    {
    }
    //Surcharge d'opérateurs

    /**                       
     * \fn const Solitaire::Solitaire& operator = (const Solitaire& p_cp) throw (std::bad_alloc)
     */
    const Solitaire& Solitaire::operator = (const Solitaire& p_cp) throw (std::bad_alloc)
    {
      m_talon = p_cp.m_talon;
      for (int i = 0 ; i < 7; i++)
        m_colonnes[i] = p_cp.m_colonnes[i];
      for (int i = 0 ; i < 4; i++)
        m_piles[i] = p_cp.m_piles[i];

      return (*this);
    }

    /**                       
     * \brief Surcharge de l'opérateur << 
     *
     * \fn std::ostream& Solitaire::operator << (std::ostream& p_f, const Solitaire& p_l)
     */
    std::ostream& operator << (std::ostream& p_f, const Solitaire& p_l)
    {
      (void)p_l;
      p_f << p_l.reqEtatJeu();
      return (p_f);
    }

    /**                       
     *  \fn void  Solitaire::avancerTalon()
     */
    void  Solitaire::avancerTalon()
    {
      if (m_talon.taille() > 1)
      {
        m_talon.enfiler(m_talon.defiler());
      }
    }

    /**                       
     * \fn  void  Solitaire::deplacerColonneAColonne( int p_colonneSource, int p_colonneDestination, int p_nbCartes) throw (std::runtime_error)
     *
     * \param[in] p_colonneSource le numéro de la colonne source.
     * \param[in] p_colonneDestination le numéro de la colonne de destination.
     * \param[in] p_nbCartes le nombre de cartes à déplacer
     */
    void  Solitaire::deplacerColonneAColonne( int p_colonneSource, int p_colonneDestination, int p_nbCartes) throw (std::runtime_error)
    {
      if (p_colonneSource < 0 && p_colonneSource > 6)
        throw std::runtime_error("deplacerColonneAColonne() : choix colonne source incorrect");
      if (p_colonneDestination < 0 && p_colonneDestination > 6)
        throw std::runtime_error("deplacerColonneAColonne() : choix colonne destination incorrect");

      m_colonnes[p_colonneSource].deplacePaquet(m_colonnes[p_colonneDestination], p_nbCartes);
    }

    /**                       
     * \fn void Solitaire::deplacerTalonAColonne ( int p_colonneDestination ) throw (std::runtime_error)
     *
     * \param[in] p_colonneDestination le numéro de la colonne de destination.
     */
    void  Solitaire::deplacerTalonAColonne ( int p_colonneDestination ) throw (std::runtime_error)
    {
      if (p_colonneDestination < 0 && p_colonneDestination > 6)
        throw std::runtime_error("deplacerTalonAColonne() : choix colonne incorrect");
      if (m_talon.taille() == 0)
        throw std::runtime_error("deplacerTalonAColonne() : erreur talon");

      m_colonnes[p_colonneDestination].ajoute(m_talon.premier());
      m_talon.defiler();
    }

    /**                       
     * \fn void Solitaire::deplacerTalonAPile ( int p_pileDestination ) throw (std::runtime_error)
     *
     * \param[in] p_pileDestination le numéro de la pile de destination
     */
    void  Solitaire::deplacerTalonAPile ( int p_pileDestination ) throw (std::runtime_error)
    {
      if (p_pileDestination < 0 && p_pileDestination > 6)
        throw std::runtime_error("deplacerTalonAPile() : choix pile incorrect");
      if (m_talon.taille() == 0)
        throw std::runtime_error("deplacerTalonAColonne() : erreur talon");

      if (
          (m_piles[p_pileDestination].taille() == 0 && m_talon.premier().reqValeur() == AS) ||
          (m_piles[p_pileDestination].taille() > 0 && m_piles[p_pileDestination].premier().estSuivante(m_talon.premier()) )
          ){
        m_piles[p_pileDestination].empiler(m_talon.premier());
        m_talon.defiler();
      }
      else
        throw std::runtime_error("deplacerTalonAPile() : valeur ou sorte de carte incorrect");
    }

    /**                       
     * \fn void Solitaire::deplacerColonneAPile ( int p_colonneSource, int p_pileDestination) throw (std::runtime_error)
     *
     * \param[in] p_pileDestination le numéro de la pile de destination
     * \param[in] p_colonneSource le numéro de la colonne source.
     */
    void  Solitaire::deplacerColonneAPile ( int p_colonneSource, int p_pileDestination) throw (std::runtime_error)
    {
      if (p_pileDestination < 0 || p_pileDestination > 3)
        throw std::runtime_error("deplacerColonneAPile() : choix de pile incorrect");
      if (p_colonneSource < 0 || p_colonneSource > 6)
        throw std::runtime_error("deplacerColonneAPile() : choix de colonne incorrect");

      if ((m_piles[p_pileDestination].taille() == 0 && m_colonnes[p_colonneSource].reqLesCartes().element(1).reqValeur() == AS) ||
          (m_piles[p_pileDestination].taille() > 0 && m_piles[p_pileDestination].premier().estSuivante(m_colonnes[p_colonneSource].reqLesCartes().element(1))))
      {
        m_piles[p_pileDestination].empiler(m_colonnes[p_colonneSource].reqLesCartes().element(1));
        m_colonnes[p_colonneSource].supprimerDerniereCarte();
      }
      else
        throw std::runtime_error("deplacerColonneAPile() : deplacement incorrect");
    }
    
    /**
     * \fn bool Solitaire::verifieGagne ( ) const
     * \return VRAI ou FAUX selon que l'état du jeu indique que le joueur a gagné la partie, (si les sept colonnes sont vides et que le talon est vide).
     */
    bool  Solitaire::verifieGagne ( ) const
    {
      for (int i = 0; i < 4; ++i)
        if (m_piles[i].taille() < 14)
          return false;
      return true;
    }

    /**
     * \fn std::string  Solitaire::reqEtatJeu ( ) const
     * \return l'état du jeu sous la forme d'un objet string formaté exactement de la même façon que la démonstration.
     */
    std::string Solitaire::reqEtatJeu ( ) const
    {
      std::stringstream etatJeu;

      etatJeu << "Talon: ";
      if (m_talon.taille() > 0)
        etatJeu << m_talon.premier();
      else
        etatJeu << "X";

      etatJeu << "\t\t\t\t";

      etatJeu << "Piles";
      for (int i = 0; i < 4; ++i)
      {
        etatJeu << " ";
        if (m_piles[i].taille() > 0)
          etatJeu << m_piles[i].premier();
        else
          etatJeu << "X";
      }
      
      etatJeu << std::endl << std::endl;

      for (int i = 0; i < 7 ; ++i)
      etatJeu << "Col." << i << ": " << m_colonnes[i] << std::endl;

      return etatJeu.str();
    }

    /**
     * \fn void Solitaire::_init()
     */
    void  Solitaire::_init()
    {
      try {
        _initTalon();
        _initColonnes();
      } catch (std::exception & e)
      {
        std::cout << e.what() << std::endl;
        throw;
      }
    }

    /**
     * \fn void Solitaire::_copie(const Solitaire& p_cp)
     */
    void  Solitaire::_copie(const Solitaire& p_cp)
    {

    }

    /**
     * \fn void Solitaire::_detruire()
     */
    void  Solitaire::_detruire()
    {

    }

    /**
     * \fn void Solitaire::_initTalon()
     */
    void  Solitaire::_initTalon()
    {
      std::vector<Carte> v;
      std::srand ( unsigned ( std::time(0) ) );

      for (int i = 0 ; i < 4 ; i++)
      {
        for (int j = 0 ; j < 13 ; j++)
        {
          Carte nouvelleCarte((Sorte)i, (Valeur)j);
          v.push_back(nouvelleCarte);
        }
      }

      std::random_shuffle ( v.begin(), v.end() );

      for (std::vector<Carte>::iterator it = v.begin(); it < v.end() ; it++)
        m_talon.enfiler(*it);
    }

    /**
     * \fn void Solitaire::_initColonnes()
     */
    void  Solitaire::_initColonnes()
    {
      for (int i = 0 ; i < 7 ; i++)
      {
        Liste<Carte> colonne;

        for (int j = 0 ; j <= i; j++)
        {
          colonne.ajouter(m_talon.defiler(), 1);
        }
        m_colonnes[i].initColonneCartes(colonne);
      }
    }
}