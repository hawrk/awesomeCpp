/*
 * time_watch.h
 *
 *  Created on: 2016年4月27日
 *      Author: Hawrk
 *        Desc: 统计程序运行的时间，以ms为单位
 */

#ifndef TIME_WATCH_H_
#define TIME_WATCH_H_

#include <sys/time.h>

class TimeWatch
{
private:
	timeval start_time;
	timeval end_time;

public:
	TimeWatch();
	~TimeWatch();

};


#endif /* TIME_WATCH_H_ */
