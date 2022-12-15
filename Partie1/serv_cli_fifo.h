#ifndef SERV_CLI
#define SERV_CLI

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<signal.h>
#include<sys/stat.h>

#define NMAX 20
#define QuestionTube "fifo11"
#define ResponseTube "fifo21"

struct question {
    int pid_client ;
    int question ;
};

struct response {
    int pid_server;
    int response[NMAX];
};

#endif