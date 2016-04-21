/* 
 * File:   urlllink.h
 * Author: fdueber
 *
 * Created on March 20, 2016, 5:32 PM
 */

#ifndef URLLINK_H
#define URLLINK_H

#include <string>
#include <fstream>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class UrlLink
{
	private:
		string						_slug;
		string						_fileName;

	public:
		string						_link;
		bool						_used  = false;
		unsigned char				_depth = 0;

									UrlLink(const string link = "", const unsigned char depth = 0);
		virtual						~UrlLink();

		virtual	string				slug();
		virtual	string				fileName();
		virtual	string				pathName();
		virtual	bool				isValidLink();
		virtual	bool				isValidImage();
		virtual	bool				isValidYoutube();

		virtual	UrlLink&			operator=(const UrlLink other);

		friend	ostream&			operator<<(ostream& stream, const UrlLink& link);
		friend	istream&			operator>>(istream& stream, UrlLink& link);
};

}  //  namespace Offshore
#endif  //  URLLINK_H