# 纯 C++ 代码实现的 INI 文件读写类

INI 文件便于配置简单的程序外部参数，在 Windows 平台上有一套专门用于 INI 文件读写的 API，但到了其他平台，好像就没了。我看了好几个 INI 文件解析的开源代码，不是那么满意，于是我按自己想法，也实现了一套很简单、很易用的 INI 文件解析的代码，只有一个头文件，所有的功能都包含了!!!

## INI 文件结构
在实现 INI 文件解析的工作前，必须先了解一下 INI 文件的结构，而据我的观察，INI 文件的结构可以如下示例所描述：
```
[文件根]
    |--[空行]
    |--[注释]
    +--[分节]
        |--[空行]
        |--[注释]
        |--[键值]
        |--[键值]
        |--[空行]
        |--[空行]
        |--[...]
    |--[空行]
    |--[空行]
    |--[空行]
    +--[分节]
          |--[空行]
          |--[注释]
          |--[键值]
          |--[空行]
          |--[键值]
          |--[键值]
          |--[键值]
          |--[空行]
          |--[...]
    |--[空行]
    |--[...]
```
> - 文件根：INI 文件的虚拟名称，不存在于文件内容中。
> - 空行：空白行，即便有空白字符占据，也算空白行。
> - 注释：以 “;” 开头后的内容，都算是注释内容。
> - 分节：格式为 “[section]” 。
> - 键值：格式为 “key=value” 。

## 封装的类关系结构
```
[xini_node_t]
      |
      +--[xini_nilline_t]
      |
      +--[xini_comment_t]
      |
      +--[xini_keyvalue_t]
      |
      +--[xini_section_t]
      |
      +--[xini_file_t]
```
> - xini_node_t : INI 节点描述基类。
> - xini_nilline_t : INI 文件中的空行节点类。
> - xini_comment_t : INI 文件中的 注释 节点类。
> - xini_keyvalue_t : INI 文件中的 分节 节点类。
> - xini_section_t : INI 文件中的 分节 节点类。
> - xini_file_t : INI 文件操作类。

## 读写操作
INI 的键值读写，都是通过操作符重载的方式实现，可满足 C 所有的基本数据类型（整型、浮点型、字符串型等）的读写操作。

基本操作流程的描述如下：
> 1. 使用 xini_file_t 构建 INI 文件对象；
> 2. 然后通过 xini_file_t 对象重载的 [] 操作符获得要操作的 xini_section_t 分节对象；
> 3. 再则就是直接使用 xini_section_t 对象重载的 [] 操作符获得要操作的 xini_keyvalue_t 键值对象；
> 4. 最后使用 xini_keyvalue_t 对象重载了各个基本数据类型的操作符进行赋值操作就可实现读写操作。

简单地说，就是可直接 **xini_file_t["分节"]["键"]** 的方式进行赋值操作实现读写操作，如下示例：
> - 读：int num = (int)xini_file_t["分节"]["键"];
> - 写：xini_file_t["分节"]["键"] = (int)1000;

另外，所实现的 INI 相关类，都支持 C++ IO 流的操作方式。详细的使用方式，参考如下测试代码(**initest.cpp**)：
```
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

    // test line break
    xini_file["section4"]["LineBreak1"] = "ABCDEF\nGHIJKLMN";
    xini_file["section4"]["LineBreak2"] = "ABCDEF\rGHIJKLMN";
    xini_file["section4"]["LineBreak3"] = "ABCDEF\r7\nGHIJKLMN";
    xini_file["section4"]["LineBreak4"] = "\rABCDEFGHIJKLMN";

    //======================================
}

////////////////////////////////////////////////////////////////////////////////

```

