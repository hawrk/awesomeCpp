/*
 * time_spend.cpp
 *
 *  Created on: 2016年4月27日
 *      Author: Hawrk
 *        Desc:统计程序运行时间，以ms 为单位 (没有设计成类是考虑类构造和析构也需要时间，直接嵌入代码就行了）
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
    struct timeval start,end;
    gettimeofday(&start,NULL);

	for(int i = 0;i<100000;i++)
	{
		int sum = 0;
		sum += i;
	}
    sleep(1);
    gettimeofday(&end,NULL);
    double timeused = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    timeused /=1000; //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
    printf("timeused :%lf ms\n",timeused);
    return 0;
}





