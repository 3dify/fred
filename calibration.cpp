#include "fred.h"
#include "calibration.h"

using namespace std;
using namespace cv;

Pair Calibration::createPair(string intrinsic, string extrinsic) {
  FileStorage infs(intrinsic, FileStorage::READ);
  FileStorage exfs(extrinsic, FileStorage::READ);
  
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
 
  return (Pair) { R, T, Q, left, right, imageSize }; 
}

Calibration::Calibration(Mat left, Mat right, Pair camPair)
  : left(left), right(right), camPair(camPair) {}

void Calibration::remapImage(Mat src, Mat &dst, Cam cam) {
  Mat Map1, Map2;
  Size size = src.size();
  cout << size << endl;
  initUndistortRectifyMap(cam.M, cam.D, cam.R, cam.P, size, CV_16SC2, Map1, Map2);
  remap(src, dst, Map1, Map2, INTER_LINEAR);
}

void Calibration::remapImages(Mat &left_dst, Mat &right_dst) {
  remapImage(left, left_dst, camPair.left); 
  remapImage(right, right_dst, camPair.right); 
}

void Calibration::computeMatches() {
  cout << "feature detect" << endl;
  // detect
  Ptr<FeatureDetector> detector;
  detector = new DynamicAdaptedFeatureDetector ( new FastAdjuster(10,true), 5000, 10000, 10);
  detector->detect(left, kp1);
  detector->detect(right, kp2);

  cout << "extract descriptors (SIFT)" << endl;
  // extract
  Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create("SIFT");
  extractor->compute( left, kp1, desc1 );
  extractor->compute( right, kp2, desc2 );

  cout << "match descriptors" << endl;
  // match
  vector< vector<DMatch> > allmatches;
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  matcher->knnMatch( desc1, desc2, allmatches, 500 );

  //look whether the match is inside a defined area of the image
  //only 25% of maximum of possible distance
  double tresholdDist = 0.25 * sqrt(double(left.size().height*left.size().height + left.size().width*left.size().width));

  cout << "filtering" << endl;

  int saved = 0;
  // filter
  good_matches.reserve(matches.size());
  for (size_t i = 0; i < matches.size(); ++i) {
    for (int j = 0; j < matches[i].size(); j++) {
      Point2f from = keypoints_1[matches[i][j].queryIdx].pt;
      Point2f to = keypoints_2[matches[i][j].trainIdx].pt;

      //calculate local distance for each possible match
      double dist = sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) * (from.y - to.y));

      //save as best match if local distance is in specified area and on same height
      if (dist < tresholdDist && abs(from.y-to.y)<5) {
        good_matches.push_back(matches[i][j]);
        j = matches[i].size();
        saved++;
      }
    }
  }

  cout << "matches size: " << good_matches.size() << " ~ " << saved << endl;
}
