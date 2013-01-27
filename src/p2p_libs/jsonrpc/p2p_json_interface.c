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
 * 	Main Json Rpc Command Parser
 **/
char * parse_json_command(char json_command){
	
	//Define Local Variables	
	char *response;
	response = "YOU KNOW";
	
	//Print out the recieved message....
	//g_message("%s", json_command);
	
	
	/** 
	 * TODO: check if the JSON is valid before parsing 
	 * 			to prevent "Segmentation Defaults" 
	 * 			and its good sanity checks.
	 **/
	
	//Parse JSON incomming
	//json_object * jobj = json_tokener_parse(json_command);
	
	/*
	enum json_type type;
	json_object_object_foreach(jobj, key, val){
		g_print("%s\n", key);

		if(g_utf8_collate(key, "cmd") >= 0){
			//Looks like the user has sent a "cmd" (command), lets analyze the "val" (value) of that command to see what the caller/client needs to be attending to...

			//Is the client requesting an "Identity Update" (Pings server: if this is the first time ping, the server and client will exachange keys if the relationship exists the server just accepts the encrypted "ping" packet update)
			type = json_object_get_type(val);
			if(type == json_type_string){
				char* cmd_value;
				cmd_value = json_object_get_string(val);
				//g_print("VALUE:%d\n", g_utf8_collate(cmd_value, "identupdate"));
				if(g_utf8_collate(cmd_value, "identupdate") == 0){
					//Call "Identity Update Response"
						//char return_response = p2pserver_json_identupdate_response(json_command);
						
				}
			}
		}
	}
	*/
	return response;
}

