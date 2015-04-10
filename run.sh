#! /usr/bin/env bash

make

# ./bin/stereo_calib -w 7 -h 10 -nr stereo_calib_SP1

./bin/app \
  --left ./test-data/Subj_Pos1_SP1_L.png \
  --right ./test-data/Subj_Pos1_SP1_R.png \
  --intrinsic ./out/stereo_calib_SP1_intrinsic.yml \
  --extrinsic ./out/stereo_calib_SP1_extrinsic.yml

