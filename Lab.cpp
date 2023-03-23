#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;

// Error return values
int FILE_ERROR = -1;

// Declare input/output images
Mat inputImage, outputImage;


void updateBinaryThresholdValue(int newThresholdValue, void*) {

    // Perform thresholding
    threshold(inputImage, outputImage, newThresholdValue, 255, THRESH_BINARY);

    // Show new image
    imshow("Image Thresholding", outputImage);
}


int main(int argc, char **argv) {

    // Check that file name has been given through command-line argument
    if (argc < 2) {
        cerr << "Error. Wrong file input." << endl;
        return FILE_ERROR;
    }

    // Get input image file path
    string imagePath = argv[1];

    // Load input image file
    inputImage = imread(imagePath, IMREAD_UNCHANGED);
    if (inputImage.empty()) {
        cerr << "Error. Failed to load image file." << endl;
        return FILE_ERROR; 
    }


    // Convert image to 8-bit greyscale
    cvtColor(inputImage, inputImage, COLOR_BGR2GRAY, 0);

    // Perform thresholding
    int thresholdValue = threshold(inputImage, outputImage, 0, 255, THRESH_OTSU);

    // Save OTSU Thresholded image
    string outputImagePath = imagePath.substr(0, imagePath.size() - 4) + "_OTSU.png";
    imwrite(outputImagePath, outputImage);


    // Create a window and display text instructions
    namedWindow("Image Thresholding", WINDOW_AUTOSIZE);
    cout << "Press 's' to save an image and 'ESC' to quit." << endl;

    // Add a trackbar for threshold value to the window (from 0 to 255 included)
    createTrackbar("Threshold val", "Image Thresholding", &thresholdValue, 255, updateBinaryThresholdValue);
    
    // Show OTSU thresholded image
    imshow("Image Thresholding", outputImage);


    // Implement saving and dynamic tresholding
    char key;

    // While "ESC" is not pressed
    while (key != 27) {
        key = waitKey(0);

        // Save image if "s" key is press
        if (key == 's') {

            // Get image path
            thresholdValue = getTrackbarPos("Threshold val", "Image Thresholding");
            outputImagePath = imagePath.substr(0, imagePath.size() - 4) + "_threshold_" + to_string(thresholdValue) + ".png";
            // Save image to path
            imwrite(outputImagePath, outputImage);
        }

    }

    return 0;

}

