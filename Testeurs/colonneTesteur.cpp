#include <sstream>
#include <gtest/gtest.h>
#include "../Colonne.h"

using namespace tp;

class ColonneCartesTest : public testing::Test
{
  
};

TEST_F(ColonneCartesTest, creation)
{
  ColonneCartes colonne;

  EXPECT_EQ(0, colonne.getNbCartesVisibles());
}

TEST_F(ColonneCartesTest, initColonneCartes)
{
  Liste<Carte> listeCartes;
  
  ColonneCartes colonne;

  colonne.initColonneCartes(listeCartes);
  EXPECT_EQ(0, colonne.getNbCartesVisibles());

  Carte asPique(PIQUE, AS);
  Carte asCoeur(COEUR, AS);

  listeCartes.ajouter(asPique, 1);
  listeCartes.ajouter(asCoeur, 1);

  colonne.initColonneCartes(listeCartes);
  EXPECT_EQ(1, colonne.getNbCartesVisibles());
}

TEST_F(ColonneCartesTest, ajoute)
{
  Liste<Carte> listeCartes;
  Carte roiPique(PIQUE, ROI);
  Carte dameCoeur(COEUR, DAME);
  Carte asPique(PIQUE, AS);

  listeCartes.ajouter(roiPique, 1);

  ColonneCartes colonne;
  
  colonne.initColonneCartes(listeCartes);
  colonne.ajoute(dameCoeur);
  EXPECT_EQ(2, colonne.getNbCartesVisibles());
  
  EXPECT_THROW(colonne.ajoute(asPique), std::runtime_error);
}

TEST_F(ColonneCartesTest, deplacePaquet)
{
  ColonneCartes source;
  ColonneCartes destination;

  Carte dixCoeur(COEUR, DIX);
  Carte neufTrefle(TREFLE, NEUF);
  Carte huitCarreau(CARREAU, HUIT);

  source.ajoute(dixCoeur);
  source.ajoute(neufTrefle);
  source.ajoute(huitCarreau);

  EXPECT_EQ(3, source.getNbCartesVisibles());

  source.deplacePaquet(destination, 3);
  EXPECT_EQ(0, source.getNbCartesVisibles());
  EXPECT_EQ(3, destination.getNbCartesVisibles());

  destination.deplacePaquet(source, 2);
  EXPECT_EQ(2, source.getNbCartesVisibles());
  EXPECT_EQ(1, destination.getNbCartesVisibles());

  source.deplacePaquet(destination, 2);
  EXPECT_EQ(0, source.getNbCartesVisibles());
  EXPECT_EQ(3, destination.getNbCartesVisibles());

  source.ajoute(huitCarreau);
  EXPECT_THROW(source.deplacePaquet(destination, 1), std::runtime_error);
}

TEST_F(ColonneCartesTest, supprimerDernierCarte)
{
  ColonneCartes colonne;

  Carte roiPique(PIQUE, ROI);
  Carte dameCoeur(COEUR, DAME);

  colonne.ajoute(roiPique);
  colonne.ajoute(dameCoeur);

  EXPECT_EQ(2, colonne.getNbCartesVisibles());

  colonne.supprimerDerniereCarte();
  EXPECT_EQ(1, colonne.getNbCartesVisibles());
  
  colonne.supprimerDerniereCarte();
  EXPECT_EQ(0, colonne.getNbCartesVisibles());
}

TEST_F(ColonneCartesTest, output)
{
  
}
