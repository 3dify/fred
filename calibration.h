struct Calibration {
  Calibration (cv::Mat left, cv::Mat right, Pair camPair);
  
  Pair camPair;
  cv::Mat left;
  cv::Mat right;
  cv::Mat leftRect;
  cv::Mat rightRect;
 
  cv::vector<cv::KeyPoint> kp1;
  cv::vector<cv::KeyPoint> kp2;
  cv::Mat desc1;
  cv::Mat desc2;
  cv::vector<cv::DMatch> matches;
  
  void remapImage(cv::Mat src, cv::Mat &dst, Cam cam);
  void remapImages(cv::Mat &left_dst, cv::Mat &right_dst);
  void computeMatches();

  static Pair createPair(std::string intrinsics, std::string extrinsics);
};
