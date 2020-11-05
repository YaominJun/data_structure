//
// Created by luyao on 2020/11/3.
//

#ifndef CPP_APPEND_CLASS_H
#define CPP_APPEND_CLASS_H

template <typename T>
struct Increase{
public:
    virtual void operator()(T &t){t++;}
};

#endif //CPP_APPEND_CLASS_H
