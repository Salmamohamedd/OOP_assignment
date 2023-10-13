// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: CS213-2023-20220152-20220377-A1.cpp
// Last Modification Date: 10/10/2023
// Author1 and ID: Salma Mohamed Sarhan => 20220152 => salmasarhan676@gmail.com
// Author2 and ID: Yasmine Sherif Mohamed => 20220377 => yasmine2110@gmail.com
// Teaching Assistant: Not known yet
// Submitted To: Dr Mohamed El-Ramly
// Purpose: Allow user to add filters to an image (will be edited to be more interactive in final version)
// 13 filters done in this version


#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bmplib.h"
#include "unistd.h"
#include <cmath>

using namespace std;
unsigned char image[SIZE][SIZE]; //2D array for grayscale images
unsigned char image2[SIZE][SIZE];//2D array for grayscale images (acts as a second array if needed or a temp array)
int n;
//unsigned char coloured_image[SIZE][SIZE][RGB]; //3D array for colored images

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

void BlackWhite() {
    //if pixel color is closer to black (between 0 and 127), make it fully black.
    //if pixel color is closer to white (between 127 and 255), make it fully white.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void Invert() {
    //this filter takes its invert color by subtracting it from 255
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void Merge() {
    //loading image function is added here to allow loading another image (array image2)
    char image_name2[100];
    cout << "Enter the source image file name of the image you want to be merged with: ";
    cin >> image_name2;

    // add to it .bmp extension and load image
    strcat(image_name2, ".bmp");
    readGSBMP(image_name2, image2);

    //this loop takes the average of pixels in same position from both photos to merge them together
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

void Flip() {
    // Ask user which way he wants to flip the image
    cout << "Do you want to flip it (1) horizontally or (2) vertically? ";
    cin >> n;
    // Handling the error in case n isn't from the proposed options
    while (n <= 0 || n >= 3) {
        cout << "Please enter a valid number\n";
        cout << "Do you want to flip it (1) horizontally or (2) vertically? ";
        cin >> n;
    }
    // Flipping the image horizontally
    if (n == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[i][SIZE - 1 - j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[i][j];
            }
        }
    }
        // Flipping the image vertically
    else if (n == 2) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[SIZE - 1 - i][j];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image2[i][j];
            }
        }
    }
}

void Rotate() {
    // Asking the user for the degree he wants the image rotated by
    cout << "Do you want to rotate by (1) 90 degrees, (2) 180 degrees, (3) 270 degrees? ";
    cin >> n;
    // Handling the error in case n isn't from the proposed options
    while (n <= 0 || n >= 4) {
        cout << "Please enter a valid number\n";
        cout << "Do you want to rotate by (1) 90 degrees, (2) 180 degrees, (3) 270 degrees? ";
        cin >> n;
    }
    // Storing the rotated image in image2 then storing image2 in image
    if (n == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[SIZE - 1 - j][i];
            }
        }
    } else if (n == 2) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
            }
        }
    } else if (n == 3) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[j][SIZE - 1 - i];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void DarkenLighten() {
    cout << "Do you want to (1) Darken the image or (2) Lighten it? ";
    cin >> n;
    // Handling the error in case n isn't from the proposed options
    while (n <= 0 || n >= 3) {
        cout << "Please enter a valid number\n";
        cout << "Do you want to (1) Darken the image or (2) Lighten it? ";
        cin >> n;
    }
    if (n == 1) {
        // Dividing each bitmap by two so it approaches zero and gets more darkened
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] /= 2;
            }
        }
    } else {
        // Adding each bitmap by 50% (while making sure it doesn't exceed 255) so that it approaches white and gets more lightened
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] += (255 - image[i][j]) / 2;
            }
        }
    }
}

