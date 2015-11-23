#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class Image
{
public:
  Image(std::string imagePath);

  cv::Mat getBinaryImage(unsigned int pixelsToBinary, unsigned int pixelBinary);
  cv::Mat getBinaryForegroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary);
  cv::Mat getBinaryBackgroundImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);
  cv::Mat getBinaryMarkersImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);
  cv::Mat getBinaryWatershedSegmenterImage(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);

  cv::Mat convertInBlackAndWhiteByStrip(unsigned int pixelsToBinary, unsigned int pixelBinary, unsigned int backgroundColor);

  std::vector< std::vector<int> > getPixelMatrix();

  int getWidth();
  int getHeight();

  cv::Mat getCvImage();
  cv::Mat getYcbcrImage();
  void setYcbcrImage(cv::Mat image);

  static void show(std::string label, cv::Mat image);
  static std::vector< std::vector<int> > getPixelMatrix(cv::Mat image);
private:
  cv::Mat cvImage;
  cv::Mat removeBlackAndWhiteNoise(cv::Mat binary, int erodeWhite);
  cv::Mat ycbcrImage;
};

class WatershedSegmenter{
private:
  cv::Mat markers;
public:
  void setMarkers(cv::Mat& markerImage)
  {
    markerImage.convertTo(markers, CV_32S);
  }

  cv::Mat process(cv::Mat &image)
  {
    cv::watershed(image, markers);
    markers.convertTo(markers,CV_8U);
    return markers;
  }
};
#endif
