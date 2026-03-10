#pragma once

#include <stddef.h>
#include <functional>
#include <assert.h>

namespace my_hash {

namespace _hash_impl {

inline size_t
shift_mix(size_t v)
{
    return v ^ (v >> 47);
}

}

template<size_t LEN>
size_t hash_size_array(const size_t *arr, size_t seed = 0xc70f6907UL)
{
    constexpr size_t mul = (((size_t) 0xc6a4a793UL) << 32UL)
            + (size_t) 0x5bd1e995UL;

    size_t hash = seed ^ (sizeof(size_t) * LEN * mul);
    for (size_t i=0; i<LEN; ++i)
    {
        const size_t data = _hash_impl::shift_mix(arr[i] * mul) * mul;
        hash ^= data;
        hash *= mul;
    }

    hash = _hash_impl::shift_mix(hash) * mul;
    hash = _hash_impl::shift_mix(hash);

#ifndef NDEBUG
    {
        size_t h2 = std::_Hash_impl::hash(arr, LEN *sizeof (size_t), seed);
        assert(h2 == hash);
    }
#endif

    return hash;
}

}
