#include <sstream>
#include <gtest/gtest.h>
#include "../Solitaire.h"

using namespace std;

using namespace tp;

class SolitaireTest : public testing::Test
{
public:
  Solitaire solitaire;
};

TEST_F(SolitaireTest, debutPartie)
{
    EXPECT_FALSE(solitaire.verifieGagne());
}
