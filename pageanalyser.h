/* 
 * File:   pageanalyser.h
 * Author: fdueber
 *
 * Created on March 22, 2016, 4:15 AM
 */

#ifndef PAGEANALYSER_H
#define PAGEANALYSER_H

#include "urllink.h"
#include <map>
#include <vector>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class PageAnalyser
{
	protected:
		map<string, UrlLink>&		_mapLinks;
		map<string, UrlLink>&		_mapImages;
		map<string, UrlLink>&		_mapYoutube;

	public:
									PageAnalyser(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt);
		virtual						~PageAnalyser();

		virtual	int					analyse(const string html, const unsigned char depth, const string tag, vector<string>& localLinks);
};

}  //  namespace Offshore
#endif  //  PAGEANALYSER_H