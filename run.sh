#! /usr/bin/env bash

make

./stereo_calib -w 10 -h 7 -nr stereo_calib_SP1
./app --intrinsic out/stereo_calib_SP1_intrinsic.yml --extrinsic out/stereo_calib_SP1_extrinsic.yml

