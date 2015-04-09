#include <string>
#include <iostream>

#include "opencv2/core/core.hpp"

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

  exfs["R1"] >> R1;
  exfs["R2"] >> R2;
  exfs["P1"] >> P1;
  exfs["P2"] >> P2;

  exfs["R"] >> R;
  exfs["T"] >> T;
  exfs["Q"] >> Q;

  
  Cam left = (Cam) { M1, D1, R1, P1 };
  Cam right = (Cam) { M2, D2, R2, P2 };
 
  Pair campair = (Pair) { R, T, Q, left, right }; 

  return campair;
}

void App::run() {
  Pair campair = readProperties(p.intrinsic, p.extrinsic);
 

    
  cout << campair.R << endl;

}

static void printHelp() {
  cout << "Usage: epipolar\n"
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
