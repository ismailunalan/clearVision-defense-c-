#include "Crypto.h"
#include "GrayscaleImage.h"
// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {

    std::vector<int> LSB_array;
    GrayscaleImage grayscale_image = secret_image.reconstruct();

    int w = grayscale_image.get_width();
    int h = grayscale_image.get_height();
    int totalBit = message_length * 7;

    if (totalBit > w*h) {
        std::cerr << "This image does not have enough pixels." << std::endl;
        exit(1);
    }

    int startingPixel = w * h - totalBit;
    int rowNumber = startingPixel / w;
    int columnNumber = startingPixel % w;

    for (int i = rowNumber; i < h ; i++) {
        for (int j = (i == rowNumber ? columnNumber : 0); j < w ; j++) {
            std::bitset<8> bits(grayscale_image.get_pixel(i, j));
            int lsb = bits[0];
            LSB_array.push_back(lsb);
        }
    }
    return LSB_array;
    // TODO: Your code goes here.
    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    // 2. Calculate the image dimensions.
    // 3. Determine the total bits required based on message length.
    // 4. Ensure the image has enough pixels; if not, throw an error.
    // 5. Calculate the starting pixel from the message_length knowing that
    //    the last LSB to extract is in the last pixel of the image.
    // 6. Extract LSBs from the image pixels and return the result.
}


// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;
    if (LSB_array.size() % 7 != 0) {
        std::cerr << "Array size is not a multiple of 7." << std::endl;
        exit(1);
    }
    for (size_t i = 0; i < LSB_array.size(); i += 7) {
        int ascii_value = 0;
        for (int j = 0; j < 7; ++j) {
            ascii_value = ascii_value * 2 + LSB_array[i+j];
        }
        char character = static_cast<char>(ascii_value);
        message += character;
    }
    return message;
    // TODO: Your code goes here.
    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.
    // 4. Return the resulting message.
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {
    std::vector<int> LSB_array;

    // TODO: Your code goes here.
    for (size_t i = 0; i < message.size(); i++) {
        int ascii_value = message[i];
        std::vector<int> bits(7, 0);
        int x = 0;
        for (int j = 6; j >= 0; j--) {
            x = ascii_value % 2;
            bits[j] = x;
            ascii_value = ascii_value / 2;
        }
        for (int bit : bits) {
            LSB_array.push_back(bit);
        }
    }
    return LSB_array;
    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.
    // 3. Return the array of bits.
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {
    // TODO: Your code goes here.
    int w = image.get_width();
    int h = image.get_height();
    int totalBit = LSB_array.size();

    if (totalBit > w * h) {
        std::cerr << "This image does not have enough pixels." << std::endl;
        exit(1);
    }
    int startingPixel = w * h - totalBit;
    for (int i = 0; i < totalBit; i++) {
        int row = (startingPixel + i) / w;
        int column = (startingPixel + i) % w;
        int pixel_value = image.get_pixel(row, column);

        if (LSB_array[i] == 1) {
            pixel_value |= 1;
        } else {
            pixel_value &= ~1;
        }
        image.set_pixel(row, column, pixel_value);
    }
    SecretImage secret_image(image);
    return secret_image;
    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.
}

