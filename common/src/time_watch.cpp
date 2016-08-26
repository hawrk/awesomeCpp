/*
 * time_watch.cpp
 *
 *  Created on: 2016Äê4ÔÂ27ÈÕ
 *      Author: Hawrk
 *        Desc:
 */

#include "time_watch.h"


TimeWatch::TimeWatch()
{
	gettimeofday(&start_time, NULL);
}

TimeWatch::~TimeWatch()
{
	gettimeofday(&end_time,NULL);
	double timeused = 1000000*(end_time.tv_sec - start_time.tv_sec) + end_time.tv_usec - start_time.tv_usec;
	timeused /=1000;
	printf("time spend:[%lf] ms",timeused);
}
