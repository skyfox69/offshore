/* 
 * File:   options.h
 * Author: fdueber
 *
 * Created on March 20, 2016, 1:02 PM
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <map>

using namespace std;

namespace Offshore {
//-----------------------------------------------------------------------------
class Options
{
	private:
		static	Options*			_pInstance;

	protected:
									Options();
		virtual	bool				usage();
		virtual	bool				parseFile(map<string, string>& mapTarget, const string fileName);

	public:
		map<string, string>			_linkIncludes;
		map<string, string>			_linkExcludes;
		map<string, string>			_imageIncludes;
		string						_linkFileNameR;
		string						_linkFileNameW;
		string						_youtubeDlFileName;
		string						_baseDir;
		unsigned char				_recurseDepth = 0;
		bool						_includeCss   = false;
		bool						_includeJs    = false;
		bool						_localOnly    = false;
		bool						_parseHeader  = false;
		bool						_showImages   = false;
		bool						_showLinks    = false;

		virtual						~Options();
		static	Options*			getInstance();

		virtual	bool				parse(int argc, char** argv);
};

}  //  namespace Offshore
#endif  //  OPTIONS_H