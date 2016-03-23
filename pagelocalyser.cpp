#include "pagelocalyser.h"
#include <vector>
#include <fstream>
#include <sstream>

namespace Offshore {

//-----------------------------------------------------------------------------
PageLocalyser::PageLocalyser(map<string, UrlLink>& mapLink, map<string, UrlLink>& mapImg)
	:	_mapLinks  (mapLink),
		_mapImages (mapImg)
{}

//-----------------------------------------------------------------------------
PageLocalyser::~PageLocalyser()
{}

//-----------------------------------------------------------------------------
int PageLocalyser::replaceAll(string& html, const string search, const string replace, const char match)
{
	int		replaced(0);
	size_t	pos     (0);

	while ((pos = html.find((search + match), pos)) != string::npos) {
		html.replace(pos, search.length(), replace);
		pos += replace.length();
		++replaced;
	}

	return replaced;
}

//-----------------------------------------------------------------------------
int PageLocalyser::localyse()
{
	vector<char>	matches = { '"', '\'', '?'};
	int				replaced(0);

	//  for each link/file
	for (auto& entry : _mapLinks) {
		UrlLink&	link(entry.second);
		string		html;

		if (!link.fileName().empty()) {
			ifstream	inFile(link.pathName(), ifstream::binary);

			//  read file
			if (inFile.good()) {
				stringstream	sStream;

				sStream << inFile.rdbuf();
				inFile.close();
				html = sStream.str();
			}

			//  if valid html content
			if (!html.empty()) {
				//  localyse links
				for (auto& repEntry : _mapLinks) {
					//  skip empty link
					if (repEntry.second._link.empty())		continue;

					//  for each match
					for (auto& match : matches) {
						replaced += replaceAll(html, repEntry.second._link, repEntry.second.pathName(), match);
					}
				}  //  for (auto& repEntry : _mapLinks)

				//  localyse images
				for (auto& repEntry : _mapImages) {
					//  skip empty link
					if (repEntry.second._link.empty())		continue;

					//  for each match
					for (auto& match : matches) {
						replaced += replaceAll(html, repEntry.second._link, repEntry.second.pathName(), match);
					}
				}  //  for (auto& repEntry : _mapLinks)
				
				//  write mofified content
				ofstream	outFile(link.pathName(), ofstream::binary);

				if (outFile.good()) {
					outFile.write(html.c_str(), html.length());
					outFile.flush();
					outFile.close();
				}
			}  //  if (!html.empty())
		}  //  if (!link.fileName().empty())
	}  //  for (auto& entry : _mapLinks)

	return replaced;
}

}  //  namespace Offshore
