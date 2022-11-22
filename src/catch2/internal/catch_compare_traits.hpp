
//              Copyright Catch2 Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0
#ifndef CATCH_COMPARE_TRAITS_HPP_INCLUDED
#define CATCH_COMPARE_TRAITS_HPP_INCLUDED

#include <catch2/internal/catch_void_type.hpp>

#include <type_traits>

namespace Catch {
    namespace Detail {

#if defined( __GNUC__ ) && !defined( __clang__ )
#    pragma GCC diagnostic push
    // GCC likes to complain about comparing bool with 0, in the decltype()
    // that defines the comparable traits below.
#    pragma GCC diagnostic ignored "-Wbool-compare"
    // "ordered comparison of pointer with integer zero" same as above,
    // but it does not have a separate warning flag to suppress
#    pragma GCC diagnostic ignored "-Wextra"
    // Did you know that comparing floats with `0` directly
    // is super-duper dangerous in unevaluated context?
#endif
#pragma GCC diagnostic ignored "-Wfloat-equal"

#define CATCH_DEFINE_COMPARABLE_TRAIT( id, op )                           \
    template <typename T, typename U> class is_##id##_comparable {        \
        template <typename, typename> static std::false_type test( ... ); \
                                                                          \
        template <typename X, typename Y>                                 \
        static auto test( int )                                           \
            -> decltype( std::declval<X>() op std::declval<Y>(),          \
                         std::true_type() );                              \
                                                                          \
    public:                                                               \
        static const bool value = decltype( test<T, U>( 0 ) )::value;     \
    };                                                                    \
    template <typename T> class is_##id##_0_comparable {                  \
        template <typename> static std::false_type test( ... );           \
                                                                          \
        template <typename X>                                             \
        static auto test( int ) -> decltype( std::declval<X>() op 0, std::true_type() );    \
                                                                          \
    public:                                                               \
        static const bool value = decltype( test<T>( 0 ) )::value;        \
    };

        // We need all 6 pre-spaceship comparison ops: <, <=, >, >=, ==, !=
        CATCH_DEFINE_COMPARABLE_TRAIT( lt, < )
        CATCH_DEFINE_COMPARABLE_TRAIT( le, <= )
        CATCH_DEFINE_COMPARABLE_TRAIT( gt, > )
        CATCH_DEFINE_COMPARABLE_TRAIT( ge, >= )
        CATCH_DEFINE_COMPARABLE_TRAIT( eq, == )
        CATCH_DEFINE_COMPARABLE_TRAIT( ne, != )

#undef CATCH_DEFINE_COMPARABLE_TRAIT

#if defined( __GNUC__ ) && !defined( __clang__ )
#    pragma GCC diagnostic pop
#endif


    } // namespace Detail
} // namespace Catch

#endif // CATCH_COMPARE_TRAITS_HPP_INCLUDED
