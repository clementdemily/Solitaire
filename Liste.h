/**
 * \file Liste.h
 * \brief Classe Définissant le type abstrait liste
 * \author Nathan Irjud
 * \version 1.0
 * \date Octobre 2013
 *
 * Implémentation dans une liste circulaire simplement chaînée
 */

#ifndef _LISTE__H
#define _LISTE__H

#include <iostream>
#include <stdexcept>
#include <string>

namespace tp
{
/**
 * \class Liste
 *
 * \brief classe generique representant une liste ordonnee
 *
 *  La classe gere une liste ordonnee generique. L'implementation
 *  se fait dans une liste circulaire.
 */
template<typename T>
class Liste
{
public:

    //Constructeurs
    /**
     *  \brief Constructeur par defaut
     *
     *  \post Une instance de la classe Liste est initialisee
     */
    Liste();

    /**
     *  \brief Constructeur de copie
     *
     *  \pre Il faut qu'il y ait suffisamment de memoire
     *  \post une copie profonde la File source
     *  \exception bad_alloc s'il n'y a pas assez de mémoire
     */
    Liste(const Liste&);
    ~Liste();

    //Surcharge d'operateurs
    Liste<T>& operator =(const Liste<T>&);

    //Modificateurs
    void ajouter(const T&, int);
    void enleverEl(const T&);
    void enleverPos(int);

    //Selecteurs
    int taille() const;
    bool estVide() const;
    bool appartient(const T&) const;
    const T& element(int) const;
    int position(const T&) const;

    // friend
    template<class U> friend std::ostream& operator <<(std::ostream& f, const Liste<U>& l);
private:

    /**
     * \class Noeud
     *
     * \brief classe interne representant un noeud typique
     *
     *  La classe represente un noeud typique
     *  pour implémenter une liste circulaire.
     */
    class Noeud
    {
    public:
        T el; /*!<L'element de base de la liste*/
        Noeud * suivant; /*!<Un pointeur vers le noeud suivant*/

        explicit Noeud(const T& data_item, Noeud * next_ptr = 0) :
                el(data_item), suivant(next_ptr)
        {
        }
    };

    /** \typedef typedef Noeud *elem
     *  \brief Définition d'un pointeur sur un Noeud
     *
     *  Pour abreger les ecritures
     */
    typedef Noeud * elem;
    elem dernier; /*!<Pointeur vers le dernier noeud de la liste*/

    //Methodes privees
    void _copier(Noeud *);
    void _detruire();
};

} //Fin du namespace

#include "Liste.hpp"

#endif
