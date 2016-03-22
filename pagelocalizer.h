/* 
 * File:   pagelcalyzer.h
 * Author: fdueber
 *
 * Created on March 22, 2016, 8:45 PM
 */

#ifndef PAGELOCALYZER_H
#define PAGELOCALYZER_H

#include "urllink.h"
#include <map>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class PageLocalyzer
{
	protected:
		map<string, UrlLink>&		_mapLinks;
		map<string, UrlLink>&		_mapImages;
		map<string, UrlLink>&		_mapYoutube;

	public:
									PageLocalyzer(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt);
		virtual						~PageLocalyzer();

};

}  //  namespace Offshore
#endif  //  PAGELOCALYZER_H