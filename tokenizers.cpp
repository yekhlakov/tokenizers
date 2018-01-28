#include "tokenizers.h"

/**
 * Nontrivial members for tokenizers
 * maxy@maxy.ru
 */
namespace maxy
{
	size_t LineTokenizer::tokenize (const std::string & src)
	{
		clear ();

		char * text = (char*) alloca (src.size () + 1);

		size_t ptr = 0, optr = 0;
		char delimiter;
		int state = 'SKIP';	// skip whitespace

		while (ptr < src.size ())
		{
			// current char
			char c = src[ptr];

			if (state == 'SKIP')
			{
				// skip whitespace and tabs
				if (c == ' ' || c == 9)
				{
					ptr++;
					continue;
				}

				// exit if we have reached eoln or eos
				if (c == 0 || c == 0x0d || c == 0x0a)
				{
					break;
				}

				// exit if we have reached a comment
				if (c == '#' || (c == '/' && ptr < src.size () - 1 && src[ptr + 1] == '/'))
				{
					break;
				}

				// non-whitespace, non-eoln symbol found -> token start

				// check for quotes
				if (c == '"' || c == '`' || c == '\'')
				{
					delimiter = c;
					state = 'QUOT';
					ptr++;
					continue;
				}
				// TODO: brackets
				else
					state = 'WORD';
			}

			// end of quoted token
			if (state == 'QUOT' && c == delimiter)
			{
				text[optr] = 0;
				if (optr)
					tokens.push_back (text);
				optr = 0;
				ptr++;
				state = 'SKIP';
				continue;
			}

			// eoln/eos inside quoted token
			if (state == 'QUOT' && (c == 0 || c == 0x0d || c == 0x0a))
			{
				text[optr] = 0;
				if (optr)
					tokens.push_back (text);
				optr = 0;
				break;
			}

			// end of unquoted token
			if (state == 'WORD' && (c == ' ' || c == 9 || c == 0 || c == 0x0d || c == 0x0a))
			{
				text[optr] = 0;
				if (optr)
					tokens.push_back (text);
				optr = 0;
				state = 'SKIP';
				continue;
			}

			// any other symbol inside token
			text[optr++] = c;
			ptr++;
		}

		// also add the final token if present
		if (optr)
		{
			text[optr] = 0;
			tokens.push_back (text);
		}

		return ptr;
	}

	std::string LineTokenizer::next_string ()
	{
		if (!has_next ()) return std::string{};
		return tokens[it++];
	}

	int stoi_nothrow (const std::string & s)
	{
		try
		{
			return std::stoi (s, nullptr, 0);
		}
		catch (...)
		{
			return 0;
		}
	}

	float stof_nothrow (const std::string & s)
	{
		try
		{
			return std::stof (s);
		}
		catch (...)
		{
			return 0;
		}
	}

	int LineTokenizer::next_int ()
	{
		if (!has_next ()) return 0;

		return stoi_nothrow (tokens[it++]);
	}

	int LineTokenizer::next_int (int ref)
	{
		if (!has_next ()) return 0;

		int v = stoi_nothrow (tokens[it]);

		if (tokens[it][tokens[it].size () - 1] == '%')
			v = int (v * ref * 0.01);

		if (v < 0) v += ref;
		it++;
		return v;
	}

	float LineTokenizer::next_float ()
	{
		if (!has_next ()) return 0;

		return stof_nothrow (tokens[it++]);
	}

	float LineTokenizer::next_float (float ref)
	{
		if (!has_next ()) return 0;

		float v = stof_nothrow (tokens[it]);

		if (tokens[it][tokens[it].size () - 1] == '%')
			v = float (v * ref * 0.01);

		if (v < 0) v += ref;
		it++;
		return v;
	}

	// "null reference"
	LineTokenizer empty_line_tokenizer{};

	size_t FileTokenizer::tokenize (const std::string & src)
	{
		clear ();

		size_t end = 0;

		while (end < src.size ())
		{
			LineTokenizer p{src.c_str () + end};
			if (p)
				lines.push_back (p);

			while (end < src.size () && src[end] && src[end] != 0x0d && src[end] != 0x0a)
				end++;

			if (src[end] == 0x0d || src[end] == 0x0a)
				end++;
		}

		restart ();
		return end;
	}

	LineTokenizer & FileTokenizer::next_line ()
	{
		if (!has_next ()) return empty_line_tokenizer;
		return lines[it++];
	}
}
