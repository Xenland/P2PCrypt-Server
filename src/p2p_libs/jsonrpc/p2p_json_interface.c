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
	char * local_response;
	
	int json_valid = 0; //0 = Invalid; 1 = Valid json;
	json_t *json;
	json_error_t error;
	json_t *client_command_called;


	//Begin local logic
		
		//Load up incomming JSON text into the JSON memory
		json = json_loads(json_command, 0, &error);
		
		//Is json valid? (Yes, keep parsing, no, return negative response)
		if(!json){
			//Json is not valid
			json_valid = 0;
		}else{
			//JSON IS VALID
			json_valid = 1;
		}
		
		if(json_valid == 1){
			//Json is valid, continue with the parsing...
				//Check what command has been called.
				client_command_called = json_object_get(json, "cmd");
				
					//Make sure this is a valid string
					g_print("CMD STRING:%s", json_string_value(client_command_called));
					
					/*if(json_equal(tmp_root_key_name, "identupdate") == 0){
						//We can't seem to find a "cmd", return command not recognized
						local_response = g_strdup_printf("%s", "{\"response\":\"Command Not Recognized\", \"return_code\":100\"}");
						
					}else{
						//We have found a "cmd" key invoked, Depending on the "value" we will parse the rest of the json accordingly
						local_response = g_strdup_printf("%s", "{\"response\":\"Command SUCCESS!\", \"return_code\":1\"}");
					}*/
				
		}else if(json_valid == 0){
			//Json is INVALID, response with the approriate response
			local_response = g_strdup_printf("%s", "{\"response\":\"Invalid json\", \"return_code\":101\"}");
		}
		
		
	//If response is not set, then it is presummed no valid command was invoked...
	/*if(sizeof(local_response) <= 0){
		local_response = g_strdup_printf("%s", "{\"response\":\"Command Not Recognized\", \"return_code\":100\"}");
	}*/
	
	
	//Define output response
	*response = local_response;
	
	return;
}

