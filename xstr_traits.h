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
 * @file xstr_traits.h
 * Copyright (c) 2021 Gaaagaa. All rights reserved.
 * 
 * @author  : Gaaagaa
 * @date    : 2021-03-26
 * @version : 1.0.0.0
 * @brief   : 提供 xstr_traits_t 类辅助字符串的一些操作。
 */

#ifndef __XSTR_TRAITS_H__
#define __XSTR_TRAITS_H__

#if __cplusplus < 201103L
// This support must be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#error "This file requires compiler and library support for the ISO C++ 2011 standard."
#endif // __cplusplus < 201103L

#include <string>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 声明 xstr_traits 的基类。
 * @tparam __char_t : char or wchar_t。
 */
template< class __char_t > struct xstr_traits_base_t;

/**
 * @struct xstr_traits_base_t< char >
 * @brief  特化 xstr_traits_base_t< char > 基类。
 */
struct xstr_traits_base_t< char >
{
    /** 空白字符集 */
    static constexpr const char xchar_set_space[] = " \t\n\r\f\v";

    /** 换行字符集 */
    static constexpr const char xchar_set_nline[] = "\r\n";

    /** "[" 字符集 */
    static constexpr const char xchar_set_lsect[] = "[";

    /** "]" 字符集 */
    static constexpr const char xchar_set_rsect[] = "]";

    /** '#' 字符 */
    static constexpr const char xchar_number_sign = '#';

    /** ';' 字符 */
    static constexpr const char xchar_semicolon = ';';

    /** '=' 字符 */
    static constexpr const char xchar_equal = '=';

    /** '[' 字符 */
    static constexpr const char xchar_lsect = '[';

    /** ']' 字符 */
    static constexpr const char xchar_rsect = ']';
};

/**
 * @struct xstr_traits_base_t< wchar_t >
 * @brief  特化 xstr_traits_base_t< wchar_t > 基类。
 */
struct xstr_traits_base_t< wchar_t >
{
    /** 空白字符集 */
    static constexpr const wchar_t xchar_set_space[] = L" \t\n\r\f\v";

    /** 换行字符集 */
    static constexpr const wchar_t xchar_set_nline[] = L"\r\n";

    /** "[" 字符集 */
    static constexpr const wchar_t xchar_set_lsect[] = L"[";

    /** "]" 字符集 */
    static constexpr const wchar_t xchar_set_rsect[] = L"]";

    /** '#' 字符 */
    static constexpr const wchar_t xchar_number_sign = L'#';

    /** ';' 字符 */
    static constexpr const wchar_t xchar_semicolon = L';';

    /** '=' 字符 */
    static constexpr const wchar_t xchar_equal = L'=';

    /** '[' 字符 */
    static constexpr const wchar_t xchar_lsect = L'[';

    /** ']' 字符 */
    static constexpr const wchar_t xchar_rsect = L']';
};

/**
 * @class xstr_traits_t< __char_t >
 * @brief 字符串各种操作的辅助工具类。
 * @tparam __char_t : char or wchar_t。
 */
template< class __char_t >
class xstr_traits_t : xstr_traits_base_t< __char_t >
{
    // common data types
public:
    using xchar_t = __char_t;
    using xsize_t = size_t;
    using xstring = std::basic_string< __char_t >;
    using xstrios = std::basic_ios< __char_t >;
    using xsuper  = xstr_traits_base_t< __char_t >;

    // common invoking
public:
    /**********************************************************/
    /**
     * @brief 削除字符串头尾的字符集。
     */
    static inline xstring &
        trim(xstring & xstr, const xchar_t * xtrim_chars = xsuper::xchar_set_space)
    {
        xstr.erase(xstr.find_last_not_of(xtrim_chars) + 1);
        xstr.erase(0, xstr.find_first_not_of(xtrim_chars));

        return xstr;
    }

    /**********************************************************/
    /**
     * @brief 削除字符串头部的字符集。
     */
    static inline xstring &
        ltrim(xstring & xstr, const xchar_t * xtrim_chars = xsuper::xchar_set_space)
    {
        xstr.erase(0, xstr.find_first_not_of(xtrim_chars));
        return xstr;
    }

    /**********************************************************/
    /**
     * @brief 削除字符串尾部的字符集。
     */
    static inline xstring &
        rtrim(xstring & xstr, const xchar_t * xtrim_chars = xsuper::xchar_set_space)
    {
        xstr.erase(xstr.find_last_not_of(xtrim_chars) + 1);
        return xstr;
    }

    /**********************************************************/
    /**
     * @brief 判断是否为单行字符串。
     */
    static inline bool is_single_line(const xstring & xstr)
    {
        return (xstr.find_first_of(xsuper::xchar_set_nline) == std::string::npos);
    }

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
    static int cmp(const xchar_t * xszt_lcmp, const xchar_t * xszt_rcmp)
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
            xit_lvalue = *(xszt_lcmp++);
            xit_rvalue = *(xszt_rcmp++);
        } while (xit_lvalue && (xit_lvalue == xit_rvalue));

        return (xit_lvalue - xit_rvalue);
    }

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
    static int icmp(const xchar_t * xszt_lcmp, const xchar_t * xszt_rcmp)
    {
        const int xit_ivcmp = xstrios::widen('A') - xstrios::widen('a');

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
            if (((xit_lvalue = (*(xszt_lcmp++))) >= xstrios::widen('A')) &&
                 (xit_lvalue <= xstrios::widen('Z')))
                xit_lvalue -= xit_ivcmp;

            if (((xit_rvalue = (*(xszt_rcmp++))) >= xstrios::widen('A')) &&
                 (xit_rvalue <= xstrios::widen('Z')))
                xit_rvalue -= xit_ivcmp;
        } while (xit_lvalue && (xit_lvalue == xit_rvalue));

        return (xit_lvalue - xit_rvalue);
    }

    /**
     * @struct xstr_icmp_t
     * @brief  as functor.
     */
    struct xstr_icmp_t
    {
        typedef xstring first_argument_type;
        typedef xstring second_argument_type;
        typedef bool    result_type;

        bool operator () (const xstring & xstr_left, const xstring & xstr_right) const
        {
            return (icmp(xstr_left.c_str(), xstr_right.c_str()) < 0);
        }
    };
};

////////////////////////////////////////////////////////////////////////////////

#endif // __XSTR_TRAITS_H__