## 详细实现的源码(xini_file.h)
可以到我的 GitHub 上直接获取源码：[https://github.com/Gaaagaa/inifile](https://github.com/Gaaagaa/inifile) 或者 [https://gitee.com/Gaaagaa/inifile](https://gitee.com/Gaaagaa/inifile) 。
下面也直接贴出来：
```
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
 * @file xini_file.h
 * Copyright (c) 2019, Gaaagaa All rights reserved.
 * 
 * @author  ：Gaaagaa
 * @date    : 2019-11-26
 * @version : 1.0.0.0
 * @brief   : ini file parser, read and write is supported.
 */

#ifndef __XINI_FILE_H__
#define __XINI_FILE_H__

#include <stdlib.h>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////

#if __cplusplus < 201103L
#define nullptr  0
#endif // __cplusplus < 201103L

/////////////////////////////////////////////////////////////////////////////////

/** 空白字符集 */
static const char xspace_chars[] = " \t\n\r\f\v";

/**********************************************************/
/**
 * @brief 削除字符串头尾的字符集。
 */
static inline std::string &
        xstr_trim(std::string & xstr,
                  const char * xtrim_chars = xspace_chars)
{
    xstr.erase(xstr.find_last_not_of(xtrim_chars) + 1);
    xstr.erase(0, xstr.find_first_not_of(xtrim_chars));

    return xstr;
}

/**********************************************************/
/**
 * @brief 削除字符串头部的字符集。
 */
static inline std::string &
        xstr_ltrim(std::string & xstr,
                   const char * xtrim_chars = xspace_chars)
{
    xstr.erase(0, xstr.find_first_not_of(xtrim_chars));
    return xstr;
}

/**********************************************************/
/**
 * @brief 削除字符串尾部的字符集。
 */
static inline std::string &
        xstr_rtrim(std::string & xstr,
                   const char * xtrim_chars = xspace_chars)
{
    xstr.erase(xstr.find_last_not_of(xtrim_chars) + 1);
    return xstr;
}

/**********************************************************/
/**
 * @brief 判断是否为单行字符串。
 */
static inline bool xstr_is_single_line(const std::string & xstr)
{
    return (xstr.find_first_of("\r\n") == std::string::npos);
}

#if 0

/**********************************************************/
/**
* @brief 字符串的比对操作。
*
* @param [in ] xszt_lcmp : 比较操作的左值字符串。
* @param [in ] xszt_rcmp : 比较操作的右值字符串。
*
* @return int
*         - xszt_lcmp <  xszt_rcmp，返回 <= -1；
*         - xszt_lcmp == xszt_rcmp，返回 ==  0；
*         - xszt_lcmp >  xszt_rcmp，返回 >=  1；
*/
static int xstr_cmp(const char * xszt_lcmp, const char * xszt_rcmp)
{
	int xit_lvalue = 0;
	int xit_rvalue = 0;

	if (xszt_lcmp == xszt_rcmp)
		return 0;
	if (NULL == xszt_lcmp)
		return -1;
	if (NULL == xszt_rcmp)
		return 1;

	do
	{
		xit_lvalue = (char)(*(xszt_lcmp++));
		xit_rvalue = (char)(*(xszt_rcmp++));
	} while (xit_lvalue && (xit_lvalue == xit_rvalue));

	return (xit_lvalue - xit_rvalue);
}

#endif

/**********************************************************/
/**
 * @brief 字符串忽略大小写的比对操作。
 *
 * @param [in ] xszt_lcmp : 比较操作的左值字符串。
 * @param [in ] xszt_rcmp : 比较操作的右值字符串。
 *
 * @return int
 *         - xszt_lcmp <  xszt_rcmp，返回 <= -1；
 *         - xszt_lcmp == xszt_rcmp，返回 ==  0；
 *         - xszt_lcmp >  xszt_rcmp，返回 >=  1；
 */
static int xstr_icmp(const char * xszt_lcmp, const char * xszt_rcmp)
{
	int xit_lvalue = 0;
	int xit_rvalue = 0;

	if (xszt_lcmp == xszt_rcmp)
		return 0;
	if (NULL == xszt_lcmp)
		return -1;
	if (NULL == xszt_rcmp)
		return 1;

	do
	{
		if (((xit_lvalue = (*(xszt_lcmp++))) >= 'A') && (xit_lvalue <= 'Z'))
			xit_lvalue -= ('A' - 'a');

		if (((xit_rvalue = (*(xszt_rcmp++))) >= 'A') && (xit_rvalue <= 'Z'))
			xit_rvalue -= ('A' - 'a');

	} while (xit_lvalue && (xit_lvalue == xit_rvalue));

	return (xit_lvalue - xit_rvalue);
}

////////////////////////////////////////////////////////////////////////////////
// xini_node_t : INI 节点的抽象定义

/**
 * <pre>
 * INI 文件格式的结构如下：
 * [文件根]
 *     |--[空行]
 *     |--[注释]
 *     +--[分节]
 *         |--[空行]
 *         |--[注释]
 *         |--[键值]
 *         |--[键值]
 *         |--[空行]
 *         |--[空行]
 *         |--[...]
 *     |--[空行]
 *     |--[空行]
 *     |--[空行]
 *     +--[分节]
 *           |--[空行]
 *           |--[注释]
 *           |--[键值]
 *           |--[空行]
 *           |--[键值]
 *           |--[键值]
 *           |--[键值]
 *           |--[空行]
 *           |--[...]
 *     |--[空行]
 *     |--[...]
 * 
 * 文件根：INI 文件的虚拟名称，不存在于文件内容中。
 * 空行：空白行，即便有空白字符占据，也算空白行。
 * 注释：以 “;” 开头后的内容，都算是注释内容。
 * 分节：格式为 “[section]” 。
 * 键值：格式为 “key=value” 。
 * </pre>
 */

/**
 * @enum  xini_node_type_t
 * @brief INI 文件中的节点信息类型。
 */
typedef enum xini_ntype_t
{
    XINI_NTYPE_UNDEFINE = 0xFFFFFFFF, ///< 未定义
    XINI_NTYPE_FILEROOT = 0x00000000, ///< 文件根
    XINI_NTYPE_NILLINE  = 0x00000100, ///< 空行
    XINI_NTYPE_COMMENT  = 0x00000200, ///< 注释
    XINI_NTYPE_SECTION  = 0x00000300, ///< 分节
    XINI_NTYPE_KEYVALUE = 0x00000400, ///< 键值
} xini_ntype_t;

/** 前置声明相关的 INI 节点类 */
class xini_keyvalue_t;
class xini_section_t;
class xini_comment_t;
class xini_nilline_t;
class xini_file_t;

/**
 * @class xini_node_t
 * @brief INI 节点描述基类。
 */
class xini_node_t
{
    friend class xini_file_t;
    friend class xini_section_t;

    // constructor/destructor
protected:
    xini_node_t(int xini_ntype, xini_node_t * xowner_ptr)
        : m_xini_ntype(xini_ntype)
        , m_xowner_ptr(xowner_ptr)
    {

    }

    virtual ~xini_node_t(void)
    {

    }

    // extensible interfaces
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流，派生的子类中必须实现具体操作。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const = 0;

    /**********************************************************/
    /**
     * @brief 脏标识。
     */
    virtual bool is_dirty(void) const
    {
        if (nullptr != m_xowner_ptr)
        {
            return m_xowner_ptr->is_dirty();
        }
        return false;
    }

    /**********************************************************/
    /**
     * @brief 设置脏标识。
     */
    virtual void set_dirty(bool x_dirty)
    {
        if (nullptr != m_xowner_ptr)
        {
            m_xowner_ptr->set_dirty(x_dirty);
        }
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 节点类型。
     */
    inline int ntype(void) const { return m_xini_ntype; }

    /**********************************************************/
    /**
     * @brief 获取节点的持有者。
     */
    inline xini_node_t * get_owner(void) const { return m_xowner_ptr; }

    // data members
protected:
    int           m_xini_ntype;   ///< 节点类型
    xini_node_t * m_xowner_ptr;   ///< 节点持有者
};

/**********************************************************/
/**
 * @brief 定义 xini_node_t 的流输出操作符函数。
 */
inline std::ostream & operator << (std::ostream & ostr,
                                   const xini_node_t & xini_node)
{
    xini_node >> ostr;
    return ostr;
}

////////////////////////////////////////////////////////////////////////////////
// xini_nilline_t

/**
 * @class xini_nilline_t
 * @brief INI 文件中的空行节点类。
 */
class xini_nilline_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief
     * 判断已经消除头尾空白字符的字符串是否
     * 符合 xini_nilline_t 定义的格式。
     */
    static bool is_ntype(const std::string & xstr_trim_line)
    {
        return xstr_trim_line.empty();
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_nilline_t 对象。
     */
    static xini_node_t * try_create(const std::string & xstr_trim_line,
                                    xini_node_t * xowner_ptr)
    {
        if (!is_ntype(xstr_trim_line))
        {
            return nullptr;
        }

        return (new xini_nilline_t(xowner_ptr));
    }

    // construcor/destructor
protected:
    xini_nilline_t(xini_node_t * xowner_ptr)
        : xini_node_t(XINI_NTYPE_NILLINE, xowner_ptr)
    {

    }

    virtual ~xini_nilline_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const
    {
        ostr << std::endl;
        return *this;
    }
};

////////////////////////////////////////////////////////////////////////////////
// xini_comment_t

/**
 * @class xini_comment_t
 * @brief INI 文件中的 注释 节点类。
 */
class xini_comment_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief
     * 判断已经消除头尾空白字符的字符串是否
     * 符合 xini_comment_t 定义的格式。
     */
    static bool is_ntype(const std::string & xstr_trim_line)
    {
        return (!xstr_trim_line.empty() && (';' == xstr_trim_line.at(0)));
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_comment_t 对象。
     */
    static xini_node_t * try_create(const std::string & xstr_trim_line,
                                    xini_node_t * xowner_ptr)
    {
        if (!is_ntype(xstr_trim_line))
        {
            return nullptr;
        }

        xini_comment_t * xnode_ptr = new xini_comment_t(xowner_ptr);
        xnode_ptr->m_xstr_text = xstr_trim_line;
        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_comment_t(xini_node_t * xowner_ptr)
        : xini_node_t(XINI_NTYPE_COMMENT, xowner_ptr)
    {

    }

    virtual ~xini_comment_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const
    {
        ostr << m_xstr_text << std::endl;
        return *this;
    }

protected:
    std::string   m_xstr_text;  ///< 注释行字符串
};

////////////////////////////////////////////////////////////////////////////////
// xini_keyvalue_t

/**
 * @class xini_keyvalue_t
 * @brief INI 文件中的 分节 节点类。
 */
class xini_keyvalue_t : public xini_node_t
{
    friend class xini_file_t;
    friend class xini_section_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief
     * 判断已经消除头尾空白字符的字符串是否
     * 符合 xini_keyvalue_t 定义的格式。
     */
    static bool is_ntype(const std::string & xstr_trim_line)
    {
        if (xstr_trim_line.empty())
        {
            return false;
        }

        // 等号位置
        size_t st_eq = xstr_trim_line.find('=');
        if ((0 == st_eq) || (std::string::npos == st_eq))
        {
            return false;
        }

        return false;
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_keyvalue_t 对象。
     */
    static xini_node_t * try_create(const std::string & xstr_trim_line,
                                    xini_node_t * xowner_ptr)
    {
        if (xstr_trim_line.empty())
        {
            return nullptr;
        }

        // 等号位置
        size_t st_eq = xstr_trim_line.find('=');
        if ((0 == st_eq) || (std::string::npos == st_eq))
        {
            return nullptr;
        }

        xini_keyvalue_t * xnode_ptr = new xini_keyvalue_t(xowner_ptr);

        xnode_ptr->m_xstr_kname = xstr_trim_line.substr(0, st_eq);
        xnode_ptr->m_xstr_value = xstr_trim_line.substr(st_eq + 1);

        xstr_trim(xnode_ptr->m_xstr_kname);
        xstr_trim(xnode_ptr->m_xstr_value);

        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_keyvalue_t(xini_node_t * xowner_ptr)
        : xini_node_t(XINI_NTYPE_KEYVALUE, xowner_ptr)
    {

    }

    virtual ~xini_keyvalue_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const
    {
        ostr << m_xstr_kname
             << '='
             << m_xstr_value
             << std::endl;
        return *this;
    }

    // operator
public:
	operator const std::string & () const
    {
        return m_xstr_value;
    }

	operator const char * () const
    {
        return m_xstr_value.c_str();
    }

    operator bool () const
    {
        if (0 == xstr_icmp(m_xstr_value.c_str(), "true"))
            return true;
        if (0 == xstr_icmp(m_xstr_value.c_str(), "false"))
            return false;
        return (0 != this->operator int());
    }

	operator short () const
    {
        return (short)atoi(m_xstr_value.c_str());
    }

	operator unsigned short () const
    {
        return (unsigned short)this->operator short();
    }

	operator int () const
    {
        return atoi(m_xstr_value.c_str());
    }

	operator unsigned int () const
    {
        return (unsigned int)this->operator int();
    }

    operator long () const
    {
        return atol(m_xstr_value.c_str());
    }

    operator unsigned long () const
    {
        return (unsigned long)this->operator long();
    }

    operator long long () const
    {
        return atoll(m_xstr_value.c_str());
    }

    operator unsigned long long () const
    {
        return (unsigned long long)this->operator long long();
    }

	operator float () const
    {
        return strtof(m_xstr_value.c_str(), nullptr);
    }

    operator double () const
    {
        return atof(m_xstr_value.c_str());
    }

    xini_keyvalue_t & operator = (const std::string & x_value)
    {
        set_value(x_value);
        return *this;
    }

    xini_keyvalue_t & operator = (const char * x_value)
    {
        set_value(x_value);
        return *this;
    }

    xini_keyvalue_t & operator = (bool x_value)
    {
        invk_set_value(x_value ? "true" : "false");
        return *this;
    }

    xini_keyvalue_t & operator = (short x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (unsigned short x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (int x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (unsigned int x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (long x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (unsigned long x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (long long x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (unsigned long long x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (float x_value)
    {
        std::ostringstream ostr;
        ostr.precision(6);
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    xini_keyvalue_t & operator = (double x_value)
    {
        std::ostringstream ostr;
        ostr.precision(16);
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 键名。
     */
    inline const std::string & xkey(void) const
    {
        return m_xstr_kname;
    }

    /**********************************************************/
    /**
     * @brief 键值。
     */
    inline const std::string & xvalue(void) const
    {
        return m_xstr_value;
    }

    /**********************************************************/
    /**
     * @brief 设置键值。
     */
    inline void set_value(const std::string & x_value)
    {
        std::string xstr = x_value.substr(0, x_value.find_first_of("\r\n"));
        invk_set_value(xstr_trim(xstr));
    }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 设置（单行文本 且 去除头尾空白字符 的）键值。
     */
    inline void invk_set_value(const std::string & xstr_single_line)
    {
        if (xstr_single_line != m_xstr_value)
        {
            m_xstr_value = xstr_single_line;
            set_dirty(true);
        }
    }

protected:
    std::string   m_xstr_kname;  ///< 键名
    std::string   m_xstr_value;  ///< 键值
};

////////////////////////////////////////////////////////////////////////////////
// xini_section_t

/**
 * @class xini_section_t
 * @brief INI 文件中的 分节 节点类。
 */
class xini_section_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief
     * 判断已经消除头尾空白字符的字符串是否
     * 符合 xini_section_t 定义的格式。
     */
    static bool is_ntype(const std::string & xstr_trim_line)
    {
        return (!xstr_trim_line.empty() &&
                ('[' == xstr_trim_line.at(0)) &&
                (']' == xstr_trim_line.at(xstr_trim_line.size() - 1)));
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_section_t 对象。
     */
    static xini_node_t * try_create(const std::string & xstr_trim_line,
                                    xini_node_t * xowner_ptr)
    {
        if (!is_ntype(xstr_trim_line))
        {
            return nullptr;
        }

        xini_section_t * xnode_ptr = new xini_section_t(xowner_ptr);
        xnode_ptr->m_xstr_name = xstr_trim_line;

        xstr_rtrim(xnode_ptr->m_xstr_name, "]");
        xstr_ltrim(xnode_ptr->m_xstr_name, "[");
        xstr_trim(xnode_ptr->m_xstr_name);

        // 将自身作为节点加入到节点表中
        xnode_ptr->m_xlst_node.push_back(xnode_ptr);

        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_section_t(xini_node_t * xowner_ptr)
        : xini_node_t(XINI_NTYPE_SECTION, xowner_ptr)
    {

    }

    virtual ~xini_section_t(void)
    {
        for (std::list< xini_node_t * >::iterator
                itlst = m_xlst_node.begin();
             itlst != m_xlst_node.end();
             ++itlst)
        {
            if (XINI_NTYPE_SECTION != (*itlst)->ntype())
            {
                delete (*itlst);
            }
        }

        m_xlst_node.clear();
    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const
    {
        for (std::list< xini_node_t * >::const_iterator
                itlst = m_xlst_node.begin();
             itlst != m_xlst_node.end();
             ++itlst)
        {
            if (this == static_cast< xini_section_t * >(
                            const_cast< xini_node_t * >(*itlst)))
            {
                if (!m_xstr_name.empty())
                {
                    ostr << "[" << m_xstr_name << "]" << std::endl;
                }
            }
            else
            {
                **itlst >> ostr;
            }
        }

        return *this;
    }

    // overrides : operator
public:
    /**********************************************************/
    /**
     * @brief 重载 operator [] 操作符，实现 键值 节点的索引操作。
     */
    xini_keyvalue_t & operator [] (const std::string & xstr_key)
    {
        assert(xstr_is_single_line(xstr_key));

        //======================================

        std::string xstr_nkey = xstr_key;
        xstr_trim(xstr_nkey);

        //======================================

        xini_keyvalue_t * xknode_ptr = find_knode(xstr_nkey);
        if (nullptr != xknode_ptr)
        {
            return *xknode_ptr;
        }

        //======================================

        xknode_ptr =
            static_cast< xini_keyvalue_t * >(
                xini_keyvalue_t::try_create(xstr_nkey + "=", get_owner()));
        assert(nullptr != xknode_ptr);

        m_xlst_node.push_back(xknode_ptr);

        //======================================

        return *xknode_ptr;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 分节 名称。
     */
    inline const std::string & name(void) const
    {
        return m_xstr_name;
    }

    /**********************************************************/
    /**
     * @brief 分节 内的节点数量。
     */
    inline size_t size(void) const
    {
        return m_xlst_node.size();
    }

    /**********************************************************/
    /**
     * @brief 分节 是否为空。
     */
    inline bool empty() const
    {
        return m_xlst_node.empty();
    }

    /**********************************************************/
    /**
     * @brief 判断当前分节是否以空行结尾。
     */
    inline bool has_end_nilline(void)
    {
        if (!m_xlst_node.empty() &&
            (XINI_NTYPE_NILLINE == m_xlst_node.back()->ntype()))
        {
            return true;
        }
        return false;
    }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 添加（空行、注释、键值 类型的）节点。
     * 
     * @param [in ] xnode_ptr: （空行、注释、键值 类型的）节点。
     * 
     * @return bool
     *         - 成功，返回 true ；
     *         - 失败，返回 false。
     */
    bool push_node(xini_node_t * xnode_ptr)
    {
        if (nullptr == xnode_ptr)
        {
            return false;
        }

        if ((XINI_NTYPE_NILLINE == xnode_ptr->ntype()) ||
            (XINI_NTYPE_COMMENT == xnode_ptr->ntype()))
        {
            m_xlst_node.push_back(xnode_ptr);
            return true;
        }

        if (XINI_NTYPE_KEYVALUE == xnode_ptr->ntype())
        {
            xini_keyvalue_t * xnode_kvptr =
                    static_cast< xini_keyvalue_t * >(xnode_ptr);

            if (nullptr != find_knode(xnode_kvptr->xkey()))
            {
                return false;
            }

            m_xlst_node.push_back(xnode_ptr);
            return true;
        }

        return false;
    }

    /**********************************************************/
    /**
     * @brief 查找分节下的 键值 节点。
     * 
     * @param [in ] xstr_xkey: 索引键字符串，比较时忽略大小写。
     * 
     * @return xini_keyvalue_t *
     *         - 成功，返回 对应的节点；
     *         - 失败，返回 nullptr 。
     */
    xini_keyvalue_t * find_knode(const std::string & xstr_xkey) const
    {
        for (std::list< xini_node_t * >::const_iterator
             itlst = m_xlst_node.begin();
             itlst != m_xlst_node.end();
             ++itlst)
        {
            if (XINI_NTYPE_KEYVALUE != (*itlst)->ntype())
            {
                continue;
            }

            xini_keyvalue_t * xnode_ptr =
                static_cast< xini_keyvalue_t * >(
                    const_cast< xini_node_t * >(*itlst));
            if (0 == xstr_icmp(xstr_xkey.c_str(), xnode_ptr->xkey().c_str()))
            {
                return xnode_ptr;
            }
        }

        return nullptr;
    }

    /**********************************************************/
    /**
     * @brief 从 节点表 尾部取出 非当前 分节 下的注释节点（按 空行 节点作为分界）。
     * 
     * @param [in ] xlst_comm : 接收返回的注释节点表（在链表头部添加返回的节点）。
     * @param [in ] xbt_front : 表明操作是从 xlst_comm 前/后附加返回的节点。
     * 
     * @return size_t
     *         - 返回取出的节点数量。
     */
    size_t pop_tail_comment(std::list< xini_node_t * > & xlst_comm, bool xbt_front)
    {
        std::list< xini_node_t * > xlst_node;

        size_t xst_line =  0;
        size_t xst_maxl = m_xlst_node.size();

        // 节点表只有三种类型的节点：键值，空行，注释，
        // 以及 另外加上 自身的 分节节点

        while ((xst_line++ < xst_maxl) && !m_xlst_node.empty())
        {
            xini_node_t * xnode_ptr = m_xlst_node.back();

            // 遇到空行节点
            if (XINI_NTYPE_NILLINE == xnode_ptr->ntype())
            {
                if (xst_line > 1)
                    break;

                // 只容许第一个是空行
                xlst_node.push_front(xnode_ptr);
                m_xlst_node.pop_back();
                continue;
            }

            // 若反向遍历过程中，一直未遇到空行，
            // 则将原取出的注释节点还回节点表中
            if ((XINI_NTYPE_KEYVALUE == xnode_ptr->ntype()) ||
                (XINI_NTYPE_SECTION  == xnode_ptr->ntype()))
            {
                m_xlst_node.splice(m_xlst_node.end(), xlst_node);
                break;
            }

            if (XINI_NTYPE_COMMENT == xnode_ptr->ntype())
            {
                xlst_node.push_front(xnode_ptr);
                m_xlst_node.pop_back();
            }
            else
            {
                // 未识别的节点类型
                assert(false);
            }
        }

        size_t xst_count = xlst_node.size();
        if (xst_count > 0)
        {
            // 设置返回结果
            if (xbt_front)
            {
                xlst_node.splice(xlst_node.end(), xlst_comm);
                xlst_comm.swap(xlst_node);
            }
            else
            {
                xlst_comm.splice(xlst_comm.end(), xlst_node);
            }
        }

        return xst_count;
    }

protected:
    std::string                m_xstr_name;  ///< 分节名称
    std::list< xini_node_t * > m_xlst_node;  ///< 分节下的节点表
};

////////////////////////////////////////////////////////////////////////////////
// xini_file_t

/**
 * @class xini_file_t
 * @brief INI 文件操作类。
 */
class xini_file_t : public xini_node_t
{
    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 依据给定的 INI 文本行，创建相应的节点。
     */
    static xini_node_t * make_node(const std::string & xstr_line,
                                   xini_file_t * xowner_ptr)
    {
        xini_node_t * xnode_ptr = nullptr;

#define XTRY_CREATE(nptr, node, owner)                 \
        do                                             \
        {                                              \
            nptr = node::try_create(xstr_line, owner); \
            if (nullptr != nptr)                       \
                return nptr;                           \
        } while (0)

        XTRY_CREATE(xnode_ptr, xini_nilline_t , xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_comment_t , xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_section_t , xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_keyvalue_t, xowner_ptr);

#undef XTRY_CREATE

        return xnode_ptr;
    }

    // constructor/destructor
public:
    xini_file_t(void)
        : xini_node_t(XINI_NTYPE_FILEROOT, nullptr)
        , m_xbt_dirty(false)
    {

    }

    xini_file_t(const std::string & xstr_filepath)
        : xini_node_t(XINI_NTYPE_FILEROOT, nullptr)
    {
        open(xstr_filepath);
    }

    virtual ~xini_file_t(void)
    {
        close();
    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t & operator >> (std::ostream & ostr) const
    {
        for (std::list< xini_section_t * >::const_iterator
                itlst = m_xlst_sect.begin();
             itlst != m_xlst_sect.end();
             ++itlst)
        {
            if ((*itlst)->empty())
                continue;

            **itlst >> ostr;
            if (!(*itlst)->has_end_nilline() &&
                ((*itlst) != m_xlst_sect.back()))
            {
                ostr << std::endl;
            }
        }

        return *this;
    }

    /**********************************************************/
    /**
     * @brief 脏标识。
     */
    virtual bool is_dirty(void) const
    {
        return m_xbt_dirty;
    }

    /**********************************************************/
    /**
     * @brief 设置脏标识。
     */
    virtual void set_dirty(bool x_dirty)
    {
        m_xbt_dirty = x_dirty;
    }

    // overrides : operator
public:
    /**********************************************************/
    /**
     * @brief 从 输出流 构建 xini_file_t 内容。
     */
    xini_file_t & operator << (std::istream & istr)
    {
        //======================================

        // 记录当前操作的分节
        xini_section_t * xsect_ptr = nullptr;

        if (m_xlst_sect.empty())
        {
            // 当前分节表为空，则创建一个空分节名的 分节 节点
            xsect_ptr = new xini_section_t(this);
            m_xlst_sect.push_back(xsect_ptr);
        }
        else
        {
            // 取尾部分节作为当前操作的 分节 节点
            xsect_ptr = m_xlst_sect.back();

            // 确保尾部分节空行结尾
            if (!xsect_ptr->has_end_nilline())
            {
                xsect_ptr->push_node(new xini_nilline_t(this));
            }
        }

        //======================================

        // 逐行解析 INI 文件，构建节点表
        while (!istr.eof())
        {
            //======================================
            // 读取文本行

            std::string xstr_line;
            std::getline(istr, xstr_line);
            xstr_trim(xstr_line);

            // 最后一个空行不放到节点表中，避免文件关闭时 持续增加 尾部空行
            if (istr.eof() && xstr_line.empty())
            {
                break;
            }

            //======================================

            // 创建节点
            xini_node_t * xnode_ptr = make_node(xstr_line, this);
            if (nullptr == xnode_ptr)
            {
                continue;
            }

            // 若为 分节 节点，则加入到分节表中，并更新当前操作的 分节节点
            if (XINI_NTYPE_SECTION == xnode_ptr->ntype())
            {
                xsect_ptr =
                    push_sect(static_cast< xini_section_t * >(xnode_ptr),
                              xsect_ptr);

                if (xsect_ptr != static_cast< xini_section_t * >(xnode_ptr))
                    delete xnode_ptr; // 添加新分节失败，删除该节点
                else
                    set_dirty(true);  // 添加新分节成功，设置脏标识

                continue;
            }

            // 加入 当前分节
            if (xsect_ptr->push_node(xnode_ptr))
            {
                set_dirty(true);
            }
            else
            {
                // 加入分节失败，可能是因为：
                // 其为 键值 节点，与 分节 节点表中已有的 节点 索引键 冲突
                delete xnode_ptr;
            }

            //======================================
        }

        //======================================

        return *this;
    }

    /**********************************************************/
    /**
     * @brief 重载 operator [] 操作符，实现 分节 索引操作。
     */
    xini_section_t & operator [] (const std::string & xstr_sect)
    {
        assert(xstr_is_single_line(xstr_sect));

        //======================================

        std::string xstr_name = xstr_sect;
        xstr_trim(xstr_name);
        xstr_rtrim(xstr_name, "]");
        xstr_ltrim(xstr_name, "[");
        xstr_trim(xstr_name);

        //======================================

        xini_section_t * xsect_ptr = find_sect(xstr_name);
        if (nullptr != xsect_ptr)
        {
            return *xsect_ptr;
        }

        //======================================

        xsect_ptr =
            static_cast< xini_section_t * >(
                xini_section_t::try_create("[" + xstr_name + "]", this));
        assert(nullptr != xsect_ptr);

        m_xlst_sect.push_back(xsect_ptr);

        //======================================

        return *xsect_ptr;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 打开文件。
     * 
     * @param [in ] xstr_text : 文件路径。
     * 
     * @return bool
     *         - 成功，返回 true ；
     *         - 失败，返回 false。
     */
    bool open(const std::string & xstr_filepath)
    {
        // 若当前对象处于打开状态，则先关闭
        if (is_open())
        {
            close();
        }

        if (xstr_filepath.empty())
        {
            return false;
        }

        // 打开文件
        std::ifstream xfile_reader(xstr_filepath.c_str());
        if (!xfile_reader.is_open())
        {
            return false;
        }

        m_xstr_path = xstr_filepath;

        *this << xfile_reader;
        set_dirty(false);

        return true;
    }

    /**********************************************************/
    /**
     * @brief 关闭文件（可以不显示调用，对象析构函数中会自动调用该接口）。
     */
    void close(void)
    {
        if (is_dirty())
        {
            dump(m_xstr_path);
            set_dirty(false);
        }
        m_xstr_path.clear();

        for (std::list< xini_section_t * >::iterator
                itlst = m_xlst_sect.begin();
             itlst != m_xlst_sect.end();
             ++itlst)
        {
            delete *itlst;
        }

        m_xlst_sect.clear();
    }

    /**********************************************************/
    /**
     * @brief 判断对象是否已经打开。
     */
    inline bool is_open(void) const
    {
        return (!m_xstr_path.empty() || !m_xlst_sect.empty());
    }

    /**********************************************************/
    /**
     * @brief 当前关联的文件路径。
     */
    inline const std::string & filepath(void) const
    {
        return m_xstr_path;
    }

    /**********************************************************/
    /**
     * @brief 返回当前分节数量。
     */
    inline size_t sect_count(void) const
    {
        return m_xlst_sect.size();
    }

    /**********************************************************/
    /**
     * @brief 将当前文件根下的所有节点直接输出到文件中。
     */
    bool dump(const std::string & xstr_filepath)
    {
        if (!is_open() || xstr_filepath.empty())
        {
            return false;
        }

        // 打开文件
        std::ofstream xfile_writer(xstr_filepath.c_str());
        if (!xfile_writer.is_open())
        {
            return false;
        }

        *this >> xfile_writer;
        return true;
    }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 查找分节。
     */
    xini_section_t * find_sect(const std::string & xstr_sect) const
    {
        for (std::list< xini_section_t * >::const_iterator
                itlst = m_xlst_sect.begin();
             itlst != m_xlst_sect.end();
             ++itlst)
        {
            if (0 == xstr_icmp(xstr_sect.c_str(),
                                (*itlst)->name().c_str()))
            {
                return (*itlst);
            }
        }

        return nullptr;
    }

    /**********************************************************/
    /**
     * @brief 加入新分节（该接口仅由 operator << 调用）。
     * 
     * @param [in ] xnew_ptr  : 新增分节。
     * @param [in ] xsect_ptr : 当前操作分节。
     * 
     * @return xini_section_t *s
     *         - 返回当前操作分节。
     *         - 若返回值 != xnew_ptr 则表示操作失败，新增分节和内部分节重名。
     */
    xini_section_t * push_sect(xini_section_t * xnew_ptr,
                               xini_section_t * xsect_ptr)
    {
        // 查找同名分节
        xini_section_t * xfind_ptr = find_sect(xnew_ptr->name());

        if (nullptr == xfind_ptr)
        {
            // 不存在同名分节，则将新增分节加入到节点表尾部
            m_xlst_sect.push_back(xnew_ptr);

            // 将当前操作分节的节点表中的 尾部注释节点，
            // 全部转移到新增分节的节点表前
            xsect_ptr->pop_tail_comment(xnew_ptr->m_xlst_node, true);

            // 将新增分节作为当前操作分节返回
            xsect_ptr = xnew_ptr;
        }
        else if (xfind_ptr != xsect_ptr)
        {
            // 将当前操作分节的节点表中的 尾部注释节点，
            // 全部转移到同名分节的节点表后

            // 保证空行隔开
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));  
            }

            // 增加注释节点
            xsect_ptr->pop_tail_comment(xfind_ptr->m_xlst_node, false);

            // 保证空行隔开
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));
            }

            // 将同名分节作为当前操作分节返回
            xsect_ptr = xfind_ptr;
        }

        return xsect_ptr;
    }

    // data members
protected:
    bool                          m_xbt_dirty;  ///< 脏标识
    std::string                   m_xstr_path;  ///< 文件路径
    std::list< xini_section_t * > m_xlst_sect;  ///< 文件根下的 分节 节点表
};

/**********************************************************/
/**
 * @brief 定义 xini_file_t 的流输入操作符函数。
 */
inline std::istream & operator >> (std::istream & istr,
                                   xini_file_t & xini_file)
{
    xini_file << istr;
    return istr;
}

////////////////////////////////////////////////////////////////////////////////

#endif // __XINI_FILE_H__

```
