#ifndef CAM_H
#define CAM_H

struct Cam {
  Cam(cv::Mat M, cv::Mat D, cv::Mat R, cv::Mat P);
  cv::Mat M;
  cv::Mat D;
  cv::Mat R;
  cv::Mat P;
};

#endif
