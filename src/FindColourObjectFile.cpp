#include <boost/program_options.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
namespace po = boost::program_options;

/** Name of the image1 file. */
std::string image1_filename;

/** Name of the image2 file. */
std::string image2_filename;

/** Name of the output file. */
std::string output_filename;

/// Global Variables
Mat src, hsvsrc, huesrc;
Mat target, hsvtarget, huetarget;
int bins = 25;

/**
 * @function Hist_and_Backproj
 * @brief Callback to Trackbar
 */
void Hist_and_Backproj(int, void* )
{
  MatND hist;
  int histSize = MAX( bins, 2 );
  float hue_range[] = { 0, 180 };
  const float* ranges = { hue_range };

  /// Get the Histogram and normalize it
  calcHist( &huesrc, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
  normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

  /// Get Backprojection
  MatND backproj;
  calcBackProject( &huetarget, 1, 0, hist, backproj, &ranges, 1, true );

  /// Draw the backproj
  imshow( "BackProj", backproj );

  /// Draw the histogram
  int w = 400; int h = 400;
  int bin_w = cvRound( (double) w / histSize );
  Mat histImg = Mat::zeros( w, h, CV_8UC3 );

  for( int i = 0; i < bins; i ++ )
     { rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }

  imshow( "Histogram", histImg );
}

int main( int argc, char** argv )
{
	
   try {
	  // Parses the command line options.
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("image1_filename", po::value<std::string>(), "set image1 filename")
            ("image2_filename", po::value<std::string>(), "set image2 filename")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }
        
        if (vm.count("image1_filename"))
			image1_filename = vm["image1_filename"].as<std::string>();
		else
			{
				cout << "Image1 filename missing" << endl;
				cout << desc << endl;
				return 0;
			}
        if (vm.count("image2_filename"))
			image2_filename = vm["image2_filename"].as<std::string>();
		else
			{
				cout << "Image2 filename missing" << endl;
				cout << desc << endl;
				return 0;
			}
 		}
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    src = imread(image1_filename.c_str(), CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! src.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the first input image" << std::endl ;
        return -1;
    }
    target = imread(image2_filename.c_str(), CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! target.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the second input image" << std::endl ;
        return -1;
    }

  /// Transform it to HSV
  cvtColor( src, hsvsrc, CV_BGR2HSV );
  cvtColor( target, hsvtarget, CV_BGR2HSV );

  /// Use only the Hue value
  huesrc.create( hsvsrc.size(), hsvsrc.depth() );
  int ch[] = { 0, 0 };
  mixChannels( &hsvsrc, 1, &huesrc, 1, ch, 1 );
  
  /// Use only the Hue value
  huetarget.create( hsvtarget.size(), hsvtarget.depth() );
  mixChannels( &hsvtarget, 1, &huetarget, 1, ch, 1 );

  /// Create Trackbar to enter the number of bins
  char* window_image = "Source1 image";
  namedWindow( window_image, CV_WINDOW_AUTOSIZE );
  createTrackbar("* Hue  bins: ", window_image, &bins, 180, Hist_and_Backproj );
  Hist_and_Backproj(0, 0);

  /// Show the image
  imshow( window_image, src );
  
  char* window_image2 = "Source2 image";
  namedWindow( window_image2, CV_WINDOW_AUTOSIZE );
  /// Show the image
  imshow( window_image2, target );

  /// Wait until user exits the program
  waitKey(0);
  return 0;

}


