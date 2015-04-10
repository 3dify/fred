#include "fred.h"
#include "calibration.h"
#include "pointcloud.h"

using namespace cv;
using namespace std;

Pointcloud::Pointcloud(Calibration calibration) :calibration(calibration) {}

void Pointcloud::computePointcloud() {
  gpu::StereoBM_GPU bm(StereoBM::PREFILTER_XSOBEL);

  bm.ndisp = 64;

  gpu::GpuMat d_left, d_right;

  d_left.upload(calibration.leftRect);
  d_right.upload(calibration.rightRect);

  Size size = calibration.leftRect.size();
  gpu::GpuMat d_disp(size, CV_8U);

  bm(d_left, d_right, d_disp);

  d_disp.download(disparity);

  reprojectImageTo3D(disparity, reprojected, Mat::eye(4, 4, CV_64F));
}
