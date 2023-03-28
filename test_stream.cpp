/**
 * @file test_rmrn.cpp
 * Copyright (c) 2023 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2023-03-15
 * @version : 1.0.0.0
 * @brief   : INI 文件 输入/输出 流 的相关操作。
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
 * @brief 测试 INI 文件 输入/输出 流 的相关操作。
 */
void test_ini_stream(const std::string & xstr_file);

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

    test_ini_stream(xstr_file);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试 INI 文件 输入/输出 流 的相关操作。
 */
void test_ini_stream(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    //======================================
    // 将 INI 文件的所有内容，转换成 字符串

    std::ostringstream ostr;
    ostr << xini_file;
    std::string xstr_ini = ostr.str();

    // 这里得到的 INI 字符串内容，直接输出到标准输出流上
    // 实际应用中，可以按字节进行 网络传输、内存转储 等操作
    std::cout << xstr_ini << std::endl;

    //======================================
    // 由 INI 格式的 字符串内容，以输入流方式，
    // 构建 INI 文件解析对象

    std::istringstream istr(xstr_ini);
    xini_file_t xini_istr;
    istr >> xini_istr;

    // 此处将 INI 文件对象，转存至 磁盘文件
    xini_istr.dump("output.ini");

    //======================================
}
