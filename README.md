# tokenizers

**LineTokenizer** splits a string into a sequence of tokens (probably quoted and separated by whitespace).
**FileTokenizer** splits a multiline string (separated by any newline) into a sequence of **LineTokenizer**s.

* Put **tokenizers.cpp** and **tokenizers.h** into your project directory.
* Include **tokenizers.h** where you wish to use tokenizers. **tokenizers_ostream.h** may be included instead; it adds definitions of operators for stream output of both tokenizers.
* **test.cpp** provides extensive examples of tokenizer usage.

