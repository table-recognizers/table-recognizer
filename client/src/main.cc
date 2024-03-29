#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  std::cout << "Test" << std::endl;

  cv::VideoCapture cap(0);  // open camera
  if (!cap.isOpened())      // check if we succeeded
    return 1;
  cv::Mat edges;
  cv::namedWindow("edges", 1);
  while (1) {
    cv::Mat frame;
    cap >> frame;  // get a new frame from camera
    cv::cvtColor(frame, edges,
                 cv::COLOR_BGR2GRAY);  // transform to black and white
    cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);  // blur
    cv::Canny(edges, edges, 0, 30, 3);  // highlight edges
    cv::imshow("edges", edges);
    if (cv::waitKey(30) >= 0) break;
  }

  return 0;
}
