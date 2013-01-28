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
void parse_json_command(char** response, char *json_command){
	
	//Define Local Variables	
	int json_is_valid;
	char * local_response = g_strdup_printf("%s", "hello world");
	
	//Begin local logic
	*response = local_response;
	
	/** 
	 * TODO: check if the JSON is valid before parsing 
	 * 			to prevent "Segmentation Defaults" 
	 * 			and its good sanity checks.
	 **/
	 
	//Check if JSON is valid before parsing...
	/*json_is_valid = p2pserver_json_is_valid(json_command);
	g_print("beforesprintf");
	g_sprintf(response, "%d", json_is_valid);
	g_print("aftersprintf");*/
	
	/*//Parse JSON incomming
	json_object * jobj = json_tokener_parse(json_command);
	
	
	enum json_type type;
	
	int first_read = 0;
	json_object_object_foreach(jobj, key, val){
		
		if(first_read == 0){
			
			//What key is this we are readying?
			int is_key_cmd = g_utf8_collate(key, "cmd");
			
			if(is_key_cmd == 0){
				//Flag "First read" (We only want to read the first keys value)
				first_read = 1;
				
				//Execute the calling ocmmand if there is any valid ones found...
				type = json_object_get_type(val);
				if(type == json_type_string){
					char* cmd_value;
					cmd_value = json_object_get_string(val);
					
					if(g_utf8_collate(cmd_value, "identupdate") == 0){
						//Call "Identity Update Response"
							//response = p2pserver_json_identupdate_response(json_command);
							response = "HELLO AGAIN!";
					}
				}
			}
		}
	}
	
	//If response is not set, then it is presummed no valid command was invoked...
	if(strlen(response) <= 0){
		response = "No valid command was called";
	}*/
	
	//response = "YOU KNOW WHO";
	return;
}

