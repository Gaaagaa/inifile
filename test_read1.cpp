/**
 * @file test_read1.cpp
 * Copyright (c) 2023 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2023-03-11
 * @version : 1.0.0.0
 * @brief   : INI 的 读测试 示例程序。
 */

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

#include "xini_file.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试 INI 的数据读取操作（这其中也包括 带默认值 的读取操作）。
 */
void test_ini_read(const std::string & xstr_file);

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试程序的入口 main() 函数。
 */
int main(int argc, char * argv[])
{
    xini_file_t xfile;

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

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试 INI 的数据读取操作（这其中也包括 带默认值 的读取操作）。
 */
void test_ini_read(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    std::string        vText1    = (const char *)xini_file["section1"]["Text1"   ];
    const char *       vText2    = xini_file["section1"]["Text2"   ];
    const char *       vText3    = xini_file["section1"]["Text3"   ];
    bool               vBool1    = xini_file["section1"]["Bool1"   ];
    bool               vBool2    = xini_file["section1"]["Bool2"   ];
    short              vSInt1    = xini_file["section1"]["SInt1"   ];
    short              vSInt2    = xini_file["section1"]["SInt2"   ];
    unsigned short     vUSInt1   = xini_file["section1"]["USInt1"  ];
    unsigned short     vUSInt2   = xini_file["section1"]["USInt2"  ];
    int                vInt1     = xini_file["section1"]["Int1"    ];
    int                vInt2     = xini_file["section1"]["Int2"    ];
    unsigned int       vUInt1    = xini_file["section1"]["UInt1"   ];
    unsigned int       vUInt2    = xini_file["section1"]["UInt2"   ];
    long               vLong1    = xini_file["section1"]["Long1"   ];
    long               vLong2    = xini_file["section1"]["Long2"   ];
    unsigned long      vULong1   = xini_file["section1"]["ULong1"  ];
    unsigned long      vULong2   = xini_file["section1"]["ULong2"  ];
    long long          vLLong1   = xini_file["section1"]["LLong1"  ];
    long long          vLLong2   = xini_file["section1"]["LLong2"  ];
    unsigned long long vULLong1  = xini_file["section1"]["ULLong1" ];
    unsigned long long vULLong2  = xini_file["section1"]["ULLong2" ];
    float              vFloat1   = xini_file["section1"]["Float1"  ];
    float              vFloat2   = xini_file["section1"]["Float2"  ];
    double             vDouble1  = xini_file["section1"]["Double1" ];
    double             vDouble2  = xini_file["section1"]["Double2" ];
    long double        vLDouble1 = xini_file["section1"]["LDouble1"];
    long double        vLDouble2 = xini_file["section1"]["LDouble2"];

    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "test_ini_read() output: " << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 常规的读取操作
    std::cout << "[section1]" << std::endl;
    std::cout << "Text1    : " << vText1    << std::endl;
    std::cout << "Text2    : " << vText2    << std::endl;
    std::cout << "Text3    : " << vText3    << std::endl;
    std::cout << "Bool1    : " << vBool1    << std::endl;
    std::cout << "Bool2    : " << vBool2    << std::endl;
    std::cout << "SInt1    : " << vSInt1    << std::endl;
    std::cout << "SInt2    : " << vSInt2    << std::endl;
    std::cout << "USInt1   : " << vUSInt1   << std::endl;
    std::cout << "USInt2   : " << vUSInt2   << std::endl;
    std::cout << "Int1     : " << vInt1     << std::endl;
    std::cout << "Int2     : " << vInt2     << std::endl;
    std::cout << "UInt1    : " << vUInt1    << std::endl;
    std::cout << "UInt2    : " << vUInt2    << std::endl;
    std::cout << "Long1    : " << vLong1    << std::endl;
    std::cout << "Long2    : " << vLong2    << std::endl;
    std::cout << "ULong1   : " << vULong1   << std::endl;
    std::cout << "ULong2   : " << vULong2   << std::endl;
    std::cout << "LLong1   : " << vLLong1   << std::endl;
    std::cout << "LLong2   : " << vLLong2   << std::endl;
    std::cout << "ULLong1  : " << vULLong1  << std::endl;
    std::cout << "ULLong2  : " << vULLong2  << std::endl;
    std::cout << "Float1   : " << vFloat1   << std::endl;
    std::cout << "Float2   : " << vFloat2   << std::endl;
    std::cout << "Double1  : " << vDouble1  << std::endl;
    std::cout << "Double2  : " << vDouble2  << std::endl;
    std::cout << "LDouble1 : " << vLDouble1 << std::endl;
    std::cout << "LDouble2 : " << vLDouble2 << std::endl;

    std::cout << "----------------------------------------" << std::endl;

    vText1    = (const char *)xini_file["section2"]["Text1"   ];
    vText2    = xini_file["section2"]["Text2"   ];
    vText3    = xini_file["section2"]["Text3"   ];
    vBool1    = xini_file["section2"]["Bool1"   ];
    vBool2    = xini_file["section2"]["Bool2"   ];
    vSInt1    = xini_file["section2"]["SInt1"   ];
    vSInt2    = xini_file["section2"]["SInt2"   ];
    vUSInt1   = xini_file["section2"]["USInt1"  ];
    vUSInt2   = xini_file["section2"]["USInt2"  ];
    vInt1     = xini_file["section2"]["Int1"    ];
    vInt2     = xini_file["section2"]["Int2"    ];
    vUInt1    = xini_file["section2"]["UInt1"   ];
    vUInt2    = xini_file["section2"]["UInt2"   ];
    vLong1    = xini_file["section2"]["Long1"   ];
    vLong2    = xini_file["section2"]["Long2"   ];
    vULong1   = xini_file["section2"]["ULong1"  ];
    vULong2   = xini_file["section2"]["ULong2"  ];
    vLLong1   = xini_file["section2"]["LLong1"  ];
    vLLong2   = xini_file["section2"]["LLong2"  ];
    vULLong1  = xini_file["section2"]["ULLong1" ];
    vULLong2  = xini_file["section2"]["ULLong2" ];
    vFloat1   = xini_file["section2"]["Float1"  ];
    vFloat2   = xini_file["section2"]["Float2"  ];
    vDouble1  = xini_file["section2"]["Double1" ];
    vDouble2  = xini_file["section2"]["Double2" ];
    vLDouble1 = xini_file["section2"]["LDouble1"];
    vLDouble2 = xini_file["section2"]["LDouble2"];

    // 常规的读取操作
    std::cout << "[section2]" << std::endl;
    std::cout << "Text1    : " << vText1    << std::endl;
    std::cout << "Text2    : " << vText2    << std::endl;
    std::cout << "Text3    : " << vText3    << std::endl;
    std::cout << "Bool1    : " << vBool1    << std::endl;
    std::cout << "Bool2    : " << vBool2    << std::endl;
    std::cout << "SInt1    : " << vSInt1    << std::endl;
    std::cout << "SInt2    : " << vSInt2    << std::endl;
    std::cout << "USInt1   : " << vUSInt1   << std::endl;
    std::cout << "USInt2   : " << vUSInt2   << std::endl;
    std::cout << "Int1     : " << vInt1     << std::endl;
    std::cout << "Int2     : " << vInt2     << std::endl;
    std::cout << "UInt1    : " << vUInt1    << std::endl;
    std::cout << "UInt2    : " << vUInt2    << std::endl;
    std::cout << "Long1    : " << vLong1    << std::endl;
    std::cout << "Long2    : " << vLong2    << std::endl;
    std::cout << "ULong1   : " << vULong1   << std::endl;
    std::cout << "ULong2   : " << vULong2   << std::endl;
    std::cout << "LLong1   : " << vLLong1   << std::endl;
    std::cout << "LLong2   : " << vLLong2   << std::endl;
    std::cout << "ULLong1  : " << vULLong1  << std::endl;
    std::cout << "ULLong2  : " << vULLong2  << std::endl;
    std::cout << "Float1   : " << vFloat1   << std::endl;
    std::cout << "Float2   : " << vFloat2   << std::endl;
    std::cout << "Double1  : " << vDouble1  << std::endl;
    std::cout << "Double2  : " << vDouble2  << std::endl;
    std::cout << "LDouble1 : " << vLDouble1 << std::endl;
    std::cout << "LDouble2 : " << vLDouble2 << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
