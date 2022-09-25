#pragma once
#include <immintrin.h>
#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>	
//  Windows
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else

//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int info[4], int InfoType) {
	__cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

#pragma region Intrinsics Defines
#define INTRIN_ALL 						0xFFFFFFFF
#define INTRIN_NONE						0x00000000
#define INTRIN_UPTO_AVX2				0xFF100000
#define INTRIN_UPTO_FMA					0xFF300000

#define INTRIN_MMX						0x10000000
#define INTRIN_SSE						0x20000000
#define INTRIN_SSE2						0x40000000
#define INTRIN_SSE3						0x80000000
#define INTRIN_SSSE3					0x01000000
#define INTRIN_SSE4_1					0x02000000
#define INTRIN_SSE4_2					0x04000000
#define INTRIN_AVX						0x08000000
#define INTRIN_AVX2						0x00100000
#define INTRIN_FMA						0x00200000
#define INTRIN_AVX_512F					0x00400000
#define INTRIN_AVX_512BW				0x00800000
#define INTRIN_AVX_512CD				0x00010000
#define INTRIN_AVX_512DQ				0x00020000
#define INTRIN_AVX_512ER				0x00040000
#define INTRIN_AVX_512IFMA52			0x00080000
#define INTRIN_AVX_512PF				0x00001000
#define INTRIN_AVX_512VL				0x00002000
#define INTRIN_AVX_512VPOPCNTDQ			0x00004000
#define INTRIN_AVX_512_4FMAPS		    0x00008000
#define INTRIN_AVX_512_4VNNIW		    0x00000100
#define INTRIN_AVX_512_BF16				0x00000200
#define INTRIN_AVX_512_BITALG		    0x00000400
#define INTRIN_AVX_512_VBMI				0x00000800
#define INTRIN_AVX_512_VBMI2		    0x00000010
#define INTRIN_AVX_512_VNNI				0x00000020
#define INTRIN_AVX_512_VP2INTERSECT		0x00000040
#define INTRIN_AVX_512_FP16				0x00000080
#define INTRIN_KNC					    0x00000001
#define INTRIN_AMX_BF16					0x00000002
#define INTRIN_AMX_INT8					0x00000004
#define INTRIN_AMX_TILE					0x00000008
#pragma endregion

#pragma region intvectortypes
using mi256_i64 = __m256i;
using mi256_i32 = __m256i;
using mi256_i16 = __m256i;
using mi256_i8  = __m256i;
using mi256_i64u = __m256i;
using mi256_i32u = __m256i;
using mi256_i16u = __m256i;
using mi256_i8u  = __m256i;

using mi128_i64 =  __m128i;
using mi128_i32 =  __m128i;
using mi128_i16 =  __m128i;
using mi128_i8 =   __m128i;
using mi128_i64u = __m128i;
using mi128_i32u = __m128i;
using mi128_i16u = __m128i;
using mi128_i8u =  __m128i;

using mi512_i64  = __m512i;
using mi512_i32  = __m512i;
using mi512_i16  = __m512i;
using mi512_i8   = __m512i;
using mi512_i64u = __m512i;
using mi512_i32u = __m512i;
using mi512_i16u = __m512i;
using mi512_i8u  = __m512i;
#pragma endregion

inline __m256 mload(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	float _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };
	return _mm256_loadu_ps(_in);
}
inline __m256d mload(const double _a, const double _b, const double _c, const double _d) {
	double _in[4] = { _a, _b, _c, _d };

	return _mm256_loadu_pd(_in);
}
inline __m256 mload(const float* _in) {
	return _mm256_loadu_ps(_in);
}
inline __m256d mload(const double* _in) {
	return _mm256_loadu_pd(_in);
}

inline __m512 m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h, const float _i, const float _j, const float _k, const float _l, const float _m, const float _n, const float _o, const float _p) {
	float _in[16] = { _a, _b, _c, _d,_e,  _f, _g, _h, _i, _j,_k,_l,_m,_n,_o,_p };
	return _mm512_loadu_ps(_in);
}
inline __m512d m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	double _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };

	return _mm512_loadu_pd(_in);
}
inline __m512 m512load(const float* _in) {
	return _mm512_loadu_ps(_in);
}
inline __m512d m512load(const double* _in) {
	return _mm512_loadu_pd(_in);
}

