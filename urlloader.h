/* 
 * File:   urlloader.h
 * Author: fdueber
 *
 * Created on March 20, 2016, 4:15 PM
 */

#ifndef URLLOADER_H
#define URLLOADER_H

#include <string>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class UrlLoader
{
	protected:
		virtual	bool				read(const string url, ostream& oStream);

	public:
									UrlLoader();
		virtual						~UrlLoader();

		virtual	string				readHtml (const string url);
		virtual	string				readImage(const string url);
};

}  //  namespace Offshore
#endif  //  URLLOADER_H