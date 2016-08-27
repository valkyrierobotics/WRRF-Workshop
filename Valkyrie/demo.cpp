// OpenCV includes
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// Standard includes
#include <iostream>
#include <exception>
#include <stdexcept>

// Non standard includes
#include "utils.hpp"

// Camera device id
const int PORT = 0;

// BGR Colors for displaying data
cv::Scalar GREEN (0, 255, 0);
cv::Scalar PURPLE (255, 0, 255);

// Gaussian Blur parameters
int blurKLen = 3;
int blurSigmaX = 25;
int blurSigmaY = 25;

// HSV Color Threshold parameters
int hMin = 135;
int hMax = 180;
int sMin = 0;
int sMax = 100;
int vMin = 80;
int vMax = 100;

// Bounded Rectangle Extraction parameters
int rectInd = 0;

// Constants to specify whether a filter will be used
const int SELECT_OPTIONS = 1;
int applyGaussianBlur = 0;
int applyHSVColorThreshold = 0;
int applyBoundedRectsExtraction = 1;

// Shows a window with trackbars to control the filters on the image
void selectFiltersWindow(cv::Mat& img)
{
    // Create a window with the unique identifier "Select Filters" that will
    // automatically resize to fit the image displayed
    cv::namedWindow("Select Filters", cv::WINDOW_AUTOSIZE);

    // Trackbars accept int variables whose contents will be temporarily
    // modified based off of the trackbar position
    cv::createTrackbar("Gaussian Blur", "Select Filters",
            &applyGaussianBlur, 1);
    cv::createTrackbar("Gaussian Blur", "Select Filters",
            &applyGaussianBlur, SELECT_OPTIONS);
    cv::createTrackbar("HSV Color Threshold", "Select Filters",
            &applyHSVColorThreshold, SELECT_OPTIONS);
    cv::createTrackbar("Bounded Rect Extraction", "Select Filters",
            &applyBoundedRectsExtraction, SELECT_OPTIONS);

    // Show the image at the bottom of the specified window
    cv::imshow("Select Filters Output", img);
}

// Window with parameters to 
void gaussianBlur(cv::Mat& img)
{
	if (applyGaussianBlur)
	{
		cv::namedWindow("Gaussian Blur", CV_WINDOW_AUTOSIZE);

		cv::createTrackbar("Kernel Length", "Gaussian Blur", &blurKLen, 10);
		cv::createTrackbar("Sigma X", "Gaussian Blur", &blurSigmaX, 100);
		cv::createTrackbar("Sigma Y", "Gaussian Blur", &blurSigmaY, 100);

		// Apply the gaussian blur with the current 
        // If kernel size is even, round to nearest upper odd number
        // because kernel sizes can only be of odd lengths
        if ((blurKLen % 2) == 0)
            blurKLen++;
		cv::GaussianBlur(img, img,
                cv::Size(blurKLen, blurKLen), blurSigmaX, blurSigmaY);
		cv::imshow("Gaussian Blur Output", img);
	}
	else
	{
		cv::destroyWindow("Gaussian Blur");	
	}
}

void hsvColorThreshold(cv::Mat& img)
{
    if (applyHSVColorThreshold)
    {
        // Convert the image from BGR to HSV
        cv::cvtColor(img, img, cv::COLOR_BGR2HSV);

        cv::namedWindow("HSV Color Threshold", CV_WINDOW_AUTOSIZE);

        cv::createTrackbar("Hue Min", "HSV Color Threshold", &hMin, 360);
        cv::createTrackbar("Sat Min", "HSV Color Threshold", &sMin, 255);
        cv::createTrackbar("Val Min", "HSV Color Threshold", &sMin, 255);
        cv::createTrackbar("Hue Max", "HSV Color Threshold", &hMax, 360);
        cv::createTrackbar("Sat Max", "HSV Color Threshold", &sMax, 255);
        cv::createTrackbar("Val Max", "HSV Color Threshold", &vMax, 255);

        // Convert to OpenCV [0, 180] from standard [0, 360]
        hMin /= 2;
        hMax /= 2;

        // Convert to OpenCV [0, 255] from standard [0, 100]
        sMin *= (255.0/100);
        sMax *= (255.0/100);
        vMin *= (255.0/100);
        vMax *= (255.0/100);

        // Threshold  the image based off of the minimum and maximum HSV values
        cv::inRange(img, cv::Scalar(hMin, sMin, vMin),
                         cv::Scalar(hMax, sMax, vMax), img);

        // Convert the image back to BGR in order to promote modularity
        cv::cvtColor(img, img, cv::COLOR_GRAY2BGR);

        cv::imshow("HSV Color Threshold Output", img);
    }
    else
    {
        cv::destroyWindow("HSV Color Threshold"); 
    }
}

// Populate the bounded rectangle and contour vectors and 
// return the index of the targetted index
void boundedRectExtraction(cv::Mat& img, 
                           std::vector<cv::RotatedRect>& boundedRects, 
                           std::vector<std::vector<cv::Point> >& contours)
{
    if (applyBoundedRectsExtraction)
    {
        cv::namedWindow("Bounded Rects", cv::WINDOW_AUTOSIZE);

        contours = getContours(img);
        boundedRects = getBoundedRects(contours);

        // Negative number indicates draw all contours
        const int drawAllContours = -1;
        cv::drawContours(img, contours, drawAllContours, GREEN);
        drawBoundedRects(img, boundedRects, PURPLE);
        cv::imshow("Bounded Rects Output", img);

        int size = boundedRects.size();
        if (size < 1)
            size = 1;
        cv::createTrackbar("Index of Rectangle", "Bounded Rects", &rectInd, size);
    }
    else
    {
        cv::destroyWindow("Bounded Rects");
    }
}



int main(int argc, char* argv[])
{
    // Matrix to represent image
    cv::Mat img, unfiltered;

    // Start the camera at the pre defined device id
    cv::VideoCapture camera(PORT);

    // Use a static image instead of opening camera if filename is passed in
    if (argc > 1)
    {
        img = cv::imread(argv[1]);
        // Check if image is not empty
        if (!img.data)
        {
            throw std::runtime_error("Image not captured successfully");
        }
    }
    else
    {
        if (!camera.isOpened())
        {
            throw std::runtime_error("Camera not opened successfully at " + 
                    std::to_string(PORT));
        }
        std::cout << "Opened camera successfully\n";
    }

    // Allow for user to use keys to control the program
    char key = ' ';

    // Local parameters for bounded rectangles and contours
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::RotatedRect> boundedRects;

    while (key != 'q')
    {
        // Extract image from the opened camera instance
        if (argc < 2) camera >> img;
        else img = cv::imread(argv[1]);
        unfiltered = img.clone();

        selectFiltersWindow(img);
        gaussianBlur(img);
        hsvColorThreshold(img);
        boundedRectExtraction(img, boundedRects, contours);

        if (boundedRects.size() > 0 && contours.size() > 0)
        {
            cv::drawContours(unfiltered, contours, rectInd, GREEN);
            // Separate the targeted rectangle from the other rectangles
            std::vector<cv::RotatedRect> targetedRect (1);
            targetedRect[0] = boundedRects[rectInd];
            drawBoundedRects(unfiltered, targetedRect, PURPLE);
        }

        cv::imshow("Final Image", unfiltered);

        // Waits at least a specified number of milliseconds for 
        // a key event from the window
        key = cv::waitKey(5);
    }
    return 0;
}
