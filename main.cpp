#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "tracker.h"
#include "kcftracker.hpp"
#include <unistd.h>

#include <cstring>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

    KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);


    //tracker.init( Rect(xMin, yMin, width, height), frame );

    // Get the position of the object for the new frame
    //result = tracker.update(frame);


    std::string video = "pets09s2l1.avi";
    VideoCapture cap(video);

    Mat frame;

    // get bounding box
    cap >> frame;

    //tracker.init( Rect(142.0,157.0,150.0,267.0), frame );

    //Rect roi = Rect(240.0,210.0,60.0,104.0);
    Rect roi2 = Rect(638.0,230.0,56.0,101.0);


    //tracker.init(roi, frame );
    tracker.init(roi2, frame );

    //638.0,230.0,56.0,101.0

    for ( ;; ){
        // get frame from the video
        cap >> frame;

        // stop the program if no more images
        if(frame.rows==0 || frame.cols==0)
          break;

        //update the tracking result
        Rect result = tracker.update(frame);
        cout << result << endl;

        // draw the tracked object
        rectangle( frame, result, Scalar( 255, 0, 0 ), 2, 1 );

        // show image with the tracked object
        imshow("tracker",frame);
        //usleep(100000);

        //quit on ESC button
        if(waitKey(1)==27)break;
      }

}



