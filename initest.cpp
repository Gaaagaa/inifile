/**
 * The MIT License (MIT)
 * Copyright (c) 2019, Gaaagaa All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file initest.cpp
 * <pre>
 * Copyright (c) 2019, Gaaagaa All rights reserved.
 *
 * author ：Gaaagaa
 * date   : 2019-11-26
 * info   : for inifile.h test program.
 * </pre>
 */

#include "xini_file.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    xini_file_t xini_file("test.ini");
    xini_file >> std::cout;

    std::ostringstream ostr;
    xini_file >> ostr;

    std::istringstream istr(ostr.str());
    xini_file_t xini_test;
    xini_test << istr;
    xini_test >> std::cout;

    return 0;
}

