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
constexpr int32_t indexes32[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
constexpr int64_t indexes64[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };



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
template<typename T>
struct m256i {
	__m256i val;


	operator __m256i() const {
		return val;
	}


};
template<typename T>

struct m128i {
	__m128i val;
	operator __m128i() const {
		return val;
	}
};
template<typename T>

struct m512i {
	__m512i val;
	operator __m512i() const {
		return val;
	}
};

#ifdef _WIN32
using m512 = __m512;
using m512d = __m512d;
using m256 = __m256;
using m256d = __m256d;
using m128 = __m128;
using m128d = __m128d;
#else
struct m512 {
	__m512 val;
	operator __m512() const {
		return val;
	}
};
struct m512d {
	__m512d val;
	operator __m512d() const {
		return val;
	}
};
struct m256 {
	__m256 val;
	operator __m256() const {
		return val;
	}
};
struct m256d {
	__m256d val;
	operator __m256d() const {
		return val;
	}
};

struct m128 {
	__m128 val;
	operator __m128() const {
		return val;
	}
};

struct m128d {
	__m128d val;
	operator __m128d() const {
		return val;
	}
};
#endif




using mi256_i64 =  m256i<int64_t>;
using mi256_i32 =  m256i<int32_t>;
using mi256_i16 =  m256i<int16_t>;
using mi256_i8  =  m256i<int8_t>;
using mi256_i64u = m256i<uint64_t>;
using mi256_i32u = m256i<uint32_t>;
using mi256_i16u = m256i<uint16_t>;
using mi256_i8u  = m256i<uint8_t>;

using mi128_i64 =  m128i<int64_t>;
using mi128_i32 = m128i<int32_t>;
using mi128_i16 = m128i<int16_t>;
using mi128_i8 = m128i<int8_t>;
using mi128_i64u = m128i<uint64_t>;
using mi128_i32u = m128i<uint32_t>;
using mi128_i16u = m128i<uint16_t>;
using mi128_i8u = m128i<uint8_t>;

using mi512_i64  = m512i<int64_t>;
using mi512_i32 = m512i<int32_t>;
using mi512_i16 = m512i<int16_t>;
using mi512_i8 = m512i<int8_t>;
using mi512_i64u = m512i<uint64_t>;
using mi512_i32u = m512i<uint32_t>;
using mi512_i16u = m512i<uint16_t>;
using mi512_i8u = m512i<uint8_t>;
#pragma endregion

#pragma region Loads



#ifdef _WIN32
inline m256 mload(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	float _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };
	return _mm256_loadu_ps(_in);
}
inline m256d mload(const double _a, const double _b, const double _c, const double _d) {
	double _in[4] = { _a, _b, _c, _d };

	return _mm256_loadu_pd(_in);
}
inline m256 mload(const float* _in) {
	return _mm256_loadu_ps(_in);
}
inline m256d mload(const double* _in) {
	return _mm256_loadu_pd(_in);
}
#else
inline m256 mload(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	float _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };
	return { _mm256_loadu_ps(_in) };
}
inline m256d mload(const double _a, const double _b, const double _c, const double _d) {
	double _in[4] = { _a, _b, _c, _d };

	return { _mm256_loadu_pd(_in) };
}
inline m256 mload(const float* _in) {
	return { _mm256_loadu_ps(_in) };
}
inline m256d mload(const double* _in) {
	return { _mm256_loadu_pd(_in) };
}
#endif

inline mi256_i64 mload(const int64_t _in[4]) {
	return {_mm256_loadu_epi64(_in) };
}
inline mi256_i32 mload(const int32_t _in[8]) {
	return { _mm256_loadu_epi32(_in) };
}
inline mi256_i16 mload(const int16_t _in[16]) {
	return { _mm256_loadu_epi16(_in) };
}
inline mi256_i8 mload(const int8_t _in[32]) {
	return { _mm256_loadu_epi8(_in) };
}
inline mi256_i64u mload(const uint64_t _in[4]) {
	return { _mm256_loadu_epi64(_in) };
}
inline mi256_i32u mload(const uint32_t _in[8]) {
	return { _mm256_loadu_epi32(_in) };
}
inline mi256_i16u mload(const uint16_t _in[16]) {
	return { _mm256_loadu_epi16(_in) };
}
inline mi256_i8u mload(const uint8_t _in[32]) {
	return { _mm256_loadu_epi8(_in) };
}
#ifdef _WIN32
inline m128  m128load(const float _a, const float _b, const float _c, const float _d) {
	float _in[4] = { _a, _b, _c, _d };

	return _mm_loadu_ps(_in);
}
inline m128 m128load(const float _in[4]) {
	return _mm_loadu_ps(_in);
}
inline m128d m128load(const double _in[2]) {
	return _mm_loadu_pd(_in);
}
#else
inline m128  m128load(const float _a, const float _b, const float _c, const float _d) {
	float _in[4] = { _a, _b, _c, _d };

	return { _mm_loadu_ps(_in) };
}
inline m128 m128load(const float _in[4]) {
	return { _mm_loadu_ps(_in) };
}
inline m128d m128load(const double _in[2]) {
	return { _mm_loadu_pd(_in) };
}
#endif


