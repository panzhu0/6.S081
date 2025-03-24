#include "kernel/types.h"
#include "user/user.h"

int
main(int argc,char* argv){
	// 创建一个长度为2的数组
	int p[2];

	// 创建管道，返回读写FID 到 数组p[2]
	pipe(p);

	// 创建一个缓冲数组,从管道中读取数据
	char charArray[4];

	// fork 
	int pid = fork();
	if(pid==0){	// 子进程
		read(p[0],charArray,4); // 从管道中读取4B数据 【管道没有数据，则会阻塞,等待父进程推送数据】
		pid = getpid(); // 获取当前线程的PID
		printf("%d: received %s\n",pid,charArray);  //输出收到的信息
		write(p[1],"pong",4); //响应数据[aka pong]回给父进程
		
	}else{		// 父进程
		write(p[1],"ping",4);
		pid = getpid();
		// wait(0); //等待子进程的响应,这里由于有pipe限制，不用wait也行
		read(p[0],charArray,4);
		printf("%d: received %s\n",pid,charArray);  //输出收到的信息
	}
	exit(0);
}
