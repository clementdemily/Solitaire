#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "Solitaire.h"

using namespace tp;


std::string& reqMenu()
{
    static std::string menu;

    menu = YELLOW;
    menu += 
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
    menu += RESETCOLOR;

    return (menu);
}

void nettoyerConsole()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif           
}

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

int main (int ac, char **av)
{
    Solitaire s;
    std::string menu;
    std::string saisie;
    int choix = -1;
    bool err = false;


    while (!s.verifieGagne())
    {
        choix = -1;
        do
        {
            nettoyerConsole();
            if (err)
                std::cout << RED << "!!! Coup invalide !!!" << RESETCOLOR << std::endl;
            std::cout << s.reqEtatJeu();
            std::cout << reqMenu();
            std::getline (std::cin, saisie);
            if(std::cin.eof())
              return (0);
            std::stringstream(saisie) >> choix;
        } while (choix < 1 || choix > 6);

        err = false;
        try {
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
                    return (0);
                break;
                default:
                break;
            }
        }catch (std::exception & e){
            // std::cout << e.what() << std::endl;
            err = true;
        }
    }

    return (0);
}