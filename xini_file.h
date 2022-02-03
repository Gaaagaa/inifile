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
 * @file xini_file.h
 * Copyright (c) 2019-2020, Gaaagaa All rights reserved.
 * 
 * @author  ：Gaaagaa
 * @date    : 2021-01-09
 * @version : 1.2.0.1
 * @brief   : `this->operator __base_type()`, gcc not supported.
 * @note    : Sepecial thanks for (qinwanlin)[https://gitee.com/qinwanlin].
 * 
 * @author  ：Gaaagaa
 * @date    : 2020-11-07
 * @version : 1.2.0.0
 * @brief   : Improved retrieval performance of the operator[].
 * 
 * @author  ：Gaaagaa
 * @date    : 2020-10-28
 * @version : 1.1.0.0
 * @brief   : update load()/release(), add operator()/try_value().
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
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////

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

/**
 * @struct xstr_icmp_t
 * @brief  as functor.
 */
struct xstr_icmp_t
{
    typedef std::string first_argument_type;
    typedef std::string second_argument_type;
    typedef bool        result_type;

    bool operator () (
        const std::string & xstr_left,
        const std::string & xstr_right) const
    {
        return (xstr_icmp(xstr_left.c_str(), xstr_right.c_str()) < 0);
    }
};

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
 * 注释：以 “;” 或者 “#” 开头后的内容，都算是注释内容。
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
        if (NULL != m_xowner_ptr)
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
        if (NULL != m_xowner_ptr)
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
inline std::ostream & operator << (
    std::ostream & ostr, const xini_node_t & xini_node)
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
            return NULL;
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
        return (!xstr_trim_line.empty() &&
                ((';' == xstr_trim_line.at(0)) ||
                 ('#' == xstr_trim_line.at(0))));
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
            return NULL;
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
            return NULL;
        }

        // 等号位置
        size_t st_eq = xstr_trim_line.find('=');
        if ((0 == st_eq) || (std::string::npos == st_eq))
        {
            return NULL;
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

    // template<> functions, for operators
protected:
    /**********************************************************/
    /**
     * @brief 整数值的读操作。
     */
    template< typename __integer_type >
    __integer_type get_ivalue() const
    {
#if __cplusplus < 201103L
        return static_cast< __integer_type >(atol(m_xstr_value.c_str()));
#else // __cplusplus >= 201103L
        // atoll() 隶属于 C11 标准
        return static_cast< __integer_type >(atoll(m_xstr_value.c_str()));
#endif // __cplusplus < 201103L
    }

    /**********************************************************/
    /**
     * @brief 实现带默认值的读操作。
     */
    template< typename __base_type >
    __base_type get_default(__base_type x_default) const
    {
        if (empty())
            return x_default;
        return (__base_type)(*this);
    }

    /**********************************************************/
    /**
     * @brief 整数值的写操作。
     */
    template< typename __integer_type >
    xini_keyvalue_t & set_ivalue(__integer_type x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    /**********************************************************/
    /**
     * @brief 实现浮点值的写操作。
     */
    template< typename __float_type >
    xini_keyvalue_t & set_fvalue(
        __float_type x_value, std::streamsize x_precision)
    {
        std::ostringstream ostr;
        ostr.precision(x_precision);
        ostr << x_value;
        invk_set_value(ostr.str());
        return *this;
    }

    /**********************************************************/
    /**
     * @brief 若当前值为 空 时，则更新为指定的值，最后再返回键值。
     */
    template< typename __base_type >
    __base_type try_set(__base_type x_value)
    {
        if (empty())
        {
            this->operator = (x_value);
        }

        return (__base_type)(*this);
    }

    // operators
public:
    //======================================
    // 基础数据类型的读操作

    operator const std::string & () const { return m_xstr_value;         }
    operator const char *        () const { return m_xstr_value.c_str(); }

    operator bool () const
    {
        if (0 == xstr_icmp(m_xstr_value.c_str(), "true"))
            return true;
        if (0 == xstr_icmp(m_xstr_value.c_str(), "false"))
            return false;
        return (0 != this->operator int());
    }

    operator short              () const { return get_ivalue< short              >(); }
    operator unsigned short     () const { return get_ivalue< unsigned short     >(); }
    operator int                () const { return get_ivalue< int                >(); }
    operator unsigned int       () const { return get_ivalue< unsigned int       >(); }
    operator long               () const { return get_ivalue< long               >(); }
    operator unsigned long      () const { return get_ivalue< unsigned long      >(); }
    operator long long          () const { return get_ivalue< long long          >(); }
    operator unsigned long long () const { return get_ivalue< unsigned long long >(); }

    operator float  () const { return static_cast< float >(this->operator double()); }
    operator double () const { return atof(m_xstr_value.c_str());                    }

    //======================================
    // 重载 operator ()，实现带上默认值的读操作

    const std::string & operator () (const std::string & x_default) const { return get_default< const std::string & >(x_default); }
    const char *        operator () (const char *        x_default) const { return get_default< const char *        >(x_default); }
    bool                operator () (bool                x_default) const { return get_default< bool                >(x_default); }
    short               operator () (short               x_default) const { return get_default< short               >(x_default); }
    unsigned short      operator () (unsigned short      x_default) const { return get_default< unsigned short      >(x_default); }
    int                 operator () (int                 x_default) const { return get_default< int                 >(x_default); }
    unsigned int        operator () (unsigned int        x_default) const { return get_default< unsigned int        >(x_default); }
    long                operator () (long                x_default) const { return get_default< long                >(x_default); }
    unsigned long       operator () (unsigned long       x_default) const { return get_default< unsigned long       >(x_default); }
    long long           operator () (long long           x_default) const { return get_default< long long           >(x_default); }
    unsigned long long  operator () (unsigned long long  x_default) const { return get_default< unsigned long long  >(x_default); }
    float               operator () (float               x_default) const { return get_default< float               >(x_default); }
    double              operator () (double              x_default) const { return get_default< double              >(x_default); }

    //======================================
    // 与重载的 operator () 操作符功能类似，
    // 但会使用默认值更新空键值

    const std::string & try_value(const std::string & x_default) { return try_set< const std::string & >(x_default); }
    const char *        try_value(const char *        x_default) { return try_set< const char *        >(x_default); }
    bool                try_value(bool                x_default) { return try_set< bool                >(x_default); }
    short               try_value(short               x_default) { return try_set< short               >(x_default); }
    unsigned short      try_value(unsigned short      x_default) { return try_set< unsigned short      >(x_default); }
    int                 try_value(int                 x_default) { return try_set< int                 >(x_default); }
    unsigned int        try_value(unsigned int        x_default) { return try_set< unsigned int        >(x_default); }
    long                try_value(long                x_default) { return try_set< long                >(x_default); }
    unsigned long       try_value(unsigned long       x_default) { return try_set< unsigned long       >(x_default); }
    long long           try_value(long long           x_default) { return try_set< long long           >(x_default); }
    unsigned long long  try_value(unsigned long long  x_default) { return try_set< unsigned long long  >(x_default); }
    float               try_value(float               x_default) { return try_set< float               >(x_default); }
    double              try_value(double              x_default) { return try_set< double              >(x_default); }

    //======================================
    // 基础数据类型的写操作

    xini_keyvalue_t & operator = (const std::string & x_value) { set_value(x_value); return *this; }
    xini_keyvalue_t & operator = (const char *        x_value) { set_value(x_value); return *this; }
    xini_keyvalue_t & operator = (bool x_value) { invk_set_value(x_value ? "true" : "false"); return *this; }
    xini_keyvalue_t & operator = (short              x_value) { return set_ivalue< short              >(x_value); }
    xini_keyvalue_t & operator = (unsigned short     x_value) { return set_ivalue< unsigned short     >(x_value); }
    xini_keyvalue_t & operator = (int                x_value) { return set_ivalue< int                >(x_value); }
    xini_keyvalue_t & operator = (unsigned int       x_value) { return set_ivalue< unsigned int       >(x_value); }
    xini_keyvalue_t & operator = (long               x_value) { return set_ivalue< long               >(x_value); }
    xini_keyvalue_t & operator = (unsigned long      x_value) { return set_ivalue< unsigned long      >(x_value); }
    xini_keyvalue_t & operator = (long long          x_value) { return set_ivalue< long long          >(x_value); }
    xini_keyvalue_t & operator = (unsigned long long x_value) { return set_ivalue< unsigned long long >(x_value); }
    xini_keyvalue_t & operator = (float  x_value) { return set_fvalue(x_value,  6); }
    xini_keyvalue_t & operator = (double x_value) { return set_fvalue(x_value, 16); }

    //======================================

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
     * @brief 判断 键值 是否为 空。
     */
    inline bool empty(void) const
    {
        return m_xstr_value.empty();
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

    // common data types
protected:
    typedef std::list< xini_node_t * >                              xlst_node_t;
    typedef std::map< std::string, xini_keyvalue_t *, xstr_icmp_t > xmap_ndkv_t;
public:
    typedef xlst_node_t::iterator       iterator;
    typedef xlst_node_t::const_iterator const_iterator;

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
            return NULL;
        }

        xini_section_t * xnode_ptr = new xini_section_t(xowner_ptr);
        xnode_ptr->m_xstr_name = xstr_trim_line;

        xstr_rtrim(xnode_ptr->m_xstr_name, "]");
        xstr_ltrim(xnode_ptr->m_xstr_name, "[");
        xstr_trim(xnode_ptr->m_xstr_name);

        // 将 自身 作为 节点 加入到 m_xlst_node 中，但并不意味着 m_xlst_node 
        // 的 首个节点 就一定是 自身节点，因为 xini_file_t 在加载过程中，
        // 会调用 pop_tail_comment() 操作，这有可能在 m_xlst_node 前端新增
        // 一些 注释/空行节点。所以在进行 流输出 操作时，自身节点 则可起到 占位行
        // 的作用，详细过程可参看 operator >> 的实现流程
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
        m_xmap_ndkv.clear();
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
        if (NULL != xknode_ptr)
        {
            return *xknode_ptr;
        }

        //======================================
        // 若索引的 键值节点 并未在节点表中，
        // 则 新增 此 键值节点，但并不设置 脏标识，
        // 避免存储不必要的 空键值节点

        xknode_ptr =
            static_cast< xini_keyvalue_t * >(
                xini_keyvalue_t::try_create(xstr_nkey + "=", get_owner()));
        assert(NULL != xknode_ptr);

        m_xlst_node.push_back(xknode_ptr);
        m_xmap_ndkv.insert(std::make_pair(xstr_nkey, xknode_ptr));

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

    // iterator
public:
    /**********************************************************/
    /**
     * @brief 节点表的起始位置迭代器。
     */
    inline iterator begin(void) { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief 节点表的起始位置迭代器。
     */
    inline const_iterator begin(void) const { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief 节点表的结束位置迭代器。
     */
    inline iterator end(void) { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief 节点表的结束位置迭代器。
     */
    inline const_iterator end(void) const { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief 返回节点表中 首个 键值节点 的迭代器。
     */
    inline iterator begin_kv(void)
    {
        iterator xiter = m_xlst_node.begin();
        if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
            return xiter;
        return next_kv(xiter);
    }

    /**********************************************************/
    /**
     * @brief 返回节点表中 首个 键值节点 的迭代器。
     */
    inline const_iterator begin_kv(void) const
    {
        const_iterator xiter = m_xlst_node.begin();
        if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
            return xiter;
        return next_kv(xiter);
    }

    /**********************************************************/
    /**
     * @brief 返回 下一个 键值节点 的迭代器。
     */
    iterator next_kv(iterator xiter)
    {
        const iterator xiter_end = m_xlst_node.end();
        if (xiter != xiter_end)
        {
            while (++xiter != xiter_end)
                if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
                    return xiter;
        }

        return xiter_end;
    }

    /**********************************************************/
    /**
     * @brief 返回 下一个 键值节点 的迭代器。
     */
    const_iterator next_kv(const_iterator xiter) const
    {
        const const_iterator xiter_end = m_xlst_node.end();
        if (xiter != xiter_end)
        {
            while (++xiter != xiter_end)
                if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
                    return xiter;
        }

        return xiter_end;
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
        if (NULL == xnode_ptr)
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

            if (NULL != find_knode(xnode_kvptr->xkey()))
            {
                return false;
            }

            m_xlst_node.push_back(xnode_ptr);
            m_xmap_ndkv.insert(std::make_pair(xnode_kvptr->xkey(), xnode_kvptr));
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
     *         - 失败，返回 NULL 。
     */
    xini_keyvalue_t * find_knode(const std::string & xstr_xkey) const
    {
#if 0
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
#else
        xmap_ndkv_t::const_iterator itfind = m_xmap_ndkv.find(xstr_xkey);
        if (itfind != m_xmap_ndkv.end())
        {
            return itfind->second;
        }
#endif
        return NULL;
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
    std::string   m_xstr_name;  ///< 分节名称
    xlst_node_t   m_xlst_node;  ///< 分节下的节点表
    xmap_ndkv_t   m_xmap_ndkv;  ///< 分节下的 键值节点 映射表
};

////////////////////////////////////////////////////////////////////////////////
// xini_file_t

/**
 * @class xini_file_t
 * @brief INI 文件操作类。
 */
class xini_file_t : public xini_node_t
{
    // common data types
protected:
    typedef std::list< xini_section_t * >                          xlst_section_t;
    typedef std::map< std::string, xini_section_t *, xstr_icmp_t > xmap_section_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 依据给定的 INI 文本行，创建相应的节点。
     */
    static xini_node_t * make_node(const std::string & xstr_line,
                                   xini_file_t * xowner_ptr)
    {
        xini_node_t * xnode_ptr = NULL;

#define XTRY_CREATE(nptr, node, owner)                 \
        do                                             \
        {                                              \
            nptr = node::try_create(xstr_line, owner); \
            if (NULL != nptr)                       \
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
        : xini_node_t(XINI_NTYPE_FILEROOT, NULL)
        , m_xbt_dirty(false)
    {

    }

    xini_file_t(const std::string & xstr_filepath)
        : xini_node_t(XINI_NTYPE_FILEROOT, NULL)
        , m_xbt_dirty(false)
    {
        load(xstr_filepath);
    }

    virtual ~xini_file_t(void)
    {
        release();
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
        xini_section_t * xsect_ptr = NULL;

        if (m_xlst_sect.empty())
        {
            // 当前分节表为空，则创建一个空分节名的 分节 节点
            xsect_ptr = new xini_section_t(this);
            m_xlst_sect.push_back(xsect_ptr);

            assert(m_xmap_sect.empty());
            m_xmap_sect.insert(std::make_pair(std::string(""), xsect_ptr));
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
            if (NULL == xnode_ptr)
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
        if (NULL != xsect_ptr)
        {
            return *xsect_ptr;
        }

        //======================================
        // 若索引的分节并未在 分节 的节点表中，
        // 则 新增 此分节，但并不设置 脏标识，
        // 避免存储不必要的  空分节

        xsect_ptr =
            static_cast< xini_section_t * >(
                xini_section_t::try_create("[" + xstr_name + "]", this));
        assert(NULL != xsect_ptr);

        m_xlst_sect.push_back(xsect_ptr);
        m_xmap_sect.insert(std::make_pair(xstr_name, xsect_ptr));

        //======================================

        return *xsect_ptr;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 从指定路径的文件中加载 INI 内容。
     * @note
     *  load() 操作的成功与否，并不影响后续的键值读写操作，
     *  其只能标示 xini_file_t 对象是否关联可至指定路径
     *  （本地磁盘 或 远程网络 等的）文件。
     * 
     * @param [in ] xstr_text : 文件路径。
     * 
     * @return bool
     *         - 成功，返回 true ；
     *         - 失败，返回 false。
     */
    bool load(const std::string & xstr_filepath)
    {
        // 先释放当前对象
        release();

        // 不管后续操作是否成功，都关联到新指定的 INI 文件路径
        m_xstr_path = xstr_filepath;

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

        // 跳过字符流的头部编码信息（如 utf-8 的 bom 标识）
        while (!xfile_reader.eof())
        {
            int xchar = xfile_reader.get();
            if (std::iscntrl(xchar) || std::isprint(xchar))
            {
                xfile_reader.putback(static_cast< char >(xchar));
                break;
            }

            m_xstr_head.push_back(static_cast< char >(xchar));
        }

        *this << xfile_reader;
        set_dirty(false);

        return true;
    }

    /**********************************************************/
    /**
     * @brief 释放对象资源（可以不显示调用，对象析构函数中会自动调用该接口）。
     */
    void release(void)
    {
        if (is_dirty())
        {
            dump(m_xstr_path);
            set_dirty(false);
        }
        m_xstr_path.clear();
        m_xstr_head.clear();

        for (std::list< xini_section_t * >::iterator
                itlst = m_xlst_sect.begin();
             itlst != m_xlst_sect.end();
             ++itlst)
        {
            delete *itlst;
        }

        m_xlst_sect.clear();
        m_xmap_sect.clear();
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
        // 打开文件
        std::ofstream xfile_writer(
            xstr_filepath.c_str(), std::ios_base::trunc);
        if (!xfile_writer.is_open())
        {
            return false;
        }

        if (!m_xstr_head.empty())
            xfile_writer << m_xstr_head.c_str();
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
#if 0
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
#else
        xmap_section_t::const_iterator itfind = m_xmap_sect.find(xstr_sect);
        if (itfind != m_xmap_sect.end())
        {
            return itfind->second;
        }
#endif
        return NULL;
    }

    /**********************************************************/
    /**
     * @brief 加入新分节（该接口仅由 operator << 调用）。
     * 
     * @param [in ] xnew_ptr  : 新增分节。
     * @param [in ] xsect_ptr : 当前操作分节。
     * 
     * @return xini_section_t *
     *         - 返回当前操作分节。
     *         - 若返回值 != xnew_ptr 则表示操作失败，新增分节和内部分节重名。
     */
    xini_section_t * push_sect(xini_section_t * xnew_ptr,
                               xini_section_t * xsect_ptr)
    {
        // 查找同名分节
        xini_section_t * xfind_ptr = find_sect(xnew_ptr->name());

        if (NULL == xfind_ptr)
        {
            // 不存在同名分节，则将新增分节加入到节点表尾部
            m_xlst_sect.push_back(xnew_ptr);
            m_xmap_sect.insert(std::make_pair(xnew_ptr->name(), xnew_ptr));

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
    bool              m_xbt_dirty;  ///< 脏标识
    std::string       m_xstr_path;  ///< 文件路径
    std::string       m_xstr_head;  ///< 用于存储文件头的编码字符信息（如 utf-8 的 bom 标识）
    xlst_section_t    m_xlst_sect;  ///< 文件根下的 分节 节点表
    xmap_section_t    m_xmap_sect;  ///< 各个 分节 的节点映射表
};

/**********************************************************/
/**
 * @brief 定义 xini_file_t 的流输入操作符函数。
 */
inline std::istream & operator >> (
    std::istream & istr, xini_file_t & xini_file)
{
    xini_file << istr;
    return istr;
}

////////////////////////////////////////////////////////////////////////////////

#endif // __XINI_FILE_H__
