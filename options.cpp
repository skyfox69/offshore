#include "options.h"
#include <unistd.h>
#include <fstream>

namespace Offshore {

//-----------------------------------------------------------------------------
Options*	Options::_pInstance = nullptr;

//-----------------------------------------------------------------------------
Options::Options()
{}

//-----------------------------------------------------------------------------
Options::~Options()
{}

//-----------------------------------------------------------------------------
Options* Options::getInstance()
{
	if (_pInstance == nullptr) {
		_pInstance = new Options();
	}
	return _pInstance;
}

//-----------------------------------------------------------------------------
bool Options::parse(int argc, char** argv)
{
	int		opt(0);
	
	while ((opt = getopt(argc, argv, "b:cd:D:e:E:hi:I:jl:o:r:t:T:xY:z:Z:")) != -1) {
		switch (opt) {
			case 'b':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a backup directory!\033[0m\n");
					return usage();
				}
				_backupDir = optarg;
				break;
			case 'c':
				_includeCss = true;
				break;
			case 'd':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify an image/video name!\033[0m\n");
					return usage();
				}
				_imageIncludes[optarg] = optarg;
				break;
			case 'D':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a image/video name file!\033[0m\n");
					return usage();
				}
				parseFile(_imageIncludes, optarg);
				break;
			case 'e':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link text!\033[0m\n");
					return usage();
				}
				_linkExcludes[optarg] = optarg;
				break;
			case 'E':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link text file!\033[0m\n");
					return usage();
				}
				parseFile(_linkExcludes, optarg);
				break;
			case 'h':
				_parseHeader = true;
				break;
			case 'i':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link text!\033[0m\n");
					return usage();
				}
				_linkIncludes[optarg] = optarg;
				break;
			case 'I':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link text file!\033[0m\n");
					return usage();
				}
				parseFile(_linkIncludes, optarg);
				break;
			case 'j':
				_includeJs = true;
				break;
			case 'l':
				if (*optarg == 'l') {
					_showLinks = true;
				} else if (*optarg == 'i') {
					_showImages = true;
				} else if (*optarg == 'v') {
					_showUnused = true;
				} else {
					return usage();
				}
				break;
			case 'o':
				if (*optarg == '0') {
					_localOnly = true;
				}
				break;
			case 'r':
				_recurseDepth = atoi(optarg);
				break;
			case 't':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify an object identifier!\033[0m\n");
					return usage();
				}
				_domExcludes[optarg] = optarg;
				break;
			case 'T':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify an object text file!\033[0m\n");
					return usage();
				}
				parseFile(_domExcludes, optarg);
				break;
			case 'x':
				_removeUnused = true;
				break;
			case 'Y':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a target file!\033[0m\n");
					return usage();
				}
				_youtubeDlFileName = optarg;
				break;
			case 'z':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link definition file!\033[0m\n");
					return usage();
				}
				_linkFileNameR = optarg;
				break;
			case 'Z':
				if (*optarg == 0) {
					printf("\x1B[31mPlease specify a link definition file!\033[0m\n");
					return usage();
				}
				_linkFileNameW = optarg;
				break;
			default:
				return usage();
		}  //  switch (opt)
	}  //  while ((opt = getopt(argc, argv, ...

	//  check for arguments
	if ((argc - optind) != 2) {
		return usage();
	}

	//  set base directory
	_baseDir = argv[optind];

	return true;
}

//-----------------------------------------------------------------------------
bool Options::parseFile(map<string, string>& mapTarget, const string fileName)
{
	ifstream	inFile(fileName);

	if (inFile.good()) {
		string		tString;

		while (getline(inFile, tString)) {
			mapTarget[tString] = tString;
		}

		inFile.close();
	}

	return true;
}

//-----------------------------------------------------------------------------
bool Options::usage()
{
	printf("\nUsage: offshore [options] TARGET URL\n"
			"Download URL to local file.\n\n"
			"  -b DIR\tsave backup copy to DIR before parsing\n"
			"  -c\t\tinclude CSS files\n"
			"  -d TEXT\tdownload images/movies containing TEXT in path (multiple occurancy possible)\n"
			"  -D FILE\tdownload images/movies containing texts defined in FILE\n"
			"  -e TEXT\texclude links containing TEXT (multiple occurancy possible)\n"
			"  -E FILE\texclude links containing texts defined in FILE\n"
			"  -h\t\tconsider links in page header (default: false)\n"
			"  -i TEXT\tinclude links containing TEXT (multiple occurancy possible)\n"
			"  -I FILE\tinclude links containing texts defined in FILE\n"
			"  -j\t\tinclude JavaScript files\n"
			"  -li\t\tshow all referenced images\n"
			"  -ll\t\tshow all referenced links\n"
			"  -lv\t\tshow all unused images\n"
			"  -o0\t\tuse local files only, don't download anything\n"
			"  -r DEPTH\trecursive follow links upto given depth\n"
			"  -t TEXT\tremove DOM objects having TEXT. Tags, classes and ids are supported (multiple occurancy possible)\n"
			"  -T FILE\tremove DOM objects defined in FILE. Tags, classes and ids are supported\n"
			"  -Y FILE\twrite youtube links to FILE for use with youtube-dl\n"
			"  -x\t\tremove unused images\n"
			"  -z FILE\tuse existing links-files defines within FILE\n"
			"  -Z FILE\twrite links-files defines to FILE\n"
			"\n"
		);
	return false;
}

}  //  namespace Offshore
