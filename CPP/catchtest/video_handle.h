#ifndef VIDEOHANDLE_H
#define VIDEOHANDLE_H

#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

#include "lib.h"

using namespace cv;
using namespace std;

class VideoHandle
{
public:
    VideoHandle(int device = 0);

    void selectImageColor();
    void prehandleImage(Size size);
    void findcenterImage();
    Result generateOutput(Point p1, Point p2);

    void getImage();
    void showImage(const string& winname = "default");

    Mat frame, frame_resize, frame_resize_hsv;
    Mat mask;
    Moments moments;
    int centerx, centery;
    int selectx, selecty;
    bool flag_select;
    Vec3b select_color;
    Vec3b select_color_hsv;
    Mat thresholdlow, thresholdhigh;
private:
    VideoCapture *cap;
    int camerawidth, cameraheight;
};

#endif // VIDEOHANDLE_H