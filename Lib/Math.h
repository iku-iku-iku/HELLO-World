//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

namespace math {
    const float pi = 3.141593;

    inline float Deg2Rad(float Deg) { return Deg * pi / 180; }

    inline float Rad2Deg(float Rad) { return 180 * Rad / pi; }

    template<typename T>
    inline T Clamp(T value, const T &minValue, const T &maxValue) {
        if (value > maxValue) { value = maxValue; }
        else if (value < minValue) { value = minValue; }
        return value;
    }
};
