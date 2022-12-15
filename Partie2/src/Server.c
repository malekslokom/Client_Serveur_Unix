#include "serv_cli_socket.h"

int main()
{
    struct sockaddr_in newAddr;
	socklen_t addr_size;
    struct question question ;
    struct response response ;

    //Créer la socket du serveur "socketServeur"
    //AF_INET est une famille d'adresses qui est utilisée pour désigner le type d'adresses avec lesquelles notre socket peut communiquer.
    //Type de socket fonctionne comme un tube (pipe). Dans le domaine de l'Internet, le type de socket SOCK_STREAM est mis en œuvre sur le protocole TCP/IP.
    //Le protocole par défaut 0
    int  socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServeur < 0 ){
		perror("[SERVER] Erreur lors de ouverture de la socket !");
		exit(1);
	}
    printf("[SERVER] Le socket de serveur est créé.\n");

    //Définir l'adresse du serveur
    //La fonction htons convertit un u_short de l'hôte à l'ordre des octets du réseau TCP/IP (qui est big-endian).
    //INADDR_ANY pour se lier à toutes les interfaces - pas seulement à "localhost".
    struct sockaddr_in serveurAdresse;
    serveurAdresse.sin_family = AF_INET;
    serveurAdresse.sin_port = htons(PORT);
    serveurAdresse.sin_addr.s_addr = INADDR_ANY;

    //Appel de la fonction bind à l'IP et au port spécifiés.
    int bindStatus = bind(socketServeur, (struct sockaddr*)&serveurAdresse, sizeof(serveurAdresse));    
    if (bindStatus <0){
		perror("[SERVER] Erreur de la liaison (binding) !");
		exit(1);
	}
    printf("[SERVER] Le Serveur est lié au port %d\n", PORT);

    //Écouter les connexions avec l'appel système listen().
    int listenStatus =listen(socketServeur, BACKLOG);
    if (listenStatus <0){
		perror("[SERVER] Erreur lors de démarrage de l'écoute du socket !");
		exit(1);
	}
    printf("[SERVER] Le serveur est a l'écoute...\n");

    while (1)
    {
        //Début de l'acceptation.
        int socketServiceClient = accept(socketServeur, (struct sockaddr*)&newAddr, &addr_size);
        if (socketServiceClient < 0) {
            perror("[SERVER] Erreur lors de l'établissement des connections !");
            exit(1);
        }
        printf("Connexion acceptée de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        //Créer un processus enfant pour traiter la communication avec un seul client.
        int pid = fork();
        if (pid < 0) {
            perror("[SERVER] Erreur lors de fork");
            exit(1);
        }
        
        if (pid == 0) {
            // Processus du client
            close(socketServeur);
            //recieve the data from the server
            int recvStatus= recv(socketServiceClient, &question, sizeof(struct question), 0) ;
            if (recvStatus <0 ){
                perror("[SERVER] Erreur lors de la reception des donnée !");
                exit(1);
            }	
            //Affichage
            printf("¤¤¤¤¤¤¤¤¤ Message Recue ¤¤¤¤¤¤¤¤¤\n");
            printf("         PID= %d \n",question.pid_client );
            printf("         Nombre= %d \n",question.question);
            printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");

            // Construction de la réponse
            for (int i=0;i<question.question;i++){
                response.response[i]= rand()%100;
            }
            response.pid_server=getpid();

            // Envoi de la réponse 
            int sendStatus = send(socketServiceClient, (const void *)&response, sizeof(struct response), 0);
            if (sendStatus< 0 ){
                perror("[SERVER] Erreur lors de l'envoi du réponse !");
                exit(1);
            }
            printf("[SERVER] Reponse envoyé.\n");
            printf("Déconnecté de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            printf("\n");
            exit(0);
        } else {
            // processus pére
            close(socketServiceClient);
        }
       
    }
    return 0;
}