#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Solitaire.h"

using namespace tp;

void deplacerCarteTalonVersColonne(Solitaire& s)
{

}

void deplacerCarteTalonVersPile(Solitaire& s)
{

}

void deplacerCartesColonneVersColonne(Solitaire& s)
{

}

void deplacerCarteColonneVersPile(Solitaire& s)
{

}

int main (int ac, char **av)
{
    Solitaire s;
    std::string menu;
    std::string saisie;
    int choix = -1;

    menu = 
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

    while (!s.verifieGagne())
    {
        do
        {
            std::cout << s.reqEtatJeu();
            std::cout << menu;
            std::getline (std::cin, saisie);
            std::stringstream(saisie) >> choix;
        } while (choix < 1 || choix > 6);

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
            std::cout << e.what() << std::endl;
        }
    }

    return (0);
}