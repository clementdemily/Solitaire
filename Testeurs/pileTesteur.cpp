#include "gtest/gtest.h"
#include "../Pile.h"

using namespace std;

using namespace tp;

class PileTest: public ::testing::Test
{
public:
   Pile<int> pile;//Liste d'entiers
};

TEST_F(PileTest, PileTailleZero) { 
	EXPECT_TRUE(pile.taille() == 0);
}

TEST_F(PileTest, PileVide) { 
	EXPECT_TRUE(pile.estVide());
}

TEST_F(PileTest, PileEnpile5Valeurs){
	pile.empiler(1);
	pile.empiler(2);
	pile.empiler(3);
	pile.empiler(4);
	pile.empiler(5);

	EXPECT_TRUE(pile.taille() == 5);
}

TEST_F(PileTest, PileTestPremiereValeur){
	pile.empiler(1);
	pile.empiler(2);
	pile.empiler(3);
	pile.empiler(4);
	pile.empiler(5);

	EXPECT_EQ(pile.premier(), 5);
}

TEST_F(PileTest, PileTestDerniereValeur){
	pile.empiler(1);
	pile.empiler(2);
	pile.empiler(3);
	pile.empiler(4);
	pile.empiler(5);

	EXPECT_EQ(pile.dernier(), 1);
}

TEST_F(PileTest, PileDepile1Valeur){
	pile.empiler(1);
	pile.empiler(2);
	pile.empiler(3);
	pile.empiler(4);
	pile.empiler(5);

	pile.depiler();


	EXPECT_EQ(pile.premier(), 4);
	EXPECT_EQ(pile.dernier(), 1);
	EXPECT_FALSE(pile.taille() == 5);
}

TEST_F(PileTest, PileDepile5Valeurs){
	pile.empiler(1);
	pile.empiler(2);
	pile.empiler(3);
	pile.empiler(4);
	pile.empiler(5);

	pile.depiler();
	pile.depiler();
	pile.depiler();
	pile.depiler();
	pile.depiler();

	EXPECT_THROW(pile.premier(), std::logic_error);
	ASSERT_THROW(pile.dernier(), std::logic_error);
	EXPECT_TRUE(pile.taille() == 0);
}