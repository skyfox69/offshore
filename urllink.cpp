#include <string.h>
#include "urllink.h"
#include "options.h"
#include "filehelper.h"

namespace Offshore {

//-----------------------------------------------------------------------------
UrlLink::UrlLink(const string link, const unsigned char depth)
	:	_link (link),
		_depth(depth)
{}

//-----------------------------------------------------------------------------
UrlLink::~UrlLink()
{}

//-----------------------------------------------------------------------------
string UrlLink::slug()
{
	if (_slug.empty()) {
		_slug = _link;
		if (_slug.find_last_of('/') == (_slug.length() - 1)) {
			_slug.pop_back();
		}
	}
	return _slug;
}

//-----------------------------------------------------------------------------
string UrlLink::fileName()
{
	if (_fileName.empty()) {
		_fileName = FileHelper::generateFileName(_link, isValidImage());
	}
	return _fileName;
}

//-----------------------------------------------------------------------------
string UrlLink::pathName()
{
	return Options::getInstance()->_baseDir + "/" + fileName();
}

//-----------------------------------------------------------------------------
bool UrlLink::isValidImage()
{
	const char*		pText  (nullptr);
	string			tString(_link);
	size_t			pos    (tString.find('?'));
	bool			isValid(false);

	//  check for parameters
	if (pos != string::npos) {
		tString = tString.substr(0, pos);
	}

	// check last 4 bytes
	tString  = tString.substr(tString.length() - 4);
	pText    = tString.c_str();
	isValid |= (strcasecmp(pText, ".jpg") == 0);
	isValid |= (strcasecmp(pText, ".png") == 0);
	isValid |= (strcasecmp(pText, ".bmp") == 0);
	isValid |= (strcasecmp(pText, ".gif") == 0);

	return isValid;
}

//-----------------------------------------------------------------------------
bool UrlLink::isValidLink()
{
	Options*	pOptions(Options::getInstance());
	bool		isValid (_link.find('#') == string::npos);

	//  check positive
	if (isValid && (pOptions->_linkIncludes.size() > 0)) {
		isValid = false;
		for (auto& text : pOptions->_linkIncludes) {
			if (_link.find(text.second) != string::npos) {
				isValid = true;
				break;
			}
		}
	}

	//  check negative
	if (isValid && (pOptions->_linkExcludes.size() > 0)) {
		for (auto& text : pOptions->_linkExcludes) {
			if (_link.find(text.second) != string::npos) {
				isValid = false;
				break;
			}
		}
	}

	return isValid;
}

//-----------------------------------------------------------------------------
bool UrlLink::isValidYoutube()
{
	bool	isValid(_link.find("youtube.com") != string::npos);

	isValid |= (_link.find("youtu.be") != string::npos);

	return isValid;
}

//-----------------------------------------------------------------------------
UrlLink& UrlLink::operator =(const UrlLink other)
{
	_depth    = other._depth;
	_link     = other._link;
	_fileName = other._fileName;
	_slug     = other._slug;
	return *this;
}

//-----------------------------------------------------------------------------
ostream& operator<<(ostream& stream, const UrlLink& link)
{

	return stream;
}

//-----------------------------------------------------------------------------
istream& operator>>(istream& stream, UrlLink& link)
{


	return stream;
}

}  //  namespace Offshore
