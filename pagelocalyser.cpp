#include "pagelocalyser.h"

namespace Offshore {

//-----------------------------------------------------------------------------
PageLocalyser::PageLocalyser(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg, map<string, UrlLink>& mapYt)
	:	_mapLinks  (mapLink),
		_mapImages (mapImg),
		_mapYoutube(mapYt)
{}

//-----------------------------------------------------------------------------
PageLocalyser::~PageLocalyser()
{}

}  //  namespace Offshore