inline mi256_i64 mload(const int64_t _in[4]) {
	return _mm256_loadu_epi64(_in);
}
inline mi256_i32 mload(const int32_t _in[8]) {
	return _mm256_loadu_epi32(_in);
}
inline mi256_i16 mload(const int16_t _in[16]) {
	return _mm256_loadu_epi16(_in);
}
inline mi256_i8 mload(const int8_t _in[32]) {
	return _mm256_loadu_epi8(_in);
}

inline mi256_i64u mload(const uint64_t _in[4]) {
	return _mm256_loadu_epi64(_in);
}
inline mi256_i32u mload(const uint32_t _in[8]) {
	return _mm256_loadu_epi32(_in);
}
inline mi256_i16u mload(const uint16_t _in[16]) {
	return _mm256_loadu_epi16(_in);
}
inline mi256_i8u mload(const uint8_t _in[32]) {
	return _mm256_loadu_epi8(_in);
}

inline mi128_i64  m128load(const int64_t _in[2]) {
	return _mm_loadu_epi64(_in);
}
inline mi128_i32  m128load(const int32_t _in[4]) {
	return _mm_loadu_epi32(_in);
}
inline mi128_i16  m128load(const int16_t _in[8]) {
	return _mm_loadu_epi16(_in);
}
inline mi128_i8   m128load(const int8_t _in[16]) {
	return _mm_loadu_epi8(_in);
}
inline mi128_i64u m128load(const uint64_t _in[2]) {
	return _mm_loadu_epi64(_in);
}
inline mi128_i32u m128load(const uint32_t _in[4]) {
	return _mm_loadu_epi32(_in);
}
inline mi128_i16u m128load(const uint16_t _in[8]) {
	return _mm_loadu_epi16(_in);
}
inline mi128_i8u  m128load(const uint8_t _in[16]) {
	return _mm_loadu_epi8(_in);
}

inline mi512_i64  m512load(const int64_t _in[8]) {
	return _mm512_loadu_epi64(_in);
}
inline mi512_i32  m512load(const int32_t _in[16]) {
	return _mm512_loadu_epi32(_in);
}
inline mi512_i16  m512load(const int16_t _in[32]) {
	return _mm512_loadu_epi16(_in);
}
inline mi512_i8   m512load(const int8_t _in[64]) {
	return _mm512_loadu_epi8(_in);
}
inline mi512_i64u m512load(const uint64_t _in[8]) {
	return _mm512_loadu_epi64(_in);
}
inline mi512_i32u m512load(const uint32_t _in[16]) {
	return _mm512_loadu_epi32(_in);
}
inline mi512_i16u m512load(const uint16_t _in[32]) {
	return _mm512_loadu_epi16(_in);
}
inline mi512_i8u  m512load(const uint8_t _in[64]) {
	return _mm512_loadu_epi8(_in);
}



inline __m128  m128load(const float _a, const float _b, const float _c, const float _d) {
	float _in[4] = { _a, _b, _c, _d };

	return _mm_loadu_ps(_in);
}
inline __m128d m128load(const double _in[2]) {
	return _mm_loadu_pd(_in);
}




#pragma region __m256 operators
__m256 operator+ (const __m256& a, const __m256& b) {
	return _mm256_add_ps(a, b);
}
__m256 operator- (const __m256& a, const __m256& b) {
	return _mm256_sub_ps(a, b);
}
__m256 operator* (const __m256& a, const __m256& b) {
	return _mm256_mul_ps(a, b);
}
__m256 operator/ (const __m256& a, const __m256& b) {
	return _mm256_div_ps(a, b);
}

__m256 operator/ (int, const __m256& b) {
	return _mm256_rcp_ps(b);
}
#pragma endregion

