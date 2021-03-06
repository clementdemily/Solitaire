/**
 * \file File.hpp
 * \brief Le code des opérateurs de la file.
 * \author Clément Demily
 * \version 1.0
 * \date octobre 2013
 *
 * Implémentation de la classe générique File dans une liste chainée
 */

namespace tp 
{

  /**
   * \fn File<T>:: File ()
   */
  template <typename T>
   File<T>::File()
    : m_debut(0), m_cpt(0)
   {
   }  

  /**
   * \fn File<T>:: ~File ()
   */
  template <typename T>
   File<T>:: ~File() 
   {  
     _detruire();
   }

   /**
   * \fn File<T>:: File (const File& source)throw(std::bad_alloc)
   *
   * \param[in] source La File source
   */
   template <typename T>
  File<T>::File(const File& p_source) throw(std::bad_alloc) 
  {
    if (p_source.m_debut== 0){
      m_debut = 0;  // la Pile originale est vide
      m_cpt = 0;
    }
    else{
      _copier(p_source.m_debut);
      m_cpt = p_source.m_cpt;
    }
  } 

   /**
   * \fn const File<T>& File<T>:: operator = (const File& source) throw (std::bad_alloc)
   *
   * \param[in] source La File qu'on veut affecter
   * \return Une File, copie profonde de source
   */
  template <typename T>
  const File<T>& File<T>::operator = (const File<T>& p_source)throw(std::bad_alloc)
  {
    if (m_debut!=0)
       _detruire();

    if (p_source.m_debut != 0)
      _copier(p_source.m_debut);

    return (*this);
  }

  /**
   * \fn int File<T>:: taille ()const
   *
   * \return la taille de la File
   */
   template <typename T>
  int File<T>:: taille() const
  {
    elem ptr;  //Pour parcourir la File
    int compte(0); //Pour compter les pointeurs non nuls

    ptr = m_debut;

    while (ptr != 0)
    {
      compte++;
      ptr = ptr->m_suivant;
    }

    return compte;
  }

  /**
   * \fn bool File<T>:: appartient(const T& x) const
   *
   * \param[in] x L'élément recherché 
   * \return VRAI si l'élément est présent, FAUX sinon
   */
  template <typename T>
  bool File<T>:: appartient(const T& p_x) const
  {
    elem  courant = m_debut;

    while (courant!=0)
    {
      if (courant->m_el == p_x) return true;
      courant = courant->m_suivant;
    }

    return false;
  }

  /**
   * \fn T File<T>:: element(int pos) const throw(std::range_error)
   *
   * \param[in] pos la position de l'élément   
   * \return L'élément à la position demandée
   */
  template <typename T>
  const T & File<T>:: element(int p_pos) const throw(std::range_error)
  {
    int cpt(1);

    //Vérification de l'hypothèse (précondition)
    // La position
    if(p_pos<1 || p_pos > taille())throw std::range_error("Element:Position de l'element est erronee");

    elem courant = m_debut; //on se positionne au début de la File chaînée
    while (cpt< p_pos)  //boucle pour positionner courant sur le bon noeud 
    {
      courant=courant->m_suivant; //on passe à la structure m_suivante..
      cpt++;            //...et on compte
    }
    return courant->m_el;
  }

  /**
   * \fn int File<T>:: position(const T& x) const throw(std::logic_error)
   *
   * \param[in] x l'élément dont on cherche sa position  
   * \return la position de l'élément
   */
  template <typename T>
  int File<T>:: position(const T& p_x) const throw(std::logic_error)
  {
    elem trouve = m_debut;
    int pos = 1;

    //on prend pour acquis que l'opérateur != s'applique sur x, sinon il faut surcharger cet opérateur  
    while (trouve != 0 && trouve->m_el != p_x )
    { 
      trouve = trouve->m_suivant;
      pos++;
    } 
    if (trouve== 0) throw std::logic_error("Position:L'element dont on cherche sa position n'est pas present dans la File");

    return pos;
  }

