#include "gtest/gtest.h"
#include <string>
#include"client.c"
 //result test
TEST(client_test, NumOfArg) {
        int argc1 =1; 
	ASSERT_EQ(1, client(argc1,NULL));

	int argc2 =2;
	char* argv2[1]= {"9999"};
	ASSERT_EQ(1, client(argc2,argv2));
 	
	int  argc3 =4;
	char*  argv3[4];
	argv3[1] = "9999";
	argv3[2] = "127.0.0.1";
	argv3[3] = "1515";
	ASSERT_EQ(1, client( argc3,argv3)); 
}


TEST(client_test, Type) {
	int argc1 =3;
	char* argv1[2];
	argv1[1] = "input";
	argv1[2] =  "127.0.0.1";
        ASSERT_EQ(2, client(argc1,argv1)); 

        char* argv2[2];
	int argc2 =3;
	argv2[1] = "9999";
	argv2[2] =  "input";
	ASSERT_EQ(2, client( argc2, argv2)); 

        char* argv3[2];
        int argc3 =3;
        argv3[1] = "9999";
        argv3[2]  = "666.299.14.1";
        ASSERT_EQ(2, client(argc3,argv3)); 
}


TEST(client_test, Range) {
	
	char*  argv1[2];
        int  argc1 =3;
	argv1[1] = "99";
	argv1[2] =  "127.0.0.1";
	ASSERT_EQ(3, client( argc1, argv1)); 

	char*  argv2[2];
	argv2[1] = "99999";
	argv2[2] =  "127.0.0.1";
	int argc2 =3;
        ASSERT_EQ(3, client(argc2,argv2)); 


        char*  argv3[2];
	argv3[1] = "5555";
	argv3[2] =  "256.255.255.256";
	int argc3 =3;
        ASSERT_EQ(2, client(argc3,argv3)); 

}


TEST(client_test, ConnectionExoServer) {
 
	 char*  argv[3]={"./main","3333","127.0.0.1"};
   	 int  argc = 3;
//!=
         ASSERT_NE(4, client( argc, argv));
	
}


 


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();

}
