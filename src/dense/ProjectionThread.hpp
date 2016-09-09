#ifndef __PROJECTIONTHREAD_H
#define __PROJECTIONTHREAD_H

#include <thread>
#include <pcl_ros/point_cloud.h>

#include "Camera.hpp"
#include "DispImageQueue.hpp"
#include "PointCloudQueue.hpp"

#define MIN_DISPARITY_THRESHOLD 20

class Dense;

class ProjectionThread
{
public:

    ProjectionThread(Dense *dense);

    inline void WaitUntilFinished()
    { projectionThread_.join(); }

private:

    Dense *dense_;
    std::thread projectionThread_;
    void compute();

    void filterDisp(const DispRawImagePtr disp_raw_img, float min_disparity);
    MatVec3fPtr processPoints(const DispRawImagePtr disp_raw_img);
    bool isValidPoint(const cv::Vec3f& pt);
    PointCloudPtr generateCloud(PointCloudEntry::Ptr entry, MatVec3fPtr dense_points_, ImagePtr raw_left_image);
    void cameraToWorld(PointCloudPtr cloud, CameraPose::Ptr current_pos);
};

#endif /* __PROJECTIONTHREAD_H */
