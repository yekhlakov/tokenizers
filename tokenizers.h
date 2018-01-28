#ifndef MAXY_TOKENIZERS
#define MAXY_TOKENIZERS

#include <vector>
#include <string>

namespace maxy
{
	/**
	 * Simple but powerful tokenizer for lines (i.e. single-line strings)
	 * maxy@maxy.ru
	 */
	class LineTokenizer
	{
		std::vector<std::string> tokens;
		size_t it;

	public:
		// constructors and assignments
		LineTokenizer () : tokens{}, it{0} {}
		LineTokenizer (const LineTokenizer & t) : tokens{t.tokens}, it{t.it} {}
		LineTokenizer (LineTokenizer && t) : tokens{t.tokens}, it{t.it} { t.clear (); }
		LineTokenizer (std::string src) { tokenize (src); } // construct from string
		LineTokenizer & operator= (const LineTokenizer & t) { tokens = t.tokens; it = t.it; }
		LineTokenizer & operator= (LineTokenizer && t) { tokens = t.tokens; it = t.it; t.clear (); }
		operator bool () { return tokens.size () > 0; }

		// some proxies to internal representation
		auto begin () const { return tokens.begin (); }
		auto end () const { return tokens.end (); }
		size_t size () const { return tokens.size (); }

		// tokenize a string
		size_t tokenize (const std::string & src);

		bool has_next () const { return it < tokens.size (); }; // check if we have any more tokens
		void clear () { tokens.clear (); restart (); }; // clear tokenizer
		void restart () { it = 0; }; // restart internal iterator

		std::string next_string (); // get next string
		int next_int (); // get next int
		int next_int (int ref); //get next int with reference value
		float next_float (); // get next float
		float next_float (float ref); // get next float with reference value
	};

	/**
	 * Simple but powerful tokenizer for files (= for multiline strings)
	 * maxy@maxy.ru
	 */
	class FileTokenizer
	{
		std::vector<LineTokenizer> lines;
		size_t it;

	public:
		// constructors and assignments
		FileTokenizer () : lines{}, it{0} {}
		FileTokenizer (const FileTokenizer & t) : lines{t.lines}, it{t.it} {}
		FileTokenizer (FileTokenizer && t) : lines{t.lines}, it{t.it} { t.clear (); }
		FileTokenizer (std::string src) { tokenize (src); } // construct from string
		FileTokenizer & operator= (const FileTokenizer & t) { lines = t.lines; it = t.it; }
		FileTokenizer & operator= (FileTokenizer && t) { lines = t.lines; it = t.it; t.clear (); }

		// some proxies to internal representation
		auto begin () const { return lines.begin (); }
		auto end () const { return lines.end (); }
		size_t size () const { return lines.size (); }

		bool has_next () const { return it < lines.size (); }; // check if we have any more lines
		void clear () { lines.clear (); restart (); }; // clear tokenizer
		void restart () { it = 0; }; // restart internal iterator

		size_t tokenize (const std::string & src);
		const LineTokenizer & next_line ();
	};
}

#endif // MAXY_TOKENIZERS
