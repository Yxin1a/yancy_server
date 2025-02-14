//写入数据到bytearray中
//设置操作位置，用来读取
//读取数据
#include"../yancy_server/bytearray.h"
#include"../yancy_server/yancy_server.h"

static yancy::Logger::ptr g_logger = YANCY_LOG_ROOT();

void test()
{
    //基础类型
#define XX(type,len,write_fun,read_fun,base_len) \
{ \
    std::vector<type> vec; \
    for(int i=0;i<len;++i) \
    { \
        vec.push_back(rand()); \
    } \
    yancy::ByteArray::ptr ba(new yancy::ByteArray(base_len)); \
    for(auto& i : vec) \
    { \
        ba->write_fun(i); \
    } \
    ba->setPosition(0); \
    for(size_t i=0;i<vec.size();++i) \
    { \
        type v=ba->read_fun(); \
        YANCY_ASSERT(v==vec[i]); \
    } \
    YANCY_ASSERT(ba->getReadSize()==0); \
    YANCY_LOG_INFO(g_logger) << #write_fun "/" #read_fun \
                    " (" #type " ) len=" << len \
                    << " base_len=" << base_len \
                    << " size=" << ba->getSize(); \
}

    XX(int8_t,100,writeFint8,readFint8,1);
    XX(uint8_t, 100, writeFuint8, readFuint8, 1);
    XX(int16_t,  100, writeFint16,  readFint16, 1);
    XX(uint16_t, 100, writeFuint16, readFuint16, 1);
    XX(int32_t,  100, writeFint32,  readFint32, 1);
    XX(uint32_t, 100, writeFuint32, readFuint32, 1);
    XX(int64_t,  100, writeFint64,  readFint64, 1);
    XX(uint64_t, 100, writeFuint64, readFuint64, 1);

    XX(int32_t,  100, writeInt32,  readInt32, 1);
    XX(uint32_t, 100, writeUint32, readUint32, 1);
    XX(int64_t,  100, writeInt64,  readInt64, 1);
    XX(uint64_t, 100, writeUint64, readUint64, 1);
#undef XX

//写入数据到bytearray中
//设置操作位置，用来读取
//读取数据
//设置操作位置，用来写入到文件中
//用新的对象从文件中读取
#define XX(type,len,write_fun,read_fun,base_len) \
{ \
    std::vector<type> vec; \
    for(int i=0;i<len;++i) \
    { \
        vec.push_back(rand()); \
    } \
    yancy::ByteArray::ptr ba(new yancy::ByteArray(base_len)); \
    for(auto& i : vec) \
    { \
        ba->write_fun(i); \
    } \
    ba->setPosition(0); \
    for(size_t i=0;i<vec.size();++i) \
    { \
        type v=ba->read_fun(); \
        YANCY_ASSERT(v==vec[i]); \
    } \
    YANCY_ASSERT(ba->getReadSize()==0); \
    YANCY_LOG_INFO(g_logger) << #write_fun "/" #read_fun \
                    " (" #type " ) len=" << len \
                    << " base_len=" << base_len \
                    << " size=" << ba->getSize(); \
    ba->setPosition(0); \
    YANCY_ASSERT(ba->writeToFile("/tmp/" #type "_" #len "-" #read_fun ".dat")); \
    yancy::ByteArray::ptr ba2(new yancy::ByteArray(base_len * 2)); \
    YANCY_ASSERT(ba2->readFromFile("/tmp/" #type "_" #len "-" #read_fun ".dat")); \
    ba2->setPosition(0); \
    YANCY_ASSERT(ba->toString() == ba2->toString()); \
    YANCY_ASSERT(ba->getPosition() == 0); \
    YANCY_ASSERT(ba2->getPosition() == 0); \
}
    XX(int8_t,  100, writeFint8, readFint8, 1);
    XX(uint8_t, 100, writeFuint8, readFuint8, 1);
    XX(int16_t,  100, writeFint16,  readFint16, 1);
    XX(uint16_t, 100, writeFuint16, readFuint16, 1);
    XX(int32_t,  100, writeFint32,  readFint32, 1);
    XX(uint32_t, 100, writeFuint32, readFuint32, 1);
    XX(int64_t,  100, writeFint64,  readFint64, 1);
    XX(uint64_t, 100, writeFuint64, readFuint64, 1);

    XX(int32_t,  100, writeInt32,  readInt32, 1);
    XX(uint32_t, 100, writeUint32, readUint32, 1);
    XX(int64_t,  100, writeInt64,  readInt64, 1);
    XX(uint64_t, 100, writeUint64, readUint64, 1);
#undef XX

}
int main(int agrc,char** agrv)
{
    test();
    return 0;
}