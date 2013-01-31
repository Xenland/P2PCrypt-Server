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
 * 	Load libraries
 **/
	//General
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <string.h>
	
	//Libevent/Libev
	#include <event.h>
	
	//Gnome
	#include <gtk/gtk.h>
	#include <glib.h>
	

/**
 * Define Global Variables
 **/
	//P2P Networking Thread
	GThread          *p2pserver_network_thread;
	GError           *p2pserver_network_thread_error = NULL ;
	
	
	//Socket Server
		//Basic vars
			int p2pserver_network_port = 8016; //Default is 8080
			int p2pserver_network_total_active_connections = 200;
			int debug = 0;
		
		//Structure vars
			struct client {
				int fd;
				struct bufferevent *buf_ev;
			};
			
			int p2pserver_network_socketlisten;
			struct sockaddr_in p2pserver_network_addresslisten;
			struct event p2pserver_network_accept_event;
			int p2pserver_network_reuse = 1;
	
/**
 * Define Functions
 **/
 void start_p2p_node( void *ptr );


/**
 * Define CALL BACK Functions
 **/
 void p2pserver_network_accept_callback(int fd, short ev, void *arg);
 void p2pserver_network_buf_write_callback(struct bufferevent *bev, void *arg);
 void p2pserver_network_buf_error_callback(struct bufferevent *bev, short what, void *arg);
 void p2pserver_network_buf_read_callback(struct bufferevent *incoming, void *arg);
 int p2pserver_network_setnonblock(int fd);
