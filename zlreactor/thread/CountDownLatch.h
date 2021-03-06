// ***********************************************************************
// Filename         : CountDownLatch.h
// Author           : LIZHENG
// Created          : 2014-06-08
// Description      : 同步辅助类，在完成一组正在其他线程中执行的操作之前，它允许一个或多个线程一直等待
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_COUNTDOWNLATCH_H
#define ZL_COUNTDOWNLATCH_H
#include "zlreactor/base/NonCopy.h"
#include "zlreactor/thread/Mutex.h"
#include "zlreactor/thread/Condition.h"
NAMESPACE_ZL_THREAD_START

class CountDownLatch : zl::NonCopy
{
public:
    explicit CountDownLatch(int count)
        : count_(count)
        , mutex_()
        , condition_(mutex_)
    {
    }

    void wait()
    {
        LockGuard<Mutex> lock(mutex_);
        while(count_ > 0)
        {
            condition_.wait();
        }
    }

    void countDown()
    {
        LockGuard<Mutex> lock(mutex_);
        --count_;
        if(count_ == 0)
        {
            condition_.notify_all();
        }
    }

    int getCount() const
    {
        LockGuard<Mutex> lock(mutex_);
        return count_;
    }

private:
    int              count_;
    mutable Mutex    mutex_;
    Condition        condition_;
};

NAMESPACE_ZL_THREAD_END

#endif /* ZL_BLOCKINGQUEUE_H */