#pragma region __m256d operators
__m256d operator+(const __m256d& _a, const __m256d& _b) {
	return _mm256_add_pd(_a, _b);
}
__m256d operator-(const __m256d& _a, const __m256d& _b) {
	return _mm256_sub_pd(_a, _b);
}
__m256d& operator+=(__m256d& _a, const __m256d& _b) {
	_a = _mm256_add_pd(_a, _b);
	return _a;
}
__m256d operator*(const __m256d& _a, const __m256d& _b) {
	return _mm256_mul_pd(_a, _b);
}
__m256d operator/ (const __m256d& a, const __m256d& b) {
	return _mm256_div_pd(a, b);
}

#pragma endregion

#pragma region __m128 operators
__m128 operator+ (const __m128& a, const __m128& b) {

	return _mm_add_ps(a, b);
}
__m128 operator- (const __m128& a, const __m128& b) {
	return _mm_sub_ps(a, b);
}
__m128 operator* (const __m128& a, const __m128& b) {
	return _mm_mul_ps(a, b);
}
__m128 operator/ (const __m128& a, const __m128& b) {
	return _mm_div_ps(a, b);
}

__m128 operator/ (int, const __m128& b) {
	return _mm_rcp_ps(b);
}
#pragma endregion

#pragma region __m128d operators
__m128d operator+(const __m128d& _a, const __m128d& _b) {
	return _mm_add_pd(_a, _b);
}
__m128d operator-(const __m128d& _a, const __m128d& _b) {
	return _mm_sub_pd(_a, _b);
}
__m128d& operator+=(__m128d& _a, const __m128d& _b) {
	_a = _mm_add_pd(_a, _b);
	return _a;
}
__m128d operator*(const __m128d& _a, const __m128d& _b) {
	return _mm_mul_pd(_a, _b);
}
__m128d operator/ (const __m128d& a, const __m128d& b) {
	return _mm_div_pd(a, b);
}
#pragma endregion

#pragma region mi256_64 operators
mi256_i64 operator+ (const mi256_i64& a, const mi256_i64& b) {

	return _mm256_add_epi64(a, b);
}
mi256_i64 operator- (const mi256_i64& a, const mi256_i64& b) {
	return _mm256_sub_epi64(a, b);
}
mi256_i64 operator* (const mi256_i64& a, const mi256_i64& b) {
	return _mm256_mullo_epi64(a, b);
}
mi256_i64 operator/ (const mi256_i64& a, const mi256_i64& b) {
	return _mm256_div_epi64(a, b);
}

#pragma endregion

#pragma region mi128_64 operators
mi128_i64 operator+ (const mi128_i64& a, const mi128_i64& b) {

	return _mm_add_epi64(a, b);
}
mi128_i64 operator- (const mi128_i64& a, const mi128_i64& b) {
	return _mm_sub_epi64(a, b);
}
mi128_i64 operator* (const mi128_i64& a, const mi128_i64& b) {
	return _mm_mullo_epi64(a, b);
}
mi128_i64 operator/ (const mi128_i64& a, const mi128_i64& b) {
	return _mm_div_epi64(a, b);
}

#pragma endregion

#pragma region mi512_64 operators
mi512_i64 operator+ (const mi512_i64& a, const mi512_i64& b) {

	return _mm512_add_epi64(a, b);
}
mi512_i64 operator- (const mi512_i64& a, const mi512_i64& b) {
	return _mm512_sub_epi64(a, b);
}
mi512_i64 operator* (const mi512_i64& a, const mi512_i64& b) {
	return _mm512_mullo_epi64(a, b);
}
mi512_i64 operator/ (const mi512_i64& a, const mi512_i64& b) {
	return _mm512_div_epi64(a, b);
}

#pragma endregion


#pragma region mi256_32 operators
mi256_i32 operator+ (const mi256_i32& a, const mi256_i32& b) {

	return _mm256_add_epi32(a, b);
}
mi256_i32 operator- (const mi256_i32& a, const mi256_i32& b) {
	return _mm256_sub_epi32(a, b);
}
mi256_i32 operator* (const mi256_i32& a, const mi256_i32& b) {
	return _mm256_mullo_epi32(a, b);
}
mi256_i32 operator/ (const mi256_i32& a, const mi256_i32& b) {
	return _mm256_div_epi32(a, b);
}

