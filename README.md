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

另外，所实现的 INI 相关类，都支持 C++ IO 流的操作方式。详细的使用方式，参考如下测试代码(**ini_test.cpp**)：
```
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

```

## 获取源码(xini_file.h)
可以到我的 GitHub 上直接获取源码：[https://gitee.com/Gaaagaa/inifile](https://gitee.com/Gaaagaa/inifile) 。
