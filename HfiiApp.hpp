#ifndef HFIIAPP_H
#define HFIIAPP_H
#pragma once
	
#include <iostream>
#include <set>
#include <opencv2/core/types.hpp>

struct classcomp {
  bool operator() (const cv::Point& lhs, const cv::Point& rhs) const
  {
	  return lhs.y<rhs.y;
}
};

class HfiiApp  
{
	private:
		//Private functions
		uint16_t showImage();
		
		// Private variables
		std::string m_strFileName;
		

	public:

		HfiiApp(std::string strFileName);
		~HfiiApp();

		// enum
		enum ERROR_CODE: std::uint16_t
		{
			SUCCESS,
			FAIL
		};

		std::set<cv::Point,classcomp> m_coordinatesSet;

};
#endif