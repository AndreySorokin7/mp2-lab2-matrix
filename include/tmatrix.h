﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_MATRIX_SIZE)
            throw out_of_range("cant_create_too_large_matrix");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("cant_create_too_large_vector");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        if (this == &v) {
            throw out_of_range("copied_vector_is_equal_to_source_one");
        }
        else {
            if (v.pMem == nullptr) {
                sz = 0;
                pMem = nullptr;
            }
            else {
                sz = v.sz;
                pMem = new T[sz];
                std::copy(v.pMem, v.pMem + sz, pMem);
            }
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr) {
            delete[] pMem;
            sz = 0;
        }
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (*this == v) {
            throw "Error";
        }
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            if (pMem == nullptr) {
                sz = 0;
                pMem = nullptr;
            }
            else {
                sz = v.sz;
                pMem = new T[sz];
                std::copy(v.pMem, v.pMem + sz, pMem);
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            if (pMem != nullptr) {
                delete[] pMem;
            }
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;

        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (pMem == nullptr) {
            throw "Error";
        }
        if ((ind < 0) || (ind >= sz)) {
            throw "Error";
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (pMem == nullptr) {
            throw "Error";
        }
        if ((ind < 0) || (ind >= sz)) {
            throw "Error";
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return true;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i])
                return true;
        }
        return false;

    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] += val;
        }
        return a;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] -= val;
        }
        return a;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] *= val;
        }
        return a;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "Error Size";
        }
        TDynamicVector a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = this->pMem[i] + v.pMem[i];
        }
        return a;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) {
            throw "Error Size";
        }
        TDynamicVector a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = this->pMem[i] - v.pMem[i];
        }
        return a;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) {
            throw "Error Size";
        }
        T sum = 0;
        for (int i = 0; i < sz; i++) {
            sum += this->pMem[i] * v.pMem[i];
        }
        return sum;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz >= pow(2.0, 32.0) + 1)
            throw out_of_range("cant_create_too_large_matrix");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i])
                return false;
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] * val;
        }
        return a;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz) {
            throw "Error Size";
        }
        TDynamicVector a(v);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] * v.pMem[i];
        }
        return a;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw "Error Size";
        }
        TDynamicMatrix a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] + m.pMem[i];
        }
        return a;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw "Error Size";
        }
        TDynamicMatrix a(*this);
        for (int i = 0; i < sz; i++) {
            a.pMem[i] = pMem[i] - m.pMem[i];
        }
        return a;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) {
            throw "Error Size";
        }
        TDynamicMatrix trn(m);
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                swap(trn.pMem[i][j], trn.pMem[j][i]);
            }
        }
        TDynamicMatrix a(*this);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                a.pMem[i][j] = pMem[i] * trn.pMem[j];
            }
        }
        return a;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n'; // требуется оператор<< для типа T
        return ostr;
    }
};

#endif
