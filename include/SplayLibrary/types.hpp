#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>


namespace spl
{
    template<typename ElementType, uint8_t N, typename AliasType> class _vec;
    template<typename ElementType> struct _vec2;
    template<typename ElementType> struct _vec3;
    template<typename ElementType> struct _vec4;
    typedef _vec2<float> vec2;
    typedef _vec3<float> vec3;
    typedef _vec4<float> vec4;
    typedef _vec2<int32_t> ivec2;
    typedef _vec3<int32_t> ivec3;
    typedef _vec4<int32_t> ivec4;
    typedef _vec2<uint32_t> uvec2;
    typedef _vec3<uint32_t> uvec3;
    typedef _vec4<uint32_t> uvec4;
    typedef _vec2<uint32_t> bvec2;
    typedef _vec3<uint32_t> bvec3;
    typedef _vec4<uint32_t> bvec4;
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType> struct _mat;
    typedef _mat<float, 2, 2, _vec2<float>, _vec2<float>> mat2;
    typedef _mat<float, 3, 2, _vec3<float>, _vec2<float>> mat2x3;
    typedef _mat<float, 4, 2, _vec4<float>, _vec2<float>> mat2x4;
    typedef _mat<float, 2, 3, _vec2<float>, _vec3<float>> mat3x2;
    typedef _mat<float, 3, 3, _vec3<float>, _vec3<float>> mat3;
    typedef _mat<float, 4, 3, _vec4<float>, _vec3<float>> mat3x4;
    typedef _mat<float, 2, 4, _vec2<float>, _vec4<float>> mat4x2;
    typedef _mat<float, 3, 4, _vec3<float>, _vec4<float>> mat4x3;
    typedef _mat<float, 4, 4, _vec4<float>, _vec4<float>> mat4;
}
