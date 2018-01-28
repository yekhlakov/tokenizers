#include "tokenizers_ostream.h"

void line_tokenizer_test ()
{
	std::cout << "\nLine tokenizer\n==============\n";

	// General test of quotes and comments
	maxy::LineTokenizer lt{" tokenizer  test\t'single quote' \"double quote\" `back quote` // comment"};
	// assignment
	auto x = lt;
	std::cout << "General test\n";
	// line tokenizer can be iterated over
	for (auto t : x)
		std::cout << "token: " << t << "\n";

	// Numbers test
	maxy::LineTokenizer ltn{"numbers 123 -1.3e-13 75% -3% \t\t# comment"};
	std::cout << "\nNumbers test\n";
	std::cout << "has_next: " << ltn.has_next () << "\n";
	std::cout << "string: " << ltn.next_string () << "\n";
	std::cout << "int: " << ltn.next_int () << "\n";
	std::cout << "float: " << ltn.next_float () << "\n";
	std::cout << "int(200): " << ltn.next_int (200) << "\n";
	std::cout << "float(200): " << ltn.next_float (200) << "\n";
	std::cout << "has_next: " << ltn.has_next () << "\n";

	// Weird case tests
	maxy::LineTokenizer lt2{"missing \"quote 'test'"};
	std::cout << "\nMissing quote test\n" << lt2;

	maxy::LineTokenizer lt3{""};
	std::cout << "\nEmpty string test (should produce no output)\n" << lt3;

	maxy::LineTokenizer lt4{"\t\t\t\n\n\n"};
	std::cout << "\nAll-whitespace string test (should produce no output)\n" << lt4;

	maxy::LineTokenizer lt5{"this string contains newline\n and tokens after that are ignored"};
	std::cout << "\nNewline test\n" << lt5;
}

void file_tokenizer_test ()
{
	std::cout << "\nFile tokenizer\n==============\n";

	maxy::FileTokenizer ft
	{
		"this file\n"
		"contains\r\n"
		"several \"lines\" 'with' `various\n"
		"\n\n//this will be ignored\n"
		"  \t tokens 3.14 666 -0.1e2"
	};
	auto x = ft;
	std::cout << "\nGeneral test\nRegular iteration\n";
	for (auto lt : x)
	{
		std::cout << "line:\n";
		for (auto t : lt)
			std::cout << "\t" << t << "\n";
	}

	std::cout << "\nAlternative iteration\n";
	maxy::FileTokenizer ft1{"one more\rfile tokenizer"};
	while (ft1.has_next ())
		std::cout << "line:\n" << ft1.next_line ();

	maxy::FileTokenizer ft2{""};
	std::cout << "\nEmpty tokenizer (this should produce no output)" << ft2;
}

int main ()
{
	line_tokenizer_test ();
	file_tokenizer_test ();
}