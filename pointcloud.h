struct Pointcloud {
  Pointcloud(Calibration calibration);
  Calibration calibration;
  cv::Mat reprojected;
  cv::Mat disparity;
  void computePointcloud();
};
