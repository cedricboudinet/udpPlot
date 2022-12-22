#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<iostream>
#include <string.h>
#include<math.h>
#include <thread>
int running = 0;
void cliLoop(double & amplitude)
{
	while(running)
	{
		char chr = getchar();
		if(chr=='q')
			running=false;
		else if(chr=='t')
		{
			amplitude = 2;
			usleep(50000);
			amplitude = 1;
		}
		//std::cout<<"'"<<chr<<"'"<<std::endl;
	}
}

int main(int argc, char ** argv)
{
    int port=43210;
    char  ip[]="127.0.0.1";
    if(argc>1)
        port=atoi(argv[1]);
    if(argc>2)
        strcpy(ip,argv[2]);
    std::cout<<"Sending to "<<ip<<":"<<port<<std::endl;
    struct sockaddr_in     servaddr;
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr =inet_addr(ip);
	running = 1;
	int nbCurvesAdd = 10;
    int64_t i=0; double vals[3+nbCurvesAdd];
	double amplitude=1.0;
	std::thread thrd(cliLoop, std::ref(amplitude));
    while(running == 1)
    {
        double theta=fmod(2*M_PI*i/50,2*M_PI);
        usleep(100);
        //vals[0]=i;
        vals[0]=amplitude*sin(theta);
        vals[1]=amplitude*cos(theta);
        vals[2]=theta;
	for(int i=0;i<nbCurvesAdd;i++)
		vals[3+i]=sin(theta+i*M_PI*2/nbCurvesAdd);
        sendto(sockfd, (const char *)vals, sizeof(double)*(3+nbCurvesAdd),
        /*MSG_CONFIRM*/ MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        i++;
        //if(i==50) i=0;
    }
}
