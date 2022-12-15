
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<signal.h>
#include<sys/stat.h>
#include<string.h>
int main(){
    int pid=fork();
    if (pid==0){
        int isRunning = Process.GetProcessesByName("Serveur")
                .FirstOrDefault(p => p.MainModule.FileName.StartsWith(@"Partie2/obj")) != default(Process);
        execlp("./Partie2/obj/Serveur","./obj/Serveur",NULL);
    }else{
        execlp("./Partie2/obj/Client","./obj/Client",NULL);
    }
}