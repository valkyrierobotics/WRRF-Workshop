#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

// Standard image sizes, hardcode them for this demo
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

std::vector<cv::RotatedRect> getBoundedRects(std::vector< std::vector<cv::Point> >& contours);
std::vector<std::vector<cv::Point> > getContours(cv::Mat& img);
void putData(cv::Mat& img, double distance, double yaw, double pitch);
void drawBoundedRects(cv::Mat& img, std::vector<cv::RotatedRect>& boundedRects, cv::Scalar& color);


#endif // UTILS_HPP
