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

		virtual	int					replaceAll(string& html, const string search, const string replace, const char match);

	public:
									PageLocalyser(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg);
		virtual						~PageLocalyser();

		virtual	int					localyse();
};

}  //  namespace Offshore
#endif  //  PAGELOCALYSER_H