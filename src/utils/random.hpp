#pragma once

#include <climits> // for constants.
#include <cstdint>
#include <cstdlib>
#include <numeric>

#include "helpers.hpp"

class Random
{
    public:
        inline static void Init( std::uint32_t seed )
        {
            std::srand(seed);
        }

        inline static std::int32_t NextInt32( int32_t min = 0, int32_t max = INT_MAX )
        {
            return Rand(min,max);
        }

        inline static std::int64_t NextInt64( int64_t min = 0, int64_t max = INT64_MAX )
        {
            return static_cast<int64_t>(Rand(min,max)) * static_cast<int64_t>(Rand(min,max));
        }

        inline static std::uint32_t NextUInt32( uint32_t min = 0, uint32_t max = UINT_MAX )
        {
            return Rand(min,max);
        }

        inline static std::uint64_t NextUInt64( uint64_t min = 0, uint64_t max = UINT64_MAX )
        {
            return static_cast<uint64_t>(Rand(min,max)) * static_cast<uint64_t>(Rand(min,max));
        }

        inline static float NextFloat( float min = 0.0f, float max = 1.0f )
        {
            return Rand(min,max);
        }

        inline static double NextDouble( double min = 0.0, double max = 1.0 )
        {
            return Rand(min,max);
        }

    private:
        template<typename FloatingType>
        inline static FloatingType Between_0_1() // returns a floating type between 0,1
        {
                return static_cast<FloatingType>(RandImplemention()) / RAND_MAX;
        }

        template<typename T>
        inline static T Rand( T min, T max ) // algorithm used for rand.
        {
            auto _pair = MinMax(min,max);

            if constexpr( IsFloatingValue<T>() )
                return _pair.first + Between_0_1<T>() * (_pair.second - _pair.first);

            else
                return _pair.first + RandImplemention() % (_pair.second - _pair.first);
        }

        inline static int32_t RandImplemention()
        {
            if constexpr( RAND_MAX == INT32_MAX )
                return rand();

            if constexpr( RAND_MAX == INT16_MAX ) // on some platforms, RAND_MAX is 16-bit.
                return static_cast<int32_t>(rand()) * static_cast<int32_t>(rand());
        }
};