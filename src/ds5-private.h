// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.

#pragma once
#ifndef LIBREALSENSE_DS5_PRIVATE_H
#define LIBREALSENSE_DS5_PRIVATE_H

#include "uvc.h"
#include <mutex>

namespace rsimpl {
    namespace ds5 {

    enum gvd_fields : int32_t
    {
        fw_version_offset = 12
    };

    enum calibration_modules_id
    {
        depth_module_id,
        left_imager_id,
        right_imager_id,
        rgb_imager_id,
        fisheye_imager_id,
        imu_id,
        lens_module_id,
        projector_module_id,
        max_calib_module_id
    };

    enum ds5_rect_resolutions : unsigned short
    {
        res_1920_1080,
        res_1280_720,
        res_960_540,
        res_640_480,
        res_854_480,
        res_640_360,
        res_432_240,
        res_320_240,
        res_480_270,
        reserved_1,
        reserved_2,
        reserved_3,
        max_ds5_rect_resoluitons
    };

    struct ds5_depth_resolutions { ds5_rect_resolutions name; int2 dims; };

    static const std::vector<ds5_depth_resolutions> resolutions_list = {
        { res_320_240,  { 320, 240 } },
        { res_432_240,  { 432, 240 } },
        { res_480_270,  { 480, 270 } },
        { res_640_360,  { 640, 360 } },
        { res_640_480,  { 640, 480 } },
        { res_854_480,  { 854, 480 } },
        { res_960_540,  { 960, 540 } },
        { res_1280_720, { 1280, 720 } },
        { res_1920_1080,{ 1920, 1080 } },
    };

    struct ds5_calibration
    {
        uint16_t        version;                        // major.minor
        rs_intrinsics   left_imager_intrinsic;
        rs_intrinsics   right_imager_intrinsic;
        rs_intrinsics   depth_intrinsic[max_ds5_rect_resoluitons];
        rs_extrinsics   left_imager_extrinsic;
        rs_extrinsics   right_imager_extrinsic;
        rs_extrinsics   depth_extrinsic;
        bool            data_present[max_calib_module_id];
    };

    std::string read_firmware_version(uvc::device & device);

    // Claim USB interface used for device
    void claim_ds5_monitor_interface(uvc::device & device);
    void claim_ds5_motion_module_interface(uvc::device & device);

    // Read device state
    void get_gvd(uvc::device & device, std::timed_mutex & mutex, size_t sz, char * gvd);
    void get_firmware_version_string(uvc::device & dev, std::timed_mutex & mutex, std::string & version);
    void get_module_serial_string(uvc::device & dev, std::timed_mutex & mutex, std::string & serial, unsigned int offset);
    void read_calibration(uvc::device & dev, std::timed_mutex & mutex, ds5_calibration& calib);

    // XU read/write
    void get_laser_power(const uvc::device & device, uint8_t & laser_power);
    void set_laser_power(uvc::device & device, uint8_t laser_power);


} //namespace rsimpl::ds5
} // namespace rsimpl

#endif  // DS5_PRIVATE_H
