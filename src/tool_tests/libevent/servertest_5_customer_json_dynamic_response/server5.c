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

#include <event.h>

#include <glib.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>

#include <json/json.h>


/* Define Variables */
#define SERVER_PORT 8081
int debug = 0;


/* Define Json functions */

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj){
  enum json_type type;
  g_print("type: ",type);
  type = json_object_get_type(jobj); /*Getting the type of the json object*/
  switch (type) {
    case json_type_boolean: g_print("json_type_boolean\n");
                         g_print("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
                         break;
    case json_type_double: g_print("json_type_double\n");
                        g_print("          value: %lf\n", json_object_get_double(jobj));
                         break;
    case json_type_int: g_print("json_type_int\n");
                        g_print("          value: %d\n", json_object_get_int(jobj));
                         break;
    case json_type_string: g_print("json_type_string\n");
                         g_print("          value: %s\n", json_object_get_string(jobj));
                         break;
  }

}

void json_parse_array( json_object *jobj, char *key) {
  void json_parse(json_object * jobj); /*Forward Declaration*/
  enum json_type type;

  json_object *jarray = jobj; /*Simply get the array*/
  if(key) {
    jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
  }

  int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
  g_print("Array Length: %dn",arraylen);
  int i;
  json_object * jvalue;

  for (i=0; i< arraylen; i++){
    jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
    type = json_object_get_type(jvalue);
    if (type == json_type_array) {
      json_parse_array(jvalue, NULL);
    }
    else if (type != json_type_object) {
      g_print("value[%d]: ",i);
      print_json_value(jvalue);
    }
    else {
      json_parse(jvalue);
    }
  }
}

/*Parsing the json object*/
void json_parse(json_object * jobj) {
	g_print("PARSING");
  enum json_type type;
  json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
    g_print("type: ",type);
    type = json_object_get_type(val);
    switch (type) {
      case json_type_boolean: 
      case json_type_double: 
      case json_type_int: 
      case json_type_string: print_json_value(val);
                           break; 
      case json_type_object: g_print("json_type_objectn");
                           jobj = json_object_object_get(jobj, key);
                           json_parse(jobj); 
                           break;
      case json_type_array: g_print("type: json_type_array, ");
                          json_parse_array(jobj, key);
                          break;
    }
  }
} 



/** BEGIN CODE **/

struct client {
  int fd;
  struct bufferevent *buf_ev;
};


int setnonblock(int fd)
{
  int flags;

  flags = fcntl(fd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(fd, F_SETFL, flags);
}

void buf_read_callback(struct bufferevent *incoming,
                       void *arg)
{
  struct evbuffer *evreturn;
  char *req;

	
  req = evbuffer_readline(incoming->input);
  if (req == NULL)
    return;


/* OLD CODE 
	int result = strncmp((char *)req, (char *)"6", 1);
	
	if(result != 0){
	  evreturn = evbuffer_new();
	  evbuffer_add_printf(evreturn,"What is 2 times 3?");
	  bufferevent_write_buffer(incoming,evreturn);
	  evbuffer_free(evreturn);
	  free(req);
	}else if(result == 0){
		evreturn = evbuffer_new();
	  evbuffer_add_printf(evreturn,"true");
	  bufferevent_write_buffer(incoming,evreturn);
	  evbuffer_free(evreturn);
	  free(req);
	}
*/

	//Parse the json
	json_object * jobj = json_tokener_parse(req);
			
	enum json_type type;
	json_object_object_foreach(jobj, key, val){
		g_print("%s\n", key);

		if(g_utf8_collate(key, "cmd") >= 0){
			//Looks like the user has sent a "cmd" (command), lets analyze the "val" (value) of that command to see what the caller/client needs to be attending to...

			//Is the client requesting an "Identity Update" (Pings server: if this is the first time ping, the server and client will exachange keys if the relationship exists the server just accepts the encrypted "ping" packet update)
			type = json_object_get_type(val);
			if(type == json_type_string){
				gchar* cmd_value;
				cmd_value = json_object_get_string(val);
				g_print("VALUE:%d\n", g_utf8_collate(cmd_value, "identupdate"));
				if(g_utf8_collate(cmd_value, "identupdate") == 0){
					g_print("ATTEMPT TO SEND...");

					evreturn = evbuffer_new();
					evbuffer_add_printf(evreturn,"THIS IS A DUMMY RESPONSE -- IDENTITY UPDATE COMPLETE");
					bufferevent_write_buffer(incoming,evreturn);
					evbuffer_free(evreturn);
					free(req);
				}
			}
		}
	}
}

void buf_write_callback(struct bufferevent *bev,
                        void *arg)
{
}

void buf_error_callback(struct bufferevent *bev,
                        short what,
                        void *arg)
{
  struct client *client = (struct client *)arg;
  bufferevent_free(client->buf_ev);
  close(client->fd);
  free(client);
}

void accept_callback(int fd,
                     short ev,
                     void *arg)
{
  int client_fd;
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  struct client *client;

  client_fd = accept(fd,
                     (struct sockaddr *)&client_addr,
                     &client_len);
  if (client_fd < 0)
    {
      warn("Client: accept() failed");
      return;
    }

  setnonblock(client_fd);

  client = calloc(1, sizeof(*client));
  if (client == NULL)
    err(1, "malloc failed");
  client->fd = client_fd;

  client->buf_ev = bufferevent_new(client_fd,
                                   buf_read_callback,
                                   buf_write_callback,
                                   buf_error_callback,
                                   client);

  bufferevent_enable(client->buf_ev, EV_READ);
}

int main(int argc,
         char **argv)
{
  int socketlisten;
  struct sockaddr_in addresslisten;
  struct event accept_event;
  int reuse = 1;

  event_init();

  socketlisten = socket(AF_INET, SOCK_STREAM, 0);

  if (socketlisten < 0)
    {
      fprintf(stderr,"Failed to create listen socket");
      return 1;
    }

  memset(&addresslisten, 0, sizeof(addresslisten));

  addresslisten.sin_family = AF_INET;
  addresslisten.sin_addr.s_addr = INADDR_ANY;
  addresslisten.sin_port = htons(SERVER_PORT);

  if (bind(socketlisten,
           (struct sockaddr *)&addresslisten,
           sizeof(addresslisten)) < 0)
    {
      fprintf(stderr,"Failed to bind");
      return 1;
    }

  if (listen(socketlisten, 5) < 0)
    {
      fprintf(stderr,"Failed to listen to socket");
      return 1;
    }

  setsockopt(socketlisten,
             SOL_SOCKET,
             SO_REUSEADDR,
             &reuse,
             sizeof(reuse));

  setnonblock(socketlisten);

  event_set(&accept_event,
            socketlisten,
            EV_READ|EV_PERSIST,
            accept_callback,
            NULL);

  event_add(&accept_event,
            NULL);

  event_dispatch();

  close(socketlisten);

  return 0;
}


