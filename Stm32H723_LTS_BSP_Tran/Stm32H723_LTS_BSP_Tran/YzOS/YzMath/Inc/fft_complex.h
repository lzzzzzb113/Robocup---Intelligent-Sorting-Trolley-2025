#ifndef FFT_COMPLEX_H
#define FFT_COMPLEX_H
typedef struct fft_complex_t {
    double re;
    double im;
} fft_complex;

fft_complex conv_from_polar(double r, double radians);
fft_complex add(fft_complex left, fft_complex right);
fft_complex multiply(fft_complex left, fft_complex right);
#endif // FFT_COMPLEX_H