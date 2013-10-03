#include <sstream>
#include <gtest/gtest.h>
#include "../Carte.h"

using namespace tp;

class CarteTest : public testing::Test
{

};

TEST_F(CarteTest, creation)
{
  Carte carte(PIQUE, AS);
}

TEST_F(CarteTest, accesseurs)
{
  Carte carte(PIQUE, AS);

  EXPECT_EQ(carte.reqSorte(), PIQUE);
  EXPECT_EQ(carte.reqValeur(), AS);
}

TEST_F(CarteTest, estSuivante)
{
  Carte asPique(PIQUE, AS);
  Carte deuxPique(PIQUE, DEUX);
  EXPECT_TRUE(asPique.estSuivante(deuxPique));
  EXPECT_FALSE(deuxPique.estSuivante(asPique));

  Carte deuxTrefle(TREFLE, DEUX);
  EXPECT_FALSE(asPique.estSuivante(deuxTrefle));

  Carte troisPique(PIQUE, TROIS);
  EXPECT_FALSE(asPique.estSuivante(troisPique));
}

TEST_F(CarteTest, peutEmpiler)
{
  Carte roiPique(PIQUE, ROI);

  Carte damePique(PIQUE, DAME);
  EXPECT_FALSE(roiPique.peutEmpiler(damePique));
  EXPECT_FALSE(damePique.peutEmpiler(roiPique));

  Carte dameCoeur(COEUR, DAME);
  EXPECT_TRUE(roiPique.peutEmpiler(dameCoeur));
  EXPECT_FALSE(dameCoeur.peutEmpiler(roiPique));

  Carte dameCarreau(CARREAU, DAME);
  EXPECT_TRUE(roiPique.peutEmpiler(dameCarreau));

  Carte dameTrefle(TREFLE, DAME);
  EXPECT_FALSE(roiPique.peutEmpiler(dameTrefle));

  Carte deuxCarreau(CARREAU, DEUX);
  
  Carte asPique(PIQUE, AS);
  EXPECT_TRUE(deuxCarreau.peutEmpiler(asPique));

  Carte asCoeur(COEUR, AS);
  EXPECT_FALSE(deuxCarreau.peutEmpiler(asCoeur));

  Carte asCarreau(CARREAU, AS);
  EXPECT_FALSE(deuxCarreau.peutEmpiler(asCarreau));

  Carte asTrefle(TREFLE, AS);
  EXPECT_TRUE(deuxCarreau.peutEmpiler(asTrefle));
}

TEST_F(CarteTest, output)
{
  std::stringstream ss;

  Carte asPique(PIQUE, AS);
  ss << asPique;
  EXPECT_STREQ(ss.str().c_str(), "AS'PI");

  ss.str("");
  Carte dameCoeur(COEUR, DAME);
  ss << dameCoeur;
  EXPECT_STREQ(ss.str().c_str(), "D'CO");
}
