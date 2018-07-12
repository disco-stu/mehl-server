/*
 * =====================================================================================
 *
 *       Filename:  mehl.c
 *
 *    Description:  This is the incredible 'mehl'-Server
 *
 *        Version:  1.0
 *        Created:  01.02.2013 18:38:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Adrian Vondendriesch (), discostu@zoozer.de
 *        Company:  brainmode
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "parser.h"
#include <pthread.h>
#include <signal.h>

#define PORT 6363
#define MAX_QUEUE 1
#define BUF_SIZE 1024

#define MKVAL(e, t); e->val=malloc(sizeof(t));

/* Begin: Global VARS */

element_t 			*list;
int 				 sock_listen;

/* End: Global VARS */

void *mehl_thread(void *s)
{
	int 		*sock = (int*)s;
	int  	 	 rec_value 		= 0;
				  /*send_value 	= 0;*/
	char 	 	 tmp[BUF_SIZE];
	char 	 	 buf[BUF_SIZE];

	strcpy(buf, "Welcome to the official Mehl-Server\n");
	/*send_value = write(*sock, buf, strlen(buf));*/;
	strcpy(buf, "");

	while(0 < (rec_value=read(*sock, tmp, BUF_SIZE)))
	{
		tmp[rec_value] = '\0';

		if(tmp[rec_value-2] == 0x0d && tmp[rec_value-1] == 0x0a)
		{
			if(rec_value > 2)
				snprintf(buf, rec_value-1, tmp);

			printf("%d Bytes received\n", rec_value);

			if(strcmp(buf, "quit") == 0 || strcmp(buf, "q") == 0) 
			{
				strcpy(buf, "Closing connection...\n");
				write(*sock, buf, strlen(buf));
				close(*sock);
				free(sock);
			}
			else
			{
				sprintf(buf, "%s\n", parse(buf));
				printf("Parser: %s", buf);
				write(*sock, buf, strlen(buf));
			}
		
			memset(buf, 0, sizeof(BUF_SIZE));
		}
		else 
		{
			strncat(buf, tmp, rec_value);
		}

	}

	return 0;
}

/**
 * Catches the SIGINT interrupt and joins all threads.
 *
 * @param: 	int 	signr - signal number
 * @return: void
 */
void exithandler(int signr)
{
	element_t 	*cur = list;

	printf("close all connection and kill threads ...\n");

	while(0 != cur->next)
	{
		pthread_join( ((pthread_t) cur->val), 0 );
		free(cur->val);
	}

	printf("All threads where terminated\n");

	close(sock_listen);
}

/**
 * Main server entry
 */
int main(int argc, char **argv)
{
	int					*sock_tmp,
						 optval 			= 1;
	struct sockaddr_in 	 server 			= {0};
	element_t			*tmp_elem;
	struct sigaction 	 sig_action;

	list = list_create_element();

	memset(&sig_action, '\0', sizeof(sig_action));

	sig_action.sa_handler = &exithandler;
	sigemptyset(&sig_action.sa_mask);
	sig_action.sa_flags = 0;
	sigaction(SIGINT, &sig_action, NULL);


	printf("%s", "try to open a socket\n");
	sock_listen = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_listen < 0)
	{
		perror("can't open socket");
		exit(1);
	}
	else
	{
		printf("%s", "socket is open\n");
	}

	server.sin_family 		= AF_INET;
	server.sin_addr.s_addr 	= INADDR_ANY;
	server.sin_port 		= htons(PORT);

	setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	if(bind(sock_listen, (struct sockaddr *) &server, sizeof(struct sockaddr_in)))
	{
		perror("bind socket to server_addr");
		exit(1);
	}

	printf("%s", "listen\n");
	listen(sock_listen, MAX_QUEUE);

	while(1)
	{
		printf("%s", "waiting ...\n");
		sock_tmp = malloc(sizeof(int));
		*sock_tmp = accept(sock_listen, 0, 0);
		if(*sock_tmp < 0)
		{
			perror("accept");
			exit(1);
		}
		else
		{
			tmp_elem = list_create_element();
			MKVAL(tmp_elem, pthread_t);
			pthread_create( ((pthread_t*) tmp_elem->val), NULL, mehl_thread, sock_tmp);
		}

	}

	/* will never be reached */
	tmp_elem = list;
	while(0 != tmp_elem->next)
	{
		pthread_join( *((pthread_t*) tmp_elem->val), 0 );
	        tmp_elem = tmp_elem->next;
	}

	close(sock_listen);

	return 0;
}
