/**
 * The MIT License (MIT)
 * Copyright (c) Gaaagaa. All rights reserved.
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
 * @file ini_test.cpp
 * Copyright (c) 2021 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2021-03-26
 * @version : 1.0.0.0
 * @brief   : 对 xini_file_t 类的测试程序。
 */

#include "xini_file.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <locale>

////////////////////////////////////////////////////////////////////////////////
// 各个测试流程的函数声明

/**********************************************************/
/**
 * @brief 测试 INI 的数据读取操作（这其中也包括 带默认值 的读取操作）。
 */
void test_ini_read(const std::string & xstr_file);

/**********************************************************/
/**
 * @brief 测试 INI 的数据写入操作。
 */
void test_ini_write(const std::string & xstr_file);

/**********************************************************/
/**
 * @brief 
 * 测试 INI 键值节点的 try_value() 操作接口，
 * 以及自定义数据类型的读写操作。
 * @note 
 * 键值节点的 try_value() 实现的功能：
 * 返回当前节点值，但若节点值为 空，则设置为指定值。
 */
void test_ini_vtry(void);

////////////////////////////////////////////////////////////////////////////////
// 测试程序的入口 main() 函数

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << "usage : "
                  << argv[0]
                  << " < ini file > [ locale : zh_CN.utf8 or en_US.utf8 ... ]"
                  << std::endl;
        return -1;
    }

    std::string xstr_file = argv[1];
    if (argc >= 3)
    {
        std::cout << "locale : "
                  << setlocale(LC_ALL, argv[2])
                  << std::endl;
    }

    test_ini_read(xstr_file);
    test_ini_write(xstr_file);

    test_ini_vtry();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 各个测试流程的函数具体实现

/**********************************************************/
/**
 * @brief 测试 INI 的数据读取操作（这其中也包括 带默认值 的读取操作）。
 */