void DetectEdges() {
    int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += image[i][j];
        }
    }
    // Getting the average bitmap color
    int avg = sum / (256 * 256);
    // Checking for edges in each bitmap with its neighbor and storing the result in image2
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((image[i][j] > avg && image[i][j + 1] <= avg) || (image[i][j] <= avg && image[i + 1][j] > avg)
                || (image[i][j] <= avg && image[i][j + 1] > avg)
                || (image[i][j] > avg && image[i + 1][j] <= avg) || (image[i][j] > avg && image[i + 1][j + 1] <= avg) ||
                (image[i][j] <= avg && image[i + 1][j + 1] > avg)) {
                image2[i][j] = 0;
            } else {
                image2[i][j] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void Enlarge() {
    cout
            << "Do you want to enlarge (1) top left quarter, (2) top right quarter, (3) bottom left quarter or (4) bottom right quarter? ";
    cin >> n;
    // Handling the error in case n isn't from the proposed options
    while (n <= 0 || n >= 5) {
        cout << "Please enter a valid number\n";
        cout
                << "Do you want to enlarge (1) top left quarter, (2) top right quarter, (3) bottom left quarter or (4) bottom right quarter? ";
        cin >> n;
    }
    // Storing the wanted quarter in image2
    if (n == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[i / 2][j / 2];
            }
        }
    } else if (n == 2) {
        int m = 0;
        for (int i = 0; i < SIZE / 2; i++) {
            int k = 0;
            for (int j = SIZE / 2; j < SIZE; j++) {
                image2[m][k] = image[i][j];
                image2[m + 1][k] = image[i][j];
                image2[m][k + 1] = image[i][j];
                image2[m + 1][k + 1] = image[i][j];
                k += 2;
            }
            m += 2;
        }
    } else if (n == 3) {
        int m = 0;
        for (int i = SIZE / 2; i < SIZE; i++) {
            int k = 0;
            for (int j = 0; j < SIZE / 2; j++) {
                image2[m][k] = image[i][j];
                image2[m + 1][k] = image[i][j];
                image2[m][k + 1] = image[i][j];
                image2[m + 1][k + 1] = image[i][j];
                k += 2;
            }
            m += 2;
        }
    } else {
        int m = 0;
        for (int i = SIZE / 2; i < SIZE; i++) {
            int k = 0;
            for (int j = SIZE / 2; j < SIZE; j++) {
                image2[m][k] = image[i][j];
                image2[m + 1][k] = image[i][j];
                image2[m][k + 1] = image[i][j];
                image2[m + 1][k + 1] = image[i][j];
                k += 2;
            }
            m += 2;
        }
    }
    // Storing image2 in image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}

void Shrink() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;
        }
    }
    cout << "Do you want to shrink the image dimensions to (1) 1/2, (2) 1/3 or (3) 1/4 the original dimensions? ";
    cin >> n;
    while (n <= 0 || n >= 4) {
        cout << "Please enter a valid number\n";
        cout << "Do you want to shrink the image dimensions to (1) 1/2, (2) 1/3 or (3) 1/4 the original dimensions? ";
        cin >> n;
    }
    if (n == 1) {
        // Storing half of the bits for each bitmap
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = image[i * 2][j * 2];
            }
        }
    } else if (n == 2) {
        // Storing third of the bits for each bitmap
        for (int i = 0; i < SIZE / 3; ++i) {
            for (int j = 0; j < SIZE / 3; ++j) {
                image2[i][j] = image[i * 3][j * 3];
            }
        }
    } else {
        // Storing quarter of the bits for each bitmap
        for (int i = 0; i < SIZE / 4; ++i) {
            for (int j = 0; j < SIZE / 4; ++j) {
                image2[i][j] = image[i * 4][j * 4];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void Mirror() {
    cout << "Do you want to mirror the (1) Left 1/2 (2) Lower 1/2 (3) Upper 1/2 or (4) Right 1/2? ";
    cin >> n;
    while (n <= 0 || n >= 5) {
        cout << "Please enter a valid number\n";
        cout << "Do you want to mirror the (1) Left 1/2 (2) Lower 1/2 (3) Upper 1/2 or (4) Right 1/2? ";
        cin >> n;
    }
    // Storing each bit in the opposite direction of it in image
    if (n == 1) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[i][j];
                image[i][SIZE - j - 1] = image2[i][j];
                image[i][j] = image[i][SIZE - j - 1];
            }
        }
    } else if (n == 2) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[SIZE - 1 - i][j];
            }
        }
    } else if (n == 3) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image2[i][j] = image[i][j];
                image[SIZE - 1 - i][j] = image2[i][j];
                image[i][j] = image[SIZE - 1 - i][j];
            }
        }
    } else if (n == 4) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][SIZE - j - 1];
            }
        }
    }
}

