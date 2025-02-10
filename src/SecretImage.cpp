#include "SecretImage.h"


// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage& image) {
    width = image.get_width();
    height = image.get_height();
    int upperCount = width * (width + 1) / 2;
    int lowerCount = width * (width - 1) / 2;

    upper_triangular = new int[upperCount];
    lower_triangular = new int[lowerCount];

    int upperIndex = 0;
    int lowerIndex = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i <= j) {
                upper_triangular[upperIndex] = image.get_pixel(i, j);
                upperIndex++;
            } else {
                lower_triangular[lowerIndex] = image.get_pixel(i, j);
                lowerIndex++;
            }
        }
    }
    // TODO: Your code goes here.
    // 1. Dynamically allocate the memory for the upper and lower triangular matrices.
    // 2. Fill both matrices with the pixels from the GrayscaleImage.
}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int * upper, int * lower) {
    width = w;
    height = h;
    upper_triangular = upper;
    lower_triangular = lower;

    // TODO: Your code goes here.
    // Since file reading part should dynamically allocate upper and lower matrices.
    // You should simply copy the parameters to instance variables.
}


// Destructor: free the arrays
SecretImage::~SecretImage() {
    delete[] upper_triangular;
    delete[] lower_triangular;
    // TODO: Your code goes here.
    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.
}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const {
    GrayscaleImage image(width, height);
    int upperIndex = 0;
    int lowerIndex = 0;

    for (int i = 0; i < width ; i++) {
        for (int j = 0; j < height ; j++) {
            if (i <= j) {
                image.set_pixel(i,j,upper_triangular[upperIndex]);
                upperIndex++;
            } else {
                image.set_pixel(i,j,lower_triangular[lowerIndex]);
                lowerIndex++;
            }
        }
    }
    // TODO: Your code goes here.

    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage& image) {
    int upperIndex = 0;
    int lowerIndex = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i <= j) {
                upper_triangular[upperIndex] = image.get_pixel(i, j);
                upperIndex++;
            } else {
                lower_triangular[lowerIndex] = image.get_pixel(i, j);
                lowerIndex++;
            }
        }
    }
    // TODO: Your code goes here.
    // Update the lower and upper triangular matrices 
    // based on the GrayscaleImage given as the parameter.
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    file << width << " " << height << std::endl;
    for (int i = 0; i < width * (width + 1) / 2; i++) {
        file << upper_triangular[i];
        if (i != width * (width + 1) / 2 - 1) {
            file << " ";
        }
    }

    file << std::endl;
    for (int i = 0; i < width * (width - 1) / 2; i++) {
        file << lower_triangular[i];
        if (i == width * (width - 1) / 2 - 1) {
            break;
        }
        file << " ";
    }
    file << std::endl;

    // TODO: Your code goes here.
    // 1. Write width and height on the first line, separated by a single space.
    // 2. Write the upper_triangular array to the second line.
    // Ensure that the elements are space-separated. 
    // If there are 15 elements, write them as: "element1 element2 ... element15"
    // 3. Write the lower_triangular array to the third line in a similar manner
    // as the second line.
}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string& filename) {
    std::ifstream file(filename);

    int w = 0;
    int h = 0;
    file >> w >> h;

    int upperSize = w * (w + 1) / 2;
    int lowerSize = w * (w - 1) / 2;

    int* upper = new int[upperSize];
    int* lower = new int[lowerSize];

    for (int i = 0; i < upperSize; i++) {
        file >> upper[i];
    }

    for (int i = 0; i < lowerSize; i++) {
        file >> lower[i];
    }

    file.close();
    // TODO: Your code goes here.
    // 1. Open the file and read width and height from the first line, separated by a space.
    // 2. Calculate the sizes of the upper and lower triangular arrays.
    // 3. Allocate memory for both arrays.
    // 4. Read the upper_triangular array from the second line, space-separated.
    // 5. Read the lower_triangular array from the third line, space-separated.
    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.
    SecretImage secret_image(w, h, upper, lower);
    return secret_image;
}

// Returns a pointer to the upper triangular part of the secret image.
int * SecretImage::get_upper_triangular() const {
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int * SecretImage::get_lower_triangular() const {
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const {
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const {
    return height;
}
