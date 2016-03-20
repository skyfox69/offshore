/* 
 * File:   fileloader.h
 * Author: fdueber
 *
 * Created on March 20, 2016, 4:32 PM
 */

#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class FileLoader
{
	public:
									FileLoader();
		virtual						~FileLoader();

		virtual	string				readHtml(const string url);
};

}  //  namespace Offshore
#endif  //  FILELOADER_H