#ifndef __TOPSON_SINGLETON_H__
#define __TOPSON_SINGLETON_H__

namespace topson {

template<typename T, typename X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        static T v;
        return &v;
    }
};

template<typename T, typename X = void, int N = 0>
class SingletonPtr {
public:
    static std::shared_ptr<T> GetInstance() {
        std::shared_ptr<T>  v(new T);
        return v;
    }
};

}

#endif
