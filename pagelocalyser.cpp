#include "pagelocalyser.h"
#include "options.h"
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
int PageLocalyser::processDOMTag(string& html, string tag)
{
	int		processed(0);
	size_t	posStart (0);
	size_t	posEnd   (0);

	while ((posStart = html.find('<' + tag, posStart)) != string::npos) {
		posEnd = html.find(tag + '>', posStart+tag.length());
		if (posEnd != string::npos) {
			posEnd += (tag.length() + 1);
			html.replace(posStart, posEnd - posStart, "");
		}
		
		posStart = posEnd;

	}  //  while ((posStart = html.find('<' + tag, posStart)) != string::npos)

	return processed;
}

//-----------------------------------------------------------------------------
int PageLocalyser::processDOMId(string& html, string id)
{
	string	tag;
	int		processed(0);
	size_t	posStart (0);
	size_t	posEnd   (0);

	while ((posStart = html.find("id=\"" + id + "\"", posStart)) != string::npos) {
		//  find tag id belongs to
		size_t	posDomStart(html.rfind('<', posStart));

		if (posDomStart != string::npos) {
			tag = html.substr(posDomStart+1, html.find(' ', posDomStart)-posDomStart-1);
			if (!tag.empty()) {
				int		openTags(1);

				posStart = posDomStart + tag.length();
				while ((posStart = html.find(tag, posStart)) != string::npos) {
					if (html[posStart - 1] == '<') {
						++openTags;
					} else if (html[posStart - 1] == '/') {
						--openTags;
						if (openTags == 0) {
							posEnd = html.find('>', posStart);
							if (posEnd != string::npos) {
								html.replace(posDomStart, posEnd - posDomStart+1, "");
								posStart = posDomStart;
								break;
							}
						}
					}
					posStart += tag.length();
				}  //  while ((posStart = html.find(tag, posStart)) != string::npos)
			}  //  if (!tag.empty())
		}  //  if (posTStart != string::npos)

		posStart = posEnd;

	}  //  while ((posStart = html.find('<' + tag, posStart)) != string::npos)

	return processed;
}

//-----------------------------------------------------------------------------
int PageLocalyser::processDOMClass(string& html, string cls)
{
	string	tag;
	int		processed(0);
	size_t	posStart (0);
	size_t	posEnd   (0);

	while ((posStart = html.find("class=\"" + cls + "\"", posStart)) != string::npos) {
		//  find tag id belongs to
		size_t	posDomStart(html.rfind('<', posStart));

		if (posDomStart != string::npos) {
			tag = html.substr(posDomStart+1, html.find(' ', posDomStart)-posDomStart-1);
			if (!tag.empty()) {
				int		openTags(1);

				posStart = posDomStart + tag.length();
				while ((posStart = html.find(tag, posStart)) != string::npos) {
					if (html[posStart - 1] == '<') {
						++openTags;
					} else if (html[posStart - 1] == '/') {
						--openTags;
						if (openTags == 0) {
							posEnd = html.find('>', posStart);
							if (posEnd != string::npos) {
								html.replace(posDomStart, posEnd - posDomStart+1, "");
								posStart = posDomStart;
								break;
							}
						}
					}
					posStart += tag.length();
				}  //  while ((posStart = html.find(tag, posStart)) != string::npos)
			}  //  if (!tag.empty())
		}  //  if (posTStart != string::npos)

		posStart = posEnd;

	}  //  while ((posStart = html.find('<' + tag, posStart)) != string::npos)

	return processed;
}

//-----------------------------------------------------------------------------
int PageLocalyser::processDOMTree(string& html)
{
	int		processed(0);

	//  for each DOM exclusion
	for (auto& exclude : Options::getInstance()->_domExcludes) {
		switch (exclude.second[0]) {
			case '.':		//  class
				processed += processDOMClass(html, exclude.second.substr(1));
				break;
			case '#':		//  id
				processed += processDOMId(html, exclude.second.substr(1));
				break;
			default:		//  tag
				processed += processDOMTag(html, exclude.second);
		}
	}  //  for (auto& tag : Options::getInstance()->_domExcludes)

	return processed;
}

//-----------------------------------------------------------------------------
int PageLocalyser::localyse()
{
	Options*		pOptions(Options::getInstance());
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
				fprintf(stderr, "processing: %s\n", link.slug().c_str());

				//  backup File if wanted
				if (!pOptions->_backupDir.empty()) {
					string	backupPath(pOptions->_backupDir + "/" + link.fileName());

					ofstream	outFile(backupPath, ofstream::binary);

					if (outFile.good()) {
						outFile.write(html.c_str(), html.length());
						outFile.flush();
						outFile.close();
					}
				}  //  if (!pOptions->_backupDir.empty())

				//  localyse links
				for (auto& repEntry : _mapLinks) {
					//  skip empty link
					if (repEntry.second._link.empty())		continue;

					//  for each match
					for (auto& match : matches) {
						replaced += replaceAll(html, repEntry.second._link, repEntry.second.fileName(), match);
					}
				}  //  for (auto& repEntry : _mapLinks)

				//  localyse images
				for (auto& repEntry : _mapImages) {
					//  skip empty link
					if (repEntry.second._link.empty())		continue;

					//  for each match
					for (auto& match : matches) {
						replaced += replaceAll(html, repEntry.second.slug(), repEntry.second.fileName(), match);
					}
				}  //  for (auto& repEntry : _mapLinks)

				//  process DOM-tree if wanted
				if (!pOptions->_domExcludes.empty()) {
					processDOMTree(html);
				}

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