void Shuffle() {
    // Storing each quarter of the image in four 2D arrays
    unsigned char quart1[SIZE / 2][SIZE / 2], quart2[SIZE / 2][SIZE / 2], quart3[SIZE / 2][SIZE / 2],
            quart4[SIZE / 2][SIZE / 2];
    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            quart1[i][j] = image[i][j];
        }
    }
    int m = 0, k;
    for (int i = 0; i < SIZE / 2; ++i) {
        k = 0;
        for (int j = SIZE / 2; j < SIZE; ++j) {
            quart2[i][k] = image[i][j];
            k++;
        }
    }
    k = 0;
    for (int i = SIZE / 2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            quart3[m][j] = image[i][j];
        }
        m++;
    }
    m = 0;
    for (int i = SIZE / 2; i < SIZE; ++i) {
        k = 0;
        for (int j = SIZE / 2; j < SIZE; ++j) {
            quart4[m][k] = image[i][j];
            k++;
        }
        m++;
    }
    m = 0, k = 0;
    int a, b, c, d;
    cout
            << "(1) Top Left , (2) Top right , (3) Bottom Left, (4) Bottom Right. Please enter the order you want the image shuffled in: ";
    cin >> a >> b >> c >> d;
    while (a <= 0 || a >= 5 || b <= 0 || b >= 5 || c <= 0 || c >= 5 || d <= 0 || d >= 5) {
        cout << "Please enter valid numbers\n";
        cout
                << "(1) Top Left , (2) Top right , (3) Bottom Left, (4) Bottom Right. Please enter the order you want the image shuffled in: ";
        cin >> n;
    }
    if (a == 1) {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart1[i][j];
            }
        }
    } else if (a == 2) {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart2[i][j];
            }
        }
    } else if (a == 3) {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart3[i][j];
            }
        }
    } else {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart4[i][j];
            }
        }
    }
    if (b == 1) {
        for (int i = 0; i < SIZE / 2; ++i) {
            k = 0;
            for (int j = SIZE; j < SIZE / 2; ++j) {
                image2[i][j] = quart1[m][k];
                k++;
            }
            m++;
        }

    } else if (b == 2) {
        for (int i = 0; i < SIZE / 2; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart2[m][k];
                k++;
            }
            m++;
        }
    } else if (b == 3) {
        for (int i = 0; i < SIZE / 2; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart3[m][k];
                k++;
            }
            m++;
        }
    } else {
        for (int i = 0; i < SIZE / 2; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart4[m][k];
                k++;
            }
            m++;
        }
    }
    m = 0, k = 0;
    if (c == 1) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart1[m][k];
                k++;
            }
            m++;
        }
    } else if (c == 2) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart2[m][k];
                k++;
            }
            m++;
        }
    } else if (c == 3) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart3[m][k];
                k++;
            }
            m++;
        }
    } else {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = 0; j < SIZE / 2; ++j) {
                image2[i][j] = quart4[m][k];
                k++;
            }
            m++;
        }
    }
    m = 0, k = 0;
    if (d == 1) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart1[m][k];
                k++;
            }
            m++;
        }
    } else if (d == 2) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart2[m][k];
                k++;
            }
            m++;
        }
    } else if (d == 3) {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart3[m][k];
                k++;
            }
            m++;
        }
    } else {
        for (int i = SIZE / 2; i < SIZE; ++i) {
            k = 0;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                image2[i][j] = quart4[m][k];
                k++;
            }
            m++;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void Blur() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Each bitmap equals the average of itself plus the neighboring bits (every time you increase the number of neighboring bits, the image gets more blurry)
            image[i][j] = (image[i - 1][j - 1] + image[i - 1][j] + image[i][j - 1]
                           + image[i + 1][j - 1] + image[i + 1][j] + image[i - 1][j + 1]
                           + image[i][j + 1] + image[i + 1][j + 1] + image[i][j]
                           + image[i - 1][j - 2] + image[i][j - 2] + image[i + 1][j - 2]
                           + image[i + 2][j - 2] + image[i + 2][j - 1] + image[i + 2][j]
                           + image[i + 2][j + 1] + image[i - 1][j + 2] + image[i][j + 2]
                           + image[i + 1][j + 2] + image[i + 2][j + 2] + image[i - 2][j - 2]
                           + image[i - 2][j - 1] + image[i - 2][j] + image[i - 2][j + 1]
                           + image[i - 2][j + 2] + image[i - 2][j + 3] + image[i - 1][j + 3]
                           + image[i][j + 3] + image[i + 1][j + 3] + image[i + 2][j + 3]
                           + image[i + 3][j - 2] + image[i + 3][j - 1] + image[i + 3][j]
                           + image[i + 3][j + 1] + image[i + 3][j + 2] + image[i + 3][j + 3]) / 36;
        }
    }
}

