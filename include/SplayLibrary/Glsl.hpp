#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
    template<typename ElementType, uint8_t N, typename AliasType>
    class _vec
    {
        ElementType& operator[](uint8_t i);
        const ElementType& operator[](uint8_t i) const;

        AliasType& operator+=(const _vec<ElementType, N, AliasType>& v);
        AliasType& operator-=(const _vec<ElementType, N, AliasType>& v);
        AliasType& operator*=(const _vec<ElementType, N, AliasType>& v);
        AliasType& operator/=(const _vec<ElementType, N, AliasType>& v);

        AliasType& operator+=(ElementType x);
        AliasType& operator-=(ElementType x);
        AliasType& operator*=(ElementType x);
        AliasType& operator/=(ElementType x);
    };

    template<typename ElementType, typename AliasType>
    AliasType cross(const _vec<ElementType, 3, AliasType>& u, const _vec<ElementType, 3, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    ElementType dot(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    ElementType length(const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    ElementType distance(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType normalize(const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType faceforward(const _vec<ElementType, N, AliasType>& n, const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& nRef);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType reflect(const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& n);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType refract(const _vec<ElementType, N, AliasType>& i, const _vec<ElementType, N, AliasType>& n, ElementType eta);

    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator+(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator-(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator*(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator/(const _vec<ElementType, N, AliasType>& u, const _vec<ElementType, N, AliasType>& v);

    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator+(const _vec<ElementType, N, AliasType>& u, ElementType x);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator-(const _vec<ElementType, N, AliasType>& u, ElementType x);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator*(const _vec<ElementType, N, AliasType>& u, ElementType x);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator/(const _vec<ElementType, N, AliasType>& u, ElementType x);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator+(ElementType x, const _vec<ElementType, N, AliasType>& u);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator-(ElementType x, const _vec<ElementType, N, AliasType>& u);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator*(ElementType x, const _vec<ElementType, N, AliasType>& u);
    template<typename ElementType, uint8_t N, typename AliasType>
    AliasType operator/(ElementType x, const _vec<ElementType, N, AliasType>& u);

    template<typename ElementType>
    struct _vec2 : _vec<ElementType, 2, _vec2<ElementType>>
    {
        _vec2() = default;
        _vec2(ElementType value);
        _vec2(ElementType xValue, ElementType yValue);
        _vec2(std::initializer_list<ElementType> tab);
        _vec2(const _vec<ElementType, 2, _vec2<ElementType>>& v);

        ElementType x, y;
    };

    template<typename ElementType>
    struct _vec3 : _vec<ElementType, 3, _vec3<ElementType>>
    {
        _vec3() = default;
        _vec3(ElementType value);
        _vec3(ElementType xValue, ElementType yValue, ElementType zValue);
        _vec3(std::initializer_list<ElementType> tab);
        _vec3(const _vec<ElementType, 3, _vec3<ElementType>>& v);
        _vec3(const _vec2<ElementType>& v, ElementType zValue);
        _vec3(ElementType xValue, const _vec2<ElementType>& v);

        ElementType x, y, z;
    };

    template<typename ElementType>
    struct _vec4 : _vec<ElementType, 4, _vec4<ElementType>>
    {
        _vec4() = default;
        _vec4(ElementType value);
        _vec4(ElementType xValue, ElementType yValue, ElementType zValue, ElementType wValue);
        _vec4(std::initializer_list<ElementType> tab);
        _vec4(const _vec<ElementType, 4, _vec4<ElementType>>& v);
        _vec4(const _vec2<ElementType>& v, ElementType zValue, ElementType wValue);
        _vec4(ElementType xValue, const _vec2<ElementType>& v, ElementType wValue);
        _vec4(ElementType xValue, ElementType yValue, const _vec2<ElementType>& v);
        _vec4(const _vec2<ElementType>& u, const _vec2<ElementType>& v);
        _vec4(const _vec3<ElementType>& v, ElementType wValue);
        _vec4(ElementType xValue, const _vec3<ElementType>& v);

        ElementType x, y, z, w;
    };


    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    struct _mat
    {
        public:

            _mat() = default;
            _mat(ElementType diagValue);
            _mat(std::initializer_list<ElementType> diag);
            _mat(std::initializer_list<ColumnType> columns);

            ColumnType& operator[](uint8_t i);
            const ColumnType& operator[](uint8_t i) const;

            _mat<ElementType, M, N, ColumnType, RowType>& operator+=(const _mat<ElementType, M, N, ColumnType, RowType>& M);
            _mat<ElementType, M, N, ColumnType, RowType>& operator-=(const _mat<ElementType, M, N, ColumnType, RowType>& M);
            _mat<ElementType, M, N, ColumnType, RowType>& operator/=(const _mat<ElementType, M, N, ColumnType, RowType>& M);

            _mat<ElementType, M, N, ColumnType, RowType>& operator+=(ElementType x);
            _mat<ElementType, M, N, ColumnType, RowType>& operator-=(ElementType x);
            _mat<ElementType, M, N, ColumnType, RowType>& operator/=(ElementType x);
            _mat<ElementType, M, N, ColumnType, RowType>& operator*=(ElementType x);

        private:

            ElementType data[M*N];
    };

    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, N, M, RowType, ColumnType> transpose(const _mat<ElementType, M, N, ColumnType, RowType>& A);

    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator+(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator-(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B);
    template<typename ElementType, uint8_t M, uint8_t N, uint8_t P, typename ColumnType, typename CommonType, typename RowType>
    _mat<ElementType, M, P, ColumnType, RowType> operator*(const _mat<ElementType, M, N, ColumnType, CommonType>& A, const _mat<ElementType, N, P, CommonType, RowType>& B);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator/(const _mat<ElementType, M, N, ColumnType, RowType>& A, const _mat<ElementType, M, N, ColumnType, RowType>& B);

    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator+(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator-(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator*(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator/(const _mat<ElementType, M, N, ColumnType, RowType>& A, ElementType x);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator+(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator-(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator*(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    _mat<ElementType, M, N, ColumnType, RowType> operator/(ElementType x, const _mat<ElementType, M, N, ColumnType, RowType>& A);

    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    ColumnType operator*(const _mat<ElementType, M, N, ColumnType, RowType>& A, const RowType& v);
    template<typename ElementType, uint8_t M, uint8_t N, typename ColumnType, typename RowType>
    RowType operator*(const ColumnType& v, const _mat<ElementType, M, N, ColumnType, RowType>& A);
}

#include <SplayLibrary/GlslT.hpp>
