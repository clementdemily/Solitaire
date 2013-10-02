/**
 * \file Liste.h
 * \brief Classe Définissant le type abstrait liste
 * \author Mathieu Dumoulin
 * \version 0.2
 * \date Septembre 2013
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
 * \brief classe générique représentant une liste ordonnée
 *
 *  La classe gére une liste ordonnée générique. L'implémentation
 *  se fait dans une liste circulaire.
 */
template<typename T>
class Liste
{
public:

    //Constructeurs
    Liste();
    Liste(const Liste&);
    ~Liste();

    //Surcharge d'opérateurs
    Liste<T>& operator =(const Liste<T>&);

    //Modificateurs
    void ajouter(const T&, int);
    void enleverEl(const T&);
    void enleverPos(int);

    //Sélécteurs
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
     * \brief classe interne représentant un noeud typique
     *
     *  La classe représente un noeud typique
     *  pour implémenter une liste circulaire.
     */
    class Noeud
    {
    public:
        T el; /*!<L'élément de base de la liste*/
        Noeud * suivant; /*!<Un pointeur vers le noeud suivant*/

        explicit Noeud(const T& data_item, Noeud * next_ptr = 0) :
                el(data_item), suivant(next_ptr)
        {
        }
    };

    /** \typedef typedef Noeud *elem
     *  \brief Définition d'un pointeur sur un Noeud
     *
     *  Pour abréger les écritures
     */
    typedef Noeud * elem;
    elem dernier; /*!<Pointeur vers le dernier noeud de la liste*/

    //Méthodes privées
    void _copier(Noeud *);
    void _detruire();
};

} //Fin du namespace

#include "Liste.hpp"

#endif
