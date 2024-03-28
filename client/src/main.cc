#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
int main() {
  std::cout << "Test" << std::endl;

  VideoCapture cap(0);  // open camera
  if (!cap.isOpened())  // check if we succeeded
    return 1;
  Mat edges;
  namedWindow("edges", 1);
  while (1) {
    Mat frame;
    cap >> frame; // get a new frame from camera
    cvtColor(frame, edges, COLOR_BGR2GRAY); // transform to black and white
    GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);  // blur
    Canny(edges, edges, 0, 30, 3);  // highlight edges
    imshow("edges", edges);
    if (waitKey(30) >= 0) break;
  }

  return 0;
}
