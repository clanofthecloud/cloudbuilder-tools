struct Tokenizer {
	const char *text;
	enum Type {End = 0, Whitespace, Letter, Number, SimpleQuotemark, DoubleQuotemark, OpeningBrace, ClosingBrace, OpeningBracket, ClosingBracket, Unknown};
	Tokenizer(const char *text): text(text) {}
	Type nextWord(char *dest, int maxSize) {
		char c;
		Type ret, t, closingChar = End;
		nextChar(c, ret);
		switch (ret) {
		case End:
			break;
		case Whitespace:
			return nextWord(dest, maxSize);
		case Letter:
			do {
				if (maxSize > 1) {
					*dest++ = c, maxSize--;
				}
				nextChar(c, t);
			} while (t == Letter || t == Number);
			putBack(c, t);
			break;
		case Number:
			do {
				if (maxSize > 1) {
					*dest++ = c, maxSize--;
				}
				nextChar(c, t);
			} while (t == Number);
			putBack(c, t);
			break;
		case OpeningBrace:
			if (!closingChar) { closingChar = ClosingBrace; }
		case ClosingBracket:
			if (!closingChar) { closingChar = ClosingBracket; }
		case SimpleQuotemark:
		case DoubleQuotemark:
			if (!closingChar) { closingChar = t; }
			if (maxSize > 1) { *dest++ = c, maxSize--; }
			nextChar(c, t);
			while (t != closingChar && t != End) {
				if (maxSize > 1) {
					*dest++ = c, maxSize--;
				}
				nextChar(c, t);
			}
			if (maxSize > 1) { *dest++ = c, maxSize--; }
			break;
		}
		if (maxSize > 0) { *dest = 0; }
		return ret;
	}

	template<size_t S> Type nextWord(char (&dest)[S]) { return nextWord(dest, S); }

	void nextChar(char &c, Type &t) {
		if (!*text) { t = End, c = 0; return; }

		c = *text++;
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n') { t = Whitespace; }
		else if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') { t = Letter; }
		else if (c >= '0' && c <= '9') { t = Number; }
		else if (c == '\"') { t = DoubleQuotemark; }
		else if (c == '\'') { t = SimpleQuotemark; }
		else if (c == '{') { t = OpeningBrace; }
		else if (c == '}') { t = ClosingBrace; }
		else { t = Unknown; }
	}

	void putBack(char c, Type t) { if (t != End) text--; }
};
