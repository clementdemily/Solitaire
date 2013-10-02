#include "Solitaire.h"

namespace tp 
{
    /**
       *  \fn Solitaire::Solitaire()
       *
       *  \post Une instance de la classe Solitaire est initialisée
       */
    Solitaire::Solitaire()
    {
      _init();
    }

    /**
       *  \brief Constructeur de copie
     *
     *  \fn Solitaire::Solitaire(const Solitaire& p_cp) throw(std::bad_alloc)
     *
     *  \pre Il faut qu'il y ait suffisamment de mémoire
     *  \post une copie profonde du Solitaire source
     *  \exception bad_alloc s'il n'y a pas assez de mémoire
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
       *
       *  \post l'instance de Solitaire est détruite
       */
    Solitaire::~Solitaire()
    {
    }
    //Surcharge d'opérateurs

    /**                       
     * \brief Surcharger l'opérateur = 
     *
     * \fn const Solitaire::Solitaire& operator = (const Solitaire& p_cp) throw (std::bad_alloc)
     *
     * \pre Il y a assez de mémoire pour l'opération 
     * \post Une copie d'une Solitaire est retournée
     * \exception bad_alloc si la précondition n'est pas respectée 
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
     *
     * \post Un flux de sortie correspondant à la Solitaire est retournée  
     */
    std::ostream& operator << (std::ostream& p_f, const Solitaire& p_l)
    {
      (void)p_l;
      p_f << "salut";
      return (p_f);
    }

    /**                       
     * \brief Fait avancer le talon d'une carte, c'est-à-dire prend la première et la place à la fin du talon 
     *
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
     * \brief Déplace p_nbCartes cartes à partir de la colonne p_colonneSource vers la colonne p_colonneDestination. 
     * 
     * \fn  void  Solitaire::deplacerColonneAColonne( int p_colonneSource, int p_colonneDestination, int p_nbCartes) throw (std::runtime_error)
     *
     * \param[in] p_colonneSource le numéro de la colonne source.
     * \param[in] p_colonneDestination le numéro de la colonne de destination.
     * \param[in] p_nbCartes le nombre de cartes à déplacer
     * \pre p_colonneSource et p_colonneDestination doivent être entre 0 et 6 inclusivement.
     * \exception runtime_error si les paramètres ne sont pas cohérents avec les règles du jeu.
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
     * \brief Déplace la carte du dessus du talon vers la colonne spécifiée par "p_colonneDestination". 
     *
     * \fn void Solitaire::deplacerTalonAColonne ( int p_colonneDestination ) throw (std::runtime_error)
     *
     * \param[in] p_colonneDestination le numéro de la colonne de destination.
     * \pre p_colonneDestination compris entre 0 et 6 inclus
     * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
     */
    void  Solitaire::deplacerTalonAColonne ( int p_colonneDestination ) throw (std::runtime_error)
    {
      if (p_colonneDestination < 0 && p_colonneDestination > 6)
        throw std::runtime_error("deplacerTalonAColonne() : choix colonne incorrect");
      if (m_talon.taille() == 0)
        throw std::runtime_error("deplacerTalonAColonne() : erreur talon");

      m_colonne[p_colonneDestination].ajoute(m_talon.defiler());
    }

    /**                       
     * \brief Déplace la carte du dessus du talon vers la pile spécifiée par "p_pileDestination".
     *
     * \fn void Solitaire::deplacerTalonAPile ( int p_pileDestination ) throw (std::runtime_error)
     *
     * \param[in] p_pileDestination le numéro de la pile de destination
     * \pre p_pileDestination compris entre 0 et 3 inclus
     * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
     */
    void  Solitaire::deplacerTalonAPile ( int p_pileDestination ) throw (std::runtime_error)
    {
      if (p_colonneDestination < 0 && p_colonneDestination > 6)
        throw std::runtime_error("deplacerTalonAPile() : choix pile incorrect");
      if (m_talon.taille() == 0)
        throw std::runtime_error("deplacerTalonAColonne() : erreur talon");

      if (m_piles[p_colonneDestination].premier().estSuivante(m_talon.premier()))
        m_piles[p_colonneDestination].empiler(m_talon.defiler());
      else
        throw std::runtime_error("deplacerTalonAPile() : valeur ou sorte de carte incorrect");
    }

    /**                       
     * \brief Déplace la dernière carte de la colonne spécifiée par "p_colonneSource" vers la pile spécifiée par "p_pileDestination".
     *
     * \fn void Solitaire::deplacerColonneAPile ( int p_colonneSource, int p_pileDestination) throw (std::runtime_error)
     *
     * \param[in] p_pileDestination le numéro de la pile de destination
     * \pre p_pileDestination compris entre 0 et 3 inclus
     * \param[in] p_colonneSource le numéro de la colonne source.
     * \pre p_colonneSource doit être entre 0 et 6 inclusivement.
     * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
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
        m_colonnes[p_colonneSource].supprimerDernierCarte();
      }
      else
        throw std::runtime_error("deplacerColonneAPile() : deplacement incorrect");
    }
    
    /**
     * \brief Vérifie si le joueur a gagné:
       *
       * \fn bool Solitaire::verifieGagne ( ) const
       *
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
     * \brief retourne l'état du jeu
     *
     * \fn std::string  Solitaire::reqEtatJeu ( ) const
     *
     * \return l'état du jeu sous la forme d'un objet string formaté exactement de la même façon que la démonstration.
     */
    std::string Solitaire::reqEtatJeu ( ) const
    {
      std::stringstream etatJeu;

      etatJeu << "Talon : ";
      if (m_talon.taille() > 0)
        etatJeu << m_talon.premier();
      else
        etatJeu << "X";

      etatJeu << "\t\t\t\t";

      etatJeu << "Piles";
      for (int i = 0; i < 4; ++i)
      {
        etatJeu << " "
        if (m_piles[i].taille() > 0)
          etatJeu << m_piles[i].premier();
        else
          etatJeu << "X";
      }
      
      etatJeu << std::endl;

      for (int i = 0; i < 7 ; ++i)
      etatJeu << "Col." << i << ": " << m_colonnes[i] << std::endl;

      return etatJeu.str();
    }

    /**
     * \brief mélange le paquet de carte, distribue les 7 colonnes de cartes, init les piles
     *
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
     * \brief Réalise une copie profonde d'un solitaire
     *
     * \fn void Solitaire::_copie(const Solitaire& p_cp)
     *
     */
    void  Solitaire::_copie(const Solitaire& p_cp)
    {

    }

    /**
     * \brief Détruit l'objet
     *
     * \fn void Solitaire::_detruire()
     *
     */
    void  Solitaire::_detruire()
    {

    }

    /**
     * \brief initialise les cartes du talon
     *
     * \fn void Solitaire::_initTalon()
     *
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
     * \brief initialise les cartes du talon
     *
     * \fn void Solitaire::_initColonnes()
     *
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