inline mi128_i64  m128load(const int64_t _in[2]) {
	return { _mm_loadu_epi64(_in) };
}
inline mi128_i32  m128load(const int32_t _in[4]) {
	return { _mm_loadu_epi32(_in) };
}
inline mi128_i16  m128load(const int16_t _in[8]) {
	return { _mm_loadu_epi16(_in) };
}
inline mi128_i8   m128load(const int8_t _in[16]) {
	return { _mm_loadu_epi8(_in) };
}
inline mi128_i64u m128load(const uint64_t _in[2]) {
	return { _mm_loadu_epi64(_in) };
}
inline mi128_i32u m128load(const uint32_t _in[4]) {
	return { _mm_loadu_epi32(_in) };
}
inline mi128_i16u m128load(const uint16_t _in[8]) {
	return { _mm_loadu_epi16(_in) };
}
inline mi128_i8u  m128load(const uint8_t _in[16]) {
	return { _mm_loadu_epi8(_in) };
}

#ifdef _WIN32
inline m512 m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h, const float _i, const float _j, const float _k, const float _l, const float _m, const float _n, const float _o, const float _p) {
	float _in[16] = { _a, _b, _c, _d,_e,  _f, _g, _h, _i, _j,_k,_l,_m,_n,_o,_p };
	return _mm512_loadu_ps(_in);
}
inline m512d m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	double _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };

	return _mm512_loadu_pd(_in);
}
inline m512 m512load(const float* _in) {
	return _mm512_loadu_ps(_in);
}
inline m512d m512load(const double* _in) {
	return _mm512_loadu_pd(_in);
}
#else
inline m512 m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h, const float _i, const float _j, const float _k, const float _l, const float _m, const float _n, const float _o, const float _p) {
	float _in[16] = { _a, _b, _c, _d,_e,  _f, _g, _h, _i, _j,_k,_l,_m,_n,_o,_p };
	return { _mm512_loadu_ps(_in) };
}
inline m512d m512load(const float _a, const float _b, const float _c, const float _d, const float _e, const float _f, const float _g, const float _h) {
	double _in[8] = { _a, _b, _c, _d,_e,  _f, _g, _h };

	return { _mm512_loadu_pd(_in) };
}
inline m512 m512load(const float* _in) {
	return { _mm512_loadu_ps(_in) };
}
inline m512d m512load(const double* _in) {
	return { _mm512_loadu_pd(_in) };
}
#endif

inline mi512_i64  m512load(const int64_t _in[8]) {
	return { _mm512_loadu_epi64(_in) };
}
inline mi512_i32  m512load(const int32_t _in[16]) {
	return { _mm512_loadu_epi32(_in) };
}
inline mi512_i16  m512load(const int16_t _in[32]) {
	return { _mm512_loadu_epi16(_in) };
}
inline mi512_i8   m512load(const int8_t _in[64]) {
	return { _mm512_loadu_epi8(_in) };
}
inline mi512_i64u m512load(const uint64_t _in[8]) {
	return { _mm512_loadu_epi64(_in) };
}
inline mi512_i32u m512load(const uint32_t _in[16]) {
	return { _mm512_loadu_epi32(_in) };
}
inline mi512_i16u m512load(const uint16_t _in[32]) {
	return { _mm512_loadu_epi16(_in) };
}
inline mi512_i8u  m512load(const uint8_t _in[64]) {
	return { _mm512_loadu_epi8(_in) };
}






#pragma endregion



#pragma region sumsaves
float msumsave(m256 in) {
	float temp[8];
	_mm256_storeu_ps(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]);
}

