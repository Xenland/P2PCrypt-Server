
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr;
   char * sendline;
  // sendline = "hellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolohellohellohellohellohellohellohellohellohellolo\r\n";
//sendline = "{\"cmd\":\"relaymsg\", \"to_pubkey_sha256\":\"SHA256 DIGEST OUTPUT\", \"to_message\":\"YHxkTtaZJJJgxmkmMcyNWRjC5Dw4KQCJJjc3BlBFCJPnEsTOAL0800AWwsuD3ztsXnOOhITjuxPRYggepL0lomMoKS2y68X0YutB1wHeWJauRDfY93NVAsvkVa7IiVrfj6HzSdCCA5bL3LfADGjChLMAVpaAQMgAGzwIef0wwBONQ7qtE9Si73cze47PlyI1LJtTJjVKJyHpCpLsVBLXRi0RWNDJCrBnyYCKGayXDy4RVdy9O4dnCY635HaP2zQXewvDbDcg1udM26BooWuw01C3HrgklELHFJQGiM3KirHl00D1H4xuMuow8FLQPdzmCwTBul7ftKWDJwms2Upz8DYmZKOBnQzRwl1AyCfuWsePpw78yRaDvoKy8o5YdSwATk1VaaJDWaykkbRS4cc8lcPOn05PNdpyWGTsM2qJfWo0VLH6o9s7DFSqOzADgDqIo5iArhXLtHuY3CbEo7lqLZ7bVXhCU1Gm3Plt4csuQ1onG9522Ad1tG6Gtdez1Q2dX5n8IcTW0pUrcVKTZdO8YZ4w0HUNL25OcDle7gmzkIgid036j9LpDk52gck8RShQMj8BApM9sSLrDujQzI7J9KQvfOnGHsY86Ph1SPFwgbjm1W3Kz49dEva9yXOLE3M9kIAPP2pvwcwGy5gwwlR4n7Hdbollx7RDrTe5JvHPWJN6hJqcbQzCFcTiW2TVPC9hbqbRDZzB7kZfF2R0vt9IKcnafLOEHH1MI58Av7Dxqikb7SG7TLNKjwEDQfjyCmJOFHp52Fa5OyhoLBmgBRyp7EDW6BCyCiPng58xWbZB6XgXF8UluqiPZzqQ8dzR2mgsHZZzGgpROIBI7H6dBnm9QxWhRIDlE6TfT9VrHTOjXXS558Zba6M8xATI73yNGrGOVxVrm0AgXyKxQKXvEZY28bEdA7LkQwalZWGbv1KqquJn4RDcYXD1iNPDPgRupPmBvgnPCUwi9zeb2lIE5o93Jp7aJWHobrhe4TE4j8Qjgp19fmJF7gSyb0n0SxawF8aPv6lHQn9wuG2iJwaGdsxboyzy3xWA2zFt0edqBHLbZvQ4DuURi7yDsNLvA80j46FDMYmbWzjduGKezq5R88tyrIBfxdfZTC9LwHlsB2zhI02fUSjj53NlQGvn3jfkUuGiotbOSILmIdnBEOqidDHIgrG9U5W9lwW6WfeoRI5e21sQYtPRvr5uCkzo9KPRPgri5zeMSYNdvailLyajPUrtV9OQrbNPeBv8fXYyZz61omQUS\"}\r\n";
	sendline = "{\"cmd\":\"identupdate\", \"public_key\":\"sGuLWerX\"}\n";
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(8024);

	int connect_status = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("%d\n", connect_status);

	int send_status = send(sockfd,sendline,strlen(sendline),0);
	printf("%d\n", send_status);

	char buffer[1024];
	char buff[1024];
	
	int continue_recieve = 1;
	while(continue_recieve == 1){
		int num = recv(sockfd, buffer, 1, 0);
		if(num <= 0){
			printf("Either Connection Closed or Error\n");
		}else{
			if(strcmp(buffer, "}") == 0){
				continue_recieve = 0;
			}
				buffer[num] = '\0';
				printf("%s\n",buffer);

		}
	}
    printf("END\n");
    return 0;
}
