#include <boost/program_options.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int getHue(int red, int green, int blue) {

    float _min = std::min(std::min(red, green), blue);
    float _max = std::max(std::max(red, green), blue);

    float hue = 0.0;
    if (_max == red) {
        hue = (green - blue) / (_max - _min);

    } else if (_max == green) {
        hue = 2.0 + (blue - red) / (_max - _min);

    } else {
        hue = 4.0 + (red - green) / (_max - _min);
    }

    hue = hue * 60;
    if (hue < 0) hue = hue + 360;

    return round(hue);
}

bool isColorHueAnalysis(int red, int green, int blue, int hue_param_1, int hue_param_2)
{
	float hue = getHue(red, green, blue);
	// if (hue > 221 and hue < 240 and blue > red + green)
	// if ((hue > hue_param_1 or hue < hue_param_2) and red > blue + green)
	if ((hue > hue_param_1 or hue < hue_param_2) and red * 1.3 > blue + green)
	//if (hue > hue_param_1 or hue < hue_param_2)
		return true;
	return false;
}

int main( int argc, const char** argv )
{
	// int hue_param_1 = 350;
	// int hue_param_2 = 10;
	int hue_param_1 = 350;
	int hue_param_2 = 10;
   VideoCapture cap(0); // open the default camera
   if(!cap.isOpened()) // check if we succeeded
     return -1;

   for(;;)
   {
     Mat frame, image;
     cap >> frame;
     imshow("webcam", frame);
     frame.copyTo(image);
     CV_Assert(image.depth() == CV_8U);
     {
    	 MatIterator_<Vec3b> it, end;
    	 for( it = image.begin<Vec3b>(), end = image.end<Vec3b>(); it != end; ++it)
    	 {
    		 int r = (*it)[0]; int g = (*it)[1]; int b = (*it)[2];
    		 if (isColorHueAnalysis(b, g, r, hue_param_1, hue_param_2))
    		 {
    			 (*it)[0] = 255; (*it)[1] = 255; (*it)[2] = 255;
    		 }
    		 else
    		 {
    			 (*it)[0] = 0; (*it)[1] = 0; (*it)[2] = 0;
    		 }
    	 }
     }
     imshow("red", image);
     if(waitKey(30) >= 0) break;
    }
}


