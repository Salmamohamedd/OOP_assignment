#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bmplib.h"
#include "unistd.h"
#include <cmath>

using namespace std;
unsigned char imageRGB[SIZE][SIZE][RGB]; //3D array for colored images
unsigned char image[SIZE][SIZE];

void LoadImage();

void Filters();

void BlackWhite();

//void Invert();
//
//void Merge();
//
//void Flip();
//
//void Rotate();
//
//void DarkenLighten();
//
//void DetectEdges();
//
//void Enlarge();
//
//void Shrink();
//
//void Mirror();
//
//void Shuffle();
//
//void Blur();
//
//void Crop();
//
//void Skew();

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
    }
//    else if (c == '2') {
//        Invert();
//    } else if (c == '3') {
//        Merge();
//    } else if (c == '4') {
//        Flip();
//    } else if (c == '5') {
//        DarkenLighten();
//    } else if (c == '6') {
//        Rotate();
//    } else if (c == '7') {
//        DetectEdges();
//    } else if (c == '8') {
//        Enlarge();
//    } else if (c == '9') {
//        Shrink();
//    } else if (c == 'a') {
//        Mirror();
//    } else if (c == 'b') {
//        Shuffle();
//    } else if (c == 'c') {
//        Blur();
//    } else if (c == 'd') {
//        Crop();
//    } else if (c == 'e') {
//        Skew();
//    }
//    while (true) {
//        //adding this loop allows you to edit more than one filter on the same picture
//        Filters();
//        cout << "Input number of the filter you want to use: ";
//        cin >> c;
//        //program stops when you enter 0, you can save image and still make more edits on the same pic till you exit.
//        if (c == '0') {
//            return 0;
//        } else if (c == '1') {
//            BlackWhite();
//        } else if (c == '2') {
//            Invert();
//        } else if (c == '3') {
//            Merge();
//        } else if (c == '4') {
//            Flip();
//        } else if (c == '5') {
//            DarkenLighten();
//        } else if (c == '6') {
//            Rotate();
//        } else if (c == '7') {
//            DetectEdges();
//        } else if (c == '8') {
//            Enlarge();
//        } else if (c == '9') {
//            Shrink();
//        } else if (c == 'a') {
//            Mirror();
//        } else if (c == 'b') {
//            Shuffle();
//        } else if (c == 'c') {
//            Blur();
//        } else if (c == 'd') {
//            Crop();
//        } else if (c == 'e') {
//            Skew();
//        } else if (c == 's') {
//            SaveImage();
//        }
//    }
    SaveImage();
    return 0;
}

void LoadImage() {
    char image_name[100];

    //get the image file name (colored RGB image)
    cout << "Enter the source image file name: ";
    cin >> image_name;

    // add to it .bmp extension and load image
    strcat(image_name, ".bmp");
    readRGBBMP(image_name, imageRGB);
}

void SaveImage() {
    char image_name[100];

    // get the image file name (colored RGB image)
    cout << "Enter the target image file name: ";
    cin >> image_name;

    // add to it .bmp extension and save image
    strcat(image_name, ".bmp");
    writeRGBBMP(image_name, imageRGB);
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

void BlackWhite() {
    int avg, sum = 0;
    //if pixel color is closer to black (between 0 and 127), make it fully black.
    //if pixel color is closer to white (between 127 and 255), make it fully white.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                sum += imageRGB[i][j][k];
            }
        }
    }
    avg = sum / (SIZE * SIZE * RGB);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 0.299 * imageRGB[i][j][0] + 0.587 * imageRGB[i][j][1] + 0.114 * imageRGB[i][j][2];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                imageRGB[i][j][k] = image[i][j];
            }
        }
    }
}
