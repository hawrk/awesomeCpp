/*
 * time_spend.cpp
 *
 *  Created on: 2016��4��27��
 *      Author: Hawrk
 *        Desc:ͳ�Ƴ�������ʱ�䣬��ms Ϊ��λ (û����Ƴ����ǿ����๹�������Ҳ��Ҫʱ�䣬ֱ��Ƕ���������ˣ�
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
    timeused /=1000; //����1000����к����ʱ���������1000000������뼶���ʱ���������1�����΢����ʱ
    printf("timeused :%lf ms\n",timeused);
    return 0;
}





