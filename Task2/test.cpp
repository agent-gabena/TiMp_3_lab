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
std::string text;
int key;
modAlphaCipher cipher(key,t);
SUITE(KeyTest){
TEST(key_1){
        CHECK(cipher.getValidKey(key=3));
    }
TEST(key_2){
    CHECK_THROW(cipher.getValidKeyText(key=10, t="abc"), cipher_error);
    }
TEST(key_3){
        CHECK_THROW(cipher.getValidKey(key=-3) , cipher_error);
    }
}

SUITE(encrypt){
    TEST(t_1){
        t = "abcdefghijklmnopqrstuxyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).encrypt(t), "qiarjbskctldumexnfyogzph");
    }
    TEST(t_2){
        t = "abc21defghi43jklmnopq34rstu18xyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).encrypt(cipher.getValidOpenText(t)), "qiarjbskctldumexnfyogzph");
    }
    TEST(t_3){
        t = "abc,,defghi;;jklmnopq//rstu][xyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).encrypt(cipher.getValidOpenText(t)), "qiarjbskctldumexnfyogzph");
    }
    TEST(t_4){
        t = "abcавdefghiвгjklmnopqжжжхrstuйййййййййxyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).encrypt(cipher.getValidOpenText(t)), "qiarjbskctldumexnfyogzph");
    }
    TEST(t_5){
        t = "238273983овыатвр№?(;(*))"; 
        CHECK_THROW(modAlphaCipher(3,t).encrypt(cipher.getValidOpenText(t)), cipher_error);
    }    
}
SUITE(decrypt){
    TEST(t_1){
        t = "abcdefghijklmnopqrstuxyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).decrypt(t), "cfiloruzbehknqtyadgjmpsx");
    }
    TEST(t_2){
        t = "abc21defghi43jklmnopq34rstu18xyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).decrypt(cipher.getValidOpenText(t)), "cfiloruzbehknqtyadgjmpsx");
    }
    TEST(t_3){
        t = "abc,,defghi;;jklmnopq//rstu][xyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).decrypt(cipher.getValidOpenText(t)), "cfiloruzbehknqtyadgjmpsx");
    }
    TEST(t_4){
        t = "abcавdefghiвгjklmnopqжжжхrstuйййййййййxyz"; 
        CHECK_EQUAL(modAlphaCipher(3,t).decrypt(cipher.getValidOpenText(t)), "cfiloruzbehknqtyadgjmpsx");
    }
    TEST(t_5){
        t = "238273983овыатвр№?(;(*))"; 
        CHECK_THROW(modAlphaCipher(3,t).decrypt(cipher.getValidOpenText(t)), cipher_error);
    }    
}

int main() {
    RunSuite("KeyTest");
    RunSuite("encrypt");
    RunSuite("decrypt");
    return 0;
    
}