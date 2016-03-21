#include "sitecrawler.h"
#include "options.h"
#include <sys/stat.h>
#include <vector>

namespace Offshore {

//-----------------------------------------------------------------------------
SiteCrawler::SiteCrawler()
{
	_pOptions = Options::getInstance();
}

//-----------------------------------------------------------------------------
SiteCrawler::~SiteCrawler()
{}

//-----------------------------------------------------------------------------
bool SiteCrawler::crawlRecursive(UrlLink& link, const unsigned char depth)
{
	vector<string>		tmpLinks;
	string				html;

	//  get html form local file
	html = _fileLoader.readHtml(link._link, link.pathName());

	//  fallback to online if permittet
	if (html.empty() && !_pOptions->_localOnly) {
		html = _urlLoader.readHtml(link._link);
		_fileLoader.writeHtml(html, link.pathName());
	}
	fprintf(stderr, "size of %s: %ld\n", link._link.c_str(), html.size());

	//  analyse links



	//  recursive parse links
	if (depth < _pOptions->_recurseDepth) {
		for (auto& url : tmpLinks) {
			crawlRecursive(_mapLinks[url], depth + 1);
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
bool SiteCrawler::crawl(const string url)
{
	fprintf(stderr, "crawling: %s => %s\n", url.c_str(), _pOptions->_baseDir.c_str());

	//  initialize lists
	_mapImages.clear();
	_mapLinks.clear();
	_mapYoutube.clear();

	//  create target directory
	struct	stat		st = {0};

	if (stat(("./" + _pOptions->_baseDir).c_str(), &st) == -1) {
		fprintf(stderr, "creating target directory\n");
		mkdir(("./" + _pOptions->_baseDir).c_str(), 0775);
	}

	//  insert initial link
	UrlLink		tLink(url, 0);

	_mapLinks[tLink.slug()] = tLink;

	//  recursive parse urls/links
	crawlRecursive(_mapLinks[tLink.slug()], 0);

	



	//  show list of links
	if (_pOptions->_showLinks) {
		fprintf(stderr, "\nfound links:\n");
		for (auto& link : _mapLinks) {
			fprintf(stderr, "  %02d - %s\n", link.second._depth, link.first.c_str());
		}
		fprintf(stderr, "\n");
	}

	//  show list of images
	if (_pOptions->_showImages) {
		fprintf(stderr, "\nfound images:\n");
		for (auto& link : _mapImages) {
			fprintf(stderr, "  %02d - %s\n", link.second._depth, link.first.c_str());
		}
		fprintf(stderr, "\n");
	}

	return true;
}

}  //  namespace Offshore
