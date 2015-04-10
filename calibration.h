struct Matches {
  cv::vector<cv::Point2f> from;
  cv::vector<cv::Point2f> to;
};

struct Calibration {
  Calibration (cv::Mat left, cv::Mat right, Pair camPair);

  Pair camPair;
  Matches matches;

  cv::Mat left;
  cv::Mat right;
  cv::Mat leftRect;
  cv::Mat rightRect;

  cv::Mat F;

  void remapImages();

  static Pair createPair(
      std::string intrinsics,
      std::string extrinsics);
};

