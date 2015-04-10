#include <string>

#include "fred.h"
#include "params.h"
#include "calibration.h"
#include "app.h"

using namespace cv;
using namespace std;

void display(cv::Mat img, bool wait = false) {
  static int count = 0;
  
  float factor = 0.3;
  
  int w = round(factor * img.cols);
  int h = round(factor * img.rows);
 
  cv::Mat dst;
  cv::Size size(w, h);
  cv::resize(img, dst, size);

  std::ostringstream sstream;
  sstream << "display-" << count;
  std::string name = sstream.str();
  
  cout << "displaying: " << name << endl;

  cv::namedWindow(name
      , cv::WINDOW_NORMAL 
      & CV_WINDOW_KEEPRATIO 
      & CV_GUI_EXPANDED);
  cv::imshow(name, dst);
  
  if(wait) cv::waitKey(0);
  
  count++;
}

bool help_showed = false;

App::App(const Params& params)
: p(params), running(false) {
  cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());
}

void App::readImages(string leftfn, string rightfn, Mat &left, Mat &right) {
  Mat left_src = imread(p.left);
  Mat right_src = imread(p.right);

  if (left_src.empty()) throw runtime_error("can't open file \"" + p.left + "\"");
  if (right_src.empty()) throw runtime_error("can't open file \"" + p.right + "\"");
  
  cvtColor(left_src, left, CV_BGR2GRAY);
  cvtColor(right_src, right, CV_BGR2GRAY);
}

void App::run() {
  Mat left, right;
  readImages(p.left, p.right, left, right); 
  
  Pair camPair = Calibration::createPair(p.intrinsic, p.extrinsic);
  
  Calibration calibration(left, right, camPair);

  calibration.remapImages(); 
  
  display(calibration.leftRect, true);
}

static void printHelp() {
  cout << "Usage: ./app\n"
  << "\t--intrinsic <intrinsic.yml> --extrinsic <extrinsic.yml>\n";
  help_showed = true;
}

int main(int argc, char** argv) {
  try {
    if (argc < 2) {
      printHelp();
      return 1;
    }
    Params args = Params::read(argc, argv);
    if (help_showed)
      return -1;
    App app(args);
    app.run();
  }
  catch (const exception& e) {
    cout << "error: " << e.what() << endl;
  }
  
  return 0;
}
