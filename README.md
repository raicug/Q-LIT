# Q-LIT

Q-LIT is a compact, header-only C++ library for compile-time string
obfuscation. It encodes string literals with XOR at compile time and
decrypts them lazily at runtime, preventing plaintext strings from
appearing directly in binaries.

## Features

-   Compile-time XOR encoding\
-   Unique per-string keys using `__COUNTER__`\
-   Time-based seed mixing via `__TIME__`\
-   One-time, in-place decryption on first use\
-   Supports `char`, `wchar_t`, `char16_t`, `char32_t`\
-   Header-only and dependency-free

## Usage

Wrap your string literals in the macros below.

### Narrow (`char`)

``` cpp
#include "Q-LIT.hpp"

const char* msg = QL_("Hello");
std::puts(msg);
```

### Wide (`wchar_t`)

``` cpp
const wchar_t* wmsg = QL_W(L"Wide string");
```

### UTF-16

``` cpp
const char16_t* s16 = QL_U16(u"UTF16 text");
```

### UTF-32

``` cpp
const char32_t* s32 = QL_U32(U"UTF32 text");
```

## How It Works

At compile time: - Each character is XOR-encoded using a key derived
from: - A time-based seed (`__TIME__`) - A unique seed from
`__COUNTER__` - The character index

At runtime: - The encoded buffer is stored in a static object. - First
access decrypts the buffer in place. - Later accesses return the
already-decrypted data.

This is obfuscation, not cryptographic security. It prevents simple
string extraction from binaries but is not intended to resist dedicated
reverse-engineering.

## Requirements

-   C++17 or later
-   Standard C++ library (`<array>`, `<cstdint>`, `<cstddef>`)

## License

Insert your license information here.
