#include "sitecrawler.h"
#include "options.h"
#include "pageanalyzer.h"
#include "pagelocalizer.h"
#include <sys/stat.h>
#include <vector>

namespace Offshore {

//-----------------------------------------------------------------------------
SiteCrawler::SiteCrawler()
{
	_pOptions   = Options::getInstance();
	_pAnalyzer  = new PageAnalyzer (_mapLinks, _mapImages, _mapYoutube);
	_pLocalyzer = new PageLocalyzer(_mapLinks, _mapImages, _mapYoutube);
}

//-----------------------------------------------------------------------------
SiteCrawler::~SiteCrawler()
{
	if (_pAnalyzer != nullptr)		delete _pAnalyzer;
	if (_pLocalyzer != nullptr)		delete _pLocalyzer;
}

//-----------------------------------------------------------------------------
int SiteCrawler::checkImages()
{
	int		downloaded(0);

	//  if online allowed
	if (!_pOptions->_localOnly) {
		//  for each image
		for (auto& image : _mapImages) {
			if (!_fileLoader.fileExists(image.second.pathName())) {
				fprintf(stderr, "### %s\n", image.second._link.c_str());
				_urlLoader.readImage(image.second._link, image.second.pathName());
			}
		}  //  for (auto& image : _mapImages)
	}  //  if (!_pOptions->_localOnly)

	return downloaded;
}

//-----------------------------------------------------------------------------
bool SiteCrawler::crawlRecursive(UrlLink& link)
{
	vector<string>		localLinks;
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
	_pAnalyzer->analyze(html, link._depth + 1, "href", localLinks);
	_pAnalyzer->analyze(html, link._depth + 1, "src", localLinks);

	//  recursive parse links
	if (link._depth < _pOptions->_recurseDepth) {
		for (auto& url : localLinks) {
			crawlRecursive(_mapLinks[url]);
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
	crawlRecursive(_mapLinks[tLink.slug()]);

	//  download images if online allowed
	checkImages();

	//  show list of links
	if (_pOptions->_showLinks) {
		fprintf(stderr, "\nfound links: (%d)\n", _mapLinks.size());
		for (auto& link : _mapLinks) {
			fprintf(stderr, "  %02d - %s\n", link.second._depth, link.first.c_str());
		}
		fprintf(stderr, "\n");
	}

	//  show list of images
	if (_pOptions->_showImages) {
		fprintf(stderr, "\nfound images: (%d)\n", _mapImages.size());
		for (auto& link : _mapImages) {
			fprintf(stderr, "  %02d - %s\n", link.second._depth, link.first.c_str());
		}
		fprintf(stderr, "\n");
	}

	//  localyze pages
	//_pLocalyzer->tueWas()

	


	return true;
}

}  //  namespace Offshore
