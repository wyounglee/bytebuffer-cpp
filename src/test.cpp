/**
   ByteBuffer
   test.cpp
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

#include "ByteBuffer.h"
#include <stdio.h>

int main() {
	ByteBuffer *bb1 = new ByteBuffer(30);
	bb1->printPosition();
	bb1->put(0xDE);
	bb1->put(0xAD);
	bb1->put(0xBA);
	bb1->put(0xBE);
	bb1->printHex();
	bb1->printPosition();
	byte t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 1;
	t1 = bb1->get();
	t2 = bb1->get();
	t3 = bb1->get();
	t4 = bb1->get();
	t5 = bb1->get();
	printf("t1 = %x, t2 = %x, t3 = %x, t4 = %x, t5 = %x\n", t1, t2, t3, t4, t5);
	bb1->printPosition();
	delete bb1;
	system("pause");
	return 0;
}
