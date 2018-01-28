#pragma once
#include <iostream>
#include "tokenizers.h"

/**
 * iostream operators for tokenizers
 */
namespace maxy
{
	std::ostream & operator<< (std::ostream & o, const LineTokenizer & lt)
	{
		for (auto t : lt) o << "\t" << t << "\n";
		return o;
	}

	std::ostream & operator<< (std::ostream & o, const FileTokenizer & ft)
	{
		for (auto lt : ft) o << "line:\n" << lt;
		return o;
	}
}
