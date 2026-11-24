#include <math.h>
#include "fft_complex.h"


fft_complex conv_from_polar(double r, double radians) {
    fft_complex result;
    result.re = r * cos(radians);
    result.im = r * sin(radians);
    return result;
}

fft_complex add(fft_complex left, fft_complex right) {
    fft_complex result;
    result.re = left.re + right.re;
    result.im = left.im + right.im;
    return result;
}

fft_complex multiply(fft_complex left, fft_complex right) {
    fft_complex result;
    result.re = left.re*right.re - left.im*right.im;
    result.im = left.re*right.im + left.im*right.re;
    return result;
}