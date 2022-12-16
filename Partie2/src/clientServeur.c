
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<signal.h>
#include<sys/stat.h>
#include<string.h>

   
int main(){
    // FILE *fp;
    // int count = 0;  // Line counter (result)
    // char filename[]="runingProcess.txt";
    // char c;  // To store a character read from file
    
    
    int pid=fork();
    if (pid==0){
    //    int pid1=fork();
    //     if (pid1==0){
    //         serverRunning();
    //     }else{
    //         sleep(3);
    //    printf("aaaa");
    //     // Open the file
    //     fp = fopen(filename, "r");
    
    //     // Check if file exists
    //     if (fp == NULL)
    //     {
    //         printf("Could not open file %s", filename);
    //         return 0;
    //     }
    //     for (c = getc(fp); c != EOF; c = getc(fp))
    //     if (c == '\n') // Increment count if this character is newline
    //         count = count + 1;
 
    //     // Close the file
    //     fclose(fp);
    //     fp =fopen(filename, "w");
    //     if(count < 2){
    //         printf("bbbbbbb");
            execlp("./Partie2/obj/Serveur","./Partie2/obj/Serveur",NULL);
            
       // }
        //  }
    }else{
        sleep(5000);
        execlp("./Partie2/obj/Client","./Partie2/obj/Client",NULL);
    }
}