double msumsave(m256d in) {
	double temp[4];
	_mm256_storeu_pd(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3]);
}

int8_t msumsave(mi256_i8 in) {
	int8_t temp[32];
	_mm256_storeu_epi8(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7] + temp[8] + temp[9] + temp[10] + temp[11] + temp[12] + temp[13] + temp[14] + temp[15] + temp[16] + temp[17] + temp[18] + temp[19] + temp[20] + temp[21] + temp[22] + temp[23] + temp[24] + temp[25] + temp[26] + temp[27] + temp[28] + temp[29] + temp[30] + temp[31]);
}

int16_t msumsave(mi256_i16 in) {
	int32_t temp[16];
	_mm256_storeu_epi32(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]+ temp[8] + temp[9] + temp[10] + temp[11] + temp[12] + temp[13] + temp[14] + temp[15]);
}

int32_t msumsave(mi256_i32 in) {
	int32_t temp[8];
	_mm256_storeu_epi32(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]);
}

int64_t msumsave(mi256_i64 in) {
	int64_t temp[4];
	_mm256_storeu_epi64(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3]);
}




float msumsave(m128 in) {
	float temp[4];
	_mm_storeu_ps(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3]);
}

double msumsave(m128d in) {
	double temp[2];
	_mm_storeu_pd(temp, in);
	return (temp[0] + temp[1]);
}

int8_t msumsave(mi128_i8 in) {
	int8_t temp[16];
	_mm_storeu_epi8(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7] + temp[8] + temp[9] + temp[10] + temp[11] + temp[12] + temp[13] + temp[14] + temp[15] );
}

int16_t msumsave(mi128_i16 in) {
	int32_t temp[8];
	_mm_storeu_epi32(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]);
}

int32_t msumsave(mi128_i32 in) {
	int32_t temp[4];
	_mm_storeu_epi32(temp, in);
	return (temp[0] + temp[1] + temp[2] + temp[3]);
}

int64_t msumsave(mi128_i64 in) {
	int64_t temp[2];
	_mm_storeu_epi64(temp, in);
	return (temp[0] + temp[1]);
}
#pragma endregion

#pragma region Sets
#ifdef _WIN32
m128 m128set(float Val) {
	return _mm_set1_ps(Val);
}

m128d m128set(double Val) {
	return _mm_set1_pd(Val);
}

m256 mset(float Val) {
	return _mm256_set1_ps(Val);
}

m256d mset(double Val) {
	return _mm256_set1_pd(Val);
}

m512 m512set(float Val) {
	return _mm512_set1_ps(Val);
}

m512d m512set(double Val) {
	return _mm512_set1_pd(Val);
}

#else

m128 m128set(float Val) {
	return { _mm_set1_ps(Val) };
}

m128d m128set(double Val) {
	return { _mm_set1_pd(Val) };
}

m256 mset(float Val) {
	return { _mm256_set1_ps(Val) };
}

m256d mset(double Val) {
	return { _mm256_set1_pd(Val) };
}


m512 m512set(float Val) {
	return { _mm512_set1_ps(Val) };
}

m512d m512set(double Val) {
	return { _mm512_set1_pd(Val) };
}

#endif

mi128_i64 m128set(int64_t Val) {
	return { _mm_set1_epi64x(Val) };
}

mi128_i32 m128set(int32_t Val) {
	return { _mm_set1_epi32(Val) };
}

mi128_i16 m128set(int16_t Val) {
	return { _mm_set1_epi16(Val) };
}

mi128_i8 m128set(int8_t Val) {
	return { _mm_set1_epi8(Val) };
}

mi128_i64u m128set(uint64_t Val) {
	return { _mm_set1_epi64x(Val) };
}

mi128_i32u m128set(uint32_t Val) {
	return { _mm_set1_epi32(Val) };
}

mi128_i16u m128set(uint16_t Val) {
	return { _mm_set1_epi16(Val) };
}

mi128_i8u m128set(uint8_t Val) {
	return { _mm_set1_epi8(Val) };
}





mi256_i64 mset(int64_t Val) {
	return { _mm256_set1_epi64x(Val) };
}

mi256_i32 mset(int32_t Val) {
	return { _mm256_set1_epi32(Val) };
}

mi256_i16 mset(int16_t Val) {
	return { _mm256_set1_epi16(Val) };
}

mi256_i8 mset(int8_t Val) {
	return { _mm256_set1_epi8(Val) };
}

