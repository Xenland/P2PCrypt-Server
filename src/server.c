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
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **


								P2P Crypt (Server)

		Short Description:
			The P2P Crypt network it self is designed to facilitate home owners, businesses, 
			and even gamers for audio,video,text or file transfer encrypted communications 
			that is a "Turn-Key" solution for the global masses. 
	 
			The servers' purpose of the network is to stay consistently online, to store messages, 
			relay real-time streams and protect the integrity of everyone’s public-key.
		
		
		Resources
			You can contact and find other community members and contributors at http://p2pcrypt.com
			
			Note: This source-code was written from the application called "Geany" for those who care.

** ** **/


// Load linkage file
#include "linkage.h"



int main(int argc, char *argv[]){
	

	/**
	 * Begin P2P Server Logic
	 **/	
	//Initialize gtk
	gtk_init(NULL, NULL);
	
	//Initialize GLib
	g_type_init();
	
	//Load default server public key
	p2pserver_rsa_active_identity = p2pserver_rsa_buffer_default_public_key();


	//debug msg
	debug_console_message("Initailized");
	debug_console_message("Booting up!");
	
	
	//Start P2P Server Networking functions
	if((p2pserver_network_thread = g_thread_create((GThreadFunc)start_p2p_node, (void *)"", TRUE, &p2pserver_network_thread_error)) == NULL){
		g_message("Thread create failed: %s!!", p2pserver_network_thread_error->message);
		g_error_free(p2pserver_network_thread_error);
	}


	//End all threads before closing the application
	g_thread_join(p2pserver_network_thread);
	
	debug_console_message("Closing socket");
	close(p2pserver_network_socketlisten);
	
	return 0;
}
