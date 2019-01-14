#-------------------------------------------------
#
# Project created by QtCreator 2019-01-11T21:44:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        neuralnetwork.cpp \
    activation.cpp \
    data_loader.cpp \
    label_loader.cpp \
    network.cpp

HEADERS += \
        neuralnetwork.h \
    activation.hpp \
    data_loader.hpp \
    label_loader.hpp \
    network.hpp \
    opencv2/calib3d/calib3d.hpp \
    opencv2/contrib/contrib.hpp \
    opencv2/contrib/detection_based_tracker.hpp \
    opencv2/contrib/hybridtracker.hpp \
    opencv2/contrib/openfabmap.hpp \
    opencv2/contrib/retina.hpp \
    opencv2/core/affine.hpp \
    opencv2/core/core.hpp \
    opencv2/core/core_c.h \
    opencv2/core/cuda_devptrs.hpp \
    opencv2/core/devmem2d.hpp \
    opencv2/core/eigen.hpp \
    opencv2/core/gpumat.hpp \
    opencv2/core/internal.hpp \
    opencv2/core/mat.hpp \
    opencv2/core/opengl_interop.hpp \
    opencv2/core/opengl_interop_deprecated.hpp \
    opencv2/core/operations.hpp \
    opencv2/core/types_c.h \
    opencv2/core/version.hpp \
    opencv2/core/wimage.hpp \
    opencv2/features2d/features2d.hpp \
    opencv2/flann/all_indices.h \
    opencv2/flann/allocator.h \
    opencv2/flann/any.h \
    opencv2/flann/autotuned_index.h \
    opencv2/flann/composite_index.h \
    opencv2/flann/config.h \
    opencv2/flann/defines.h \
    opencv2/flann/dist.h \
    opencv2/flann/dummy.h \
    opencv2/flann/dynamic_bitset.h \
    opencv2/flann/flann.hpp \
    opencv2/flann/flann_base.hpp \
    opencv2/flann/general.h \
    opencv2/flann/ground_truth.h \
    opencv2/flann/hdf5.h \
    opencv2/flann/heap.h \
    opencv2/flann/hierarchical_clustering_index.h \
    opencv2/flann/index_testing.h \
    opencv2/flann/kdtree_index.h \
    opencv2/flann/kdtree_single_index.h \
    opencv2/flann/kmeans_index.h \
    opencv2/flann/linear_index.h \
    opencv2/flann/logger.h \
    opencv2/flann/lsh_index.h \
    opencv2/flann/lsh_table.h \
    opencv2/flann/matrix.h \
    opencv2/flann/miniflann.hpp \
    opencv2/flann/nn_index.h \
    opencv2/flann/object_factory.h \
    opencv2/flann/params.h \
    opencv2/flann/random.h \
    opencv2/flann/result_set.h \
    opencv2/flann/sampling.h \
    opencv2/flann/saving.h \
    opencv2/flann/simplex_downhill.h \
    opencv2/flann/timer.h \
    opencv2/gpu/device/detail/color_detail.hpp \
    opencv2/gpu/device/detail/reduce.hpp \
    opencv2/gpu/device/detail/reduce_key_val.hpp \
    opencv2/gpu/device/detail/transform_detail.hpp \
    opencv2/gpu/device/detail/type_traits_detail.hpp \
    opencv2/gpu/device/detail/vec_distance_detail.hpp \
    opencv2/gpu/device/block.hpp \
    opencv2/gpu/device/border_interpolate.hpp \
    opencv2/gpu/device/color.hpp \
    opencv2/gpu/device/common.hpp \
    opencv2/gpu/device/datamov_utils.hpp \
    opencv2/gpu/device/dynamic_smem.hpp \
    opencv2/gpu/device/emulation.hpp \
    opencv2/gpu/device/filters.hpp \
    opencv2/gpu/device/funcattrib.hpp \
    opencv2/gpu/device/functional.hpp \
    opencv2/gpu/device/limits.hpp \
    opencv2/gpu/device/reduce.hpp \
    opencv2/gpu/device/saturate_cast.hpp \
    opencv2/gpu/device/scan.hpp \
    opencv2/gpu/device/simd_functions.hpp \
    opencv2/gpu/device/static_check.hpp \
    opencv2/gpu/device/transform.hpp \
    opencv2/gpu/device/type_traits.hpp \
    opencv2/gpu/device/utility.hpp \
    opencv2/gpu/device/vec_distance.hpp \
    opencv2/gpu/device/vec_math.hpp \
    opencv2/gpu/device/vec_traits.hpp \
    opencv2/gpu/device/warp.hpp \
    opencv2/gpu/device/warp_reduce.hpp \
    opencv2/gpu/device/warp_shuffle.hpp \
    opencv2/gpu/devmem2d.hpp \
    opencv2/gpu/gpu.hpp \
    opencv2/gpu/gpumat.hpp \
    opencv2/gpu/stream_accessor.hpp \
    opencv2/highgui/cap_ios.h \
    opencv2/highgui/highgui.hpp \
    opencv2/highgui/highgui_c.h \
    opencv2/highgui/ios.h \
    opencv2/imgproc/imgproc.hpp \
    opencv2/imgproc/imgproc_c.h \
    opencv2/imgproc/types_c.h \
    opencv2/legacy/blobtrack.hpp \
    opencv2/legacy/compat.hpp \
    opencv2/legacy/legacy.hpp \
    opencv2/legacy/streams.hpp \
    opencv2/ml/ml.hpp \
    opencv2/nonfree/features2d.hpp \
    opencv2/nonfree/gpu.hpp \
    opencv2/nonfree/nonfree.hpp \
    opencv2/nonfree/ocl.hpp \
    opencv2/objdetect/objdetect.hpp \
    opencv2/ocl/matrix_operations.hpp \
    opencv2/ocl/ocl.hpp \
    opencv2/photo/photo.hpp \
    opencv2/photo/photo_c.h \
    opencv2/stitching/detail/autocalib.hpp \
    opencv2/stitching/detail/blenders.hpp \
    opencv2/stitching/detail/camera.hpp \
    opencv2/stitching/detail/exposure_compensate.hpp \
    opencv2/stitching/detail/matchers.hpp \
    opencv2/stitching/detail/motion_estimators.hpp \
    opencv2/stitching/detail/seam_finders.hpp \
    opencv2/stitching/detail/util.hpp \
    opencv2/stitching/detail/util_inl.hpp \
    opencv2/stitching/detail/warpers.hpp \
    opencv2/stitching/detail/warpers_inl.hpp \
    opencv2/stitching/stitcher.hpp \
    opencv2/stitching/warpers.hpp \
    opencv2/superres/optical_flow.hpp \
    opencv2/superres/superres.hpp \
    opencv2/ts/gpu_perf.hpp \
    opencv2/ts/gpu_test.hpp \
    opencv2/ts/ts.hpp \
    opencv2/ts/ts_gtest.h \
    opencv2/ts/ts_perf.hpp \
    opencv2/video/background_segm.hpp \
    opencv2/video/tracking.hpp \
    opencv2/video/video.hpp \
    opencv2/videostab/deblurring.hpp \
    opencv2/videostab/fast_marching.hpp \
    opencv2/videostab/fast_marching_inl.hpp \
    opencv2/videostab/frame_source.hpp \
    opencv2/videostab/global_motion.hpp \
    opencv2/videostab/inpainting.hpp \
    opencv2/videostab/log.hpp \
    opencv2/videostab/motion_stabilizing.hpp \
    opencv2/videostab/optical_flow.hpp \
    opencv2/videostab/stabilizer.hpp \
    opencv2/videostab/videostab.hpp \
    opencv2/calib3d.hpp \
    opencv2/core.hpp \
    opencv2/features2d.hpp \
    opencv2/flann.hpp \
    opencv2/highgui.hpp \
    opencv2/imgproc.hpp \
    opencv2/ml.hpp \
    opencv2/objdetect.hpp \
    opencv2/opencv.hpp \
    opencv2/opencv_modules.hpp \
    opencv2/photo.hpp \
    opencv2/stitching.hpp \
    opencv2/superres.hpp \
    opencv2/ts.hpp \
    opencv2/video.hpp \
    opencv2/videostab.hpp \
    opencv2/calib3d/calib3d.hpp \
    opencv2/contrib/contrib.hpp \
    opencv2/contrib/detection_based_tracker.hpp \
    opencv2/contrib/hybridtracker.hpp \
    opencv2/contrib/openfabmap.hpp \
    opencv2/contrib/retina.hpp \
    opencv2/core/affine.hpp \
    opencv2/core/core.hpp \
    opencv2/core/core_c.h \
    opencv2/core/cuda_devptrs.hpp \
    opencv2/core/devmem2d.hpp \
    opencv2/core/eigen.hpp \
    opencv2/core/gpumat.hpp \
    opencv2/core/internal.hpp \
    opencv2/core/mat.hpp \
    opencv2/core/opengl_interop.hpp \
    opencv2/core/opengl_interop_deprecated.hpp \
    opencv2/core/operations.hpp \
    opencv2/core/types_c.h \
    opencv2/core/version.hpp \
    opencv2/core/wimage.hpp \
    opencv2/features2d/features2d.hpp \
    opencv2/flann/all_indices.h \
    opencv2/flann/allocator.h \
    opencv2/flann/any.h \
    opencv2/flann/autotuned_index.h \
    opencv2/flann/composite_index.h \
    opencv2/flann/config.h \
    opencv2/flann/defines.h \
    opencv2/flann/dist.h \
    opencv2/flann/dummy.h \
    opencv2/flann/dynamic_bitset.h \
    opencv2/flann/flann.hpp \
    opencv2/flann/flann_base.hpp \
    opencv2/flann/general.h \
    opencv2/flann/ground_truth.h \
    opencv2/flann/hdf5.h \
    opencv2/flann/heap.h \
    opencv2/flann/hierarchical_clustering_index.h \
    opencv2/flann/index_testing.h \
    opencv2/flann/kdtree_index.h \
    opencv2/flann/kdtree_single_index.h \
    opencv2/flann/kmeans_index.h \
    opencv2/flann/linear_index.h \
    opencv2/flann/logger.h \
    opencv2/flann/lsh_index.h \
    opencv2/flann/lsh_table.h \
    opencv2/flann/matrix.h \
    opencv2/flann/miniflann.hpp \
    opencv2/flann/nn_index.h \
    opencv2/flann/object_factory.h \
    opencv2/flann/params.h \
    opencv2/flann/random.h \
    opencv2/flann/result_set.h \
    opencv2/flann/sampling.h \
    opencv2/flann/saving.h \
    opencv2/flann/simplex_downhill.h \
    opencv2/flann/timer.h \
    opencv2/gpu/device/detail/color_detail.hpp \
    opencv2/gpu/device/detail/reduce.hpp \
    opencv2/gpu/device/detail/reduce_key_val.hpp \
    opencv2/gpu/device/detail/transform_detail.hpp \
    opencv2/gpu/device/detail/type_traits_detail.hpp \
    opencv2/gpu/device/detail/vec_distance_detail.hpp \
    opencv2/gpu/device/block.hpp \
    opencv2/gpu/device/border_interpolate.hpp \
    opencv2/gpu/device/color.hpp \
    opencv2/gpu/device/common.hpp \
    opencv2/gpu/device/datamov_utils.hpp \
    opencv2/gpu/device/dynamic_smem.hpp \
    opencv2/gpu/device/emulation.hpp \
    opencv2/gpu/device/filters.hpp \
    opencv2/gpu/device/funcattrib.hpp \
    opencv2/gpu/device/functional.hpp \
    opencv2/gpu/device/limits.hpp \
    opencv2/gpu/device/reduce.hpp \
    opencv2/gpu/device/saturate_cast.hpp \
    opencv2/gpu/device/scan.hpp \
    opencv2/gpu/device/simd_functions.hpp \
    opencv2/gpu/device/static_check.hpp \
    opencv2/gpu/device/transform.hpp \
    opencv2/gpu/device/type_traits.hpp \
    opencv2/gpu/device/utility.hpp \
    opencv2/gpu/device/vec_distance.hpp \
    opencv2/gpu/device/vec_math.hpp \
    opencv2/gpu/device/vec_traits.hpp \
    opencv2/gpu/device/warp.hpp \
    opencv2/gpu/device/warp_reduce.hpp \
    opencv2/gpu/device/warp_shuffle.hpp \
    opencv2/gpu/devmem2d.hpp \
    opencv2/gpu/gpu.hpp \
    opencv2/gpu/gpumat.hpp \
    opencv2/gpu/stream_accessor.hpp \
    opencv2/highgui/cap_ios.h \
    opencv2/highgui/highgui.hpp \
    opencv2/highgui/highgui_c.h \
    opencv2/highgui/ios.h \
    opencv2/imgproc/imgproc.hpp \
    opencv2/imgproc/imgproc_c.h \
    opencv2/imgproc/types_c.h \
    opencv2/legacy/blobtrack.hpp \
    opencv2/legacy/compat.hpp \
    opencv2/legacy/legacy.hpp \
    opencv2/legacy/streams.hpp \
    opencv2/ml/ml.hpp \
    opencv2/nonfree/features2d.hpp \
    opencv2/nonfree/gpu.hpp \
    opencv2/nonfree/nonfree.hpp \
    opencv2/nonfree/ocl.hpp \
    opencv2/objdetect/objdetect.hpp \
    opencv2/ocl/matrix_operations.hpp \
    opencv2/ocl/ocl.hpp \
    opencv2/photo/photo.hpp \
    opencv2/photo/photo_c.h \
    opencv2/stitching/detail/autocalib.hpp \
    opencv2/stitching/detail/blenders.hpp \
    opencv2/stitching/detail/camera.hpp \
    opencv2/stitching/detail/exposure_compensate.hpp \
    opencv2/stitching/detail/matchers.hpp \
    opencv2/stitching/detail/motion_estimators.hpp \
    opencv2/stitching/detail/seam_finders.hpp \
    opencv2/stitching/detail/util.hpp \
    opencv2/stitching/detail/util_inl.hpp \
    opencv2/stitching/detail/warpers.hpp \
    opencv2/stitching/detail/warpers_inl.hpp \
    opencv2/stitching/stitcher.hpp \
    opencv2/stitching/warpers.hpp \
    opencv2/superres/optical_flow.hpp \
    opencv2/superres/superres.hpp \
    opencv2/ts/gpu_perf.hpp \
    opencv2/ts/gpu_test.hpp \
    opencv2/ts/ts.hpp \
    opencv2/ts/ts_gtest.h \
    opencv2/ts/ts_perf.hpp \
    opencv2/video/background_segm.hpp \
    opencv2/video/tracking.hpp \
    opencv2/video/video.hpp \
    opencv2/videostab/deblurring.hpp \
    opencv2/videostab/fast_marching.hpp \
    opencv2/videostab/fast_marching_inl.hpp \
    opencv2/videostab/frame_source.hpp \
    opencv2/videostab/global_motion.hpp \
    opencv2/videostab/inpainting.hpp \
    opencv2/videostab/log.hpp \
    opencv2/videostab/motion_stabilizing.hpp \
    opencv2/videostab/optical_flow.hpp \
    opencv2/videostab/stabilizer.hpp \
    opencv2/videostab/videostab.hpp \
    opencv2/calib3d.hpp \
    opencv2/core.hpp \
    opencv2/features2d.hpp \
    opencv2/flann.hpp \
    opencv2/highgui.hpp \
    opencv2/imgproc.hpp \
    opencv2/ml.hpp \
    opencv2/objdetect.hpp \
    opencv2/opencv.hpp \
    opencv2/opencv_modules.hpp \
    opencv2/photo.hpp \
    opencv2/stitching.hpp \
    opencv2/superres.hpp \
    opencv2/ts.hpp \
    opencv2/video.hpp \
    opencv2/videostab.hpp

FORMS += \
        neuralnetwork.ui

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
