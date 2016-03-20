/* 
 * File:   filehelper.h
 * Author: fdueber
 *
 * Created on March 20, 2016, 5:10 PM
 */

#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class FileHelper
{
	public:
		static	string				generateFileName(const string url);
};

}  //  namespace Offshore
#endif  //  FILEHELPER_H