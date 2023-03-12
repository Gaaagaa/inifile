/**
 * @file test_read2.cpp
 * Copyright (c) 2023 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2023-03-11
 * @version : 1.0.0.0
 * @brief   : INI 的 （带默认值）读测试 示例程序。
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
 * @brief 测试 INI 的数据 带默认值 的读取操作。
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
 * @brief 测试 INI 的数据 带默认值 的读取操作。
 */
void test_ini_read(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    std::string        vText1    = xini_file["section1"]["Text1"   ](std::string("Default Text1")        );
    const char *       vText2    = xini_file["section1"]["Text2"   ]("Default Text2"                     );
    const char *       vText3    = xini_file["section1"]["Text3"   ]("Default Text3"                     );
    bool               vBool1    = xini_file["section1"]["Bool1"   ](true                                );
    bool               vBool2    = xini_file["section1"]["Bool2"   ](false                               );
    short              vSInt1    = xini_file["section1"]["SInt1"   ]((short)12345                        );
    short              vSInt2    = xini_file["section1"]["SInt2"   ]((short)0                            );
    unsigned short     vUSInt1   = xini_file["section1"]["USInt1"  ]((unsigned short)256                 );
    unsigned short     vUSInt2   = xini_file["section1"]["USInt2"  ]((unsigned short)128                 );
    int                vInt1     = xini_file["section1"]["Int1"    ](1234567890                          );
    int                vInt2     = xini_file["section1"]["Int2"    ](-1                                  );
    unsigned int       vUInt1    = xini_file["section1"]["UInt1"   ](100000U                             );
    unsigned int       vUInt2    = xini_file["section1"]["UInt2"   ](200000U                             );
    long               vLong1    = xini_file["section1"]["Long1"   ](123456789L                          );
    long               vLong2    = xini_file["section1"]["Long2"   ](987654321L                          );
    unsigned long      vULong1   = xini_file["section1"]["ULong1"  ](10086UL                             );
    unsigned long      vULong2   = xini_file["section1"]["ULong2"  ](10010UL                             );
    long long          vLLong1   = xini_file["section1"]["LLong1"  ](10086LL                             );
    long long          vLLong2   = xini_file["section1"]["LLong2"  ](10010LL                             );
    unsigned long long vULLong1  = xini_file["section1"]["ULLong1" ](10086ULL                            );
    unsigned long long vULLong2  = xini_file["section1"]["ULLong2" ](10010ULL                            );
    float              vFloat1   = xini_file["section1"]["Float1"  ](3.1415926F                          );
    float              vFloat2   = xini_file["section1"]["Float2"  ](-3.1415926F                         );
    double             vDouble1  = xini_file["section1"]["Double1" ](2.7182818284590452                  );
    double             vDouble2  = xini_file["section1"]["Double2" ](-2.7182818284590452                 );
    long double        vLDouble1 = xini_file["section1"]["LDouble1"]((long double)0.61803398874989484820 );
    long double        vLDouble2 = xini_file["section1"]["LDouble2"]((long double)-0.61803398874989484820);

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

    vText1    = xini_file["section2"]["Text1"   ](std::string("Default Text1")        );
    vText2    = xini_file["section2"]["Text2"   ]("Default Text2"                     );
    vText3    = xini_file["section2"]["Text3"   ]("Default Text3"                     );
    vBool1    = xini_file["section2"]["Bool1"   ](true                                );
    vBool2    = xini_file["section2"]["Bool2"   ](false                               );
    vSInt1    = xini_file["section2"]["SInt1"   ]((short)12345                        );
    vSInt2    = xini_file["section2"]["SInt2"   ]((short)0                            );
    vUSInt1   = xini_file["section2"]["USInt1"  ]((unsigned short)256                 );
    vUSInt2   = xini_file["section2"]["USInt2"  ]((unsigned short)128                 );
    vInt1     = xini_file["section2"]["Int1"    ](1234567890                          );
    vInt2     = xini_file["section2"]["Int2"    ](-1                                  );
    vUInt1    = xini_file["section2"]["UInt1"   ](100000U                             );
    vUInt2    = xini_file["section2"]["UInt2"   ](200000U                             );
    vLong1    = xini_file["section2"]["Long1"   ](123456789L                          );
    vLong2    = xini_file["section2"]["Long2"   ](987654321L                          );
    vULong1   = xini_file["section2"]["ULong1"  ](10086UL                             );
    vULong2   = xini_file["section2"]["ULong2"  ](10010UL                             );
    vLLong1   = xini_file["section2"]["LLong1"  ](10086LL                             );
    vLLong2   = xini_file["section2"]["LLong2"  ](10010LL                             );
    vULLong1  = xini_file["section2"]["ULLong1" ](10086ULL                            );
    vULLong2  = xini_file["section2"]["ULLong2" ](10010ULL                            );
    vFloat1   = xini_file["section2"]["Float1"  ](3.1415926F                          );
    vFloat2   = xini_file["section2"]["Float2"  ](-3.1415926F                         );
    vDouble1  = xini_file["section2"]["Double1" ](2.7182818284590452                  );
    vDouble2  = xini_file["section2"]["Double2" ](-2.7182818284590452                 );
    vLDouble1 = xini_file["section2"]["LDouble1"]((long double)0.61803398874989484820 );
    vLDouble2 = xini_file["section2"]["LDouble2"]((long double)-0.61803398874989484820);

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
