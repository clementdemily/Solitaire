#include <sstream>
#include <gtest/gtest.h>
#include "../Solitaire.h"

using namespace std;

using namespace tp;

class SolitaireTest : public testing::Test
{
  Solitaire solitaire;
};

TEST_F(SolitaireTest, debutPartie)
{
}

int main(int ac, char **av)
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
