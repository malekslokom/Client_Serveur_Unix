#ifndef SERV_CLI_SOCKET
#define SERV_CLI_SOCKET
#include<string.h>

//ajout des headers 
#include <stdlib.h>
#include <stdio.h>

//Pour le socket
#include <sys/socket.h>
#include <sys/types.h>

//Pour obtenir le nom de l'hôte
#include "netdb.h"
#include "arpa/inet.h"

//Pour inclure les structures qui stockeront les informations nécessaires
#include <netinet/in.h>
#include <unistd.h>

//Nombre max peut étre tiré au hasard par le client
#define NMAX 20

//Numéro de PORT qui sera utilisé pour nommer la prise
#define PORT 9000

//Nombre max de connexions en attente dans la file d'attente
//Sous Lunix le nombre max est égale à 128 (SOMAXCONN)
//Sous d'autre systèmes, elle est limitée à 5 
#define BACKLOG 5

//Déclaration des structures
struct question {
    int pid_client ;
    int question ;
};

struct reponse {
    int pid_server;
    int reponse[NMAX];
};


#endif
