#pragma once


template<typename T>
class Vec_t
{
public:
    T x;
    T y;

    Vec_t()
    {
        x = (T)0;
        y = (T)0;
    }

    Vec_t(T px, T py)
    {
        x = px;
        y = py;
    }
};


typedef Vec_t<int> Vec;
typedef Vec_t<int> VecI;
typedef Vec_t<float> VecF;
