#ifndef TEST__
#define TEST__

#include <iostream>
#include "core/logger.h"
#include "core/event.hpp"

using namespace std;

class Test
{
public:
    static void pointer()
    {
        string value = "abc";
        int MAX = 3;
        int var[MAX] = {10, 100, 200};

        //将value的内存地址赋给指针p1
        string *p1 = &value;
        //将指针p1赋给指针p2
        string *p2 = p1;
        //将指针p2的内存地址赋给指针p3
        string **p3 = &p2;

        Logger::info("-------------------NULL 指针--------------------");
        string *p_null = NULL;
        Logger::log("Null 指针 *p_null 的值是:%p", p_null);

        Logger::info("-----------------指针的算术运算(递增)------------------");
        int *array_p;
        array_p = var; // 指针中的数组地址
        for (int i = 0; i < MAX; i++)
        {
            Logger::log("var[%d]的地址是:%x,值是:%d", i, array_p, *array_p);
            // 移动到下一个位置
            array_p++;
        }
        Logger::info("-----------------指针的算术运算(比较)------------------");
        array_p = var; // 指针中第一个元素的地址
        int i = 0;
        while (array_p <= &var[MAX - 1])
        {
            Logger::log("var[%d]的地址是:%x,值是:%d", i, array_p, *array_p);
            // 指向上一个位置
            array_p++;
            i++;
        }

        Logger::info("-------------------指针&数组--------------------");
        *(var + 2) = 500; //把 var[2] 赋值为 500：
        for (int i = 0; i < MAX; i++)
        {
            Logger::log("赋值前,i:%d,var值是:%x,%d,%d", i, var, *var, var[i]);
            *var = i; // 这是正确的语法
            Logger::log("赋值后,i:%d,var值是:%x,%d,%d", i, var, *var, var[i]);
            //var++;    // 这是不正确的
        }
        //把指针运算符 * 应用到 var 上是完全可以的，但修改 var 的值是非法的。这是因为 var 是一个指向数组开头的常量，不能作为左值。
        //由于一个数组名对应一个指针常量，只要不改变数组的值，仍然可以用指针形式的表达式。

        ///////////////////////////////////////////////////////////////////
        vitamin::EventEmitter event;

        event.on("hi", []() {
                 std::cout << "Hello World!" << std::endl;
             })
            .emit("hi");

        event.on("twice", []() {
                 std::cout << "Hello World!1" << std::endl;
             })
            .on("twice", []() {
                std::cout << "Hello World!2" << std::endl;
            })
            .emit("twice");

        event.on("hello", [](int nb) {
                 std::cout << "Hello " << nb << "!" << std::endl;
             })
            .emit("hello", 42);

        vitamin::EventEmitter event2 = event;

        event2.emit("hello", 24); /*.On("ref", [](ium::EventEmitter &e) { e.Emit("hello"); })
            .Emit("ref", event2)*/
    }
};

#endif