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
#include <cassert>

#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////

void test_ini_read(xini_file_t & xini_file);
void test_ini_write(xini_file_t & xini_file);

int main(int argc, char * argv[])
{
    //======================================
    // test read

    xini_file_t xini_reader("test.ini");
    assert(xini_reader.is_open());
    test_ini_read(xini_reader);

    std::cout << "reader is dirty: " << xini_reader.is_dirty() << std::endl;

    if (xini_reader.is_dirty())
    {
        // set dirty false, that will not dump to ini file.
        // xini_reader.set_dirty(false);
    }

    // output all
    std::cout << std::endl << "//======================================" << std::endl;
    std::cout << "output all ini node: " << std::endl;
    std::cout << xini_reader;
    std::cout << std::endl << "//======================================" << std::endl;

    //======================================
    // test write

    assert(xini_reader.dump("test_write.ini"));

    xini_file_t xini_write("test_write.ini");
    test_ini_write(xini_write);

    // output all
    std::cout << std::endl << "//======================================" << std::endl;
    std::cout << "output all ini node: " << std::endl;
    xini_write >> std::cout;
    std::cout << std::endl << "//======================================" << std::endl;

    //======================================
    // istream operator

    std::ostringstream ostr;
    xini_write >> ostr;

    std::istringstream istr(ostr.str());

    xini_file_t xini_clone;
    istr >> xini_clone;
    xini_clone.dump("test_clone.ini");

    //======================================

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void test_ini_read(xini_file_t & xini_file)
{
    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_reader() output: " << std::endl;
    std::cout << "//======================================" << std::endl;

    std::cout << "[section1]" << std::endl;
    std::cout << "Text1   : " << (const std::string &)xini_file["section1"]["Text1"  ] << std::endl;
    std::cout << "Text2   : " << (const char *       )xini_file["section1"]["Text2"  ] << std::endl;
    std::cout << "Bool1   : " << (bool               )xini_file["section1"]["Bool1"  ] << std::endl;
    std::cout << "Bool2   : " << (bool               )xini_file["section1"]["Bool2"  ] << std::endl;
    std::cout << "Int1    : " << (int                )xini_file["section1"]["Int1"   ] << std::endl;
    std::cout << "Int2    : " << (int                )xini_file["section1"]["Int2"   ] << std::endl;
    std::cout << "UInt1   : " << (unsigned int       )xini_file["section1"]["UInt1"  ] << std::endl;
    std::cout << "UInt2   : " << (unsigned int       )xini_file["section1"]["UInt2"  ] << std::endl;
    std::cout << "Long1   : " << (long               )xini_file["section1"]["Long1"  ] << std::endl;
    std::cout << "Long2   : " << (long               )xini_file["section1"]["Long2"  ] << std::endl;
    std::cout << "LLong1  : " << (long long          )xini_file["section1"]["LLong1" ] << std::endl;
    std::cout << "LLong2  : " << (long long          )xini_file["section1"]["LLong2" ] << std::endl;
    std::cout << "Float1  : " << (float              )xini_file["section1"]["Float1" ] << std::endl;
    std::cout << "Float2  : " << (float              )xini_file["section1"]["Float2" ] << std::endl;
    std::cout << "Double1 : " << (double             )xini_file["section1"]["Double1"] << std::endl;
    std::cout << "Double2 : " << (double             )xini_file["section1"]["Double2"] << std::endl;

    std::cout << "//======================================" << std::endl;

    std::cout << "[section2]" << std::endl;
    std::cout << "Text1   : " << (const std::string &)xini_file["section2"]["Text1"  ] << std::endl;
    std::cout << "Text2   : " << (const char *       )xini_file["section2"]["Text2"  ] << std::endl;
    std::cout << "Bool1   : " << (bool               )xini_file["section2"]["Bool1"  ] << std::endl;
    std::cout << "Bool2   : " << (bool               )xini_file["section2"]["Bool2"  ] << std::endl;
    std::cout << "Int1    : " << (int                )xini_file["section2"]["Int1"   ] << std::endl;
    std::cout << "Int2    : " << (int                )xini_file["section2"]["Int2"   ] << std::endl;
    std::cout << "UInt1   : " << (unsigned int       )xini_file["section2"]["UInt1"  ] << std::endl;
    std::cout << "UInt2   : " << (unsigned int       )xini_file["section2"]["UInt2"  ] << std::endl;
    std::cout << "Long1   : " << (long               )xini_file["section2"]["Long1"  ] << std::endl;
    std::cout << "Long2   : " << (long               )xini_file["section2"]["Long2"  ] << std::endl;
    std::cout << "LLong1  : " << (long long          )xini_file["section2"]["LLong1" ] << std::endl;
    std::cout << "LLong2  : " << (long long          )xini_file["section2"]["LLong2" ] << std::endl;
    std::cout << "Float1  : " << (float              )xini_file["section2"]["Float1" ] << std::endl;
    std::cout << "Float2  : " << (float              )xini_file["section2"]["Float2" ] << std::endl;
    std::cout << "Double1 : " << (double             )xini_file["section2"]["Double1"] << std::endl;
    std::cout << "Double2 : " << (double             )xini_file["section2"]["Double2"] << std::endl;

    std::cout << "//======================================" << std::endl;
    std::cout << "[section1][AppendText] : " << (const char *)xini_file["section1"]["AppendText"] << std::endl;
    std::cout << "[section1][AppendText] : " << (const char *)xini_file["section1"]["AppendText"] << std::endl;
    std::cout << "[section1][AppendInt ] : " << (int         )xini_file["section1"]["AppendInt" ] << std::endl;
    std::cout << "//======================================" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void test_ini_write(xini_file_t & xini_file)
{
    srand((unsigned int)time(NULL));

    //======================================
    // section1

    xini_file["section1"]["Text1"  ] = std::string("Write text"); // (operator const std::string &)
    xini_file["section1"]["Text2"  ] = ""                       ; // (operator const char *       )
    xini_file["section1"]["Bool1"  ] = (0 == (rand() % 2))      ; // (operator bool               )
    xini_file["section1"]["Bool2"  ] = true                     ; // (operator bool               )
    xini_file["section1"]["Int1"   ] = 12345678                 ; // (operator int                )
    xini_file["section1"]["Int1"   ] = -rand()                  ; // (operator int                )
    xini_file["section1"]["UInt1"  ] = (unsigned int)0xFFFFFFFF ; // (operator unsigned int       )
    xini_file["section1"]["UInt2"  ] = (unsigned int)rand()     ; // (operator unsigned int       )
    xini_file["section1"]["Long1"  ] = -12345678                ; // (operator long               )
    xini_file["section1"]["Long2"  ] = (long)-rand()            ; // (operator long               )
    xini_file["section1"]["LLong1" ] = -1234567890123456L       ; // (operator long long          )
    xini_file["section1"]["LLong2" ] = rand() * 100L            ; // (operator long long          )
    xini_file["section1"]["Float1" ] = (float)(rand() / 10000.0); // (operator float              )
    xini_file["section1"]["Float2" ] = (float)(-0.123456)       ; // (operator float              )
    xini_file["section1"]["Double1"] = (double)(rand() / 1000.0); // (operator double             )
    xini_file["section1"]["Double2"] = (double)3.141592653589793; // (operator double             )

    // add a new key value
    xini_file["section1"]["NewInt" ] = rand();

    //======================================
    // section3

    // add a string value
    xini_file["section3"]["NewText"] = "information";

    //======================================
    // section4

    // add section4 and key value
    xini_file["section4"]["EmptyKey"];
    xini_file["section4"]["ValueKey"] = rand();

    //======================================
}

////////////////////////////////////////////////////////////////////////////////
