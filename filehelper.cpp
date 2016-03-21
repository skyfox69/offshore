#include "filehelper.h"
#include <algorithm>

namespace Offshore {

//-----------------------------------------------------------------------------
string FileHelper::generateFileName(const string url, const bool isImage)
{
	string	fileName(url);
	size_t	pos     (0);

	//  remove http://
	while ((pos = fileName.find("http://", pos)) != string::npos) {
		fileName.replace(pos, 7, "");
	}

	//  remove https://
	pos = 0;
	while ((pos = fileName.find("https://", pos)) != string::npos) {
		fileName.replace(pos, 8, "");
	}

	//  replace / with _
	replace(fileName.begin(), fileName.end(), '/', '_');

	//  replace . with _
	replace(fileName.begin(), fileName.end(), '.', '_');

	//  append .html if not set
	if (!isImage && (fileName.find_last_of(".html") != (fileName.length() - 5))) {
		fileName += ".html";
	}

	return fileName;
}

}  //  namespace Offshore
