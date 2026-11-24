
#ifndef FFT_H
#define FFT_H
#include "fft_complex.h"

fft_complex* FFT_CooleyTukey(fft_complex* x, int N, int N1, int N2);
fft_complex* FFT_GoodThomas(fft_complex* x, int N, int N1, int N2);
fft_complex* DFT_naive(fft_complex* x, int N);
#endif