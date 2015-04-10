struct Calibration {
  Pair camPair;
  cv::Mat left;
  cv::Mat right;
  cv::Mat leftRect;
  cv::Mat rightRect;
  Calibration (cv::Mat left, cv::Mat right, Pair camPair);
  void remapImage(cv::Mat src, cv::Mat &dst, Cam cam);
  void remapImages(cv::Mat &left_dst, cv::Mat &right_dst);
  void getMatches(cv::vector<cv::KeyPoint> &keypoints_1, cv::vector<cv::KeyPoint> &keypoints_2
    , cv::Mat &descriptors_1, cv::Mat &descriptors_2, cv::vector< cv::DMatch > &good_matches);

  static Pair createPair(std::string intrinsics, std::string extrinsics);
};
