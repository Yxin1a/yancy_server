#include "yancy_server/uri.h"
#include <iostream>

int main(int argc, char** argv)
{
    //yancy::Uri::ptr uri = yancy::Uri::Create("http://www.yancy.top/test/uri?id=100&name=yancy#frg");
    //yancy::Uri::ptr uri = yancy::Uri::Create("http://admin@www.yancy.top/test/中文/uri?id=100&name=yancy&vv=中文#frg中文");
    //yancy::Uri::ptr uri = yancy::Uri::Create("http://admin@www.yancy.top");
    yancy::Uri::ptr uri = yancy::Uri::Create("http://www.yancy.top/test/uri");
    std::cout << uri->toString() << std::endl;
    auto addr = uri->createAddress();   //根据uri类，获取Address
    std::cout << *addr << std::endl;
    return 0;
}
