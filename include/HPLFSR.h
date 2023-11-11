#pragma once

#include <stdint.h>

#ifdef HPLFSR_DONT_USE_FAST_INTS
#define HPLFSR_INT_16 uint16_t
#else
#define HPLFSR_INT_16 uint_fast16_t
#endif

#ifdef _MSC_VER
#define HPLFSR_FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define HPLFSR_FORCE_INLINE __attribute__((always_inline))
#else
#define HPLFSR_FORCE_INLINE inline
#endif

template <HPLFSR_INT_16 START_STATE = 0xACE1u, HPLFSR_INT_16 MASK = 0x8000u,
          HPLFSR_INT_16 T1 = 7u,
          HPLFSR_INT_16 T2 = 9u,
          HPLFSR_INT_16 T3 = 13u>
class HPPRFG
{
public:
    HPLFSR_FORCE_INLINE HPLFSR_INT_16 XorShift()
    {
        HPLFSR_INT_16 s = START_STATE;
        unsigned p = 0;
#ifdef HPLFSR_USE_SYNCHRONIZED
        synchronized
        {
#endif
            do
            {
                s = (s ^ (s >> T1)) & MASK;
                s = (s ^ (s >> T2)) & MASK;
                s = (s ^ (s >> T3)) & MASK;
                p++;
            } while (s != START_STATE);

#ifdef HPLFSR_USE_SYNCHRONIZED
        }
#endif

        return s;
    }

    HPLFSR_FORCE_INLINE HPLFSR_INT_16 operator()()
    {
        return XorShift();
    }
};

template <HPLFSR_INT_16 START_STATE = 0xACE1u, HPLFSR_INT_16 MASK = 0x8000u,
          HPLFSR_INT_16 T1 = 7u,
          HPLFSR_INT_16 T2 = 9u,
          HPLFSR_INT_16 T3 = 13u>
class HPPRFG_CT
{
public:
    HPLFSR_INT_16 s = START_STATE;
    do
    {
        s = (s ^ (s >> T1)) & MASK;
        s = (s ^ (s >> T2)) & MASK;
        s = (s ^ (s >> T3)) & MASK;
        p++;
    } while (s != START_STATE);

    HPLFSR_FORCE_INLINE HPLFSR_INT_16 operator()()
    {
        return s;
    }
};