#include <UnitTest++/UnitTest++.h>
#include "routecipher.h"
#include <string>

std::string s = "THEHANDO";

SUITE(KeyTest) {
    TEST(ValidKey) {
        code cipher(4, "THEHANDO");
        CHECK_EQUAL("HOEDHNTA", cipher.encryption(s));
    }
    TEST(LongKey) {
        CHECK_THROW(code(1, "THEHANDO"), cipher_error);
    }
}

struct KeyB_fixture {
    code * t;
    KeyB_fixture() {
        t = new code(4, "THEHANDO");
    }
    ~KeyB_fixture() {
        delete t;
    }
};

SUITE(EncryptTest) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::string input = "THEHANDO";
        CHECK_EQUAL("HOEDHNTA", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::string input = "thehando";
        CHECK_EQUAL("hoedhnta", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        std::string input = "THE HANDO";
        CHECK_EQUAL("HOEDHNTA", t->encryption(input));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        std::string input = "THEHAND0";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        std::string input = "";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        std::string input = "34";
        CHECK_THROW(t->encryption(input), cipher_error);
    }
    TEST(MaxShiftKey) {
        code cipher(8, "THEHANDO");
        std::string input1 = "ODNAHEHT";
        std::string input2 = "THEHANDO";
        CHECK_EQUAL("THEHANDO", cipher.transcript(input1, input2));
    }
}

SUITE(DecryptText) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::string input1 = "HOEDHNTA";
        std::string input2 = "THEHANDO";
        CHECK_EQUAL("THEHANDO", t->transcript(input1, input2));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::string input1 = "hoedhnta";
        std::string input2 = "thehando";
        CHECK_EQUAL("thehando", t->transcript(input1, input2));
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        std::string input1 = "hoedhn ta";
        std::string input2 = "THEHANDO";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        std::string input1 = "VALO4ANT";
        std::string input2 = "VALO4ANT";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        std::string input1 = "hoedhnta!";
        std::string input2 = "THEHANDO!";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        std::string input1 = "";
        std::string input2 = "";
        CHECK_THROW(t->transcript(input1, input2), cipher_error);
    }
    TEST(MaxShiftKey) {
        code cipher(8, "Serafime");
        std::string input1 = "ODNAHEHT";
        std::string input2 = "THEHANDO";
        CHECK_EQUAL("THEHANDO", cipher.transcript(input1, input2));
    }
}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
