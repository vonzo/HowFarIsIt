#ifndef HFIIAPP_H
#define HFIIAPP_H
#pragma once
	
#include <iostream>
#include <set>
#include <opencv2/core/types.hpp>

static const cv::Scalar blue(255,0,0);
static const cv::Scalar red(0,0,255);
static int ticknes(5);
static const int A4wmm = 297;
static const int A4hmm = 210;


// This struct will define how to sort the sets of type Point
struct classcomp
{
  	bool operator() (const cv::Point& lhs, const cv::Point& rhs) const
  	{
		return lhs.y < rhs.y;
	}
};

// This struct will contain shared data for callbacks
struct SharedHfiiApp
{
	// This set will contain the 4 Points of the cornners
	std::set<cv::Point,classcomp> m_coordinatesSet;
	// resized image to be showed
	cv::Mat * m_resized_down;
	// Window name
	const std::string m_strWindowName = "Display Window";
};

// enum
enum EnuCamera: std::uint16_t
{
	CHALLENGE
};

class Camera;

class HfiiApp  
{
	private:
		//Private functions
		uint16_t showImage();
		
		// Private variables
		std::string m_strFileName;

		// Shared data
		SharedHfiiApp m_ptrSharedHfiiApp;

		std::shared_ptr<Camera> m_camera;
		

	public:

		HfiiApp(std::string strFileName, EnuCamera enuCamera);
		~HfiiApp();

		// enum
		enum ERROR_CODE: std::uint16_t
		{
			SUCCESS,
			FAIL
		};
};
#endif