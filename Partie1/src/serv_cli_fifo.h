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
#define QuestionTube "fifo1"
#define ResponseTube "fifo2"

struct question {
    int pid_client ;
    int question ;
};

struct reponse {
    int pid_server;
    int reponse[NMAX];
};

#endif