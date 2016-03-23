/* 
 * File:   pagelcalyser.h
 * Author: fdueber
 *
 * Created on March 22, 2016, 8:45 PM
 */

#ifndef PAGELOCALYSER_H
#define PAGELOCALYSER_H

#include "urllink.h"
#include <map>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class PageLocalyser
{
	protected:
		map<string, UrlLink>&		_mapLinks;
		map<string, UrlLink>&		_mapImages;
		map<string, UrlLink>&		_mapYoutube;

	public:
									PageLocalyser(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt);
		virtual						~PageLocalyser();

};

}  //  namespace Offshore
#endif  //  PAGELOCALYSER_H