#include <boost/program_options.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
namespace po = boost::program_options;

/** Name of the image file. */
std::string image_filename;

/** Name of the output file. */
std::string output_filename;

/** X coordinate of the initial point of the bubble. */
size_t x_init;

/** Y coordinate of the initial point of the bubble. */
size_t y_init;

/** Font scale.*/
double scale;

/** Font thickness.*/
double thickness;

/** Font face.*/
int font;

/** Text in the bubble.*/
std::string text;

/** Bubble length.*/
size_t length;

/** Bubble width.*/
size_t width;

int main( int argc, char** argv )
{
	
   try {
	  // Parses the command line options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("image_filename", po::value<std::string>(), "set image filename")
            ("x", po::value<size_t>(), "set X coordinate")
            ("y", po::value<size_t>(), "set Y coordinate")
            ("scale", po::value<double>(), "set font scale")
            ("thickness", po::value<int>(), "set font thickness")
            ("font", po::value<int>(), "set font")
            ("output", po::value<std::string>(), "set output image filename")
            ("text", po::value<std::string>(), "set text")
            ("length", po::value<std::string>(), "set bubble length")
            ("width", po::value<std::string>(), "set bubble width")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }
        
        if (vm.count("image_filename"))
			image_filename = vm["image_filename"].as<std::string>();
		else
			{
				cout << "Image filename missing" << endl;
				cout << desc << endl;
				return 0;
			}
        if (vm.count("x"))
			x_init = vm["x"].as<size_t>();
		else
			x_init = 0;
        if (vm.count("y"))
			y_init = vm["y"].as<size_t>();
		else
			y_init = 0;
        if (vm.count("scale"))
			scale = vm["scale"].as<double>();
		else
			scale = 0.5;
        if (vm.count("thickness"))
			thickness = vm["thickness"].as<int>();
		else
			thickness = 1;
		if (vm.count("font"))
			font = vm["font"].as<int>();
		else
			font = CV_FONT_HERSHEY_SIMPLEX;
		if (vm.count("output"))
			output_filename = vm["output"].as<std::string>();
		else
			output_filename = "output.png";
		if (vm.count("text"))
			text = vm["text"].as<std::string>();
		else
			text = "";
        if (vm.count("length"))
			length = vm["length"].as<size_t>();
		else
			length = 200;
        if (vm.count("width"))
			width = vm["width"].as<size_t>();
		else
			width = 70;
		}
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    Mat image;
    image = imread(image_filename.c_str(), CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
	// define a polygon (as a vector of points)

	vector<Point> contour;
	contour.push_back(Point(x_init, y_init));
	contour.push_back(Point(x_init, y_init + 20));
	contour.push_back(Point(x_init - 20, y_init + 20));
	contour.push_back(Point(x_init - 20, y_init + width));
	contour.push_back(Point(x_init + length, y_init + width));
	contour.push_back(Point(x_init + length, y_init + 20));
	contour.push_back(Point(x_init + 20, y_init + 20));

	// create a pointer to the data as an array of points (via a conversion to 
	// a Mat() object)

	const cv::Point *pts = (const cv::Point*) Mat(contour).data;
	int npts = Mat(contour).rows;
	
	// draw the polygon 

	polylines(image, &pts,&npts, 1,
	    		true, 			// draw closed contour (i.e. joint end to start) 
	            Scalar(0,0,0),// colour RGB ordering (here = green) 
	    		1, 		        // line thickness
			    CV_AA, 0);
			    
	fillPoly(image, &pts,&npts, 1, Scalar(255,255,255), 8);
	//CvFont font = fontQt("Times");

    //addText( image, "Hello World !", Point(x_init, y_init + 40), font);
    putText( image, text, Point(x_init, y_init + 40), font, scale,
           Scalar(0, 0, 0), thickness, 8 );
           
    imwrite(output_filename, image);

    //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //imshow( "Display window", image );                   // Show our image inside it.

    //waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
