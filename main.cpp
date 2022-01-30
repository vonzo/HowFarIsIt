#include <iostream>
//#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(int, char**) {
    std::cout << "Hello, world! from vscode + cmake \n";
    
    cv::Mat img = imread("/home/ivan/Downloads/calibration.jpg", cv::IMREAD_COLOR);

    if(img.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }
    
    cv::imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        cv::imwrite("starry_night.png", img);
    }
    return 0;
}