mi256_i64u mset(uint64_t Val) {
	return { _mm256_set1_epi64x(Val) };
}

mi256_i32u mset(uint32_t Val) {
	return { _mm256_set1_epi32(Val) };
}

mi256_i16u mset(uint16_t Val) {
	return { _mm256_set1_epi16(Val) };
}

mi256_i8u mset(uint8_t Val) {
	return {_mm256_set1_epi8(Val) };
}




mi512_i64 m512set(int64_t Val) {
	return { _mm512_set1_epi64(Val) };
}

mi512_i32 m512set(int32_t Val) {
	return { _mm512_set1_epi32(Val) };
}

mi512_i16 m512set(int16_t Val) {
	return { _mm512_set1_epi16(Val) };
}

mi512_i8 m512set(int8_t Val) {
	return { _mm512_set1_epi8(Val) };
}

mi512_i64u m512set(uint64_t Val) {
	return { _mm512_set1_epi64(Val) };
}

mi512_i32u m512set(uint32_t Val) {
	return { _mm512_set1_epi32(Val) };
}

mi512_i16u m512set(uint16_t Val) {
	return {_mm512_set1_epi16(Val)};
}

mi512_i8u m512set(uint8_t Val) {
	return { _mm512_set1_epi8(Val) };
}

#pragma endregion

