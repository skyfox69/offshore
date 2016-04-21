#include "sitecrawler.h"
#include "options.h"
#include "pageanalyser.h"
#include "pagelocalyser.h"
#include <sys/stat.h>
#include <vector>

namespace Offshore {

//-----------------------------------------------------------------------------
SiteCrawler::SiteCrawler()
{
	_pOptions   = Options::getInstance();
	_pAnalyser  = new PageAnalyser (_mapLinks, _mapImages, _mapYoutube);
	_pLocalyser = new PageLocalyser(_mapLinks, _mapImages);
}

//-----------------------------------------------------------------------------
SiteCrawler::~SiteCrawler()
{
	if (_pAnalyser != nullptr)		delete _pAnalyser;
	if (_pLocalyser != nullptr)		delete _pLocalyser;
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
	_pAnalyser->analyse(html, link._depth + 1, "href", localLinks);
	_pAnalyser->analyse(html, link._depth + 1, "src", localLinks);

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

	//  create backup directory
	if (!_pOptions->_backupDir.empty()) {
		if (stat(("./" + _pOptions->_backupDir).c_str(), &st) == -1) {
			fprintf(stderr, "creating backup directory\n");
			mkdir(("./" + _pOptions->_backupDir).c_str(), 0775);
		}
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

	//  localise pages
	_pLocalyser->localyse();

	//  show list of unused images
	if (_pOptions->_showUnused) {
		fprintf(stderr, "\nunused images:\n");
		for (auto& link : _mapImages) {
			if (!link.second._used) {
				fprintf(stderr, "  %02d - %s\n", link.second._depth, link.first.c_str());
			}
		}
		fprintf(stderr, "\n");
	}

	//  remove unused images
	if (_pOptions->_removeUnused) {
		fprintf(stderr, "\ndeleting unused images:\n");
		for (auto& link : _mapImages) {
			if (!link.second._used) {
				remove(link.second.pathName().c_str());
				fprintf(stderr, "  deleted: %s\n", link.second.pathName().c_str());
			}
		}
		fprintf(stderr, "\n");
	}

	


	return true;
}

}  //  namespace Offshore
