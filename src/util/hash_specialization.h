#ifndef HASH_SPECIALIZATION_H
#define HASH_SPECIALIZATION_H

/*
 * Declare a specialization of std::hash that works for
 * an enumeration. This is useful for using an enum
 * as a key in an std::unordered_map.
 */

#define HASH_SPECIALIZATION(enum_type) \
namespace std \
{ \
    template<> \
    struct hash< ::enum_type > \
    { \
        typedef ::enum_type argument_type; \
        typedef std::underlying_type< argument_type >::type underlying_type; \
        typedef std::hash< underlying_type >::result_type result_type; \
        result_type operator()( const argument_type& arg ) const \
        { \
            std::hash< underlying_type > hasher; \
            return hasher( static_cast< underlying_type >( arg ) ); \
        } \
    }; \
} 

#endif // HASH_SPECIALIZATION_H
