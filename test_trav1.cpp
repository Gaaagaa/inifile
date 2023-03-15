/**
 * @file test_trav1.cpp
 * Copyright (c) 2023 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2023-03-15
 * @version : 1.0.0.0
 * @brief   : INI 节点遍历操作 的 测试示例程序。
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
 * @brief 测试 INI 的节点遍历操作。
 */
void test_ini_trav(const std::string & xstr_file);

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

    test_ini_trav(xstr_file);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/**
 * @brief 测试 INI 的 节点遍历操作。
 * 
 * @note 
 * 节点遍历操作的过程时，若调用 xini_file_t::sect_remove() 或 
 * xini_section_t::key_remove() 操作，会更新内部 节点存储链表，
 * 可能会引发遍历操作的异常，此情况应当慎重对待，
 * 如 remove() 后就结束遍历，这是允许的。
 */
void test_ini_trav(const std::string & xstr_file)
{
    xini_file_t xini_file(xstr_file);

    // 遍历 分节 节点
    for (xini_file_t::iterator
            itsect  = xini_file.begin();
            itsect != xini_file.end();
            ++itsect)
    {
        // 遍历 分节 下的各个 节点
        for (xini_section_t::iterator
                itnode  = (*itsect)->begin();
                itnode != (*itsect)->end(); 
                ++itnode)
        {
            switch ((*itnode)->ntype())
            {
            case XINI_NTYPE_NILLINE  :
                std::cout << "NILLINE : " << std::endl;
                break;

            case XINI_NTYPE_COMMENT  :
                std::cout << "COMMENT : " 
                          << (static_cast< xini_comment_t * >(*itnode))->text()
                          << std::endl;
                break;

            case XINI_NTYPE_KEYVALUE :
                std::cout << "KEYVALUE: "
                          << (static_cast< xini_keyvalue_t * >(*itnode))->key()
                          << " = "
                          << (static_cast< xini_keyvalue_t * >(*itnode))->value()
                          << std::endl;
                break;

            // 在 分节 的节点存储链表中，会将 自身的 this 指针 存储进去，
            // 其目的是要起到占位的作用，故遍历操作，也会出现 分节类型的节点
            case XINI_NTYPE_SECTION  :
                std::cout << "SECTION : " 
                          << (static_cast< xini_section_t * >(*itnode))->name()
                          << std::endl;
                break;

            default:
                break;
            }
        }
    }
}
