#include "filehelper.h"
#include "options.h"

namespace Offshore {

//-----------------------------------------------------------------------------
string FileHelper::generateFileName(const string url)
{
	string	fileName(url);

	


	return Options::getInstance()->_baseDir + "/" + fileName;
}

}  //  namespace Offshore
