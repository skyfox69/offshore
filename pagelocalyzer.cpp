#include "pagelocalizer.h"

namespace Offshore {

//-----------------------------------------------------------------------------
PageLocalyzer::PageLocalyzer(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt)
	:	_mapLinks  (mapLink),
		_mapImages (mapImg),
		_mapYoutube(mapYt)
{}

//-----------------------------------------------------------------------------
PageLocalyzer::~PageLocalyzer()
{}

}  //  namespace Offshore
