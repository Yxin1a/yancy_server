//  删除默认拷贝构造函数，即不能进行默认拷贝
#ifndef __YANCY_NONCOPYABLE_H__
#define __YANCY_NONCOPYABLE_H__

namespace yancy
{

    class Noncopyable
    {
    public:
        Noncopyable()=default;
        ~Noncopyable()=default;
        Noncopyable(const Noncopyable&)=delete;
        Noncopyable& operator=(const Noncopyable&)=delete;
    };

}
#endif