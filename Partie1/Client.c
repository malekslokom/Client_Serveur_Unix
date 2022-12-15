#include "serv_cli_fifo.h" 
#include "Handlers_Cli.h" 

void hand_reveil (int sig ){
    printf("[CLIENT] Réveiller le Client (par le signal %d)\n",sig);
}

int main()
{ 
    /* Déclarations */ 
    int  questionT;
    int responseT;
    struct question question ;
    struct reponse reponse ;
    /* Ouverture des tubes nommés */
    questionT=open(QuestionTube,O_WRONLY);
    responseT=open(ResponseTube,O_RDONLY);
    /* Installation des Handlers */ 
    signal(SIGUSR1,hand_reveil);

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
    if(write(questionT,&question,sizeof(struct question))<0){
        perror("[CLIENT] Probléme d'écriture \n");
        exit(1);
    }

    printf("[CLIENT] Message envoyée => Client en attente \n");

    /* Attente de la réponse */ 
    pause(); 

    /* Lecture de la réponse */ 
    if (read(responseT,&reponse,sizeof(struct reponse))<0){
        perror("[CLIENT] Probléme de lecture \n");
        exit(2);
    }
    /* Envoi du signal SIGUSR1 au serveur */ 
    kill (reponse.pid_server,SIGUSR1);

    /* Traitement local de la réponse */ 
    printf("\n");
    printf("¤¤¤¤¤¤¤¤¤ Response ¤¤¤¤¤¤¤¤¤\n");
    printf("  PID= %d\n",reponse.pid_server);
    printf("  Tableau de %d entiers :\n",question.question);
    printf("  ");
    for (int i=0;i<question.question;i++)
        printf ("|%d ",reponse.reponse[i]);
    printf("|\n ");
    printf("¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
   return 0;
} 