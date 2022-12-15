
#include "serv_cli_socket.h"

int main(){
    // Déclaration des structures
    struct question question ;
    struct reponse reponse ;

    //Créer la socket du client "clientSocket"
    //AF_INET est une famille d'adresses qui est utilisée pour désigner le type d'adresses avec lesquelles notre socket peut communiquer.
    //Type de socket fonctionne comme un tube (pipe). Dans le domaine de l'Internet, le type de socket SOCK_STREAM est mis en œuvre sur le protocole TCP/IP.
    //Le protocole par défaut 0
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
		perror("[CLIENT] Erreur lors de ouverture de la socket !\n");
		exit(1);
	}
    printf("[CLIENT] Le socket de client est créé.\n");

    //Définir l'adresse du serveur
    //La fonction htons convertit un u_short de l'hôte à l'ordre des octets du réseau TCP/IP (qui est big-endian).
    //INADDR_ANY pour se lier à toutes les interfaces - pas seulement à "localhost".
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY; 

    //Connecter le client avec le serveur
    int connectStatus=connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectStatus<0){
		perror("[CLIENT] Erreur lors de la connexion au socket !\n");
		exit(1);
	}
    printf("[CLIENT] Client connecté au serveur.\n");

    /* Construction et envoi d'une question */ 
    //Initialisation
    srand ( getpid ());
 
    question.pid_client = getpid();
    question.question = 1+rand()% NMAX;

    // Affichage
    printf("¤¤¤¤¤¤¤¤¤¤¤¤  Client-Serveur  ¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf("\n");
    printf("¤ Coté Client (pid= %d) \n",getpid());
    printf("¤¤¤¤¤¤¤¤¤ Message ¤¤¤¤¤¤¤¤¤\n");
    printf("         PID= %d         \n",question.pid_client );
    printf("         Nombre= %d        \n",question.question);
    printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf("\n");

    //Envoi du question
    int sendStatus = send(clientSocket, (const void *)&question, sizeof(struct question), 0);
	if (sendStatus <0 ){
		perror("[CLIENT] Erreur lors de l'envoi du question !");
		exit(1);
	}
    printf("[CLIENT] Question envoyé.\n");

    //recieve the data from the server
	int recvStatus = recv(clientSocket, &reponse, sizeof(struct reponse), 0);
	if (recvStatus < 0 ){
		perror("[CLIENT] Erreur lors de reception du reponse !");
		exit(1);
	}
    printf("[CLIENT] Reponse recu.\n");
    printf("\n");

    // Affichage
    printf("¤¤¤¤¤¤¤¤¤ Response ¤¤¤¤¤¤¤¤¤\n");
    printf("  PID= %d\n",reponse.pid_server);
    printf("  Tableau de %d entiers :\n",question.question);
    printf("  ");
    for (int i=0;i<question.question;i++)
        printf ("|%d ",reponse.reponse[i]);
    printf("|\n");
    printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");

    //Fermer socket
    close(clientSocket);
    return 0;
}

