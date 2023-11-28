#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"


// проверка, чтобы строка состояла только из прописных букв
bool isValid(const std::wstring& s) {
    for(auto c:s)
        if (!iswalpha(c) || !iswupper(c))
            return false;
    return true;
}

void check(const std::wstring& Text, const std::wstring& key, const bool destructCipherText=false)
{ 
    try{
        std::wstring cipherText;
        std::wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
            if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        std::wcout<<"key="<<key<<std::endl;
        std::wcout<<Text<<std::endl;
        std::wcout<<cipherText<<std::endl;
        std::wcout<<decryptedText<<std::endl;
    }
    catch (const cipher_error & e) {
        std::wcerr<<"Error: "<<e.what()<<std::endl;
    }
}

int main(int argc, char **argv) {
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    check(L"БОЛЬШАЯКОРИЧНЕВАЯЛИСАБЫСТРОПРЫГАЕТЧЕРЕЗСОБАКУ",L"ТОПСЕКРЕТ");
    check(L"ТЕКСТДЛЯШИФРА",L"");
    check(L"ТЕКСТДЛЯШИФРА",L"АБВГ123");
    check(L"БОЛЬШАЯ КОРИЧНЕВАЯ ЛИСА БЫСТРО ПРЫГАЕТ ЧЕРЕЗ СОБАКУ ",L"СУПЕР");
    check(L"123",L"АБВГ");
    check(L"БОЛЬШАЯКОРИЧНЕВАЯЛИСАБЫСТРОПРЫГАЕТЧЕРЕЗСОБАКУ",L"ТОПСЕКРЕТ",true);
    return 0;
}