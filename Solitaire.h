/**
 * \file Solitaire.h
 * \brief Classe contenant la logique du jeu
 * \author Clément Demily
 * \version 0.1
 * \date octobre 2013
 *
 * Classe Solitaire
 */

#ifndef _SOLITAIRE__H
#define _SOLITAIRE__H

#include <iostream>
#include <sstream>
#include <stdexcept>	// Pour les exceptions standards
#include <string>

#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include "File.h"
#include "Pile.h"
#include "Liste.h"
#include "Carte.h"
#include "Colonne.h"

#ifndef __COLOR__
	#define BLACK  "\033[22;30m"
	#define RED  "\033[22;31m"
	#define GREEN  "\033[22;32m"
	#define YELLOW  "\033[22;33m"

	#define RESETCOLOR "\033[0m"
#endif

#pragma warning( disable : 4290 )// Une fonction est déclarée avec une spécification d'exception (voir la méthode 
// ajouter(), ce que Visual Studio accepte mais n'implémente pas. Le code avec spécification d'exception ignoré lors
//de la compilation peut nécessiter une nouvelle compilation et édition de liens pour pouvoir être 
//réutilisé dans des versions ultérieures prenant en charge les spécifications d'exception. 
//Vous pouvez éviter cet avertissement par le pragma warning (disable : 4290) 

namespace tp
{

	/** 
    * \file Solitaire.hpp
    * \brief Classe contenant la logique du jeu
 	*
	*/
	class Solitaire {
	public:
		/**
	     *  \brief Constructeur par défaut
	     *
	     *  \post Une instance de la classe Solitaire est initialisée
	     */
		Solitaire();

		/**
	     *  \brief Constructeur de copie
		 *
		 *  \pre Il faut qu'il y ait suffisamment de mémoire
		 *  \post une copie profonde du Solitaire source
		 *  \exception bad_alloc s'il n'y a pas assez de mémoire
	     */
		Solitaire(const Solitaire&) throw(std::bad_alloc);	

		/**
	     *  \brief Destructeur
	     *
	     *  \post l'instance de Solitaire est détruite
	     */
		~Solitaire();
		//Surcharge d'opérateurs

		/**                       
		 * \brief Surcharger l'opérateur = 
		 *
		 * \pre Il y a assez de mémoire pour l'opération 
		 * \post Une copie d'une Solitaire est retournée
		 * \exception bad_alloc si la précondition n'est pas respectée 
		 */
		const Solitaire& operator=(const Solitaire&) throw (std::bad_alloc);

		/**                       
		 * \brief Surcharge de l'opérateur << 
		 *
		 * \post Un flux de sortie correspondant à la Solitaire est retournée  
		 */
		friend std::ostream& operator << (std::ostream& p_f, const Solitaire& p_l);

	public:
		/**                       
		 * \brief Fait avancer le talon d'une carte, c'est-à-dire prend la première et la place à la fin du talon 
		 */
		void	avancerTalon(); 

		/**                       
		 * \brief Déplace p_nbCartes cartes à partir de la colonne p_colonneSource vers la colonne p_colonneDestination. 
		 *
		 * \param[in] p_colonneSource le numéro de la colonne source.
		 * \param[in] p_colonneDestination le numéro de la colonne de destination.
		 * \param[in] p_nbCartes le nombre de cartes à déplacer
		 * \pre p_colonneSource et p_colonneDestination doivent être entre 0 et 6 inclusivement.
		 * \exception runtime_error si les paramètres ne sont pas cohérents avec les règles du jeu.
		 */
		void	deplacerColonneAColonne( int p_colonneSource, int p_colonneDestination, int p_nbCartes) throw (std::runtime_error);

		/**                       
		 * \brief Déplace la carte du dessus du talon vers la colonne spécifiée par "p_colonneDestination". 
		 *
		 * \param[in] p_colonneDestination le numéro de la colonne de destination.
		 * \pre p_colonneDestination compris entre 0 et 6 inclus
		 * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
		 */
		void	deplacerTalonAColonne ( int p_colonneDestination ) throw(std::runtime_error);

		/**                       
		 * \brief Déplace la carte du dessus du talon vers la pile spécifiée par "p_pileDestination".
		 *
		 * \param[in] p_pileDestination le numéro de la pile de destination
		 * \pre p_pileDestination compris entre 0 et 3 inclus
		 * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
		 */
		void	deplacerTalonAPile ( int p_pileDestination ) throw (std::runtime_error);

		/**                       
		 * \brief Déplace la dernière carte de la colonne spécifiée par "p_colonneSource" vers la pile spécifiée par "p_pileDestination".
		 *
		 * \param[in] p_pileDestination le numéro de la pile de destination
		 * \pre p_pileDestination compris entre 0 et 3 inclus
		 * \param[in] p_colonneSource le numéro de la colonne source.
		 * \pre p_colonneSource doit être entre 0 et 6 inclusivement.
		 * \exception runtime_error si le déplacement demandé par l'appel de cette méthode n'est pas réglementaire
		 */
		void	deplacerColonneAPile ( int p_colonneSource, int p_pileDestination) throw (std::runtime_error);
		
		/**
		 * \brief Vérifie si le joueur a gagné:
	     *
		 * \return VRAI ou FAUX selon que l'état du jeu indique que le joueur a gagné la partie, (si les sept colonnes sont vides et que le talon est vide).
		 */
		bool	verifieGagne ( ) const;

		/**
		 * \brief retourne l'état du jeu
		 *
		 * \return l'état du jeu sous la forme d'un objet string formaté exactement de la même façon que la démonstration.
		 */
		std::string	reqEtatJeu ( ) const;
	private:
		/**
		 * \brief mélange le paquet de carte, distribue les 7 colonnes de cartes, init les piles
		 */
		void	_init();

		/**
		 * \brief Réalise une copie profonde d'un solitaire
		 */
		void	_copie(const Solitaire&);

		/**
		 * \brief Détruit l'objet
		 */
		void	_detruire();

		/**
		 * \brief initialise les cartes du talon
		 */
		void	_initTalon();

		/**
		 * \brief initialise les cartes du talon
		 */
		void	_initColonnes();
	protected:
		File<Carte> m_talon;
		ColonneCartes m_colonnes[7];
		Pile<Carte> m_piles[4];
	};
}

#endif