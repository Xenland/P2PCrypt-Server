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
	
	int valid_cmd_found = 0;
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
				
				const char * cmd_message;
				cmd_message = g_strdup_printf("%s", json_string_value(client_command_called));
				
				//Make sure the "cmd" key was called
				const char * cmd_message_comparison;
				cmd_message_comparison = g_strdup_printf("%s", json_string_value(json_string("identupdate")));
				g_print("\n%s\n%s\n", cmd_message, cmd_message_comparison);
				
				int cmd_comparison_bool = g_utf8_collate(cmd_message, cmd_message_comparison);

				if(cmd_comparison_bool == 0){
					//We have found the "command" currently being invoked is "identityupdate" aka "identupdate"
					p2pserver_json_identupdate_response(&local_response, json);

					//Flag we found a valid command
					valid_cmd_found = 1;
				}
				
				if(valid_cmd_found == 0){
					//We can't seem to find a "cmd", return command not recognized
					local_response = g_strdup_printf("%s", "{\"response\":\"Command Not Recognized\", \"return_code\":100\"}");
					
				}
				
		}else if(json_valid == 0){
			//Json is INVALID, response with the approriate response
			local_response = g_strdup_printf("%s", "{\"response\":\"Invalid json\", \"return_code\":101\"}");
		}
	
	
	//Define output response
	*response = local_response;
	
	return;
}




/**
 * 	RPC Command Responses
 **/


	/** ** **
	 * Identity Update
	 * Purpose: "Initailizing connections, or if connection is not-new than updating online status of the client"
	 ** ** **/
	 
	 void p2pserver_json_identupdate_response(char **response, json_t *json){
		 
		 //Define local variables
		 char * local_response;
		 
		 json_t *client_public_key;
		 
		 //Begin local function logic
		 
			/**
			 * Parse "json", check if this clients publickey is in the database
			 * if no: Add it to the database and send back our public key
			 * if yes: Update the users current "status"
			 **/
			 
			//JSON: Get the public_key value of the user.
			client_public_key = json_object_get(json, "public_key");
			 
			const guchar * client_public_key_string;
			client_public_key_string = g_strdup_printf("%s", json_string_value(client_public_key));
			
			//SHA256: public_key 
			gchar * client_public_key_string_sha256;
			client_public_key_string_sha256 = g_compute_checksum_for_data(G_CHECKSUM_SHA256, client_public_key_string, sizeof(client_public_key_string));
			
			//Search for the "sha256s' associated public key in the SQLite3 DB then match that found result with its public key (efficent search, less characters to match)
			 g_print("%s\n", client_public_key_string_sha256);
			 
		 local_response = g_strdup_printf("%s", "{\"return_code\":1\", \"public_key\":\"node_something_key\"}");
		 
		 //output with response
		 *response = local_response;
		 
		 return;
	 }