void Crop() {
    cout
            << "Enter the X and Y dimensions you would like to crop from and also the length & width of the cropped image\n";
    // "Please note that X + Length must be a number smaller than or equal SIZE
    // Y + Width must be a number smaller than or equal SIZE
    int x, y, len, wid;
    cout << "Enter X: ";
    cin >> x;
    while (x < 0 || x > 255) {
        cout << "Please enter a valid number (between 0 and 255): \n";
        cout << "Enter X: ";
        cin >> x;
    }
    cout << "Enter Y: ";
    cin >> y;
    while (y < 0 || y > 255) {
        cout << "Please enter a valid number (between 0 and 255): \n";
        cout << "Enter Y: ";
        cin >> y;
    }
    cout << "Enter Length: ";
    cin >> len;
    while (x + len > 255) {
        cout << "Please enter a valid number (Length + X should be less than or equal to 255): \n";
        cout << "Enter Length: ";
        cin >> len;
    }
    cout << "Enter Width: ";
    cin >> wid;
    while (y + wid > 255) {
        cout << "Please enter a valid number (Width + Y should be less than or equal to 255): \n";
        cout << "Enter Width: ";
        cin >> wid;
    }
    for (int i = 0; i < SIZE; ++i) {//x->i, y->j
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;
        }
    }
    // Store the cropped image in image2 after filling it with white color
    for (int i = y; i < len + y; ++i) {
        for (int j = x; j < wid + x; ++j) {
            image2[i][j] = image[i][j];
        }
    }
    // store image2 in image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}

void Skew() {
    cout << "Enter the angle you want to skew upon: ";
    double rad;
    cin >> rad;
    rad = (rad * 22) / (180 * 7);
    double s, step;
    double x= (SIZE/(1+(tan(rad))));
    //s = tan(rad) * SIZE;
    s=SIZE-x;
    step = s / SIZE;
    unsigned char img[SIZE][SIZE + int(s)];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            img[i][j] = 255;
            image2[i][j]=255;
        }
    }

    double shrink=SIZE/x;
    shrink=round(shrink);
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE/shrink; ++j) {
//            image2[i][j]=image[i][j*int(shrink)];
//        }
//   }
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE ; ++j) {
//            image[i][j]=image2[i][j];
//        }
//    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/shrink; ++j) {
            img[i][j + int(s)] = image[i][j*int(shrink)];
        }
        s -= step;
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = img[i][j];
        }
    }
}
