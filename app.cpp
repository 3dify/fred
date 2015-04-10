#include <string>
#include <iostream>

#include "fred.h"
#include "params.h"
#include "app.h"

using namespace cv;
using namespace std;

bool help_showed = false;


App::App(const Params& params)
: p(params), running(false) {
  cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());
}

Pair App::readProperties(string intrinsicfn, string extrinsicfn) {
  FileStorage infs(intrinsicfn, FileStorage::READ);
  FileStorage exfs(extrinsicfn, FileStorage::READ);

  Mat M1, M2, D1, D2, R1, R2, P1, P2, R, T, Q;
  
  infs["M1"] >> M1;
  infs["M2"] >> M2;
  infs["D1"] >> D1;
  infs["D2"] >> D2;

  Size imageSize;
  infs["imageSize"] >> imageSize;

  exfs["R1"] >> R1;
  exfs["R2"] >> R2;
  exfs["P1"] >> P1;
  exfs["P2"] >> P2;

  exfs["R"] >> R;
  exfs["T"] >> T;
  exfs["Q"] >> Q;

  
  Cam left = (Cam) { M1, D1, R1, P1 };
  Cam right = (Cam) { M2, D2, R2, P2 };
 
  Pair campair = (Pair) { R, T, Q, left, right, imageSize }; 

  return campair;
}

void App::readImages(string leftfn, string rightfn, Mat &left, Mat &right) {
  Mat left_src = imread(p.left);
  Mat right_src = imread(p.right);

  if (left_src.empty()) throw runtime_error("can't open file \"" + p.left + "\"");
  if (right_src.empty()) throw runtime_error("can't open file \"" + p.right + "\"");
  
  cvtColor(left_src, left, CV_BGR2GRAY);
  cvtColor(right_src, right, CV_BGR2GRAY);
}

void App::remapImages(Pair campair, Mat left, Mat right, Mat left_rect, Mat right_rect) {
  Mat rmap[2][2];
  initUndistortRectifyMap(campair.left.M, campair.left.D, campair.left.R, campair.left.P, campair.imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
  initUndistortRectifyMap(campair.right.M, campair.right.D, campair.left.R, campair.left.P, campair.imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

  remap(left, left_rect, rmap[0][0], rmap[0][1], CV_INTER_LINEAR);
  remap(right, right_rect, rmap[1][0], rmap[1][1], CV_INTER_LINEAR);
}

void App::run() {
  Pair campair = readProperties(p.intrinsic, p.extrinsic);
 
  Mat left, right;
  readImages(p.left, p.right, left, right); 
 
  Mat left_rect, right_rect;
  remapImages(campair, left, right, left_rect, right_rect); 

  imshow("left", left_rect);
  waitKey(0);
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
