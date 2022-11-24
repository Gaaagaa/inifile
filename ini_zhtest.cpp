/**
 * @file ini_zhtest.cpp
 * Copyright (c) 2022 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2022-11-24
 * @version : 1.0.0.0
 * @brief   : 中文 键值的测试程序。
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
// 测试程序的入口 main() 函数

int main(int argc, char * argv[])
{
    xini_file_t xfile("test_zh.ini");

    // INI 文件编码，需要与 应用程序 当前使用的字符编码 一致，否则容易出现乱码

    std::cout << "Name_EN = " << (const char *)xfile["Unit1"]["Name_EN"] << std::endl;
    std::cout << "Name_CN = " << (const char *)xfile["Unit1"]["Name_CN"] << std::endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
