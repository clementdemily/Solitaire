#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "Solitaire.h"

using namespace tp;

/**
 * \brief Recupere le prompt du menu
 *
 * \fn std::string& reqMenu()
 * \return Le prompt du menu
*/
std::string& reqMenu()
{
    static std::string menu;

/*#if !defined(_WIN32)
    menu = YELLOW;
    menu += 
#else*/
    menu =
//#endif
    "\n"
    "*******************************************\n"
    "Menu\n"
    "*******************************************\n"
    "1. Prochaine carte du talon.\n"
    "2. Deplacer une carte du talon vers une colonne.\n"
    "3. Deplacer une carte du talon vers une pile.\n"
    "4. Deplacer une(des) carte(s) d'une colonne vers une autre.\n"
    "5. Deplacer une carte d'une colonne vers une pile.\n"
    "6. Quitter.\n"
    "*******************************************\n"
    "Votre choix : ";
/*#if !defined(_WIN32)
    menu += RESETCOLOR;
#endif*/
    return (menu);
}

/**
 * \brief Nettoye la console
 *
 * \fn void nettoyerConsole()
*/
void nettoyerConsole()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif           
}

/**
 * \brief S'occupe de recupérer les données pour effectuer la fonction deplacerTalonAColonne() de Solitaire()
 *
 * \fn void deplacerCarteTalonVersColonne()
 * \param[in] Solitaire& Instance du jeu de Solitaire
*/
void deplacerCarteTalonVersColonne(Solitaire& s)
{
    std::string saisie;
    int choixColonne = -1;

    do {
        std::cout << "Entrer le numero de la colonne de destination [0, 6] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixColonne;
    } while (choixColonne < 0 || choixColonne > 6);

    s.deplacerTalonAColonne(choixColonne);
}

/**
 * \brief S'occupe de recupérer les données pour effectuer la fonction deplacerCarteTalonVersPile() de Solitaire()
 *
 * \fn void deplacerCarteTalonVersPile()
 * \param[in] Solitaire& Instance du jeu de Solitaire
*/
void deplacerCarteTalonVersPile(Solitaire& s)
{
    std::string saisie;
    int choixPile = -1;

    do {
        std::cout << "Entrer le numero de la pile de destination [0, 3] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixPile;
    } while (choixPile < 0 || choixPile > 3);

    s.deplacerTalonAPile(choixPile);
}

/**
 * \brief S'occupe de recupérer les données pour effectuer la fonction deplacerCartesColonneVersColonne() de Solitaire()
 *
 * \fn void deplacerCartesColonneVersColonne()
 * \param[in] Solitaire& Instance du jeu de Solitaire
*/
void deplacerCartesColonneVersColonne(Solitaire& s)
{
    std::string saisie;
    int choixColonne1 = -1;
    int choixColonne2 = -1;
    int nbCartes = -1;

    do {
        std::cout << "Entrer le numero de la colonne d'origine [0, 6] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixColonne1;
    } while (choixColonne1 < 0 || choixColonne1 > 6);

    saisie = "";
    do {
        std::cout << "Entrer le numero de la colonne de destination [0, 6] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixColonne2;
    } while (choixColonne2 < 0 || choixColonne2 > 6);

    saisie = "";
    do {
        std::cout << "Entrer le nombre de carte(s) a deplacer [1, 13] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> nbCartes;
    } while (nbCartes < 1 || nbCartes > 13);

    s.deplacerColonneAColonne(choixColonne1, choixColonne2, nbCartes);
}

/**
 * \brief S'occupe de recupérer les données pour effectuer la fonction deplacerCarteColonneVersPile() de Solitaire()
 *
 * \fn void deplacerCarteColonneVersPile()
 * \param[in] Solitaire& Instance du jeu de Solitaire
*/
void deplacerCarteColonneVersPile(Solitaire& s)
{
    std::string saisie;
    int choixColonne = -1;
    int choixPile = -1;

    do {
        std::cout << "Entrer le numero de la colonne d'origine [0, 6] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixColonne;
    } while (choixColonne < 0 || choixColonne > 6);

    saisie = "";
    do {
        std::cout << "Entrer le numero de la pile de destination [0, 3] : ";
        std::getline (std::cin, saisie);
        std::stringstream(saisie) >> choixPile;
    } while (choixPile < 0 || choixPile > 3);

    s.deplacerColonneAPile(choixColonne, choixPile);
}

/**
 * \brief Lance la fonction associé au choix de l'utilisateur
 *
 * \fn void jouer()
 * \param[in] Solitaire& Instance du jeu de Solitaire
 * \pre le choix doit être compris entre 1 et 6 inclusivement
 * \param[in] int choix de l'utilisateur
*/
void jouer(Solitaire& s, int choix)
{
    switch (choix)
    {
        case 1:
            s.avancerTalon();
        break;
        case 2:
            deplacerCarteTalonVersColonne(s);
        break;
        case 3:
            deplacerCarteTalonVersPile(s);
        break;
        case 4:
            deplacerCartesColonneVersColonne(s);
        break;
        case 5:
            deplacerCarteColonneVersPile(s);
        break;
        case 6:
            exit(0);
        break;
        default:
        break;
    }
}

/**
 * \brief On recupere le choix de l'utilisateur
 *
 * \fn int recupererChoixMenu()
 * \param[in] Solitaire& Instance du jeu de Solitaire
 * \param[in] bool code d'erreur
 * \return Choix de l'utilisateur
*/
int recupererChoixMenu(Solitaire& s, bool err)
{
    std::string saisie;
    int choix = -1;

    do
    {
        nettoyerConsole();
        if (err)
            std::cout << RED << "!!! Coup invalide !!!" << RESETCOLOR << std::endl;
        std::cout << s.reqEtatJeu();
        std::cout << reqMenu();
        std::getline (std::cin, saisie);
        if(std::cin.eof())
          exit (0);
        std::stringstream(saisie) >> choix;
    } while (choix < 1 || choix > 6);

    return (choix);
}

int main (int ac, char **av)
{
    Solitaire s;
    int choix = 0;
    bool err = false;

    while (!s.verifieGagne())
    {
        choix = recupererChoixMenu(s, err);
        err = false;
        try {
            jouer(s, choix);
        }catch (std::exception & e){
            err = true;
        }
    }

    std::cout << "Felicitation! Vous avez gagne!" << std::endl;
    return (0);
}