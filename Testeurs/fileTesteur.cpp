#include "gtest/gtest.h"
#include "../File.h"

using namespace std;

using namespace tp;

class FileTest: public ::testing::Test
{
public:
   File<int> file;
};

TEST_F(FileTest, FileTailleZero) { 
	EXPECT_TRUE(file.taille() == 0);
}

TEST_F(FileTest, FileVide) { 
	EXPECT_TRUE(file.estVide());
}

TEST_F(FileTest, FileEnfile5Valeurs){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	EXPECT_TRUE(file.taille() == 5);
}

TEST_F(FileTest, FileTestPremiereValeur){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	EXPECT_EQ(file.premier(), 1);
}

TEST_F(FileTest, FileTestDerniereValeur){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	EXPECT_EQ(file.dernier(), 5);
}

TEST_F(FileTest, FileDefile1Valeur){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	file.defiler();


	EXPECT_EQ(file.premier(), 2);
	EXPECT_EQ(file.dernier(), 5);
	EXPECT_FALSE(file.taille() == 5);
}

TEST_F(FileTest, FileDefile5Valeurs){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	file.defiler();
	file.defiler();
	file.defiler();
	file.defiler();
	file.defiler();

	EXPECT_THROW(file.premier(), std::logic_error);
	ASSERT_THROW(file.dernier(), std::logic_error);
	EXPECT_TRUE(file.taille() == 0);
} 

TEST_F(FileTest, FileDefile1Enfile1Valeur){
	file.enfiler(1);
	file.enfiler(2);
	file.enfiler(3);
	file.enfiler(4);
	file.enfiler(5);

	file.defiler();

	file.enfiler(1);

	EXPECT_EQ(file.premier(), 2);
	EXPECT_EQ(file.dernier(), 1);
	EXPECT_TRUE(file.taille() == 5);
}
