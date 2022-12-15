#ifndef HANDLER_SERV
#define HANDLER_SERV
/* Réveiler le serveur suite à la réception du signal SIGUSR1 */
void hand_reveil ( int sig );

/* Fin du serveur suite à la réception d'un signal quelconque */
void fin_serveur ( int sig );

#endif