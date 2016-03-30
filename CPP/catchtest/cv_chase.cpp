/*
using trad method to chase the object
*/
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "lib.h"
#include "car_handle.h"
#include "video_handle.h"

using namespace cv;
using namespace std;

int max_speed = 60;
Result result;
Size re_size(80 ,60);  // first is width

VideoHandle cam(0);
//CarHandle car(0);

int main(int argc, char* argv[])
{
    cam.selectImageColor();
    destroyAllWindows();
    //sleep(5);
    cout << "start now" << endl;

    while(true) {
        cam.getImage();
        cam.prehandleImage(re_size);

        //cam.prehandle_image()
        cam.findcenterImage();

        //detect the glob
        if (cam.moments.m00 != 0) {
            //cv2.line(cam.frame, (cam.centerx,cam.centery), (x_pre, y_pre), (255,0,0),3)
            result = cam.generateOutput(Point(re_size.width/2,re_size.height/2), Point(cam.centerx,cam.centery));
        } else {
            result = Result(result.angle, 0);
        }
        imshow("catch", cam.mask);
        waitKey(1);
        cout << result.angle << " " << result.length << " (" << cam.centerx << "," << cam.centery << ")" << endl;
        /*
        测一下length的大小:(320,0) -> length = 200
        				   (40,0) -> length = 30  speed*=3
    					   (60,0) -> length = 45  speed*=2
        距离小于多少时自动stop？
        ->(120,90) 大约20左右合适
        */
        int speed = result.length*2 + 30;
        if (speed < 60) {
            speed = 0;
        } else {
            speed = (speed - 60) * 2;
        }
        if (speed > max_speed) {
            speed = max_speed;
        }
//        car.sendCmd(speed, -result.angle); //angle is reverse from the vision of the car
    }

    return 0;
}
