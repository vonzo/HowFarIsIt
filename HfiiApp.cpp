#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
	
#include "HfiiApp.hpp"  

HfiiApp::HfiiApp(std::string strFileName)
{
	m_strFileName = strFileName;
	showImage();
}
	
HfiiApp::~HfiiApp()
{
	
}

void ClickCallBackFunc(int event, int x, int y, int flags, void* userdata);

uint16_t HfiiApp::showImage()
{
	cv::Mat img = imread(m_strFileName, cv::IMREAD_COLOR);
	cv::Mat resized_down;

    if(img.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }
    
	cv::namedWindow( "Display window", cv::WINDOW_NORMAL);
	cv::resize(img, resized_down, cv::Size{0,0}, 0.5, 0.5, cv::INTER_LINEAR);
	cv::setMouseCallback("Display window", ClickCallBackFunc, &m_coordinatesSet);
    cv::imshow("Display window", resized_down);
    int k = cv::waitKey(0); // Wait for a keystroke in the window

	return SUCCESS;
}

void ClickCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	std::set<cv::Point,classcomp> * coordinatesSet = (std::set<cv::Point,classcomp> *)userdata;

    if  ( event == cv::EVENT_LBUTTONDOWN )
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    	if(coordinatesSet->size() <4)
		{
			coordinatesSet->insert(cv::Point(x,y));
		}
		std::set<cv::Point,classcomp>::iterator it;
		std::cout << "myset contains:";
		for (it=coordinatesSet->begin(); it!=coordinatesSet->end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
     else if  ( event == cv::EVENT_RBUTTONDOWN )
     {
          std::cout << "Points Cleared" << std::endl;
		  coordinatesSet->clear();
     }
}

/* fncomp (cv::Point lpnt, cv::Point rpnt)
{
	return lpnt.y < rpnt.y;
} */