#pragma endregion

#pragma region mi128_32 operators
mi128_i32 operator+ (const mi128_i32& a, const mi128_i32& b) {

	return _mm_add_epi32(a, b);
}
mi128_i32 operator- (const mi128_i32& a, const mi128_i32& b) {
	return _mm_sub_epi32(a, b);
}
mi128_i32 operator* (const mi128_i32& a, const mi128_i32& b) {
	return _mm_mullo_epi32(a, b);
}
mi128_i32 operator/ (const mi128_i32& a, const mi128_i32& b) {
	return _mm_div_epi32(a, b);
}

#pragma endregion

#pragma region mi512_32 operators
mi512_i32 operator+ (const mi512_i32& a, const mi512_i32& b) {

	return _mm512_add_epi32(a, b);
}
mi512_i32 operator- (const mi512_i32& a, const mi512_i32& b) {
	return _mm512_sub_epi32(a, b);
}
mi512_i32 operator* (const mi512_i32& a, const mi512_i32& b) {
	return _mm512_mullo_epi32(a, b);
}
mi512_i32 operator/ (const mi512_i32& a, const mi512_i32& b) {
	return _mm512_div_epi32(a, b);
}

#pragma endregion

#pragma region mi256_16 operators
mi256_i16 operator+ (const mi256_i16& a, const mi256_i16& b) {

	return _mm256_add_epi16(a, b);
}
mi256_i16 operator- (const mi256_i16& a, const mi256_i16& b) {
	return _mm256_sub_epi16(a, b);
}
mi256_i16 operator* (const mi256_i16& a, const mi256_i16& b) {
	return _mm256_mullo_epi16(a, b);
}
mi256_i16 operator/ (const mi256_i16& a, const mi256_i16& b) {
	return _mm256_div_epi16(a, b);
}

#pragma endregion

#pragma region mi128_16 operators
mi128_i16 operator+ (const mi128_i16& a, const mi128_i16& b) {

	return _mm_add_epi16(a, b);
}
mi128_i16 operator- (const mi128_i16& a, const mi128_i16& b) {
	return _mm_sub_epi16(a, b);
}
mi128_i16 operator* (const mi128_i16& a, const mi128_i16& b) {
	return _mm_mullo_epi16(a, b);
}
mi128_i16 operator/ (const mi128_i16& a, const mi128_i16& b) {
	return _mm_div_epi16(a, b);
}

#pragma endregion

#pragma region mi512_16 operators
mi512_i16 operator+ (const mi512_i16& a, const mi512_i16& b) {

	return _mm512_add_epi16(a, b);
}
mi512_i16 operator- (const mi512_i16& a, const mi512_i16& b) {
	return _mm512_sub_epi16(a, b);
}
mi512_i16 operator* (const mi512_i16& a, const mi512_i16& b) {
	return _mm512_mullo_epi16(a, b);
}
mi512_i16 operator/ (const mi512_i16& a, const mi512_i16& b) {
	return _mm512_div_epi16(a, b);
}

#pragma endregion




#pragma region mi256_64u operators

mi256_i64u operator/ (const mi256_i64u& a, const mi256_i64u& b) {
	return _mm256_div_epu64(a, b);
}

#pragma endregion

#pragma region mi128_64u operators

mi128_i64u operator/ (const mi128_i64u& a, const mi128_i64u& b) {
	return _mm_div_epu64(a, b);
}

#pragma endregion

#pragma region mi512_64u operators

mi512_i64u operator/ (const mi512_i64u& a, const mi512_i64u& b) {
	return _mm512_div_epu64(a, b);
}

#pragma endregion


#pragma region mi256_32u operators

mi256_i32u operator/ (const mi256_i32u& a, const mi256_i32u& b) {
	return _mm256_div_epu32(a, b);
}

#pragma endregion

#pragma region mi128_32u operators

mi128_i32u operator/ (const mi128_i32u& a, const mi128_i32u& b) {
	return _mm_div_epu32(a, b);
}

