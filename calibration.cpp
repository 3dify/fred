#include "fred.h"
#include "calibration.h"

using namespace std;
using namespace cv;

Pair Calibration::createPair(string intrinsic, string extrinsic) {
  FileStorage infs(intrinsic, FileStorage::READ);
  FileStorage exfs(extrinsic, FileStorage::READ);
  
  Mat M1, M2, D1, D2, R1, R2, P1, P2, R, T, Q, RL1, RL2, RR1, RR2;
  
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

  exfs["URML1"] >> RL1;
  exfs["URMR1"] >> RR1;

  exfs["URML2"] >> RL2;
  exfs["URMR2"] >> RR2;

  Cam left = (Cam) { M1, D1, R1, P1, RL1, RL2 };
  Cam right = (Cam) { M2, D2, R2, P2, RR1, RR2 };
 
  return (Pair) { R, T, Q, left, right, imageSize }; 
}

Calibration::Calibration(Mat left, Mat right, Pair camPair)
  : left(left), right(right), camPair(camPair) {}


void Calibration::remapImages() {
  remap(left, leftRect, camPair.left.Map1, camPair.right.Map2, INTER_LINEAR);
  remap(right, rightRect, camPair.right.Map1, camPair.right.Map2, INTER_LINEAR);
}

