# Q‑LIT

**Q‑LIT** is a lightweight, header‑only C++ library for **compile‑time string obfuscation**. It encodes string literals using XOR at compile time and decrypts them lazily at runtime, helping avoid plaintext strings appearing in binaries.

---

## Features

- Compile‑time XOR encoding of literals  
- Unique per‑string keys via `__COUNTER__`  
- Time‑based seed derived from `__TIME__`  
- In‑place, one‑time decryption on first access  
- Supports: `char`, `wchar_t`, `char16_t`, `char32_t`  
- Header‑only, no external dependencies  

---

## Usage

Include the header (`q_lit.hpp`) and wrap your string literals with one of the macros:

### Narrow (`char`)
```cpp
#include "q_lit.hpp"

const char* msg = QL_("Hello, world!");
std::puts(msg);
```

### Wide (`wchar_t`)
```cpp
const wchar_t* wmsg = QL_W(L"Wide string example");
std::wcout << wmsg << L"\n";
```

### UTF‑16
```cpp
const char16_t* u16 = QL_U16(u"UTF16 sample");
```

### UTF‑32
```cpp
const char32_t* u32 = QL_U32(U"UTF32 sample");
```

---

## How It Works

### Compile Time  
- A base key is generated from `__TIME__`.  
- Each string literal uses a unique `Seed` (via `__COUNTER__`).  
- Each character is XOR‑encoded with:  
  `base_key + 37 * Seed + 17 * index + 23`  
- The encoded array is stored in a `constexpr` object.

### Runtime  
- On first call to `c_str()`, the buffer is decrypted in place and a flag prevents repeated decryption.  
- Subsequent calls return the same decrypted buffer efficiently.

### Important Notes  
- This is **obfuscation**, not encryption.  
- Decryption modifies a static object: **not thread‑safe**.  
- Works only with **compile‑time literals**, not runtime strings.

---

## Compatibility & Requirements

- Requires **C++17** or later.  
- Known-compatible compilers: GCC, Clang, MSVC.  
- Supports the following character types:  
  `char`, `wchar_t`, `char16_t`, `char32_t`.

---

## Limitations & Recommendations

- Avoid multithreaded access before decryption unless synchronized.  
- Runtime-generated strings cannot be obfuscated using this method.  
- Consider this a deterrent, not a secure encryption strategy.

---

## Example Project Structure

```
Q‑LIT/
 ├─ include/
 │   └─ q_lit.hpp
 ├─ examples/
 │   └─ example.cpp
 ├─ tests/
 │   └─ test.cpp
 ├─ README.md
 └─ LICENSE
```

---

## License

Distributed under the **MIT License**.

---

## Contribution & Versioning

- Pull requests are welcome.
