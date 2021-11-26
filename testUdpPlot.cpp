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
int main(int argc, char ** argv)
{
    int port=43210;
    char * ip="127.0.0.1";
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
    int64_t i=0; double vals[4];
    while(1)
    {
        double theta=fmod(2*M_PI*i/50,2*M_PI);
        usleep(208);
        //vals[0]=i;
        vals[0]=sin(theta);
        vals[1]=cos(theta);
        vals[2]=theta;
        sendto(sockfd, (const char *)vals, sizeof(double)*3,
        /*MSG_CONFIRM*/ MSG_DONTWAIT, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
        i++;
        //if(i==50) i=0;
    }
}
