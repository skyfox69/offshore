#include "pageanalyzer.h"
#include "options.h"

namespace Offshore {

//-----------------------------------------------------------------------------
PageAnalyzer::PageAnalyzer(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt)
	:	_mapLinks  (mapLink),
		_mapImages (mapImg),
		_mapYoutube(mapYt)
{}

//-----------------------------------------------------------------------------
PageAnalyzer::~PageAnalyzer()
{}

//-----------------------------------------------------------------------------
int PageAnalyzer::analyze(const string html, const unsigned char depth, const string tag, vector<string>& localLinks)
{
	string	locTag  (tag + "=\"");
	size_t	posStart(0);
	size_t	posEnd  (0);
	char	match   ('"');

	//  ignore links within header
	if (!Options::getInstance()->_parseHeader) {
		posStart = html.find("<body");
		if (posStart == string::npos) {
			return 0;
		}
	}

	//  get first tag
	posEnd   = posStart;
	posStart = html.find(locTag, posEnd);
	if (posStart == string::npos) {
		locTag   = tag + "='";
		posStart = html.find(locTag, posEnd);
		match    = '\'';
	}

	//  get each tag
	while (posStart != string::npos) {
		posStart += locTag.length();
		posEnd    = html.find(match, posStart);
		if (posEnd != string::npos) {
			UrlLink		tmpLink(html.substr(posStart, (posEnd - posStart)), depth);

			//  valid image
			if (tmpLink.isValidImage()) {
				_mapImages[tmpLink.slug()] = tmpLink;
			}
			//  valid link
			else if (tmpLink.isValidLink()) {
				_mapLinks[tmpLink.slug()] = tmpLink;
				localLinks.push_back(tmpLink.slug());
			}

			//  valid youtube
			if (tmpLink.isValidYoutube()) {
				_mapYoutube[tmpLink.slug()] = tmpLink;
			}

			//  get next tag
			match  = '"';
			locTag = tag + "=\"";
			posStart = html.find(locTag, posEnd);
			if (posStart == string::npos) {
				locTag   = tag + "='";
				posStart = html.find(locTag, posEnd);
				match    = '\'';
			}
		}  //  if (posEnd != string::npos)
	}  //  while (posStart != string::npos)
	
	return localLinks.size();
}

}  //  namespace Offshore
