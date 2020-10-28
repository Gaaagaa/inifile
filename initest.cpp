/**
 * The MIT License (MIT)
 * Copyright (c) 2019-2020, Gaaagaa All rights reserved.
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
 * Copyright (c) 2019-2020, Gaaagaa All rights reserved.
 * 
 * @author  ：Gaaagaa
 * @date    : 2020-10-28
 * @version : 1.1.0.0
 * @brief   : test_ini_default(), test_ini_struct() .
 * 
 * @author  ：Gaaagaa
 * @date    : 2019-11-26
 * @version : 1.0.0.0
 * @brief   : for xini_file.h test program.
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

void test_ini_default(void);
void test_ini_struct(void);

int main(int argc, char * argv[])
{
    //======================================
    // test read

    xini_file_t xini_reader("test.ini");
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
    std::cout << xini_write;
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

    test_ini_default();
    test_ini_struct();

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

    // test line break
    xini_file["section4"]["LineBreak1"] = "ABCDEF\nGHIJKLMN";
    xini_file["section4"]["LineBreak2"] = "ABCDEF\rGHIJKLMN";
    xini_file["section4"]["LineBreak3"] = "ABCDEF\r7\nGHIJKLMN";
    xini_file["section4"]["LineBreak4"] = "\rABCDEFGHIJKLMN";

    //======================================
}

////////////////////////////////////////////////////////////////////////////////

void test_ini_default(void)
{
    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_default() output: " << std::endl;
    std::cout << "//======================================" << std::endl;

    xini_file_t xini_file("test_default.ini");

    // operator ()
    std::cout << "test_default.ini" << std::endl;
    std::cout << "[section1]" << std::endl;
    std::cout << "Text1   : " << xini_file["section1"]["Text1"  ](std::string("Hello world")) << std::endl;
    std::cout << "Text2   : " << xini_file["section1"]["Text2"  ]("Hello world"             ) << std::endl;
    std::cout << "Bool1   : " << xini_file["section1"]["Bool1"  ](true                      ) << std::endl;
    std::cout << "Bool2   : " << xini_file["section1"]["Bool2"  ](false                     ) << std::endl;
    std::cout << "Int1    : " << xini_file["section1"]["Int1"   ](123456                    ) << std::endl;
    std::cout << "Int2    : " << xini_file["section1"]["Int2"   ](654321                    ) << std::endl;
    std::cout << "UInt1   : " << xini_file["section1"]["UInt1"  ](123456U                   ) << std::endl;
    std::cout << "UInt2   : " << xini_file["section1"]["UInt2"  ](654321U                   ) << std::endl;
    std::cout << "Long1   : " << xini_file["section1"]["Long1"  ](1234567890L               ) << std::endl;
    std::cout << "Long2   : " << xini_file["section1"]["Long2"  ](9876543210L               ) << std::endl;
    std::cout << "LLong1  : " << xini_file["section1"]["LLong1" ](1234567890LL              ) << std::endl;
    std::cout << "LLong2  : " << xini_file["section1"]["LLong2" ](9876543210LL              ) << std::endl;
    std::cout << "Float1  : " << xini_file["section1"]["Float1" ](1.23456789F               ) << std::endl;
    std::cout << "Float2  : " << xini_file["section1"]["Float2" ](9.87654321F               ) << std::endl;
    std::cout << "Double1 : " << xini_file["section1"]["Double1"](1.234567890123456789      ) << std::endl;
    std::cout << "Double2 : " << xini_file["section1"]["Double2"](9.876543210987654321      ) << std::endl;

    std::cout << "//======================================" << std::endl;

    xini_file_t xini_try("test_try.ini");

    // try_value()
    std::cout << "test_try.ini" << std::endl;
    std::cout << "[section1]" << std::endl;
    std::cout << "Text1   : " << xini_try["section1"]["Text1"  ].try_value(std::string("Hello world")) << std::endl;
    std::cout << "Text2   : " << xini_try["section1"]["Text2"  ].try_value("Hello world"             ) << std::endl;
    std::cout << "Bool1   : " << xini_try["section1"]["Bool1"  ].try_value(true                      ) << std::endl;
    std::cout << "Bool2   : " << xini_try["section1"]["Bool2"  ].try_value(false                     ) << std::endl;
    std::cout << "Int1    : " << xini_try["section1"]["Int1"   ].try_value(123456                    ) << std::endl;
    std::cout << "Int2    : " << xini_try["section1"]["Int2"   ].try_value(654321                    ) << std::endl;
    std::cout << "UInt1   : " << xini_try["section1"]["UInt1"  ].try_value(123456U                   ) << std::endl;
    std::cout << "UInt2   : " << xini_try["section1"]["UInt2"  ].try_value(654321U                   ) << std::endl;
    std::cout << "Long1   : " << xini_try["section1"]["Long1"  ].try_value(1234567890L               ) << std::endl;
    std::cout << "Long2   : " << xini_try["section1"]["Long2"  ].try_value(9876543210L               ) << std::endl;
    std::cout << "LLong1  : " << xini_try["section1"]["LLong1" ].try_value(1234567890LL              ) << std::endl;
    std::cout << "LLong2  : " << xini_try["section1"]["LLong2" ].try_value(9876543210LL              ) << std::endl;
    std::cout << "Float1  : " << xini_try["section1"]["Float1" ].try_value(1.23456789F               ) << std::endl;
    std::cout << "Float2  : " << xini_try["section1"]["Float2" ].try_value(9.87654321F               ) << std::endl;
    std::cout << "Double1 : " << xini_try["section1"]["Double1"].try_value(1.234567890123456789      ) << std::endl;
    std::cout << "Double2 : " << xini_try["section1"]["Double2"].try_value(9.876543210987654321      ) << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

typedef struct __color__
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
} color_t;

xini_keyvalue_t & operator << (xini_keyvalue_t & xini_kv, const color_t & xclr)
{
    std::ostringstream ostr;
    ostr << "(" << xclr.r << ","
                << xclr.g << ","
                << xclr.b << ","
                << xclr.a << ")";
    xini_kv.set_value(ostr.str());
    return xini_kv;
}

xini_keyvalue_t & operator >> (xini_keyvalue_t & xini_kv, color_t & xclr)
{
    char xsplit;
    std::istringstream istr(xini_kv.xvalue());
    istr >> xsplit >> xclr.r >> xsplit
                   >> xclr.g >> xsplit
                   >> xclr.b >> xsplit
                   >> xclr.a >> xsplit;
    return xini_kv;
}

void test_ini_struct(void)
{
    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_struct() output: " << std::endl;
    std::cout << "//======================================" << std::endl;

    xini_file_t xini_file("test_struct.ini");

    color_t clr1 = { 128, 192, 225, 255 };
    color_t clr2;

    xini_file["section1"]["color1"] << clr1;
    xini_file["section1"]["color1"] >> clr2;
    clr2.r -= 128;
    clr2.g -= 128;
    clr2.b -= 128;
    clr2.a -= 128;

    xini_file["section1"]["color2"] << clr2;

    std::cout << "clr1: (" << clr1.r << "," << clr1.g << "," << clr1.b << "," << clr1.a << ")" << std::endl; 
    std::cout << "clr2: (" << clr2.r << "," << clr2.g << "," << clr2.b << "," << clr2.a << ")" << std::endl; 

    // operator ()
    std::cout << "test_struct.ini" << std::endl;
    std::cout << xini_file;
}

////////////////////////////////////////////////////////////////////////////////
