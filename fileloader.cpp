#include "fileloader.h"
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
string FileLoader::readHtml(const string url, const string fileName)
{
	ifstream		inFile(fileName, ifstream::binary);
	stringstream	sStream;

	if (inFile.good()) {
		sStream << inFile.rdbuf();
		inFile.close();
	}

	return sStream.str();
}

//-----------------------------------------------------------------------------
bool FileLoader::writeHtml(const string html, const string fileName)
{
	ofstream	outFile(fileName, ofstream::binary);
	bool		retVal(false);
	
	if (outFile.good()) {
		outFile.write(html.c_str(), html.size());
		outFile.flush();
		outFile.close();
		retVal = true;
	}

	return retVal;
}

}  //  namespace Offshore
