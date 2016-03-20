#include "fileloader.h"
#include "filehelper.h"
#include <sstream>
#include <fstream>

namespace Offshore {

//-----------------------------------------------------------------------------
FileLoader::FileLoader()
{}

//-----------------------------------------------------------------------------
FileLoader::~FileLoader()
{}

//-----------------------------------------------------------------------------
string FileLoader::readHtml(const string url)
{
	ifstream		inFile(FileHelper::generateFileName(url), ifstream::binary);
	stringstream	sStream;

	if (inFile.good()) {
		sStream << inFile.rdbuf();
		inFile.close();
	}

	return sStream.str();
}

}  //  namespace Offshore