#pragma endregion

#pragma region mi512_32u operators

mi512_i32u operator/ (const mi512_i32u& a, const mi512_i32u& b) {
	return _mm512_div_epu32(a, b);
}

#pragma endregion


#pragma region mi256_16u operators
mi256_i16u operator+ (const mi256_i16u& a, const mi256_i16u& b) {

	return _mm256_adds_epu16(a, b);
}
mi256_i16u operator- (const mi256_i16u& a, const mi256_i16u& b) {
	return _mm256_subs_epu16(a, b);
}

mi256_i16u operator/ (const mi256_i16u& a, const mi256_i16u& b) {
	return _mm256_div_epu16(a, b);
}

#pragma endregion

#pragma region mi128_16u operators
mi128_i16u operator+ (const mi128_i16u& a, const mi128_i16u& b) {

	return _mm_adds_epu16(a, b);
}
mi128_i16u operator- (const mi128_i16u& a, const mi128_i16u& b) {
	return _mm_subs_epu16(a, b);
}

mi128_i16u operator/ (const mi128_i16u& a, const mi128_i16u& b) {
	return _mm_div_epu16(a, b);
}

#pragma endregion

#pragma region mi512_16u operators
mi512_i16u operator+ (const mi512_i16u& a, const mi512_i16u& b) {

	return _mm512_adds_epu16(a, b);
}
mi512_i16u operator- (const mi512_i16u& a, const mi512_i16u& b) {
	return _mm512_subs_epu16(a, b);
}

mi512_i16u operator/ (const mi512_i16u& a, const mi512_i16u& b) {
	return _mm512_div_epu16(a, b);
}

#pragma endregion

#pragma region fmadd
inline __m256 fmadd(__m256 op1, __m256 op2, __m256 op3) {
	return _mm256_fmadd_ps(op1, op2, op3);
}

inline __m256d fmadd(__m256d op1, __m256d op2, __m256d op3) {
	return _mm256_fmadd_pd(op1, op2, op3);
}

inline __m128 fmadd(__m128 op1, __m128 op2, __m128 op3) {
	return _mm_fmadd_ps(op1, op2, op3);
}

inline __m128d fmadd(__m128d op1, __m128d op2, __m128d op3) {
	return _mm_fmadd_pd(op1, op2, op3);
}

inline __m512 fmadd(__m512 op1, __m512 op2, __m512 op3) {
	return _mm512_fmadd_ps(op1, op2, op3);
}

inline __m512d fmadd(__m512d op1, __m512d op2, __m512d op3) {
	return _mm512_fmadd_pd(op1, op2, op3);
}
#pragma endregion

#pragma region fmsub
inline __m256 fmsub(__m256 op1, __m256 op2, __m256 op3) {
	return _mm256_fmsub_ps(op1, op2, op3);
}

inline __m256d fmsub(__m256d op1, __m256d op2, __m256d op3) {
	return _mm256_fmsub_pd(op1, op2, op3);
}

inline __m128 fmsub(__m128 op1, __m128 op2, __m128 op3) {
	return _mm_fmsub_ps(op1, op2, op3);
}

inline __m128d fmsub(__m128d op1, __m128d op2, __m128d op3) {
	return _mm_fmsub_pd(op1, op2, op3);
}

inline __m512 fmsub(__m512 op1, __m512 op2, __m512 op3) {
	return _mm512_fmsub_ps(op1, op2, op3);
}

inline __m512d fmsub(__m512d op1, __m512d op2, __m512d op3) {
	return _mm512_fmsub_pd(op1, op2, op3);
}
#pragma endregion

#pragma region fmaddsub
inline __m256 fmaddsub(__m256 op1, __m256 op2, __m256 op3) {
	return _mm256_fmaddsub_ps(op1, op2, op3);
}

inline __m256d fmaddsub(__m256d op1, __m256d op2, __m256d op3) {
	return _mm256_fmaddsub_pd(op1, op2, op3);
}

inline __m128 fmaddsub(__m128 op1, __m128 op2, __m128 op3) {
	return _mm_fmaddsub_ps(op1, op2, op3);
}

