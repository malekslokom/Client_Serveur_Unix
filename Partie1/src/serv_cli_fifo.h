#ifndef SERV_CLI
#define SERV_CLI

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<signal.h>
#include<sys/stat.h>
#include<string.h>

#define NMAX 10
#define QuestionTube "fifo12"
#define ResponseTube "fifo22"

struct question {
    int pid_client ;
    int question ;
};

struct reponse {
    int pid_server;
    int reponse[NMAX];
};

#endif