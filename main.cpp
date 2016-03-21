#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include "options.h"
#include "sitecrawler.h"

using namespace	Offshore;

int main(int argc, char** argv)
{
	SiteCrawler	crawler;

	//  initialize options
	if (!Options::getInstance()->parse(argc, argv)) {
		delete Options::getInstance();
		return EX_USAGE;
	}

	//  crawl url
	crawler.crawl(argv[optind + 1]);

	//  clean up
	delete Options::getInstance();
	return EX_OK;
}

