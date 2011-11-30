/**
 ByteBuffer
 http.cpp
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

#include <iostream>
#include "../../ByteBuffer.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

using namespace std;

int main() {
	HTTPMessage *msg = new HTTPMessage("line1\r\nline2\nline3");
    HTTPRequest *req = new HTTPRequest("POST /sample/path.html HTTP/1.1\r\nHeader1: value1\r\nHeader2: value2\r\nHeader3: value3\r\n\r\ndata");
    //HTTPResponse *resp = new HTTPResponse();

	// Test getLine() in HTTPMessage

	string l1 = "", l2 = "", l3 = "", l4 = "";
	l1 = msg->getLine(); // Expected: test1
	l2 = msg->getLine(); // Expected: test2
	l3 = msg->getLine(); // Expected: 
	l4 = msg->getLine(); // Expected: 

    printf("%s (%i)\n%s (%i)\n%s (%i)\n%s (%i)\n\n", l1.c_str(), l1.size(), l2.c_str(), l2.size(), l3.c_str(), l3.size(), l4.c_str(), l4.size());

	// Test HTTPRequest parse()
	req->parse();
	if(req->hasParseError()) {
		printf("HTTPRequest had a parse error: %s\n", req->getParseError().c_str());
	}
	printf("HTTPRequest: %i %s\n", req->getMethod(), req->getVersion().c_str());
	byte *data = req->getData();
	printf("Data (%i):\n", req->getDataLength());
	for(unsigned int i = 0; i < req->getDataLength(); i++) {
		printf("0x%02x ", data[i]);
	}
    
	delete msg;
    delete req;
    //delete resp;
    return 0;
}
