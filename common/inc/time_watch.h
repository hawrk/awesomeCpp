/*
 * time_watch.h
 *
 *  Created on: 2016��4��27��
 *      Author: Hawrk
 *        Desc: ͳ�Ƴ������е�ʱ�䣬��msΪ��λ
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
