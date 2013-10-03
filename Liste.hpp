/**
 * \file Liste.inl
 * \brief Le code des operateurs de la liste.
 * \author Nathan IRJUD
 * \version 1
 * \date septembre 2013
 *
 * Implementation de la classe generique Liste dans une liste doublement chainee
 */

namespace tp
{

/**
 * \fn Liste<T>::Liste()
 */
template<typename T>
Liste<T>::Liste()
  : dernier(0)
{

}

/**
 * \fn Liste<T>::~Liste()
 */
template<typename T>
Liste<T>::~Liste() 
{
  _detruire();
}

/**
 * \fn Liste<T>::Liste(const Liste &p_liste)
 *
 * \param[in] p_liste La liste source
 */
template<typename T>
Liste<T>::Liste(const Liste& p_liste)
  : dernier(0)
{
  if (p_liste.dernier != 0)
  {
    _copier(p_liste.dernier);
  }
} 

 /**
 * \fn const Liste<T> &Liste<T>::operator=(const Liste &p_liste)
 *
 * \param[in] p_liste La liste que l'on veut affecter
 * \return L'operande gauche de l'assignation
 */
template<typename T>
Liste<T> &Liste<T>::operator=(const Liste<T> &p_liste)
{
  if (&p_liste == this)
    return *this;

  if (dernier != 0)
    _detruire();

  if (p_liste.dernier != 0)
    _copier(p_liste.dernier);

  return *this;
}

/**
 * \fn int Liste<T>::taille() const
 *
 * \return La taille de la liste
 */
template<typename T>
inline int Liste<T>::taille() const
{
  if (dernier == 0)
    return 0;

  elem courant = dernier->suivant;
  int taille = 1;

  while (courant != dernier)
  {
    ++taille;
    courant = courant->suivant;
  }

  return taille;
}

/**
 * \fn bool Liste<T>::appartient(const T &p_element) const
 *
 * \param[in] p_element L'element recherche 
 * \return VRAI si l'element appartient a la liste, FAUX sinon
 */
template<typename T>
bool Liste<T>::appartient(const T &p_element) const
{
  if (dernier == 0)
    return false;

  elem courant = dernier;
  
  do
  {
    if (courant->el == p_element)
      return true;
    courant = courant->suivant;
  }
  while (courant != dernier);

  return false;
}

/**
 * \fn T Liste<T>::element(int p_position) const
 *
 * \param[in] p_position La position de l'element   
 * \return L'element à la position demandee
 *
 * \pre p_postion compris entre 1 et la taille inclus
 * \exception range_error si p_position n'est pas dans la liste
 */
template<typename T>
const T &Liste<T>::element(int p_position) const
{
  if (p_position < 1 || p_position > taille())
    throw std::range_error("element() : position erronee");

  elem courant = dernier->suivant;
  
  for (int i = 1; i < p_position; ++i)
    courant = courant->suivant;

  return courant->el;
}

/**
 * \fn int Liste<T>::position(const T &x) const
 *
 * \param[in] p_element L'element dont on cherche la position  
 * \return La position de l'element
 *
 * \pre la liste ne doit pas etre vide
 * \exception logic_error si la liste est vide
 * \pre p_element doit etre present dans la liste
 * \exception logic_error si p_element n'est pas trouve dans la liste
 */
template<typename T>
int Liste<T>::position(const T &p_element) const
{
  if (dernier == 0)
    throw std::logic_error("position() : la liste est vide");

  elem courant = dernier;
  int position = 0;

  do
  {
    ++position;
    courant = courant->suivant;
  }
  while (courant != dernier && courant->el != p_element);

  if (courant == dernier && courant->el != p_element)
    throw std::logic_error("position() : element non present dans la liste");

  return position;
}

/**
 * \fn bool Liste<T>::estVide() const
 *
 * \return VRAI si la liste est vide, FAUX sinon 
 */
template<typename T>
inline bool Liste<T>::estVide() const
{
  return (dernier == 0);
}

/**
 * \fn void Liste<T>::ajouter(const T &p_element, int p_position)
 *
 * \param[in] p_element Element à ajouter 
 * \param[in] p_position Position où inserer l'element
 *
 * \pre p_position compris entre 1 et [taille de la liste] + 1 inclus
 * \exception range_error si la position demandee n'est pas possible
 */
template<typename T>
void Liste<T>::ajouter(const T& p_element, int p_position)
{
  if (p_position < 1 || p_position > taille() + 1)
    throw std::range_error("ajouter() : position erronee");

  elem nouveau = new Noeud(p_element);
  
  if (dernier == 0)
    dernier = nouveau;
  
  elem courant = dernier;
  
  for (int i = 0; i < p_position - 1; ++i)
    courant = courant->suivant;
  
  nouveau->suivant = courant->suivant;
  courant->suivant = nouveau;

  if (dernier == courant && p_position != 1)
    dernier = nouveau;
}

/**
 * \fn void Liste<T>::enleverEl(const T& x)
 *
 * \param[in] p_element La valeur de l'element a enlever, seul le premier trouve est enleve
 * 
 * \pre la liste ne doit pas etre vide
 * \exception logic_error si la liste est vide
 * \pre p_element doit etre present dans la liste
 * \exception logic_error si p_element n'est pas trouve dans la liste
 */
template<typename T>
void Liste<T>::enleverEl(const T& p_element)
{
  if (dernier == 0)
    throw std::logic_error("enleverEl() : la liste est vide");

  elem courant = dernier;

  while (courant->suivant != dernier && courant->suivant->el != p_element)
    courant = courant->suivant;

  if (courant->suivant == dernier && dernier->el != p_element)
    throw std::logic_error("enleverEl() : element a enlever non present dans la liste");

  elem aSupprimer = courant->suivant;
  
  courant->suivant = aSupprimer->suivant;

  if (dernier == aSupprimer)
    dernier = courant;
  if (dernier == aSupprimer)
    dernier = 0;

  delete aSupprimer;
}

/**
 * \fn void Liste<T>::enleverPos(int p_position)
 *
 * \param[in] p_position Position de l'element a enlever 
 *
 * \pre p_position compris entre 1 et la taille de la liste inclus
 * \exception range_error si p_position n'est pas dans la liste
 */
template<typename T>
void Liste<T>::enleverPos(int p_position)
{
  if (p_position < 1 || p_position > taille())
    throw std::range_error("enleverPos() : position erronee");

  elem courant = dernier;

  for (int i = 0; i < p_position - 1; ++i)
    courant = courant->suivant;

  elem aSupprimer = courant->suivant;

  courant->suivant = aSupprimer->suivant;

  if (dernier == aSupprimer)
    dernier = courant;
  if (dernier == aSupprimer)
    dernier = 0;

  delete aSupprimer;
}

/**                                                                      
 * \fn std::ostream &operator<<(std::ostream & p_os, const Liste<T> &p_liste)    
 *
 * \param[in] p_os Le flux de sortie
 * \param[in] p_liste La liste a envoyer au flux de sortie 
 * \return Une reference sur le flux de sortie
 */
template<class T>
std::ostream &operator<<(std::ostream& p_os, const Liste<T> &p_liste)
{
  for (int i = 1; i <= p_liste.taille(); ++i)
    p_os << p_liste.element(i) << std::endl;

  return p_os;
}

/**
 * \fn Liste<T>::_copier(Noeud *p_noeud)
 *
 * \param[in] p_noeud Le pointeur sur le debut de la liste a copier
 */
template<typename T>
void Liste<T>::_copier(Noeud *p_noeud)
{
  if (p_noeud == 0)
    return;

  try
  {
    dernier = new Noeud(p_noeud->el);
    
    elem courant = dernier;
    elem courantCopie = p_noeud;

    courantCopie = courantCopie->suivant;
    while (courantCopie != p_noeud)
    {
      courant->suivant = new Noeud(courantCopie->el);
      courant = courant->suivant;
      courantCopie = courantCopie->suivant;
    }
    courant->suivant = dernier;
  }
  catch (std::exception &e)
  {
    _detruire();

    throw e;
  }
}

/**
 * \fn void Liste<T>::_detruire()
 */
template<typename T>
void Liste<T>::_detruire()
{
  if (dernier == 0)
    return;

  elem courant = dernier->suivant;
  elem aSupprimer;

  while (courant != dernier)
  {
    aSupprimer = courant;
    courant = courant->suivant;
    delete aSupprimer;
  }

  delete dernier;
  dernier = 0;
}

}