void test_ini_read(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_read() output: " << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 常规的读取操作
    std::cout << "[section1]" << std::endl;
    std::cout << "Text1   : " << (const std::string &)xini_file["section1"]["Text1"  ] << std::endl;
    std::cout << "Text2   : " << (const char *       )xini_file["section1"]["Text2"  ] << std::endl;
    std::cout << "Text3   : " << (const char *       )xini_file["section1"]["Text3"  ] << std::endl;
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

    std::cout << "----------------------------------------" << std::endl;

    // 常规的读取操作
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

    std::cout << "----------------------------------------" << std::endl;

    // 带默认值的读取操作
    std::cout << "[default]" << std::endl;
    std::cout << "Text1   : " << xini_file["default"]["Text1"  ](std::string("stl string")) << std::endl; // (const std::string &)
    std::cout << "Text2   : " << xini_file["default"]["Text2"  ]("c string"               ) << std::endl; // (const char *       )
    std::cout << "Bool1   : " << xini_file["default"]["Bool1"  ](true                     ) << std::endl; // (bool               )
    std::cout << "Bool2   : " << xini_file["default"]["Bool2"  ](false                    ) << std::endl; // (bool               )
    std::cout << "Int1    : " << xini_file["default"]["Int1"   ](123456                   ) << std::endl; // (int                )
    std::cout << "Int2    : " << xini_file["default"]["Int2"   ](-123456                  ) << std::endl; // (int                )
    std::cout << "UInt1   : " << xini_file["default"]["UInt1"  ](123456U                  ) << std::endl; // (unsigned int       )
    std::cout << "UInt2   : " << xini_file["default"]["UInt2"  ](0U                       ) << std::endl; // (unsigned int       )
    std::cout << "Long1   : " << xini_file["default"]["Long1"  ](123456L                  ) << std::endl; // (long               )
    std::cout << "Long2   : " << xini_file["default"]["Long2"  ](-123456L                 ) << std::endl; // (long               )
    std::cout << "LLong1  : " << xini_file["default"]["LLong1" ](123456LL                 ) << std::endl; // (long long          )
    std::cout << "LLong2  : " << xini_file["default"]["LLong2" ](-123456LL                ) << std::endl; // (long long          )
    std::cout << "Float1  : " << xini_file["default"]["Float1" ](1.23456F                 ) << std::endl; // (float              )
    std::cout << "Float2  : " << xini_file["default"]["Float2" ](-1.23456F                ) << std::endl; // (float              )
    std::cout << "Double1 : " << xini_file["default"]["Double1"](1.234567890123456789     ) << std::endl; // (double             )
    std::cout << "Double2 : " << xini_file["default"]["Double2"](-0.1234567890123456789   ) << std::endl; // (double             )

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "[section1][AppendText] : " << (const char *)xini_file["section1"]["AppendText"] << std::endl;
    std::cout << "[section1][AppendText] : " << (const char *)xini_file["section1"]["AppendText"] << std::endl;
    std::cout << "[section1][AppendInt ] : " << (int         )xini_file["section1"]["AppendInt" ] << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

/**********************************************************/
/**
 * @brief 测试 INI 的数据写入操作。
 */
void test_ini_write(const std::string & xstr_file)
{
    //======================================

    {
        // 将 test.ini 克隆到 write.ini 文件，用于后续的写操作测试
        xini_file_t xini_clone(xstr_file);
        xini_clone.dump("write.ini");
    }

    xini_file_t xini_file("write.ini");

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
    xini_file["section3"]["ZHText" ] = "中国制造";

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

    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_write() output: " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << xini_file;
    std::cout << "----------------------------------------" << std::endl;

    //======================================
}

/**
 * @struct color_t
 * @brief  用于测试 INI 存储自定义的数据结构。
 */
struct color_t
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;

    color_t(
        unsigned int r = 0,
        unsigned int g = 0,
        unsigned int b = 0,
        unsigned int a = 255)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

/**********************************************************/
/**
 * @brief 使用 INI 键值节点的流输出操作符 存储 color_t 类型数据。
 */
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

/**********************************************************/
/**
 * @brief 使用 INI 键值节点的流输入操作符 读取 color_t 类型数据。
 */
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

/**********************************************************/
/**
 * @brief 使用标准流输出操作符 输出 color_t 类型数据。
 */
std::ostream & operator << (std::ostream & ostr, const color_t & xclr)
{
    ostr << "(" << xclr.r << ","
                << xclr.g << ","
                << xclr.b << ","
                << xclr.a << ")";
    return ostr;
}

/**********************************************************/
/**
 * @brief 
 * 测试 INI 键值节点的 try_value() 操作接口，
 * 以及自定义数据类型的读写操作。
 * @note 
 * 键值节点的 try_value() 实现的功能：
 * 返回当前节点值，但若节点值为 空，则设置为指定值。
 */
void test_ini_vtry(void)
{
    xini_file_t xini_file("try_value.ini");

    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "//====================================================================" << std::endl;
    std::cout << "test_ini_try() output: " << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "try_value() test : " << std::endl;

    std::cout << "Text1   : " << xini_file["vtry"]["Text1"  ].try_value(std::string("try text")  ) << std::endl;
    std::cout << "Text2   : " << xini_file["vtry"]["Text2"  ].try_value("中国制造 INI"            ) << std::endl;
    std::cout << "Bool1   : " << xini_file["vtry"]["Bool1"  ].try_value((0 == (rand() % 2))      ) << std::endl;
    std::cout << "Bool2   : " << xini_file["vtry"]["Bool2"  ].try_value(true                     ) << std::endl;
    std::cout << "Int1    : " << xini_file["vtry"]["Int1"   ].try_value(12345678                 ) << std::endl;
    std::cout << "Int1    : " << xini_file["vtry"]["Int1"   ].try_value(-rand()                  ) << std::endl;
    std::cout << "UInt1   : " << xini_file["vtry"]["UInt1"  ].try_value((unsigned int)0xFFFFFFFF ) << std::endl;
    std::cout << "UInt2   : " << xini_file["vtry"]["UInt2"  ].try_value((unsigned int)rand()     ) << std::endl;
    std::cout << "Long1   : " << xini_file["vtry"]["Long1"  ].try_value(-12345678                ) << std::endl;
    std::cout << "Long2   : " << xini_file["vtry"]["Long2"  ].try_value((long)-rand()            ) << std::endl;
    std::cout << "LLong1  : " << xini_file["vtry"]["LLong1" ].try_value(-1234567890123456L       ) << std::endl;
    std::cout << "LLong2  : " << xini_file["vtry"]["LLong2" ].try_value(rand() * 100L            ) << std::endl;
    std::cout << "Float1  : " << xini_file["vtry"]["Float1" ].try_value((float)(rand() / 10000.0)) << std::endl;
    std::cout << "Float2  : " << xini_file["vtry"]["Float2" ].try_value((float)(-0.123456)       ) << std::endl;
    std::cout << "Double1 : " << xini_file["vtry"]["Double1"].try_value((double)(rand() / 1000.0)) << std::endl;
    std::cout << "Double2 : " << xini_file["vtry"]["Double2"].try_value((double)3.141592653589793) << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "color_t test : " << std::endl;

    xini_file["color"]["red"  ] << color_t(255, 0, 0, 255);
    xini_file["color"]["green"] << color_t(0, 255, 0, 255);
    xini_file["color"]["blue" ] << color_t(0, 0, 255, 255);

    color_t xclr;
    xini_file["color"]["red"  ] >> xclr; std::cout << "[color][red  ] : " << xclr << std::endl;
    xini_file["color"]["green"] >> xclr; std::cout << "[color][green] : " << xclr << std::endl;
    xini_file["color"]["blue" ] >> xclr; std::cout << "[color][blue ] : " << xclr << std::endl;

    std::cout << "INI [color][red  ] : " << (const char *)xini_file["color"]["red"  ] << std::endl;
    std::cout << "INI [color][green] : " << (const char *)xini_file["color"]["green"] << std::endl;
    std::cout << "INI [color][blue ] : " << (const char *)xini_file["color"]["blue" ] << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}
