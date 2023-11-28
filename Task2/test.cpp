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
SUITE(KeyTest){
TEST(boost1_test){
        const char* test_argv[] = {"name", "-k", "98"};
    }
}

SUITE(client_base){

}

int main() {
    RunSuite("KeyTest");
    return 0;
    
}