#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc < 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
	// define a polygon (as a vector of points)
	// first point is argv[1], argv[2]
	
	size_t x_init = atoi(argv[2]);
	size_t y_init = atoi(argv[3]);

	vector<Point> contour;
	contour.push_back(Point(x_init, y_init));
	contour.push_back(Point(x_init, y_init + 20));
	contour.push_back(Point(x_init - 20, y_init + 20));
	contour.push_back(Point(x_init - 20, y_init + 70));
	contour.push_back(Point(x_init + 200, y_init + 70));
	contour.push_back(Point(x_init + 200, y_init + 20));
	contour.push_back(Point(x_init + 20, y_init + 20));

	// create a pointer to the data as an array of points (via a conversion to 
	// a Mat() object)

	const cv::Point *pts = (const cv::Point*) Mat(contour).data;
	int npts = Mat(contour).rows;

	std::cout << "Number of polygon vertices: " << npts << std::endl;
	
	// draw the polygon 

	polylines(image, &pts,&npts, 1,
	    		true, 			// draw closed contour (i.e. joint end to start) 
	            Scalar(0,0,0),// colour RGB ordering (here = green) 
	    		1, 		        // line thickness
			    CV_AA, 0);
			    
	fillPoly(image, &pts,&npts, 1, Scalar(255,255,255), 8);
	putText( image, "OpenCV forever!", Point(x_init, y_init + 40), CV_FONT_HERSHEY_COMPLEX, 0.5,
           Scalar(0, 0, 0), 0.5, 8 );

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
