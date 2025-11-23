#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("ЭХОСЭ",modAlphaCipher("ЭХОС").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("ТРЕТИ",modAlphaCipher("ТРЕТИЙ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("АКТАК",modAlphaCipher("акт").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("АКТ3"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("ЭХОС,"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Э Х О С"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("С");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ЖСЮАЯ", p->encrypt("ХАМОН"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ЖСЮАЯ", p->encrypt("хамон"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ЖСЮАЯАУЦВХВСЫУ", p->encrypt("ХАМОН ОВЕРДРАЙВ!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ЖСЮАЯ", p->encrypt("0ХАМОН0"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("67"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ФЯЛНМ", modAlphaCipher("Я").encrypt("ХАМОН"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ОЪЙШЭРУЯТЯОШР", p->decrypt("АЛЫЙОВЕРДРАЙВ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("шсъЦДСОЯЫЗЖЗРЗЁ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ШСЪЦД СОЯЫЗЖЗРЗЁ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("55ДСОЯЫЗЖЗРЗЁ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ШСЪЦДСОЯЫЗЖЗРЗЁ!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("БМЬКПГЁСЕСБКГ", modAlphaCipher("Я").decrypt("АЛЫЙОВЕРДРАЙВ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
