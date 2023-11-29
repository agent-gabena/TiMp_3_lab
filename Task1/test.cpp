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
    TEST(ValidKey) {
        CHECK_THROW(modAlphaCipher(L"АБВГД").encrypt(L"АААА"), cipher_error);
        
    }

}


int main() {
    RunSuite("KeyTest");
    return 0;
    
}