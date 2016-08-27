#include "utils.hpp"

#include <iostream>
std::vector<cv::RotatedRect> getBoundedRects(std::vector< std::vector<cv::Point> >& contours)
{
    std::vector<cv::RotatedRect> boundedRects (contours.size());
    for (size_t i = 0; i < contours.size(); ++i)
    {
        // Get the minimal area bounded rects
        boundedRects[i] = cv::minAreaRect(contours[i]);
    }
    return boundedRects;
}

std::vector<std::vector<cv::Point> > getContours(cv::Mat& img)
{
    std::vector< std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    // Convert img to gray format
    cv::cvtColor(img, img, CV_BGR2GRAY);

    cv::Canny(img, img, 100, 200);

    // Extract the contours from the img and store them in the vector of vector of points
    cv::findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    cv::cvtColor(img, img, CV_GRAY2BGR);
    
    return contours;
}

void putData(cv::Mat& img, double distance, double yaw, double pitch)
{
    char str[30];
    
	sprintf(str, "Distance = %4.2f", distance);
	cv::putText(img, str, cv::Point(10, 430), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.75, cv::Scalar(255, 0, 200), 1, 8, false);
	sprintf(str, "Yaw      = %4.2f", yaw);
	cv::putText(img, str, cv::Point(10, 450), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.75, cv::Scalar(255, 0, 200), 1, 8, false);
	sprintf(str, "Pitch    = %4.2f", pitch);
	cv::putText(img, str, cv::Point(10, 470), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.75, cv::Scalar(255, 0, 200), 1, 8, false);
}

void drawBoundedRects(cv::Mat& img, std::vector<cv::RotatedRect>& boundedRects, cv::Scalar& color)
{
	int thickness = 1;
	int lineType = 0;
	for (size_t i = 0; i < boundedRects.size(); ++i)
	{
        cv::Point2f rectPoints[4];
        boundedRects[i].points(rectPoints);

        for (int p = 0; p < 4; ++p)
            cv::line(img, rectPoints[p], rectPoints[(p+1) % 4], color, thickness, lineType);
    }
}
