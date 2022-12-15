#include "serv_cli_socket.h"
#include<string.h>

int main()
{
    struct sockaddr_in newAddr;
	socklen_t addr_size;
    struct question question ;
    struct reponse reponse ;


    //Créer la socket du serveur "socketServeur"
    //AF_INET est une famille d'adresses qui est utilisée pour désigner le type d'adresses avec lesquelles notre socket peut communiquer.
    //Type de socket fonctionne comme un tube (pipe). Dans le domaine de l'Internet, le type de socket SOCK_STREAM est mis en œuvre sur le protocole TCP/IP.
    //Le protocole par défaut 0
    int  socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServeur < 0 ){
		perror("[SERVEUR] Erreur lors de ouverture de la socket !");
		exit(1);
	}
    printf("[SERVEUR] Le socket de serveur est créé.\n");

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
		perror("[SERVEUR] Erreur de la liaison (binding) !");
		exit(1);
	}
    printf("[SERVEUR] Le Serveur est lié au port %d\n", PORT);

    //Écouter les connexions avec l'appel système listen().
    int listenStatus =listen(socketServeur, BACKLOG);
    if (listenStatus <0){
		perror("[SERVEUR] Erreur lors de démarrage de l'écoute du socket !");
		exit(1);
	}
    printf("[SERVEUR] Le serveur est a l'écoute...\n");

    while (1)
    {
        //Début de l'acceptation.
        int socketServiceClient = accept(socketServeur, (struct sockaddr*)&newAddr, &addr_size);
        if (socketServiceClient < 0) {
            perror("[SERVEUR] Erreur lors de l'établissement des connections !");
            exit(1);
        }
        printf("Connexion acceptée de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        //Créer un processus enfant pour traiter la communication avec un seul client.
        int pid = fork();
        if (pid < 0) {
            perror("[SERVEUR] Erreur lors de fork");
            exit(1);
        }
        
        if (pid == 0) {
            // Processus du client
            close(socketServeur);
            //recieve the data from the server
            int recvStatus= recv(socketServiceClient, &question, sizeof(struct question), 0) ;
            if (recvStatus <0 ){
                perror("[SERVEUR] Erreur lors de la reception des donnée !");
                exit(1);
            }	

            //Affichage
            printf("¤¤¤¤¤¤¤¤¤¤¤¤  Client-Serveur  ¤¤¤¤¤¤¤¤¤¤¤¤\n");
            printf("\n");
            printf("¤ Coté Serveur (pid= %d) \n",getpid());
            printf("¤¤¤¤¤¤¤¤¤ Message Recue ¤¤¤¤¤¤¤¤¤\n");
            printf("         PID= %d \n",question.pid_client );
            printf("         Nombre= %d \n",question.question);
            printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");

           

            // Ouvrir le fichier "result"
            char pid_client_str[10];
            sprintf(pid_client_str, "%d", question.pid_client);
            char resultPath[100]="";
            strcat(resultPath,"results/");
            strcat(resultPath,pid_client_str);
            strcat(resultPath,".txt");

            //Pointeur de fichier pour contenir la référence à notre fichier
            FILE * fPtr;
            //Supprimer le fichier si deja existe
            remove(resultPath);
            //Creer et ouvrir le fichier
            fPtr = fopen(resultPath, "w");
             
            
            // fopen() retourne NULL si la dernière opération a échoué.
            if(fPtr == NULL)
            {
                perror("[SERVEUR] Erreur lors de création du fichier 'result' !");
                exit(1);
            }
            //Sauvegarder les données dans le fichier
            fprintf(fPtr, "%d", question.pid_client);
            fprintf(fPtr,"\n");
            fprintf(fPtr, "%d", question.question);
            fprintf(fPtr,"\n");

            // Construction de la réponse
            reponse.pid_server=getpid();
            fprintf(fPtr, "%d", reponse.pid_server);
            fprintf(fPtr,"\n");
            for (int i=0;i<question.question;i++){
                reponse.reponse[i]= rand()%100;

                //Sauvegarder les données dans le fichier
                fprintf(fPtr, "%d", reponse.reponse[i]);
                fprintf(fPtr,"\n");
            }
            

            // Envoi de la réponse 
            int sendStatus = send(socketServiceClient, (const void *)&reponse, sizeof(struct reponse), 0);
            if (sendStatus< 0 ){
                perror("[SERVEUR] Erreur lors de l'envoi du réponse !");
                exit(1);
            }
            printf("[SERVEUR] Reponse envoyé.\n");
            printf("Déconnecté de %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
            printf("\n");

            //Fermer le fichier pour sauvegarder les données du fichier
            fclose(fPtr);

            exit(0);
        } else {
            // processus pére
            close(socketServiceClient);
        }
       
    }
    return 0;
}