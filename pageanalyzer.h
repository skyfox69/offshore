/* 
 * File:   pageanalyzer.h
 * Author: fdueber
 *
 * Created on March 22, 2016, 4:15 AM
 */

#ifndef PAGEANALYZER_H
#define PAGEANALYZER_H

#include "urllink.h"
#include <map>
#include <vector>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class PageAnalyzer
{
	protected:
		map<string, UrlLink>&		_mapLinks;
		map<string, UrlLink>&		_mapImages;
		map<string, UrlLink>&		_mapYoutube;

	public:
									PageAnalyzer(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt);
		virtual						~PageAnalyzer();

		virtual	int					analyze(const string html, const unsigned char depth, const string tag, vector<string>& localLinks);
};

}  //  namespace Offshore
#endif  //  PAGEANALYZER_H