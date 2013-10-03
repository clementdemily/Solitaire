/**
 * \file File.h
 * \brief Classe définissant le type abstrait file
 * \author Clément Demily
 * \version 1.0
 * \date octobre 2013
 *
 * Représentation dans une liste chainée
 */

#ifndef _FILE__H
#define _FILE__H

#include <iostream>
# include <stdexcept> // Pour les exceptions standards
#include <string>

#pragma warning( disable : 4290 )// Une fonction est déclarée avec une spécification d'exception (voir la méthode 
// ajouter(), ce que Visual Studio accepte mais n'implémente pas. Le code avec spécification d'exception ignoré lors
//de la compilation peut nécessiter une nouvelle compilation et édition de liens pour pouvoir être 
//réutilisé dans des versions ultérieures prenant en charge les spécifications d'exception. 
//Vous pouvez éviter cet avertissement par le pragma warning (disable : 4290) 

namespace tp
{

  /** 
  * \class File
  *
  * \brief classe générique représentant une File ordonnée
  *
  *  La classe gère une File générique ordonnée. L'implémentation
  *  se fait dans une liste simplement chaînée.
  */
  template <typename T>
  class File {
  public:
    //Constructeurs

    /**
       *  \brief Constructeur par défaut
       *
       *  \post Une instance de la classe File est initialisée
       */
    File(); 

    /**
       *  \brief Constructeur de copie
     *
     *  \pre Il faut qu'il y ait suffisamment de mémoire
     *  \post une copie profonde la File source
     *  \exception bad_alloc s'il n'y a pas assez de mémoire
       */
    File(const File&) throw(std::bad_alloc);  

    /**
       *  \brief Destructeur
       *
       *  \post l'instance de File est détruite
       */
    ~File();         

    //Surcharge d'opérateurs

    /**                       
     * \brief Surcharger l'opérateur = 
     *
     * \pre Il y a assez de mémoire pour l'opération 
     * \post Une copie d'une File est retournée
     * \exception bad_alloc si la précondition n'est pas respectée 
     */
    const File<T>& operator = (const File<T>&) throw (std::bad_alloc);

    /**                       
     * \brief Surcharge de l'opérateur << 
     *
     * \post Un flux de sortie correspondant à la File est retournée  
     */
    template <class U> friend std::ostream& operator << (std::ostream& p_f, const File<U>& p_l);

    //Modificateurs

    //  modificateurs

    /**                       
     *  \brief Enfiler un nouvel élément dans la file
     * 
     * \post La file comprend un élément de plus
     */
    void enfiler(const T&);

    /**                       
     * \brief Défiler un élément 
     * 
     * \pre La file ne doit pas être vide
     * \post La file comprend un élément de moins
     * \exception logic_error si la file est vide
     */
    T defiler() throw(std::logic_error);

    //Sélecteurs

    /**                       
     * \brief Demander la taille de la File 
     *
     * \post La File est inchangée 
     * \post La taille de File 
     */
    int taille() const;  

    /**                       
     * \brief Vérifier si la File est vide
     *
     * \post La File est inchangée 
     * \post VRAI est retourné si la File est vide, FAUX sinon
     */
    bool estVide() const;

    /**                       
     * \brief Recherche d'un élément dans la File
     *
     * \post La File est inchangée 
     * \post VRAI si l'élément est présent, FAUX sinon
     */
    bool appartient(const T&) const;  

    /**                       
     * \brief Retourner l'élément à une certaine position
     *
     *  La position commence à partir de 1
     *
     * \pre La position est comprise entre 1 et |L|+1 
     * \post La File est inchangée dans tous les cas
     * \post L'élément à la position demandée est retourné
     * \exception range_error si la précondition n'est pas respectée 
     */
    const T & element(int) const throw(std::range_error);  

    /**                       
     * \brief Retourner la position d'un élément 
     *
     * \pre L'élement doit être présent dans la File 
     * \post La File est inchangée dans tous les cas
     * \post La position de l'élément retourné
     * \exception logic_error si la précondition n'est pas respectée 
     */
    int position(const T&) const throw(std::logic_error);  

    /**                       
     * \brief Retourner l'élément au début de la file
     *
     * \pre La file ne doit pas être vide 
     * \post Une copie de l'élément est retourné
     * \post La file est inchangée  
     * \exception logic_error si la file est vide
     */
    const T& premier() const throw (std::logic_error);  

    /**                       
     * \brief Retourner l'élément au queue de la file
     *
     * \pre La file ne doit pas être vide 
     * \post Une copie de l'élément est retourné
     * \post La file est inchangée  
     * \exception logic_error si la file est vide
     */
    const T& dernier() const throw (std::logic_error);   


  private:    
    /** 
    * \class Noeud
    *
    * \brief classe interne représentant un noeud typique
    *
    *  La classe représente un noeud typique
    *  pour implémenter une liste simplement chaînée.
    */

    class Noeud;
    /** \typedef typedef Noeud *elem
     *  \brief Définition d'un pointeur sur un Noeud
     *
     *  Pour abréger les écritures
     */
    typedef Noeud * elem;

    class Noeud{  
    public:
      T m_el;     /*!<L'élément de base de la liste*/
      elem  m_suivant;  /*!<Un pointeur vers le noeud suivant*/

      /**                       
       * \brief Constructeur de la classe Noeud
       *
       * \post un noeud typique est intialisé 
       */
        explicit Noeud (const T& data_item, Noeud * next_ptr = 0) :                                
      m_el(data_item), m_suivant(next_ptr) {}
    };  

    elem m_debut;       /*!<Pointeur vers le premier noeud de la liste*/
    int m_cpt;


    //Méthodes privées

    /**                       
     *  \brief Copier deux listes
     *
     * \post Une copie profonde d'une liste est créée
     */
    void _copier( Noeud *) throw (std::bad_alloc);

    /**                       
     *  \brief Détruire une File
     */
    void  _detruire();

  } ;               

}

#include "File.hpp"

#endif