#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace qx
{
    namespace detail
    {
        constexpr std::uint8_t compile_time_seed()
        {
            return static_cast<std::uint8_t>(
                __TIME__[0] * 1u +
                __TIME__[1] * 3u +
                __TIME__[3] * 5u +
                __TIME__[4] * 7u +
                __TIME__[6] * 11u +
                __TIME__[7] * 13u);
        }

        template <std::size_t N, std::uint32_t Seed, typename CharT>
        struct basic_enc_string
        {
            std::array<CharT, N> data_{};
            bool decrypted_ = false;

            static constexpr std::uint8_t base_key()
            {
                return compile_time_seed();
            }

            static constexpr std::uint8_t key_for(std::size_t i)
            {
                return static_cast<std::uint8_t>(
                    base_key() + 37u * Seed + 17u * static_cast<std::uint32_t>(i) + 23u);
            }

            constexpr basic_enc_string(const CharT (&str)[N])
            {
                for (std::size_t i = 0; i < N; ++i)
                {
                    auto k = key_for(i);
                    data_[i] = static_cast<CharT>(str[i] ^ static_cast<CharT>(k));
                }
            }

            CharT *decrypt()
            {
                if (!decrypted_)
                {
                    volatile std::uint8_t sink = 0;
                    for (std::size_t i = 0; i < N; ++i)
                    {
                        auto k = key_for(i);
                        sink ^= k;
                        data_[i] = static_cast<CharT>(data_[i] ^ static_cast<CharT>(k));
                    }
                    (void)sink;
                    decrypted_ = true;
                }
                return data_.data();
            }

            const CharT *c_str()
            {
                return decrypt();
            }
        };

        template <std::size_t N, std::uint32_t Seed>
        using enc_n = basic_enc_string<N, Seed, char>;

        template <std::size_t N, std::uint32_t Seed>
        using enc_w = basic_enc_string<N, Seed, wchar_t>;

        template <std::size_t N, std::uint32_t Seed>
        using enc_u16 = basic_enc_string<N, Seed, char16_t>;

        template <std::size_t N, std::uint32_t Seed>
        using enc_u32 = basic_enc_string<N, Seed, char32_t>;

    } // namespace detail
} // namespace qx

#define QL_(s) \
    []() -> const char * { \
        using qx_char_t = char; \
        constexpr std::size_t qx_len = sizeof(s) / sizeof(qx_char_t); \
        using qx_enc_t = ::qx::detail::enc_n<qx_len, static_cast<std::uint32_t>(__COUNTER__)>; \
        static qx_enc_t qx_store(s); \
        return qx_store.c_str(); }()

// wide
#define QL_W(s) \
    []() -> const wchar_t * { \
        using qx_char_t = wchar_t; \
        constexpr std::size_t qx_len = sizeof(s) / sizeof(qx_char_t); \
        using qx_enc_t = ::qx::detail::enc_w<qx_len, static_cast<std::uint32_t>(__COUNTER__)>; \
        static qx_enc_t qx_store(s); \
        return qx_store.c_str(); }()

// UTF-16
#define QL_U16(s) \
    []() -> const char16_t * { \
        using qx_char_t = char16_t; \
        constexpr std::size_t qx_len = sizeof(s) / sizeof(qx_char_t); \
        using qx_enc_t = ::qx::detail::enc_u16<qx_len, static_cast<std::uint32_t>(__COUNTER__)>; \
        static qx_enc_t qx_store(s); \
        return qx_store.c_str(); }()

// UTF-32
#define QL_U32(s) \
    []() -> const char32_t * { \
        using qx_char_t = char32_t; \
        constexpr std::size_t qx_len = sizeof(s) / sizeof(qx_char_t); \
        using qx_enc_t = ::qx::detail::enc_u32<qx_len, static_cast<std::uint32_t>(__COUNTER__)>; \
        static qx_enc_t qx_store(s); \
        return qx_store.c_str(); }()
