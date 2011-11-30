#include "HTTPMessage.h"

HTTPMessage::HTTPMessage() : ByteBuffer() {
    this->init();
}

HTTPMessage::HTTPMessage(string sData) : ByteBuffer(sData.size()+1) {
    putBytes((byte*)sData.c_str(), sData.size()+1);
    this->init();
}

HTTPMessage::HTTPMessage(byte* pData, unsigned int len) : ByteBuffer(pData, len) {
    this->init();
}

HTTPMessage::~HTTPMessage() {
    headers->clear();
    delete headers;
}

void HTTPMessage::init() {
    parseError = false;
	parseErrorStr = "";
    
    headers = new map<string, string>();
}

/**
 * Get Line
 * Retrive the entire contents of a line: string from current position until CR or LF, whichever comes first, then increment the read position
 * until it's past the last CR or LF in the line
 *
 * @return Contents of the line in a string (without CR or LF)
 */
string HTTPMessage::getLine() {
	string ret = "";
	int startPos = getReadPos();
	bool newLineReached = false;
	char c = 0;

	// Append characters to the return string until we hit the end of the buffer, a CR (13) or LF (10)
	for(unsigned int i = startPos; i < size(); i++) {
		// If the next byte is a \r or \n, we've reached the end of the line and should break out of the loop
		c = peek();
		if((c == 13) || (c == 10)) {
			newLineReached = true;
			break;
		}

		// Otherwise, append the next character to the string
		ret += getChar();
	}

	// If a line termination was never reached, discard the result and conclude there are no more lines to parse
	if(!newLineReached) {
		setReadPos(startPos); // Reset the position to before the last line read that we are now discarding
		ret = "";
		return ret;
	}

	// Increment the read position until the end of a CR or LF chain, so the read position will then point to the next line
	for(unsigned int i = getReadPos(); i < size(); i++) {
		c = getChar();
		if((c != 13) && (c != 10)) {
			// Set the Read position back one because the retrived character wasn't a LF or CR
			setReadPos(getReadPos()-1);
			break;
		}
	}

	return ret;
}

/**
 * getStrElement
 * Get a token from the current buffer, stopping at the delimiter. Returns the token as a string
 *
 * @param delim The delimiter to stop at when retriving the element. By default, it's a space
 * @return Token found in the buffer. Empty if delimiter wasn't reached
 */
string HTTPMessage::getStrElement(char delim) {
    string ret = "";
    int startPos = getReadPos();
    unsigned int size = 0;
    int endPos = find(delim, startPos);

	// Calculate the size based on the found ending position
    size = (endPos+1) - startPos;

    if((endPos == -1) || (size <= 0))
        return "";
    
    // Grab the string from the byte buffer up to the delimiter
    char *str = new char[size];
    getBytes((byte*)str, size);
	str[size-1] = 0x00; // NULL termination
    ret.assign(str);
    
    // Increment the read position PAST the delimiter
    setReadPos(endPos+1);
    
    return ret;
}

void HTTPMessage::addHeader(string line) {
	//addHeader(key, value);
}

void HTTPMessage::addHeader(string key, string value) {
    headers->insert(pair<string, string>(key, value));
}

/**
 * Get Header Value
 * Given a header name (key), return the value associated with it in the headers map
 *
 * @param key Key to identify the header
 */
string HTTPMessage::getHeaderValue(string key) {
    // Lookup in map
    map<string, string>::const_iterator it;
    it = headers->find(key);
    
    // Key wasn't found, return a blank value
    if (it == headers->end())
        return "";
    
    // Otherwise, return the value
    return it->second;
}

void HTTPMessage::clearHeaders() {
    headers->clear();
}