inline __m128d fmaddsub(__m128d op1, __m128d op2, __m128d op3) {
	return _mm_fmaddsub_pd(op1, op2, op3);
}

inline __m512 fmaddsub(__m512 op1, __m512 op2, __m512 op3) {
	return _mm512_fmaddsub_ps(op1, op2, op3);
}

inline __m512d fmaddsub(__m512d op1, __m512d op2, __m512d op3) {
	return _mm512_fmaddsub_pd(op1, op2, op3);
}
#pragma endregion

#pragma region casts

__m256 CastToM256(__m256d toCast) {
	return _mm256_castpd_ps(toCast);
}

#pragma endregion


#pragma region Relation operators
__m256 operator< (__m256 LeftOperand, __m256 RightOperand) {
	return _mm256_cmp_ps(LeftOperand, RightOperand, _CMP_LT_OQ);
}

__m128 operator< (__m128 LeftOperand, __m128 RightOperand) {
	return _mm_cmp_ps(LeftOperand, RightOperand, _CMP_LT_OQ);
}

__m256 operator> (__m256 LeftOperand, __m256 RightOperand) {
	return _mm256_cmp_ps(LeftOperand, RightOperand, _CMP_GT_OQ);
}

__m128 operator> (__m128 LeftOperand, __m128 RightOperand) {
	return _mm_cmp_ps(LeftOperand, RightOperand, _CMP_GT_OQ);
}

__m256 operator<= (__m256 LeftOperand, __m256 RightOperand) {
	return _mm256_cmp_ps(LeftOperand, RightOperand, _CMP_LE_OQ);
}

__m128 operator<= (__m128 LeftOperand, __m128 RightOperand) {
	return _mm_cmp_ps(LeftOperand, RightOperand, _CMP_LE_OQ);
}

__m256 operator>= (__m256 LeftOperand, __m256 RightOperand) {
	return _mm256_cmp_ps(LeftOperand, RightOperand, _CMP_GE_OQ);
}

__m128 operator>= (__m128 LeftOperand, __m128 RightOperand) {
	return _mm_cmp_ps(LeftOperand, RightOperand, _CMP_GE_OQ);
}
__m128 operator== (__m128 LeftOperand, __m128 RightOperand) {
	return _mm_cmp_ps(LeftOperand, RightOperand, _CMP_EQ_OQ);
}
__m256 operator== (__m256 LeftOperand, __m256 RightOperand) {
	return _mm256_cmp_ps(LeftOperand, RightOperand, _CMP_EQ_OQ);
}

#pragma endregion


#pragma region abs
mi256_i8 abs(mi256_i8 Num) {
	return _mm256_abs_epi8(Num);
}
mi256_i16 abs(mi256_i16 Num) {
	return _mm256_abs_epi16(Num);
}
mi256_i32 abs(mi256_i32 Num) {
	return _mm256_abs_epi32(Num);
}
mi256_i64 abs(mi256_i64 Num) {
	return _mm256_abs_epi64(Num);
}

mi128_i8 abs(mi128_i8 Num) {
	return _mm_abs_epi8(Num);
}
mi128_i16 abs(mi128_i16 Num) {
	return _mm_abs_epi16(Num);
}
mi128_i32 abs(mi128_i32 Num) {
	return _mm_abs_epi32(Num);
}
mi128_i64 abs(mi128_i64 Num) {
	return _mm_abs_epi64(Num);
}

mi512_i8 abs(mi512_i8 Num) {
	return _mm512_abs_epi8(Num);
}
mi512_i16 abs(mi512_i16 Num) {
	return _mm512_abs_epi16(Num);
}
mi512_i32 abs(mi512_i32 Num) {
	return _mm512_abs_epi32(Num);
}
mi512_i64 abs(mi512_i64 Num) {
	return _mm512_abs_epi64(Num);
}

