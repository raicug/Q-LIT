// tests.cpp
// Basic validation tests for Q-LIT

#include <iostream>
#include <cstring>
#include "q_lit.hpp"

// Simple assertion helper
static void check(bool condition, const char* msg)
{
    if (!condition)
    {
        std::cerr << "[FAIL] " << msg << "\n";
        std::exit(1);
    }
    std::cout << "[PASS] " << msg << "\n";
}

int main()
{
    // Test narrow-string decoding
    {
        const char* raw = "Hello World";
        const char* obf = QL_("Hello World");
        check(std::strcmp(raw, obf) == 0, "QL_ narrow string decrypts correctly");
    }

    // Test wide-string decoding
    {
        const wchar_t* raw = L"Wide String";
        const wchar_t* obf = QL_W(L"Wide String");
        check(std::wcscmp(raw, obf) == 0, "QL_W wide string decrypts correctly");
    }

    // Test UTF-16 decoding
    {
        const char16_t* raw = u"U16 Test";
        const char16_t* obf = QL_U16(u"U16 Test");

        bool ok = true;
        for (size_t i = 0; raw[i] != 0; i++)
            if (raw[i] != obf[i]) ok = false;

        check(ok, "QL_U16 UTF-16 string decrypts correctly");
    }

    // Test UTF-32 decoding
    {
        const char32_t* raw = U"U32 Test";
        const char32_t* obf = QL_U32(U"U32 Test");

        bool ok = true;
        for (size_t i = 0; raw[i] != 0; i++)
            if (raw[i] != obf[i]) ok = false;

        check(ok, "QL_U32 UTF-32 string decrypts correctly");
    }

    // Test that decrypted data remains decrypted
    {
        const char* first = QL_("Persist Test");
        const char* second = QL_("Persist Test");
        check(std::strcmp(first, second) == 0, "Decryption persists across calls");
    }

    // Test that two different strings do NOT share keys
    {
        const char* a = QL_("AAA");
        const char* b = QL_("BBB");
        check(std::strcmp(a, b) != 0, "Different literals produce different decoded strings");
    }

    std::cout << "\nAll tests passed.\n";
    return 0;
}
