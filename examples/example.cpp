// QLIB - Compile-time string obfuscation
// Copyright (c) 2025-2026 raicug
// Licensed under the MIT License

#include <iostream>
#include "q_lit.hpp"

int main()
{
    const char* a = QL_("Hello, world!");
    const wchar_t* b = QL_W(L"Wide text");
    const char16_t* c = QL_U16(u"UTF-16 sample");
    const char32_t* d = QL_U32(U"UTF-32 sample");

    std::cout << a << "\n";

    std::wcout << b << L"\n";

    std::cout << "UTF-16 length: " << std::char_traits<char16_t>::length(c) << "\n";
    std::cout << "UTF-32 length: " << std::char_traits<char32_t>::length(d) << "\n";

    return 0;
}