#pragma region stores
//will allocate memory and store to allocated memory, returning pointer to the memory
inline float* mstore(const __m512 toStore) {
	float* temp = (float*)malloc(sizeof(float) * 16);
	_mm512_store_ps(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(float* storeTo, const __m512 toStore) {
	_mm512_store_ps(storeTo, toStore);
}


//will allocate memory and store to allocated memory, returning pointer to the memory
inline double* mstore(const __m512d toStore) {
	double* temp = (double*)malloc(sizeof(double) * 8);
	_mm512_store_pd(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(double* storeTo, const __m512d toStore) {
	_mm512_store_pd(storeTo, toStore);
}


//will allocate memory and store to allocated memory, returning pointer to the memory
inline float* mstore(const __m256 toStore) {
	float* temp = (float*)malloc(sizeof(float) * 8);
	_mm256_store_ps(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(float* storeTo,const __m256 toStore) {
	_mm256_store_ps(storeTo, toStore);
}

//will allocate memory and store to allocated memory, returning pointer to the memory
inline double* mstore(const __m256d toStore) {
	double* temp = (double*)malloc(sizeof(double) * 4);
	_mm256_store_pd(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(double* storeTo, const __m256d toStore) {
	_mm256_store_pd(storeTo, toStore);
}


//will allocate memory and store to allocated memory, returning pointer to the memory
inline float* mstore(const __m128 toStore) {
	float* temp = (float*)malloc(sizeof(float) * 4);
	_mm_store_ps(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(float* storeTo, const __m128 toStore) {
	_mm_store_ps(storeTo, toStore);
}

//will allocate memory and store to allocated memory, returning pointer to the memory
inline double* mstore(const __m128d toStore) {
	double* temp = (double*)malloc(sizeof(double) * 2);
	_mm_store_pd(temp, toStore);
	return temp;
}
//will store to preallocated memory
inline void mstore(double* storeTo, const __m128d toStore) {
	_mm_store_pd(storeTo, toStore);
}

inline int64_t* mstore(const mi256_i64 toStore) {
	int64_t* temp = (int64_t*)malloc(sizeof(int64_t) * 2);
	_mm256_storeu_epi64(temp, toStore);
	return temp;
}

inline void mstore(int64_t* storeTo, const mi256_i64 toStore) {
	_mm256_storeu_epi64(storeTo, toStore);
}

inline int32_t* mstore(const mi256_i32 toStore) {
	int32_t* temp = (int32_t*)malloc(sizeof(int32_t) * 2);
	_mm256_storeu_epi32(temp, toStore);
	return temp;
}

inline void mstore(int32_t* storeTo, const mi256_i32 toStore) {
	_mm256_storeu_epi32(storeTo, toStore.val);
}


#pragma endregion
#ifdef _WIN32
#pragma region __m512 operators
m512 operator*(const m512& a, const m512& b) {
	return _mm512_mul_ps(a, b);
}
m512& operator*=(m512& a, const m512& b) {
	a =  _mm512_mul_ps(a, b) ;
	return a;
}
m512 operator/(const m512& a, const m512& b) {
	return _mm512_div_ps(a, b);
}
m512& operator/=(m512& a, const m512& b) {
	a = _mm512_div_ps(a, b);
	return a;
}
m512 operator+(const m512& a, const m512& b) {
	return _mm512_add_ps(a, b);
}
m512& operator+=(m512& a, const m512& b) {
	a = _mm512_add_ps(a, b);
	return a;
}
m512 operator-(const m512& a, const m512& b) {
	return _mm512_sub_ps(a, b);
}
m512& operator-=(m512& a, const m512& b) {
	a = _mm512_sub_ps(a, b);
	return a;
}
m512 operator/(int,const m512& b) {
	return _mm512_rcp14_ps(b);
}
#pragma endregion

#pragma region __m512d operators
m512d operator*(const m512d& a, const m512d& b) {
	return _mm512_mul_pd(a, b);
}
m512d operator*=(m512d& a, const m512d& b) {
	a = _mm512_mul_pd(a, b);
	return a;
}
m512d operator/(const m512d& a, const m512d& b) {
	return _mm512_div_pd(a, b);
}
m512d operator/=(m512d& a, const m512d& b) {
	a = _mm512_div_pd(a, b);
	return a;
}
m512d operator+(const m512d& a, const m512d& b) {
	return _mm512_add_pd(a, b);
}
m512d operator+=(m512d& a, const m512d& b) {
	a = _mm512_add_pd(a, b);
	return a;
}
m512d operator-(const m512d& a, const m512d& b) {
	return _mm512_sub_pd(a, b);
}
m512d operator-=(m512d& a, const m512d& b) {
	a = _mm512_sub_pd(a, b);
	return a;
}
m512d operator/(int, const __m512d& b) {
	return _mm512_rcp14_pd(b);
}
#pragma endregion

#pragma region _m512i operators
mi512_i32 operator*(const mi512_i32& a, const mi512_i32& b) {
	return { _mm512_mullo_epi32(a, b) };
}
mi512_i32 operator+(const mi512_i32& a, const mi512_i32& b) {
	return { _mm512_add_epi32(a, b) };
}
mi512_i32 operator-(const mi512_i32& a, const mi512_i32& b) {
	return { _mm512_sub_epi32(a, b) };
}
mi512_i32 operator/(const mi512_i32& a, const mi512_i32& b) {
	return { _mm512_div_epi32(a, b) };
}


mi512_i64 operator*(const mi512_i64& a, const mi512_i64& b) {
	return { _mm512_mullo_epi64(a, b) };
}
mi512_i64 operator+(const mi512_i64& a, const mi512_i64& b) {
	return { _mm512_add_epi64(a, b) };
}
mi512_i64 operator-(const mi512_i64& a, const mi512_i64& b) {
	return { _mm512_sub_epi64(a, b) };
}
mi512_i64 operator/(const mi512_i64& a, const mi512_i64& b) {
	return { _mm512_div_epi64(a, b) };
}

mi512_i16 operator*(const mi512_i16& a, const mi512_i16& b) {
	return { _mm512_mullo_epi16(a, b) };
}
mi512_i16 operator+(const mi512_i16& a, const mi512_i16& b) {
	return { _mm512_add_epi16(a, b) };
}
mi512_i16 operator-(const mi512_i16& a, const mi512_i16& b) {
	return { _mm512_sub_epi16(a, b) };
}
mi512_i16 operator/(const mi512_i16& a, const mi512_i16& b) {
	return { _mm512_div_epi16(a, b) };
}

mi512_i8 operator+(const mi512_i8& a, const mi512_i8& b) {
	return { _mm512_add_epi8(a, b) };
}
mi512_i8 operator-(const mi512_i8& a, const mi512_i8& b) {
	return { _mm512_sub_epi8(a, b) };
}
mi512_i8 operator/(const mi512_i8& a, const mi512_i8& b) {
	return { _mm512_div_epi8(a, b) };
}
#pragma endregion

#pragma region _m128i operators
mi128_i32 operator*(const mi128_i32& a, const mi128_i32& b) {
	return { _mm_mullo_epi32(a, b) };
}
mi128_i32 operator+(const mi128_i32& a, const mi128_i32& b) {
	return { _mm_add_epi32(a, b) };
}
mi128_i32 operator-(const mi128_i32& a, const mi128_i32& b) {
	return { _mm_sub_epi32(a, b) };
}
mi128_i32 operator/(const mi128_i32& a, const mi128_i32& b) {
	return { _mm_div_epi32(a, b) };
}

mi128_i64 operator*(const mi128_i64& a, const mi128_i64& b) {
	return { _mm_mullo_epi64(a, b) };
}
mi128_i64 operator+(const mi128_i64& a, const mi128_i64& b) {
	return { _mm_add_epi64(a, b) };
}
mi128_i64 operator-(const mi128_i64& a, const mi128_i64& b) {
	return { _mm_sub_epi64(a, b) };
}
mi128_i64 operator/(const mi128_i64& a, const mi128_i64& b) {
	return { _mm_div_epi64(a, b) };
}

mi128_i16 operator*(const mi128_i16& a, const mi128_i16& b) {
	return { _mm_mullo_epi16(a, b) };
}
mi128_i16 operator+(const mi128_i16& a, const mi128_i16& b) {
	return { _mm_add_epi16(a, b) };
}
mi128_i16 operator-(const mi128_i16& a, const mi128_i16& b) {
	return { _mm_sub_epi16(a, b) };
}
mi128_i16 operator/(const mi128_i16& a, const mi128_i16& b) {
	return { _mm_div_epi16(a, b) };
}

mi128_i8 operator+(const mi128_i8& a, const mi128_i8& b) {
	return { _mm_add_epi8(a, b) };
}
mi128_i8 operator-(const mi128_i8& a, const mi128_i8& b) {
	return { _mm_sub_epi8(a, b) };
}
mi128_i8 operator/(const mi128_i8& a, const mi128_i8& b) {
	return { _mm_div_epi8(a, b) };
}
#pragma endregion

#pragma region __m256 operators
m256 operator+ (const m256& a, const m256& b) {
	return _mm256_add_ps(a, b);
}
m256 operator- (const m256& a, const m256& b) {
	return _mm256_sub_ps(a, b);
}
m256 operator* (const m256& a, const m256& b) {
	return _mm256_mul_ps(a, b);
}
m256 operator/ (const m256& a, const m256& b) {
	return _mm256_div_ps(a, b);
}

m256 operator/ (int, const m256& b) {
	return _mm256_rcp_ps(b);
}
#pragma endregion

#pragma region __m256d operators
m256d operator+(const m256d& _a, const m256d& _b) {
	return _mm256_add_pd(_a, _b);
}
m256d operator-(const m256d& _a, const m256d& _b) {
	return _mm256_sub_pd(_a, _b);
}
m256d& operator+=(m256d& _a, const m256d& _b) {
	_a = _mm256_add_pd(_a, _b);
	return _a;
}
m256d operator*(const m256d& _a, const m256d& _b) {
	return _mm256_mul_pd(_a, _b);
}
m256d operator/ (const m256d& a, const m256d& b) {
	return _mm256_div_pd(a, b);
}

#pragma endregion

#pragma region __m128 operators
m128 operator+ (const m128& a, const m128& b) {

	return _mm_add_ps(a, b);
}
m128 operator- (const m128& a, const m128& b) {
	return _mm_sub_ps(a, b);
}
m128 operator* (const m128& a, const m128& b) {
	return _mm_mul_ps(a, b);
}
m128 operator/ (const m128& a, const m128& b) {
	return _mm_div_ps(a, b);
}

m128 operator/ (int, const m128& b) {
	return _mm_rcp_ps(b);
}
#pragma endregion

#pragma region __m128d operators
m128d operator+(const m128d& _a, const m128d& _b) {
	return _mm_add_pd(_a, _b);
}
m128d operator-(const m128d& _a, const m128d& _b) {
	return _mm_sub_pd(_a, _b);
}
m128d& operator+=(m128d& _a, const m128d& _b) {
	_a = _mm_add_pd(_a, _b);
	return _a;
}
m128d operator*(const m128d& _a, const m128d& _b) {
	return _mm_mul_pd(_a, _b);
}
m128d operator/ (const m128d& a, const m128d& b) {
	return _mm_div_pd(a, b);
}
#pragma endregion
#else
#pragma region __m512 operators
m512 operator*(const m512& a, const m512& b) {
	return { _mm512_mul_ps(a, b) };
}

m512 operator/(const m512& a, const m512& b) {
	return { _mm512_div_ps(a, b) };
}

m512 operator+(const m512& a, const m512& b) {
	return{ _mm512_add_ps(a, b) };
}

m512 operator-(const m512& a, const m512& b) {
	return { _mm512_sub_ps(a, b) };
}

m512 operator/(int, const m512& b) {
	return { _mm512_rcp14_ps(b) };
}
#pragma endregion

#pragma region __m512d operators
m512d operator*(const m512d& a, const m512d& b) {
	return { _mm512_mul_pd(a, b) };
}
m512d operator/(const m512d& a, const m512d& b) {
	return { _mm512_div_pd(a, b) };
}
m512d operator+(const m512d& a, const m512d& b) {
	return { _mm512_add_pd(a, b) };
}
m512d operator-(const m512d& a, const m512d& b) {
	return { _mm512_sub_pd(a, b) };
}
m512d operator/(int, const m512d& b) {
	return { _mm512_rcp14_pd(b) };
}
#pragma endregion

#pragma region __m256 operators
m256 operator+ (const m256& a, const m256& b) {
	return { _mm256_add_ps(a, b) };
}
m256 operator- (const m256& a, const m256& b) {
	return { _mm256_sub_ps(a, b) };
}
m256 operator* (const m256& a, const m256& b) {
	return { _mm256_mul_ps(a, b) };
}
m256 operator/ (const m256& a, const m256& b) {
	return { _mm256_div_ps(a, b) };
}

m256 operator/ (int, const m256& b) {
	return { _mm256_rcp_ps(b) };
}
#pragma endregion

#pragma region __m256d operators
m256d operator+(const m256d& _a, const m256d& _b) {
	return { _mm256_add_pd(_a, _b) };
}
m256d operator-(const m256d& _a, const m256d& _b) {
	return { _mm256_sub_pd(_a, _b) };
}
m256d& operator+=(m256d& _a, const m256d& _b) {
	_a = { _mm256_add_pd(_a, _b) };
	return _a;
}
m256d operator*(const m256d& _a, const m256d& _b) {
	return { _mm256_mul_pd(_a, _b) };
}
m256d operator/ (const m256d& a, const m256d& b) {
	return { _mm256_div_pd(a, b) };
}

#pragma endregion

#pragma region __m128 operators
m128 operator+ (const m128& a, const m128& b) {

	return { _mm_add_ps(a, b) };
}
m128 operator- (const m128& a, const m128& b) {
	return { _mm_sub_ps(a, b) };
}
m128 operator* (const m128& a, const m128& b) {
	return { _mm_mul_ps(a, b) };
}
m128 operator/ (const m128& a, const m128& b) {
	return { _mm_div_ps(a, b) };
}

m128 operator/ (int, const m128& b) {
	return { _mm_rcp_ps(b) };
}
#pragma endregion

#pragma region __m128d operators
m128d operator+(const m128d& _a, const m128d& _b) {
	return { _mm_add_pd(_a, _b) };
}
m128d operator-(const m128d& _a, const m128d& _b) {
	return { _mm_sub_pd(_a, _b) };
}
m128d& operator+=(m128d& _a, const m128d& _b) {
	_a = { _mm_add_pd(_a, _b) };
	return _a;
}
m128d operator*(const m128d& _a, const m128d& _b) {
	return { _mm_mul_pd(_a, _b) };
}
m128d operator/ (const m128d& a, const m128d& b) {
	return { _mm_div_pd(a, b) };
}
#pragma endregion

#endif
#pragma region mi256_64 operators
mi256_i64 operator+ (const mi256_i64& a, const mi256_i64& b) {

	return { _mm256_add_epi64(a.val, b.val) };
}
mi256_i64 operator- (const mi256_i64& a, const mi256_i64& b) {
	return { _mm256_sub_epi64(a.val, b.val) };
}
mi256_i64 operator* (const mi256_i64& a, const mi256_i64& b) {
	return { _mm256_mul_epi32(a.val, b.val) };
}
mi256_i64 operator/ (const mi256_i64& a, const mi256_i64& b) {
	return { _mm256_div_epi64(a, b) };
}

#pragma endregion

mi256_i32 operator+ (const mi256_i32& a, const mi256_i32& b) {

	return { _mm256_add_epi32(a, b) };
}

mi256_i32 operator- (const mi256_i32& a, const mi256_i32& b) {
	return { _mm256_sub_epi32(a, b) };
}
mi256_i32 operator* (const mi256_i32& a, const mi256_i32& b) {
	return { _mm256_mullo_epi32(a, b) };
}
mi256_i32 operator/ (const mi256_i32& a, const mi256_i32& b) {
	return { _mm256_div_epi64(a, b) };
}

#pragma region Gathers
m512	  m512gather(float* Val, int32_t offset) {
	mi512_i32 _indexes = m512load(indexes32) * m512set(offset);

	return _mm512_i32gather_ps(_indexes, Val, sizeof(float));
}
m512d	  m512gather(double* Val, int64_t offset) {

	mi512_i64 _indexes = m512load(indexes64) * m512set(offset);
	return _mm512_i64gather_pd(_indexes, Val, sizeof(double));
}
mi512_i32 m512gather(int32_t* Val, int32_t offset) {
	mi512_i32 _indexes = m512load(indexes32) * m512set(offset);
	return { _mm512_i32gather_epi32(_indexes, Val,  sizeof(float)) };
}
mi512_i64 m512gather(int64_t* Val, int64_t offset) {
	mi512_i64 _indexes = m512load(indexes64) * m512set(offset);
	return { _mm512_i64gather_epi64(_indexes, Val,  sizeof(int64_t)) };
}

m256 mgather(float* Val, int32_t offset) {
	mi256_i32 _indexes = mload(indexes32) * mset(offset);
	int32_t test[8];
	mstore(test, _indexes);
	return _mm256_i32gather_ps(Val, _indexes, sizeof(int32_t));
}
m256d mgather(double* Val, int64_t offset) {
	mi256_i64 _indexes = mload(indexes64) * mset(offset);
	return _mm256_i64gather_pd(Val, _indexes, sizeof(int64_t));
}
mi256_i32 mgather(int32_t* Val, int32_t offset) {
	mi256_i32 _indexes = mload(indexes32) * mset(offset);
	return { _mm256_i32gather_epi32(Val, _indexes, sizeof(int32_t)) };
}
mi256_i64 mgather(int64_t* Val, int64_t offset) {
	mi256_i64 _indexes = mload(indexes64) * mset(offset);
	return { _mm256_i64gather_epi64(Val, _indexes, sizeof(int32_t)) };
}
m128 m128gather(float* Val, int32_t offset) {
	mi128_i32 _indexes = m128load(indexes32) * m128set(offset);
	return _mm_i32gather_ps(Val, _indexes, sizeof(int32_t));
}
m128d m128gather(double* Val, int64_t offset) {
	mi128_i64 _indexes = m128load(indexes64) * m128set(offset);
	return _mm_i64gather_pd(Val, _indexes, sizeof(int64_t));
}
mi128_i32 m128gather(int32_t* Val, int32_t offset) {
	mi128_i32 _indexes = m128load(indexes32) * m128set(offset);
	return { _mm_i32gather_epi32(Val, _indexes, sizeof(int32_t)) };
}
mi128_i64 m128gather(int64_t* Val, int64_t offset) {
	mi128_i64 _indexes = m128load(indexes64) * m128set(offset);
	return { _mm_i64gather_epi64(Val, _indexes, sizeof(int32_t)) };
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



template< typename T>
void MulRow(T Multiplier, T* Values, size_t AmmountOfElements) {
	uint32_t intrinsics = GetIntrinsics();

	while (AmmountOfElements > 0) {
		if (intrinsics & INTRIN_AVX_512F && AmmountOfElements >= 64 / sizeof(T)) {
			auto val = m512load(Values);
			auto mult = m512set(Multiplier);
			val = mult * val;
			
			mstore(Values, val);
			Values += 64 / sizeof(T);
			AmmountOfElements -= 64 / sizeof(T);
			continue;
		}
		if (intrinsics & INTRIN_AVX2 && AmmountOfElements >= 32 / sizeof(T)) {
			auto val = mload(Values);
			auto mult = mset(Multiplier);
			val = mult * val;

			mstore(Values, val);
			Values += 32 / sizeof(T);
			AmmountOfElements -= 32 / sizeof(T);
			continue;
		}

		if (intrinsics & INTRIN_AVX && AmmountOfElements >= 16 / sizeof(T)) {
			auto val = m128load(Values);
			auto mult = m128set(Multiplier);
			val = mult * val;

			mstore(Values, val);
			Values += 16 / sizeof(T);
			AmmountOfElements -= 16 / sizeof(T);
			continue;
		}

		for (size_t i = 0; i < AmmountOfElements; i++) {
			Values[i] *= Multiplier;
		}
		return;
	}

	
}


/*todo
operator*=

*/