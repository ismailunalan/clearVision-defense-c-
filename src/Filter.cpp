#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {

    GrayscaleImage copy_image = image;

    int width = image.get_width();
    int height = image.get_height();
    int halfKernel = kernelSize / 2;

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int total = 0;
            for (int k = -halfKernel; k <= halfKernel; k++ ) {
                for (int l = -halfKernel; l <= halfKernel; l++) {
                    total += i+k < 0 || i+k >= height || j+l < 0 || j+l >= width ? 0 : copy_image.get_pixel(i+k,j+l);
                }
            }
            image.set_pixel(i,j,(total/(kernelSize*kernelSize)));
        }
    }
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {

    GrayscaleImage copyImage = image;

    int width = image.get_width();
    int height = image.get_height();
    int halfKernel = kernelSize / 2;
    double sum = 0;
    double** kernel = new double*[kernelSize];

    for (int i = 0; i < kernelSize; i++) {
        kernel[i] = new double[kernelSize];
    }

    for (int i = -halfKernel; i <= halfKernel; i++) {
        for (int j = -halfKernel; j <= halfKernel; j++) {
            double exp = -(i * i + j * j) / (2 * sigma * sigma);
            kernel[i + halfKernel][j + halfKernel] = (1 / (2 * M_PI * sigma * sigma)) * std::exp(exp);
            sum += kernel[i + halfKernel][j + halfKernel];
        }
    }

    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            kernel[i][j] /= sum;
        }
    }

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double weightedSum = 0.0;
            double totalWeight = 0.0;

            for (int k = -halfKernel; k <= halfKernel; k++ ) {
                for (int l = -halfKernel; l <= halfKernel; l++) {
                    int x = i + k;
                    int y = j + l;

                    double pixelValue = x >= 0 && x < height && y >= 0 && y < width ? copyImage.get_pixel(x, y) : 0 ;
                    double weight = kernel[k + halfKernel][l + halfKernel];
                    weightedSum += pixelValue * weight;
                    totalWeight += weight;

                }
            }
            image.set_pixel(i, j, weightedSum / totalWeight);
        }
    }
    for (int i = 0; i < kernelSize; i++) {
        delete[] kernel[i];
    }
    delete[] kernel;

    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {

    GrayscaleImage copyImage = image;
    apply_gaussian_smoothing(image,kernelSize,1);

    for(int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            int newValue =static_cast<int>(copyImage.get_pixel(i, j) + (amount * (copyImage.get_pixel(i, j) - image.get_pixel(i, j))));
            newValue > 255 ? newValue = 255 : newValue < 0 ? newValue = 0 : newValue = newValue;
            image.set_pixel(i,j,newValue);
        }
    }
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
}
