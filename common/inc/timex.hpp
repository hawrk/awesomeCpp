//
// Created by hawrk on 2022/3/1.
// desc : 时间的一些处理函数

#ifndef TIMEX_HPP
#define TIMEX_HPP

// 1 时间的休眠
#include <unistd.h>
#include <chrono>
void timex() {
    sleep(10)   // 休眠 10 秒， sleep 函数后面以秒为单位 second
    usleep(100)  // 休眠 100 微秒 usleep 函数后面以微少为单位 microsecond

}
// 如果要实现 毫秒， c99 下面实现有点麻烦， 可以用 c++ 11 标准的chrono
void msleepx(unsigned long duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));   // 休眠100 毫秒
}
// 也可以实现微秒
void usleepx(unsigned long duration) {
    std::this_thread::sleep_for(std::chrono::microseconds(duration));   // 休眠 100 微秒
}
// 当然也可以实现秒
void sleepx(unsigned long duration) {
    std::this_thread::sleep_for(std::chrono::seconds(duration));    // 休眠 100 秒
}

#endif //TIMEX_HPP
