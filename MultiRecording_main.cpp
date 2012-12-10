#pragma once
#include <stdio.h>
#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <Utils.h>
#include <KinectSensor.h>
#include <ctype.h>
#include "XnCppWrapper.h"

using namespace std;
using namespace cv;
using namespace xn;

const int NUM_SENSORS = 3;

int main()
{
	char* paths[NUM_SENSORS];
	//paths[0] = "d:/Emilio/Calibration/Calib_21/kinect0_calib.oni";
	//paths[1] = "d:/Emilio/Calibration/Calib_21/kinect1_calib.oni";
	//paths[2] = "d:/Emilio/Calibration/Calib_21/kinect2_calib.oni";

	paths[0] = "d:/Emilio/Tracking/DataSet/s_2pers_occl/kinect0_calib.oni";
	paths[1] = "d:/Emilio/Tracking/DataSet/s_2pers_occl/kinect1_calib.oni";
	paths[2] = "d:/Emilio/Tracking/DataSet/s_2pers_occl/kinect2_calib.oni";

	//char* incoming[NUM_SENSORS];
	//incoming[0] = "d:/kinect0.oni";
	//incoming[1] = "d:/kinect1.oni";
	//incoming[2] = "d:/kinect2.oni";

	char* titles[NUM_SENSORS];
	titles[0] = "Image 0";
	titles[1] = "Image 1";
	titles[2] = "Image 2";

	KinectSensor kinects[NUM_SENSORS];
	Recorder records[NUM_SENSORS];

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		kinects[i].initDevice(i,1,true);
		kinects[i].startDevice();
		kinects[i].createRecorder(&(records[i]), paths[i]);
	}

	Mat images[NUM_SENSORS];
	for (int i = 0; i < NUM_SENSORS; i++)
		images[i] = Mat(XN_VGA_Y_RES, XN_VGA_X_RES, CV_8UC3);

	bool bShouldStop = false;
	while (!bShouldStop)
	{
		for (int i = 0; i < NUM_SENSORS; i++)
			kinects[i].waitAndUpdate();

		for (int i = 0; i < NUM_SENSORS; i++)
		{
			kinects[i].getRGBImage(images[i]);
			imshow(titles[i], images[i]);
		}

		bShouldStop = 27 == waitKey(1);

		for (int i = 0; i < NUM_SENSORS; i++)
		{
				records[i].Record();
		}
	}

	for (int i = 0; i < NUM_SENSORS; i++)
	{
		kinects[i].releaseRecorder(&records[i]);
		kinects[i].stopDevice();
		kinects[i].shutDown();
	}
	return 0;
}