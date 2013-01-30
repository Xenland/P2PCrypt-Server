/** ** **
				Copyright (c) 2013 "Shane B. and Contributors"
				Representative: www.P2PCrypt.com

		Permission is hereby granted, free of charge, to any person obtaining a copy
		of this software and associated documentation files (the "Software"), to deal
		in the Software without restriction, including without limitation the rights
		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
		copies of the Software, and to permit persons to whom the Software is
		furnished to do so, subject to the following conditions:

		The above copyright notice and this permission notice shall be included in
		all copies or substantial portions of the Software.

		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
		THE SOFTWARE.
** ** **/

	
/**
 * Define Functions
 **/

 
	/***
	 * 		Start the P2P Node
	 ***/
	 
	 void start_p2p_node( void *ptr ){
		 
		 //Initiate events
		 event_init();
		 
		 //Initiate a "handle" to the "socket"
		 p2pserver_network_socketlisten = socket(AF_INET, SOCK_STREAM, 0);
		 
			//Error Handling (NOT YET IMPLEMENTED)
			/**
			 if (socketlisten < 0)
			 {
				fprintf(stderr,"Failed to create listen socket");
				return 1;
			 }
			**/
		
		//Fill memory		
		memset(&p2pserver_network_addresslisten, 0, sizeof(p2pserver_network_addresslisten));
	 
	 
		//Define the networking stream
		p2pserver_network_addresslisten.sin_family = AF_INET;
		p2pserver_network_addresslisten.sin_addr.s_addr = INADDR_ANY;
		p2pserver_network_addresslisten.sin_port = htons(p2pserver_network_port);
		
		//Bind "socket"/"handle" to network address
		int bind_successful = bind(p2pserver_network_socketlisten, (struct sockaddr *)&p2pserver_network_addresslisten, sizeof(p2pserver_network_addresslisten));
		if(bind_successful < 0){
			//Failure to bind to socket
			debug_console_message("Failed to bind socket-handle to address\n");
		}else if(bind_successful == 0){
			//Success!
			debug_console_message("Successfuly opened the hardware network stream\n");
		}

		//Start listening to the network stream
		int listen_successful = listen(p2pserver_network_socketlisten, p2pserver_network_total_active_connections);
		g_message("%d", bind_successful);
		
		if(listen_successful == 0){
			//Succesfully listening on the socket stream
			debug_console_message("Successfuly listening on the stream and ready to relay data!\n");
			
		}else if(listen_successful < 0){
			//Fail to listen on the socket stream
			debug_console_message("Failed to listen on the socket stream\n");
		}


		//Set socket options
		int reuse = 1;
		setsockopt(p2pserver_network_socketlisten, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		
		//Set Libev event
		event_set(&p2pserver_network_accept_event, p2pserver_network_socketlisten, EV_READ|EV_PERSIST, p2pserver_network_accept_callback, NULL);
		
		
		//Activate event
		event_add(&p2pserver_network_accept_event, NULL);
	
		event_dispatch();

	 }
	 
	 
	 
	 
	 
	 
	 
	 
/**
 * Define CALL BACK Functions
 **/
 
void p2pserver_network_accept_callback(int fd, short ev, void *arg){
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct client *client;

	client_fd = accept(fd,(struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0){
		warn("Client: accept() failed");
		return;
	}

	p2pserver_network_setnonblock(client_fd);

	client = calloc(1, sizeof(*client));
	if (client == NULL)
	err(1, "malloc failed");
	client->fd = client_fd;

	client->buf_ev = bufferevent_new(client_fd, p2pserver_network_buf_read_callback, p2pserver_network_buf_write_callback, p2pserver_network_buf_error_callback, client);

	bufferevent_enable(client->buf_ev, EV_READ);
}



void p2pserver_network_buf_write_callback(struct bufferevent *bev, void *arg){
}



void p2pserver_network_buf_error_callback(struct bufferevent *bev, short what, void *arg){
	//Define function local variables
	struct client *client = (struct client *)arg;
	
	//Define function local logic
	bufferevent_free(client->buf_ev);
	close(client->fd);
	free(client);
}


void p2pserver_network_buf_read_callback(struct bufferevent *incoming, void *arg){
	//Define function local variables
	struct evbuffer *evreturn;
	char *req;

	//Begin function local logic
	req = evbuffer_readline(incoming->input);
	if (req == NULL){
		return;    
	}
	
	
	char * response;
	parse_json_command(&response, req);

	evreturn = evbuffer_new();
	evbuffer_add_printf(evreturn, "%s", response);
	
	bufferevent_write_buffer(incoming,evreturn);
	evbuffer_free(evreturn);
	free(req);
	
}


int p2pserver_network_setnonblock(int fd){
  int flags;

  flags = fcntl(fd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(fd, F_SETFL, flags);
}
