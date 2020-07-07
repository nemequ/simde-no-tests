/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2020      Evan Nemerson <evan@nemerson.com>
 *   2020      Sean Maher <seanptmaher@gmail.com>
 */

#if !defined(SIMDE_ARM_NEON_QADD_H)
#define SIMDE_ARM_NEON_QADD_H

#include "types.h"

#include "add.h"
#include "movl.h"
#include "qmovn.h"
#include "combine.h"
#include "get_low.h"
#include "get_high.h"

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_int8x8_t
simde_vqadd_s8(simde_int8x8_t a, simde_int8x8_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_s8(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_s16(simde_vaddq_s16(simde_vmovl_s8(a), simde_vmovl_s8(b)));
  #else
    simde_int8x8_private
      r_,
      a_ = simde_int8x8_to_private(a),
      b_ = simde_int8x8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovnh_s16(HEDLEY_STATIC_CAST(int16_t, a_.values[i]) + HEDLEY_STATIC_CAST(int16_t, b_.values[i]));
    }

    return simde_int8x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_s8
  #define vqadd_s8(a, b) simde_vqadd_s8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int16x4_t
simde_vqadd_s16(simde_int16x4_t a, simde_int16x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_s16(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_s32(simde_vaddq_s32(simde_vmovl_s16(a), simde_vmovl_s16(b)));
  #else
    simde_int16x4_private
      r_,
      a_ = simde_int16x4_to_private(a),
      b_ = simde_int16x4_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovns_s32(HEDLEY_STATIC_CAST(int32_t, a_.values[i]) + HEDLEY_STATIC_CAST(int32_t, b_.values[i]));
    }
    return simde_int16x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_s16
  #define vqadd_s16(a, b) simde_vqadd_s16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int32x2_t
simde_vqadd_s32(simde_int32x2_t a, simde_int32x2_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_s32(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_s64(simde_vaddq_s64(simde_vmovl_s32(a), simde_vmovl_s32(b)));
  #else
    simde_int32x2_private
      r_,
      a_ = simde_int32x2_to_private(a),
      b_ = simde_int32x2_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovnd_s64(HEDLEY_STATIC_CAST(int64_t, a_.values[i]) + HEDLEY_STATIC_CAST(int64_t, b_.values[i]));
    }

    return simde_int32x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_s32
  #define vqadd_s32(a, b) simde_vqadd_s32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int64x1_t
simde_vqadd_s64(simde_int64x1_t a, simde_int64x1_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_s64(a, b);
  #else
    simde_int64x1_private
      r_,
      a_ = simde_int64x1_to_private(a),
      b_ = simde_int64x1_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      if (a_.values[i] > 0 && b_.values[i] > 0) {
        r_.values[i] = (a_.values[i] > (INT64_MAX - b_.values[i])) ? INT64_MAX : a_.values[i] + b_.values[i];
      } else if (a_.values[i] < 0 && b_.values[i] < 0) {
        r_.values[i] = (a_.values[i] < (INT64_MIN - b_.values[i])) ? INT64_MIN : a_.values[i] + b_.values[i];
      } else {
        r_.values[i] = a_.values[i] + b_.values[i];
      }
    }
    return simde_int64x1_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_s64
  #define vqadd_s64(a, b) simde_vqadd_s64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint8x8_t
simde_vqadd_u8(simde_uint8x8_t a, simde_uint8x8_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_u8(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_u16(simde_vaddq_u16(simde_vmovl_u8(a), simde_vmovl_u8(b)));
  #else
    simde_uint8x8_private
      r_,
      a_ = simde_uint8x8_to_private(a),
      b_ = simde_uint8x8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT8_MAX - b_.values[i]) ? UINT8_MAX : a_.values[i] + b_.values[i];
    }
    return simde_uint8x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_u8
  #define vqadd_u8(a, b) simde_vqadd_u8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint16x4_t
simde_vqadd_u16(simde_uint16x4_t a, simde_uint16x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_u16(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_u32(simde_vaddq_u32(simde_vmovl_u16(a), simde_vmovl_u16(b)));
  #else
    simde_uint16x4_private
      r_,
      a_ = simde_uint16x4_to_private(a),
      b_ = simde_uint16x4_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT16_MAX - b_.values[i]) ? UINT16_MAX : a_.values[i] + b_.values[i];
    }
    return simde_uint16x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_u16
  #define vqadd_u16(a, b) simde_vqadd_u16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint32x2_t
simde_vqadd_u32(simde_uint32x2_t a, simde_uint32x2_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_u32(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vqmovn_u64(simde_vaddq_u64(simde_vmovl_u32(a), simde_vmovl_u32(b)));
  #else
    simde_uint32x2_private
      r_,
      a_ = simde_uint32x2_to_private(a),
      b_ = simde_uint32x2_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > (UINT32_MAX - b_.values[i])) ? UINT32_MAX : a_.values[i] + b_.values[i];
    }
    return simde_uint32x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_u32
  #define vqadd_u32(a, b) simde_vqadd_u32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint64x1_t
simde_vqadd_u64(simde_uint64x1_t a, simde_uint64x1_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqadd_u64(a, b);
  #else
    simde_uint64x1_private
      r_,
      a_ = simde_uint64x1_to_private(a),
      b_ = simde_uint64x1_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT64_MAX - b_.values[i]) ? UINT64_MAX : a_.values[i] + b_.values[i];
    }
    return simde_uint64x1_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqadd_u64
  #define vqadd_u64(a, b) simde_vqadd_u64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int8x16_t
simde_vqaddq_s8(simde_int8x16_t a, simde_int8x16_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_s8(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i8x16_add_saturate(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_s8(simde_vqadd_s8(simde_vget_low_s8(a), simde_vget_low_s8(b)), simde_vqadd_s8(simde_vget_high_s8(a), simde_vget_high_s8(b)));
  #else
    simde_int8x16_private
      r_,
      a_ = simde_int8x16_to_private(a),
      b_ = simde_int8x16_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovnh_s16(HEDLEY_STATIC_CAST(int16_t, a_.values[i]) + HEDLEY_STATIC_CAST(int16_t, b_.values[i]));
    }

    return simde_int8x16_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_s8
  #define vqaddq_s8(a, b) simde_vqaddq_s8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int16x8_t
simde_vqaddq_s16(simde_int16x8_t a, simde_int16x8_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_s16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_i16x8_add_saturate(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_s16(simde_vqadd_s16(simde_vget_low_s16(a), simde_vget_low_s16(b)), simde_vqadd_s16(simde_vget_high_s16(a), simde_vget_high_s16(b)));
  #else
    simde_int16x8_private
      r_,
      a_ = simde_int16x8_to_private(a),
      b_ = simde_int16x8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovns_s32(HEDLEY_STATIC_CAST(int32_t, a_.values[i]) + HEDLEY_STATIC_CAST(int32_t, b_.values[i]));
    }

    return simde_int16x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_s16
  #define vqaddq_s16(a, b) simde_vqaddq_s16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int32x4_t
simde_vqaddq_s32(simde_int32x4_t a, simde_int32x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_s32(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_s32(simde_vqadd_s32(simde_vget_low_s32(a), simde_vget_low_s32(b)), simde_vqadd_s32(simde_vget_high_s32(a), simde_vget_high_s32(b)));
  #else
    simde_int32x4_private
      r_,
      a_ = simde_int32x4_to_private(a),
      b_ = simde_int32x4_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = simde_vqmovnd_s64(HEDLEY_STATIC_CAST(int64_t, a_.values[i]) + HEDLEY_STATIC_CAST(int64_t, b_.values[i]));
    }

    return simde_int32x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_s32
  #define vqaddq_s32(a, b) simde_vqaddq_s32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_int64x2_t
simde_vqaddq_s64(simde_int64x2_t a, simde_int64x2_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_s64(a, b);
  #else
    simde_int64x2_private
      r_,
      a_ = simde_int64x2_to_private(a),
      b_ = simde_int64x2_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      if (a_.values[i] > 0 && b_.values[i] > 0) {
        r_.values[i] = (a_.values[i] > (INT64_MAX - b_.values[i])) ? INT64_MAX : a_.values[i] + b_.values[i];
      } else if (a_.values[i] < 0 && b_.values[i] < 0) {
        r_.values[i] = (a_.values[i] < (INT64_MIN - b_.values[i])) ? INT64_MIN : a_.values[i] + b_.values[i];
      } else {
        r_.values[i] = a_.values[i] + b_.values[i];
      }
    }
    return simde_int64x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_s64
  #define vqaddq_s64(a, b) simde_vqaddq_s64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint8x16_t
simde_vqaddq_u8(simde_uint8x16_t a, simde_uint8x16_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_u8(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_u8x16_add_saturate(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_u8(simde_vqadd_u8(simde_vget_low_u8(a), simde_vget_low_u8(b)), simde_vqadd_u8(simde_vget_high_u8(a), simde_vget_high_u8(b)));
  #else
    simde_uint8x16_private
      r_,
      a_ = simde_uint8x16_to_private(a),
      b_ = simde_uint8x16_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT8_MAX - b_.values[i]) ? UINT8_MAX : a_.values[i] + b_.values[i];
    }

    return simde_uint8x16_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_u8
  #define vqaddq_u8(a, b) simde_vqaddq_u8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint16x8_t
simde_vqaddq_u16(simde_uint16x8_t a, simde_uint16x8_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_u16(a, b);
  #elif defined(SIMDE_WASM_SIMD128_NATIVE)
    return wasm_u16x8_add_saturate(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_u16(simde_vqadd_u16(simde_vget_low_u16(a), simde_vget_low_u16(b)), simde_vqadd_u16(simde_vget_high_u16(a), simde_vget_high_u16(b)));
  #else
    simde_uint16x8_private
      r_,
      a_ = simde_uint16x8_to_private(a),
      b_ = simde_uint16x8_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT16_MAX - b_.values[i]) ? UINT16_MAX : a_.values[i] + b_.values[i];
    }

    return simde_uint16x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_u16
  #define vqaddq_u16(a, b) simde_vqaddq_u16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint32x4_t
simde_vqaddq_u32(simde_uint32x4_t a, simde_uint32x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_u32(a, b);
  #elif SIMDE_NATURAL_VECTOR_SIZE > 0
    return simde_vcombine_u32(simde_vqadd_u32(simde_vget_low_u32(a), simde_vget_low_u32(b)), simde_vqadd_u32(simde_vget_high_u32(a), simde_vget_high_u32(b)));
  #else
    simde_uint32x4_private
      r_,
      a_ = simde_uint32x4_to_private(a),
      b_ = simde_uint32x4_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT32_MAX - b_.values[i]) ? UINT32_MAX : a_.values[i] + b_.values[i];
    }

    return simde_uint32x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_u32
  #define vqaddq_u32(a, b) simde_vqaddq_u32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint64x2_t
simde_vqaddq_u64(simde_uint64x2_t a, simde_uint64x2_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vqaddq_u64(a, b);
  #else
    simde_uint64x2_private
      r_,
      a_ = simde_uint64x2_to_private(a),
      b_ = simde_uint64x2_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.values) / sizeof(r_.values[0])) ; i++) {
      r_.values[i] = (a_.values[i] > UINT64_MAX - b_.values[i]) ? UINT64_MAX : a_.values[i] + b_.values[i];
    }

    return simde_uint64x2_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vqaddq_u64
  #define vqaddq_u64(a, b) simde_vqaddq_u64((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_QADD_H) */
