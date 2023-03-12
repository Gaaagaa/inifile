/**
 * @file test_write1.cpp
 * Copyright (c) 2023 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2023-03-11
 * @version : 1.0.0.0
 * @brief   : INI 的 写测试 示例程序。
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
 * @brief 测试 INI 的数据 常规写操作。
 */
void test_ini_write(const std::string & xstr_file);

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试程序的入口 main() 函数。
 */
int main(int argc, char * argv[])
{
    xini_file_t xfile;
    std::string xstr_file;

    std::cout << "usage : "
              << argv[0]
              << " [ output ini file ] [ locale : zh_CN.utf8 or en_US.utf8 ... ]"
              << std::endl;

    if (argc >= 2)
    {
        xstr_file = argv[1];
    }
    else
    {
        xstr_file = argv[0];
        xstr_file += ".ini";
    }

    if (argc >= 3)
    {
        std::cout << "locale : "
                  << setlocale(LC_ALL, argv[2])
                  << std::endl;
    }

    test_ini_write(xstr_file);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试 INI 的数据 常规写操作。
 */
void test_ini_write(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    std::string        vText1    = "std::string"          ;
    const char *       vText2    = "Hello,World!"         ;
    const char *       vText3    = ""                     ;
    bool               vBool1    = true                   ;
    bool               vBool2    = false                  ;
    short              vSInt1    = 123                    ;
    short              vSInt2    = -123                   ;
    unsigned short     vUSInt1   = 0                      ;
    unsigned short     vUSInt2   = -1                     ;
    int                vInt1     = 1234567890             ;
    int                vInt2     = -1234567890            ;
    unsigned int       vUInt1    = 1234567890U            ;
    unsigned int       vUInt2    = 0U                     ;
    long               vLong1    = 1234567890L            ;
    long               vLong2    = -1L                    ;
    unsigned long      vULong1   = 1234567890UL           ;
    unsigned long      vULong2   = (unsigned long)-2      ;
    long long          vLLong1   = 12345678901234567890LL ;
    long long          vLLong2   = -12345678901234567890LL;
    unsigned long long vULLong1  = 12345678901234567890ULL;
    unsigned long long vULLong2  = (unsigned long long)-1 ;
    float              vFloat1   = 0.123456789F           ;
    float              vFloat2   = -0.123456789F          ;
    double             vDouble1  = 0.1234567890123456789  ;
    double             vDouble2  = -0.1234567890123456789 ;
    long double        vLDouble1 = 0.1234567890123456789  ;
    long double        vLDouble2 = -0.1234567890123456789 ;

    std::cout.precision(20);
    std::cout.setf(std::ios_base::boolalpha);

    std::cout << "test_ini_write() output: " << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 常规写操作
    xini_file["section1"]["Text1"   ] = vText1   ;
    xini_file["section1"]["Text2"   ] = vText2   ;
    xini_file["section1"]["Text3"   ] = vText3   ;
    xini_file["section1"]["Bool1"   ] = vBool1   ;
    xini_file["section1"]["Bool2"   ] = vBool2   ;
    xini_file["section1"]["SInt1"   ] = vSInt1   ;
    xini_file["section1"]["SInt2"   ] = vSInt2   ;
    xini_file["section1"]["USInt1"  ] = vUSInt1  ;
    xini_file["section1"]["USInt2"  ] = vUSInt2  ;
    xini_file["section1"]["Int1"    ] = vInt1    ;
    xini_file["section1"]["Int2"    ] = vInt2    ;
    xini_file["section1"]["UInt1"   ] = vUInt1   ;
    xini_file["section1"]["UInt2"   ] = vUInt2   ;
    xini_file["section1"]["Long1"   ] = vLong1   ;
    xini_file["section1"]["Long2"   ] = vLong2   ;
    xini_file["section1"]["ULong1"  ] = vULong1  ;
    xini_file["section1"]["ULong2"  ] = vULong2  ;
    xini_file["section1"]["LLong1"  ] = vLLong1  ;
    xini_file["section1"]["LLong2"  ] = vLLong2  ;
    xini_file["section1"]["ULLong1" ] = vULLong1 ;
    xini_file["section1"]["ULLong2" ] = vULLong2 ;
    xini_file["section1"]["Float1"  ] = vFloat1  ;
    xini_file["section1"]["Float2"  ] = vFloat2  ;
    xini_file["section1"]["Double1" ] = vDouble1 ;
    xini_file["section1"]["Double2" ] = vDouble2 ;
    xini_file["section1"]["LDouble1"] = vLDouble1;
    xini_file["section1"]["LDouble2"] = vLDouble2;

    // 输出 分节 section1 下的内容 
    std::cout << xini_file["section1"] << std::endl;

    std::cout << "----------------------------------------" << std::endl;

    // 赋值 键值节点 的值
    xini_file["section2"]["X_Text1"   ] = xini_file["section1"]["Text1"   ];
    xini_file["section2"]["X_Text2"   ] = xini_file["section1"]["Text2"   ];
    xini_file["section2"]["X_Text3"   ] = xini_file["section1"]["Text3"   ];
    xini_file["section2"]["X_Bool1"   ] = xini_file["section1"]["Bool1"   ];
    xini_file["section2"]["X_Bool2"   ] = xini_file["section1"]["Bool2"   ];
    xini_file["section2"]["X_SInt1"   ] = xini_file["section1"]["SInt1"   ];
    xini_file["section2"]["X_SInt2"   ] = xini_file["section1"]["SInt2"   ];
    xini_file["section2"]["X_USInt1"  ] = xini_file["section1"]["USInt1"  ];
    xini_file["section2"]["X_USInt2"  ] = xini_file["section1"]["USInt2"  ];
    xini_file["section2"]["X_Int1"    ] = xini_file["section1"]["Int1"    ];
    xini_file["section2"]["X_Int2"    ] = xini_file["section1"]["Int2"    ];
    xini_file["section2"]["X_UInt1"   ] = xini_file["section1"]["UInt1"   ];
    xini_file["section2"]["X_UInt2"   ] = xini_file["section1"]["UInt2"   ];
    xini_file["section2"]["X_Long1"   ] = xini_file["section1"]["Long1"   ];
    xini_file["section2"]["X_Long2"   ] = xini_file["section1"]["Long2"   ];
    xini_file["section2"]["X_ULong1"  ] = xini_file["section1"]["ULong1"  ];
    xini_file["section2"]["X_ULong2"  ] = xini_file["section1"]["ULong2"  ];
    xini_file["section2"]["X_LLong1"  ] = xini_file["section1"]["LLong1"  ];
    xini_file["section2"]["X_LLong2"  ] = xini_file["section1"]["LLong2"  ];
    xini_file["section2"]["X_ULLong1" ] = xini_file["section1"]["ULLong1" ];
    xini_file["section2"]["X_ULLong2" ] = xini_file["section1"]["ULLong2" ];
    xini_file["section2"]["X_Float1"  ] = xini_file["section1"]["Float1"  ];
    xini_file["section2"]["X_Float2"  ] = xini_file["section1"]["Float2"  ];
    xini_file["section2"]["X_Double1" ] = xini_file["section1"]["Double1" ];
    xini_file["section2"]["X_Double2" ] = xini_file["section1"]["Double2" ];
    xini_file["section2"]["X_LDouble1"] = xini_file["section1"]["LDouble1"];
    xini_file["section2"]["X_LDouble2"] = xini_file["section1"]["LDouble2"];

    // 输出 分节 section2 下的内容
    std::cout << xini_file["section2"] << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
