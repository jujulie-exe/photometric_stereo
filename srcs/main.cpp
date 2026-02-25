#include <opencv2/opencv.hpp>
int main() {
    cv::Mat img = cv::imread("image.jpg");
    std::cout << img.size() << std::endl;
    return 0;
}
