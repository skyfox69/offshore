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
class	PageAnalyser;
class	PageLocalyser;

//-----------------------------------------------------------------------------
class SiteCrawler
{
	protected:
		Options*					_pOptions;
		PageAnalyser*				_pAnalyser;
		PageLocalyser*				_pLocalyser;
		UrlLoader					_urlLoader;
		FileLoader					_fileLoader;
		map<string, UrlLink>		_mapLinks;
		map<string, UrlLink>		_mapImages;
		map<string, UrlLink>		_mapYoutube;

		virtual	bool				crawlRecursive(UrlLink& link);
		virtual	int					checkImages();

	public:
									SiteCrawler();
		virtual						~SiteCrawler();

		virtual	bool				crawl(const string url);
};

}  //  namespace Offshore
#endif  //  SITECRAWLER_H