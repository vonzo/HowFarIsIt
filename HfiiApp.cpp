#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
	
#include "HfiiApp.hpp"  

cv::Point MIN_X(const cv::Point p1, const cv::Point p2)
{
	return (p1.x < p2.x) ? p1 : p2;
}

cv::Point MAX_X(const cv::Point p1, const cv::Point p2)
{
	return (p1.x > p2.x) ? p1 : p2;
}

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
	m_ptrSharedHfiiApp.m_resized_down = &resized_down;
	const std::string stiWindowName = m_ptrSharedHfiiApp.m_strWindowName;

    if(img.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }
    
	cv::namedWindow(stiWindowName, cv::WINDOW_NORMAL);
	cv::resize(img, resized_down, cv::Size{0,0}, 0.5, 0.5, cv::INTER_LINEAR);
	cv::setMouseCallback(stiWindowName, ClickCallBackFunc, &m_ptrSharedHfiiApp);
    cv::imshow(stiWindowName, resized_down);
    int k = cv::waitKey(0); // Wait for a keystroke in the window

	return SUCCESS;
}

void ClickCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	// Get shared data
	SharedHfiiApp * ptrSharedHfiiApp = (SharedHfiiApp *)userdata;
	// Get set with coordinates
	std::set<cv::Point,classcomp> * coordinatesSet = &(ptrSharedHfiiApp->m_coordinatesSet);
	// Get pointer to image
	cv::Mat * resized_down = ptrSharedHfiiApp->m_resized_down;

    if(event == cv::EVENT_LBUTTONDOWN)
    {
		// Fill the set until it's size is == 4
    	if(coordinatesSet->size() < 4)
		{
			// Draw circles where the user has clicked
			cv::circle(*resized_down, cv::Point(x,y), ticknes, red);
			cv::imshow(ptrSharedHfiiApp->m_strWindowName, *resized_down);
			
			// Add new element to set
			coordinatesSet->insert(cv::Point(x,y));
		}
		// If set's size is 4, draw "box"
		if (coordinatesSet->size() == 4)
		{
			std::set<cv::Point,classcomp>::iterator it = coordinatesSet->begin();
			cv::Point p1, p2, p3, p4;
			p1 = *(it++);
			p2 = *(it++);
			p3 = *(it++);
			p4 = *(it++);

			cv::line(*resized_down, p1, p2, blue, 5);
			cv::line(*resized_down, MIN_X(p1, p2), MIN_X(p3, p4), blue, ticknes);
			cv::line(*resized_down, MAX_X(p1, p2), MAX_X(p3, p4), blue, ticknes);
			cv::line(*resized_down, p3, p4, blue, 5);

			cv::imshow(ptrSharedHfiiApp->m_strWindowName, *resized_down);
		}

	}
	else if(event == cv::EVENT_RBUTTONDOWN)
	{
		std::cout << "Points Cleared" << std::endl;
		coordinatesSet->clear();
	}
}
