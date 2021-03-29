
#include "csapp.h"

#define MAX_NAME_LEN 256

void echo(int connfd);


// Note that this code only works with IPv4 addresses
//(IPv6 is not supported)


int main(int argc, char **argv)
{
        pid_t pid;
        int listenfd, connfd, port;
        int nbProc;
        socklen_t clientlen;
        struct sockaddr_in clientaddr;
        char client_ip_string[INET_ADDRSTRLEN];
        char client_hostname[MAX_NAME_LEN];
        int nbClientClose=0;

        if (argc != 2) {
                fprintf(stderr, "usage: %s <nbProc>\n", argv[0]);
                exit(0);
        }
        port = 2121;
        nbProc=atoi(argv[1]);

        clientlen = (socklen_t)sizeof(clientaddr);

        listenfd = Open_listenfd(port);
        if(nbProc>1) {
                for(int i=1; i<nbProc/(nbProc-1); i++) {
                        pid=Fork();
                        if(pid==-1) {
                                printf("ERREUR CREE PID\n");
                        }else if(pid==0) {
                                break;
                        }
                }
        }else{
                pid=Fork();
                if(pid==-1) {
                        printf("ERREUR CREE PID\n");
                }

        }

        if(pid==0) {
                while (1) {
                        while((connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen))<0);

                        // determine the name of the client
                        Getnameinfo((SA *) &clientaddr, clientlen,  client_hostname, MAX_NAME_LEN, 0, 0, 0);

                        // determine the textual representation of the client's IP address
                        Inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip_string,INET_ADDRSTRLEN);

                        printf("server connected to %s (%s)\n", client_hostname,client_ip_string);

                        echo(connfd);

                        Close(connfd);

                        nbClientClose++;
                        printf("Il y a %d Clients closed \n",nbClientClose );

                        if(nbClientClose>=nbProc) {
                                exit(0);
                        }
                }
                exit(0);

        }else{
                //  Close(connfd);
                for(int i=0; i< nbProc; i++) {
                        //    printf("Il y a %d Clients closed sur pere \n",nbClientClose );

                        wait(NULL);
                }

                exit(0);
        }
        exit(0);
}