  /**
   * \fn bool File<T>:: estVide ()const
   *
   * \return VRAI si la File est vide
   * \return FAUX sinon 
   */
  template <typename T>
  bool File<T>:: estVide() const
  {
    return m_debut==0;
  }

  /**
   * \fn void File<T>::enfiler(const T& elementAEnfiler)
   * \param[in] elementAEnfiler Élément à enfiler
   */
  template<typename T>
  void File<T>::enfiler(const T& p_elementAEnfiler)
  {
    // enfiler un élément dans la file
    elem tmp;
    elem nouveau = new Noeud(p_elementAEnfiler);

    nouveau->m_suivant = 0;
    if (m_debut != 0)
    {
      tmp = m_debut;
      while (tmp->m_suivant != 0)
        tmp = tmp->m_suivant;
      tmp->m_suivant = nouveau;
    } else {
      m_debut = nouveau;
    }
    m_cpt++;
  }

  /**
   * \fn T File<T>::defiler()throw(std::logic_error)
   *
   * \return T - Élément défilé
   */
  template<typename T>
  T File<T>::defiler() throw (std::logic_error)
  {
    T elementaDefiler;

    // defiler un élément dans la file
    if (m_cpt != 0)
    {
      elementaDefiler = m_debut->m_el;
      m_debut = m_debut->m_suivant;
      m_cpt--;
      return elementaDefiler;
    }
    else
      throw std::logic_error("Defiler: La file est vide!");
  }

  /**
   * \fn const T& File<T>:: premier()const throw (logic_error)
   * 
   * \return Une copie de T, l'élément en tête de file
   */
  template <typename T>
  const T& File<T>::premier() const throw (std::logic_error)
  {
    if(m_cpt != 0)
      return m_debut->m_el;
    throw std::logic_error("Dernier: la file est vide!");
  }

  /**
   * \fn const T& File<T>:: dernier()const throw (logic_error)
   * 
   * \return Une copie de T, l'élément en queue de file
   */
  template <typename T>
  const T& File<T>::dernier()const throw (std::logic_error)
  {
    elem tmp;

    if(m_cpt == 0)
      throw std::logic_error("Premier: la file est vide!");
    tmp = m_debut;

    while (tmp->m_suivant != 0)
      tmp = tmp->m_suivant;
    return tmp->m_el;
  }

   /**
   * \fn std::ostream& operator << (std::ostream& f, const File<T> & l)
   *
   * \param[in, out] f Le flux de sortie
   * \param[in] l Une File 
   * \return Une référence sur le flux de sortie
   */
  template <typename T>
  std::ostream& operator<<(std::ostream& p_f, const File<T> & p_l)
  {
    for (int i = 1 ; i < (p_l.taille() + 1) ; i++)
      p_f << p_l.element(i) << " ";  
    return p_f;
  }

  /**
   * \fn File<T>:: _copier(Noeud * sn) throw (std::bad_alloc)
   *
   * \param[in] sn Le pointeur sur le début de la File source
   */
  template <typename T>
  void File<T>:: _copier(Noeud * p_sn) throw (std::bad_alloc)
  {
    try{
        //copie le permier noeud
        m_debut = new Noeud(p_sn->m_el);
        
        // copie le reste de la File
        elem nouveau = m_debut;
        for (elem temp = p_sn->m_suivant; temp != 0; temp = temp->m_suivant )
        {
          nouveau->m_suivant = new Noeud(temp->m_el);
          nouveau = nouveau->m_suivant;
          nouveau->m_suivant = 0;
        }// fin for
        nouveau->m_suivant = 0;
      }catch(std::exception&){
             //Si on arrive ici c'est qu'il y a une erreur d'allocation
             //On doit donc libérer la mémoire déjà allouée
             _detruire();
   
             //On relance alors l'exception pour indiquer qu'une erreur est survenue
             throw;
      }
  }

  /**
   * \fn void File<T>:: _detruire()
   */
  template <typename T>
  void File<T>:: _detruire()
  {
    File<T>::elem courant = m_debut;         
    while(courant!=0) 
    {
      m_debut=m_debut->m_suivant;  
      delete courant;
      courant=m_debut;     
    }
  }

}