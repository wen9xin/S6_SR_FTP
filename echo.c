/*
 * echo - read and echo text lines until client closes connection
 */
#include "csapp.h"
#include <stdio.h>

#define FILE_SIZE 1000

//vision string
/*
   void echo(int connfd)
   {
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %u bytes\n", (unsigned int)n);
        Rio_writen(connfd, buf, n);
    }
   }
*/

//vision FTP

void echo(int connfd)
{
        FILE *fp;
        size_t n;
        char recu[MAXLINE];
  //      char buf[1000];
        rio_t rio;

        Rio_readinitb(&rio, connfd);
        while ((n = Rio_readlineb(&rio, recu, MAXLINE)) != 0) {
//        int i=0;
       char nomFicher[n];


        for(int i=0;i<=n;i++){
            nomFicher[i]=recu[i];
        }

          printf("%s\n",nomFicher);
        /*
        memset( nomFicher,0, sizeof(nomFicher) );
        strncpy(nomFicher, buf, strlen(buf)>FILE_SIZE?FILE_SIZE:strlen(buf));
        memset( buf,0, sizeof(buf) );
        */
        printf("%s\n", nomFicher);

        fp=Fdopen(connfd,"r");

        if(fp==NULL){
          printf("Ne peut pas ouvir\n");
        }
        /*
        buf[i]=fgetc(fp);
        i++;
        while (buf[i]!=EOF) {
            buf[i]=fgetc(fp);
            i++;
          }
          Rio_writen(connfd, buf, (size_t)i-1);
          */
          fclose(fp);

    }
   }