__m256 abs(__m256 Num) {
	return _mm256_and_ps(Num, _mm256_castsi256_ps(_mm256_set1_epi32(0x7FFFFFFF)));
}
__m128 abs(__m128 Num) {
	return _mm_and_ps(Num, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
}

__m512 abs(__m512 Num) {
	return _mm512_and_ps(Num, _mm512_castsi512_ps(_mm512_set1_epi32(0x7FFFFFFF)));
}

__m256d abs(__m256d Num) {
	return _mm256_and_pd(Num, _mm256_castsi256_pd(_mm256_set1_epi32(0x7FFFFFFFFFFFFFFF)));
}
__m128d abs(__m128d Num) {
	return _mm_and_pd(Num, _mm_castsi128_pd(_mm_set1_epi32(0x7FFFFFFFFFFFFFFF)));
}

__m512d abs(__m512d Num) {
	return _mm512_and_pd(Num, _mm512_castsi512_pd(_mm512_set1_epi32(0x7FFFFFFFFFFFFFFF)));
}

#pragma endregion

uint32_t GetIntrinsics() {
	static uint32_t AlreadyHaveASolution = 0;
	uint32_t Result = INTRIN_NONE;

	if (AlreadyHaveASolution)return AlreadyHaveASolution;

	int info[4];
	cpuid(info, 0);
	int nIds = info[0];

	cpuid(info, 0x80000000);
	unsigned nExIds = info[0];

	//  Detect Features
	if (nIds >= 0x00000001) {
		cpuid(info, 0x00000001);
		if((info[3] & ((int)1 << 23)) != 0) Result |= INTRIN_MMX;
		if((info[3] & ((int)1 << 25)) != 0) Result |= INTRIN_SSE;
		if((info[3] & ((int)1 << 26)) != 0) Result |= INTRIN_SSE2;
		if ((info[2] & ((int)1 << 0)) != 0) Result |= INTRIN_SSE3;



		if((info[2] & ((int)1 << 9) ) != 0) Result |= INTRIN_SSSE3;
		if((info[2] & ((int)1 << 19)) != 0) Result |= INTRIN_SSE4_1;
		if((info[2] & ((int)1 << 20)) != 0) Result |= INTRIN_SSE4_2;

		if((info[2] & ((int)1 << 12)) != 0) Result |= INTRIN_FMA;

	}
	if (nIds >= 0x00000007) {
		cpuid(info, 0x00000007);
		if((info[1] & ((int)1 << 5)) != 0) Result |= INTRIN_AVX2;

		bool osUsesXSAVE_XRSTORE = info[2] & (1 << 27) || false;
		
		if (osUsesXSAVE_XRSTORE) {
			unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
			if((xcrFeatureMask & 0xe6) != 0xe6)goto skp;
		}
		if((info[1] & ((int)1 << 16)) != 0) Result |= INTRIN_AVX_512F	;
		if((info[1] & ((int)1 << 28)) != 0) Result |= INTRIN_AVX_512CD	;
		if((info[1] & ((int)1 << 26)) != 0) Result |= INTRIN_AVX_512PF	;
		if((info[1] & ((int)1 << 27)) != 0) Result |= INTRIN_AVX_512ER	;
		if((info[1] & ((int)1 << 31)) != 0) Result |= INTRIN_AVX_512VL	;
		if((info[1] & ((int)1 << 30)) != 0) Result |= INTRIN_AVX_512BW	;
		if((info[1] & ((int)1 << 17)) != 0) Result |= INTRIN_AVX_512DQ	;
		if((info[1] & ((int)1 << 21)) != 0) Result |= INTRIN_AVX_512IFMA52;
		if((info[2] & ((int)1 << 1) ) != 0) Result |= INTRIN_AVX_512_VBMI;
	}
	skp:

	bool avxSupported = false;


	bool osUsesXSAVE_XRSTORE = info[2] & (1 << 27) || false;
	bool AVXSupport = ((info[2] & ((int)1 << 28)) != 0);

	if (osUsesXSAVE_XRSTORE && AVXSupport) {
		unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
		avxSupported = (xcrFeatureMask & 0x6) == 0x6;
	}
	if (avxSupported)Result |= INTRIN_AVX;

	AlreadyHaveASolution = Result;
	return Result;
}
