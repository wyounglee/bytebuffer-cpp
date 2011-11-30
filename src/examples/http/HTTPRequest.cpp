/**
 ByteBuffer
 HTTPRequest.cpp
 Copyright 2011 Ramsey Kant
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "HTTPMessage.h"
#include "HTTPRequest.h"

HTTPRequest::HTTPRequest() : HTTPMessage() {
    this->init();
}

HTTPRequest::HTTPRequest(string sData) : HTTPMessage(sData) {
    this->init();
}

HTTPRequest::HTTPRequest(byte* pData, unsigned int len) : HTTPMessage(pData, len) {
    this->init();
}

HTTPRequest::~HTTPRequest() {
	if(data != NULL) {
		delete data;
		data = NULL;
		dataLen = 0;
	}
}

void HTTPRequest::init() {
    method = 0;
    requestUri = "";
    version = "";
	data = NULL;
	dataLen = 0;
}

int HTTPRequest::methodStrToInt(string name) {
	int ret = -1;
	for(int i = 0; i < 9; i++) {
		if(strcmp(requestMethodStr[i], name.c_str()) == 0) {
			ret = i;
			break;
		}
	}
	return ret;
}

byte* HTTPRequest::create() {
	return NULL;
}

void HTTPRequest::parse() {
	string initial = "", methodName = "", hline = "";

	// Get elements from the initial line: <method> <path> <version>\r\n
	methodName = getStrElement();
	requestUri = getStrElement();
	version = getLine(); // End of the line, pull till \r\n

	// Convert the name to the internal enumeration number
	method = methodStrToInt(methodName);
	if(method == -1) {
		parseError = true;
		parseErrorStr = "Invalid Method";
		return;
	}

	// Validate the HTTP version. If there is a mismatch, there's no point in continuing
	if(strcmp(version.c_str(), HTTP_VERSION) != 0) {
		parseError = true;
		parseErrorStr = "Supported HTTP version does not match";
		return;
	}

	// Get the first header
	hline = getLine();

	// Keep pulling headers until a blank line has been reached (signaling the end of headers)
	while(hline.size() > 0) {
		// TODO: handle case where values are on multiple lines ending with ,\r\n
		addHeader(hline);
		hline = getLine();
	}

	// If the method has data, pull the binary data starting from here until the end of the buffer
	if((method != POST) && (method != PUT))
		return;

	// Create a big enough buffer to store the data
	unsigned int dIdx = 0, s = size();
	dataLen = bytesRemaining();
	data = new byte[dataLen];
	
	// Grab all the bytes from the current position to the end
	for(unsigned int i = getReadPos(); i < s; i++) {
		data[dIdx] = get(i);
		dIdx++;
	}
}
