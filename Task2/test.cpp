#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <UnitTest++/TestReporterStdout.h>
#include "modAlphaCipher.h"
auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}
std::string t;
int key;
modAlphaCipher cipher(key,t);
SUITE(KeyTest){
TEST(boost1_test){
        CHECK_THROW(cipher.getValidKey(key=-3) , cipher_error);
    }
}

SUITE(client_base){

}

int main() {
    RunSuite("KeyTest");
    return 0;
    
}