#include "serv_cli_fifo.h" 
#include "Handlers_Serv.h" 

void hand_reveil(int sig){
    printf("-- La réponse est bien recu au client\n");
}

void fin_serveur(int sig){
    printf("%d",sig);
    printf("-- Fin serveur ( par le signal %d)\n",sig);
    unlink (QuestionTube);
    unlink (ResponseTube);
    exit(0);
}

int main(){ 
    /*Déclarations */ 
    int questionT;
    int responseT;
    struct question question ;
    struct response response ;
    mode_t mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
    /* Création des tubes nommés */
    if ( mkfifo (QuestionTube,mode) == -1)
    {
        perror (" La Création du tube 1 est impossible \n");
        exit (1);
    };
    if ( mkfifo (ResponseTube,mode)== -1)
    {
        perror (" La Création du tube 2 est impossible \n");
        exit (2);
    };
    /*initialisation du générateur de nombres aléatoires*/ 
    srand(getpid());

    /* Ouverture des tubes nommés */ 
    questionT = open (QuestionTube,O_RDONLY );
    responseT = open (ResponseTube,O_WRONLY );

    /* Installation des Handlers */ 

    //Tous les signaux mettront fin au serveur
    for(int sig=1;sig<NSIG;sig++){
        signal(sig,fin_serveur);
    }
    // Sauf, SIGUSR1 qui réveil le serveur 
    signal(SIGUSR1,hand_reveil);
   
    // Affichage
    printf("¤¤¤¤¤¤¤¤¤¤¤¤  Client-Serveur  ¤¤¤¤¤¤¤¤¤¤¤¤\n");
    printf("\n");
    printf("¤ Coté Serveur (pid= %d) \n",getpid());
    while(1){
        printf("-- Serveur en attente \n");
        /* lecture d'une question */ 
        if(read(questionT,&question,sizeof(struct question))<=0){
            close ( questionT );
            questionT = open ( QuestionTube , O_RDONLY );
            continue ;
        }
        //Affichage
        printf("¤¤¤¤¤¤¤¤¤ Message Recue ¤¤¤¤¤¤¤¤¤\n");
        printf("         PID= %d \n",question.pid_client );
        printf("         Nombre= %d \n",question.question);
        printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
        printf("\n");

        /* construction de la réponse */ 
        for (int i=0;i<question.question;i++){
            response.response[i]= rand()%100;
        }
        response.pid_server=getpid();

        /* envoi de la réponse */ 
        if(write(responseT,&response,sizeof(struct response ))<0){
            perror("-- Probléme d'écriture \n");
            exit(4);
        }
        /* envoi du signal SIGUSR1 au client conceré */ 
        kill(question.pid_client,SIGUSR1);
        
    }

return 0;
}