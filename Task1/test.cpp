#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <cctype>
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
    
    TEST(t1) {
        CHECK(modAlphaCipher(L"БВГ").encrypt(L"ПРИВЕТ")==L"РТЛГЖХ");
    }
    TEST(t2) {
        CHECK(modAlphaCipher(L"БВГБВГБВГ").encrypt(L"ПРИВЕТ")==L"РТЛГЖХ");
    }
    TEST(t3) {
        CHECK(modAlphaCipher(L"бвг").encrypt(L"ПРИВЕТ")==L"РТЛГЖХ");
    }
    TEST(t4) {
        CHECK_THROW(modAlphaCipher(L"Б1"), cipher_error);
    }
    TEST(t5) {
        CHECK_THROW(modAlphaCipher(L"Б,В"), cipher_error);
    }
    TEST(t6) {
        CHECK_THROW(modAlphaCipher(L"Б В"), cipher_error);
    }
    TEST(t7) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error);
    }
};
struct KeyB_fixture {
modAlphaCipher * p;
KeyB_fixture()
{ p = new modAlphaCipher(L"В");
}
~KeyB_fixture()
{ delete p;
}
};

SUITE(EncryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"));
        }
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИ ЙКЛМНОПРСТУФ ХЦЧШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, Numbers) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИ22ЙКЛМНОП13РСТУФ58ХЦЧШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->encrypt(L"123#5"), cipher_error);
        }
    TEST(MaxShiftKey) {
        CHECK(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ" == modAlphaCipher(L"Я").encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
};
SUITE(DecryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == p->decrypt(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ"));
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"вгдеёжзийклмнопрстуфхцчшщъыьэюяаб"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK_THROW(p->decrypt(L"АБВГДЕЁЖЗИ ЙКЛМНОПРСТУФ ХЦЧШЩЪЫЬЭЮЯ"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Digit) {
        CHECK_THROW(p->decrypt(L"АБВ1ГД2ЕЁ3ЖЗ4И"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Punct) {
        CHECK_THROW(p->decrypt(L"АБВ,ГД.ЕЁ/ЖЗ;И"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->decrypt(L"123#5"), cipher_error);
        }
    TEST(MaxShiftKey) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == modAlphaCipher(L"Я").decrypt(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ"));
        }
};

int main() {
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    RunSuite("KeyTest");
    RunSuite("EncryptTest");
    RunSuite("DecryptTest");
    return 0;
}