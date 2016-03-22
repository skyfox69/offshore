/* 
 * File:   sitecrawler.h
 * Author: fdueber
 *
 * Created on March 21, 2016, 4:55 AM
 */

#ifndef SITECRAWLER_H
#define SITECRAWLER_H

#include "fileloader.h"
#include "urlloader.h"
#include "urllink.h"
#include <map>

using namespace std;

namespace Offshore {

class	Options;

//-----------------------------------------------------------------------------
class SiteCrawler
{
	protected:
		Options*					_pOptions;
		UrlLoader					_urlLoader;
		FileLoader					_fileLoader;
		map<string, UrlLink>		_mapLinks;
		map<string, UrlLink>		_mapImages;
		map<string, UrlLink>		_mapYoutube;

		virtual	bool				crawlRecursive(UrlLink& link, const unsigned char depth);

	public:
									SiteCrawler();
		virtual						~SiteCrawler();

		virtual	bool				crawl(const string url);
};

}  //  namespace Offshore
#endif  //  SITECRAWLER_H