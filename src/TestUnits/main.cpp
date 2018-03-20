#include <gtest\gtest.h>
#include "../src/IO/SDL_ReadWrite.h"

TEST(FileReadWriteTests, FileExistsWhenExists)
{
	FileReadWrite* fileReadWrite = new SDL_ReadWrite();
	EXPECT_EQ(true, fileReadWrite->FileExists("main.cpp"));
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
