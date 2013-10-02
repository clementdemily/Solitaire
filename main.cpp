#include <iostream>

#include "Solitaire.h"

int main (int ac, char **av)
{
	tp::Solitaire s;
	std::string menu;
	int	choix = -1;

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
"Votre choix :\n"
;
	while (!s.verifieGagne())
	{
		do 
		{
			std::cout << s.reqEtatJeu();
			std::cout << menu;
			std::cin >> choix;
			std::cout << choix;
		} while (choix < 0 && choix > 6);
	}
	return (0);
}