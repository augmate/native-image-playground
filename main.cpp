#include <iostream>
#include "cimg-lib/CImg.h"
using namespace cimg_library;

using namespace std;

void convolveTest3x3(unsigned char *src, unsigned char *dst, int width, int height, float *k) {
    int ncm1 = width - 1, nrm1 = height - 1;
    float s = k[0] + k[1] + k[2] + k[3] + k[4] + k[5] + k[6] + k[7] + k[8]; // Sum kernel elements so can gen normalized variables
    float k00 = k[0] / s, k01 = k[1] / s, k02 = k[2] / s, k10 = k[3] / s, k11 = k[4] / s, k12 = k[5] / s, k20 = k[6] / s, k21 = k[7] / s, k22 = k[8] / s;

    for (int i = 1; i < nrm1; i++) {
        unsigned char *r00 = src + (i - 1) * width;
        unsigned char *r01 = r00 + 1;
        unsigned char *r02 = r01 + 1;
        unsigned char *r10 = r00 + width;
        unsigned char *r11 = r10 + 1;
        unsigned char *r12 = r11 + 1;
        unsigned char *r20 = r10 + width;
        unsigned char *r21 = r20 + 1;
        unsigned char *r22 = r21 + 1;
        unsigned char *rOut = dst + i * width + 1;
        for (int j = 1; j < ncm1; j++) {
            *rOut++ = (unsigned char) ((k00 * *r00++) + (k01 * *r01++) + (k02 * *r02++) +
                    (k10 * *r10++) + (k11 * *r11++) + (k12 * *r12++) +
                    (k20 * *r20++) + (k21 * *r21++) + (k22 * *r22++));
        }
    }
}

float sharpenKernel[3][3];

int main() {
    cout << "Opening image.." << endl;
    CImg<unsigned char> image("lena.jpg");


    cout << "Sharpening.." << endl;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            sharpenKernel[x][y] = -1;
        }
    }

    sharpenKernel[1][1] = 9;

    int width = 320;
    int height = 240;
    unsigned char* src = new unsigned char[320 * 240];
    unsigned char* dst = new unsigned char[320 * 240];

    for(int x = 0; x < 320; x ++) {
        for(int y = 0; y < 240; y ++) {
            src[y * 320 + x] = (unsigned char) (x % 2);
        }
    }

    convolveTest3x3(src, dst, width, height, (float*) sharpenKernel);

    return 0;
}