#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"
#include "unistd.h"

using namespace std;
unsigned char image[SIZE][SIZE]; //2D array for grayscale images
unsigned char image2[SIZE][SIZE];//2D array for grayscale images (acts as a second array if needed or a temp array)
int n;

void LoadImage();

void Filters();

void BlackWhite();

void Invert();

void Merge();

void Flip();

void Rotate();

void DarkenLighten();

void DetectEdges();

void Enlarge();

void Shrink();

void Mirror();

void Shuffle();

void Blur();

void Crop();

void Skew();

void SaveImage();
int main() {
    LoadImage();
    Filters();
    cout << "Input number of the filter you want to use: ";
    char c;
    cin >> c;
    if (c == '0') {
        return 0;
    } else if (c == '1') {
        BlackWhite();
    } else if (c == '2') {
        Invert();
    } else if (c == '3') {
        Merge();
    } else if (c == '4') {
        Flip();
    } else if (c == '5') {
        DarkenLighten();
    } else if (c == '6') {
        Rotate();
    } else if (c == '7') {
        DetectEdges();
    } else if (c == '8') {
        Enlarge();
    } else if (c == '9') {
        Shrink();
    } else if (c == 'a') {
        Mirror();
    } else if (c == 'b') {
        Shuffle();
    } else if (c == 'c') {
        Blur();
    } else if (c == 'd') {
        Crop();
    } else if (c == 'e') {
        Skew();
    }


    SaveImage();
    return 0;
}

void LoadImage() {
    char image_name[100];

    //get the image file name (gray scale image)
    cout << "Enter the source image file name: ";
    cin >> image_name;

    // add to it .bmp extension and load image
    strcat(image_name, ".bmp");
    readGSBMP(image_name, image);
}

void SaveImage() {
    char image_name[100];

    // get the image file name (gray scale image)
    cout << "Enter the target image file name: ";
    cin >> image_name;

    // add to it .bmp extension and save image
    strcat(image_name, ".bmp");
    writeGSBMP(image_name, image);
}

void Filters() {
    cout << "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter\n"
            "4- Flip Image\n"
            "5- Darken and Lighten Image\n"
            "6- Rotate Image\n"
            "7- Detect Image Edges\n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror 1/2 Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "d- Crop Image\n"
            "e- Skew Image Right\n"
            "f- Skew Image Up\n"
            "s- Save the image to a file\n"
            "0- Exit\n";
}
