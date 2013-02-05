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
	
	const char * cmd_message_comparison;
	int valid_cmd_found = 0;
	int cmd_comparison_bool = 0;
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
				//Init handle for cmd value
				client_command_called = json_object_get(json, "cmd");
				
					//Define value of cmd
					const char * cmd_message;
					cmd_message = g_strdup_printf("%s", json_string_value(client_command_called));
				

				//What command was called?
					//Identity Update? | identupdate
					cmd_message_comparison = g_strdup_printf("%s", json_string_value(json_string("identupdate")));
				
					cmd_comparison_bool = g_utf8_collate(cmd_message, cmd_message_comparison);
					
					if(cmd_comparison_bool == 0){
						//We have found the "command" currently being invoked is "identityupdate" aka "identupdate"
						p2pserver_json_identupdate_response(&local_response, json);

						//Flag we found a valid command
						valid_cmd_found = 1;
					}
					
					
					//Relay Message | relaymsg
					if(valid_cmd_found == 0){
						cmd_message_comparison = g_strdup_printf("%s", json_string_value(json_string("relaymsg")));
						
						cmd_comparison_bool = g_utf8_collate(cmd_message, cmd_message_comparison);
						
						if(cmd_comparison_bool == 0){
							//We have found the "command" currently being invoked is "relaymsg"
							p2pserver_json_relaymsg_response(&local_response, json);
							
							//Flag we found a valid command
							valid_cmd_found = 1;
						}
					}
					
					
					//Receive Message Queue | receivemsgq
					if(valid_cmd_found == 0){
						cmd_message_comparison = g_strdup_printf("%s", json_string_value(json_string("receivemsgq")));
						
						cmd_comparison_bool = g_utf8_collate(cmd_message, cmd_message_comparison);
						
						if(cmd_comparison_bool == 0){
							//We have found the "command" currently being invoked is "relaymsg"
							p2pserver_json_receivemsgqueue_response(&local_response, json);
							
							//Flag we found a valid command
							valid_cmd_found = 1;
						}
					}
				
			//No valid "cmd" could be found....
			if(valid_cmd_found == 0){
				//We can't seem to find a "cmd", return command not recognized
				local_response = g_strdup_printf("%s", "{\"response\":\"Command Not Recognized\", \"return_code\":\"100\"}");
				
			}
				
		}else if(json_valid == 0){
			//Json is INVALID, response with the approriate response
			local_response = g_strdup_printf("%s", "{\"response\":\"Invalid json\", \"return_code\":\"101\"}");
		}
	
	
	//Define output response
	*response = local_response;
	
	return;
}




/**
 * 	RPC Command Responses
 **/


	/** ** **
	 * Identity Update | identupdate
	 * Purpose: "Initailizing connections, or if connection is not-new than updating online status of the client"
	 ** ** **/
	 
	 void p2pserver_json_identupdate_response(char **response, json_t *json){
		 
		 //Define local variables
		 char * local_response;
		 
		 json_t *client_public_key;
		 
		 //Begin local function logic
		 
			/** General Instruction Description
			 * 
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
			client_public_key_string_sha256 = g_compute_checksum_for_string(G_CHECKSUM_SHA256, client_public_key_string, strlen(client_public_key_string));
			
			//SQLite3: Search for the "sha256s" associated public key in the SQLite3 DB and match that found result with its public key (efficent search, less characters to match)
			int client_public_key_exists = p2pserver_sql_client_pubkey_exists(client_public_key_string_sha256, client_public_key_string);
			
			//Decision: If no: add it to the DB, if yes, update the current users "status" (Only if the status is signed and valid, of course)
			if(client_public_key_exists == 1){
				//TO DO: Update the clients "status" locally to DB
				
				//Respond to the client with a return_code of 1001 (identupdate success)
				local_response = g_strdup_printf("{\"return_code\":\"1001\", \"public_key\":\"%s\"}\n", p2pserver_rsa_active_identity);
				
			}else if(client_public_key_exists == 0){
				//This client is new, save it into the database
				int add_client_locally_success = p2pserver_sql_add_client_identity(client_public_key_string_sha256, client_public_key_string);
				
				local_response = g_strdup_printf("{\"return_code\":\"1002\", \"public_key\":\"%s\"}\n", p2pserver_rsa_active_identity);
			}else{
				//Error status invoked during the search
				local_response = g_strdup_printf("{\"return_code\":\"-1000\"}\n");
			}
			
			g_print("%s\n", local_response);

		 //output with response
		 *response = local_response;
		 
		 return;
	 }



	/** ** **
	 * Relay Message | relaymsg
	 * Purpose: "When a message is recieved from a relaymsg command this message is saved to the database locally,
	 * 			until another client asks for its "messages".
	 ** ** **/
	
	void p2pserver_json_relaymsg_response(char **response, json_t *json){
		 
		//Define local variables
		char * local_response;
		 
		json_t *to_pubkey_sha256;
		const guchar * to_pubkey_sha256_string;
		
		json_t *to_message;
		const guchar * to_message_string;
		
		//Begin local function logic
			/** General Instruction Description
			* 	TO DO: Describe what is happening in the logic below in engrish.
			**/
			
			//JSON: Get the sha256 of the receipts publickey
			to_pubkey_sha256 = json_object_get(json, "to_pubkey_sha256");
			to_pubkey_sha256_string = g_strdup_printf("%s", json_string_value(to_pubkey_sha256));
			
			//JSON: Get the message to be relayed
			to_message = json_object_get(json, "to_message");
			to_message_string = g_strdup_printf("%s", json_string_value(to_message));
			
			//SQLite3: Save the message along with the "to_pubkey_sha256" data as well into the database.
			p2pserver_sql_add_relaymsg(to_pubkey_sha256_string, to_message_string);
			
		//output with reponse
		*response = local_response;
		
		return;
	}
	
	
	/** ** **
	 * Receive Message Queue | receivemsgq
	 * Purpose: A client is requesting messages specifically attributed to the publickey/sha256 digest.
	 ** ** **/
	
	void p2pserver_json_receivemsgqueue_response(char **response, json_t *json){
		 g_print("EXECUTE RECEIVEMSGQUUE");
		 
		//Define local variables
		int return_code = 0;
		
		char * local_response;
		
		json_t *json_response;
		json_t *json_messages_array;
		 
		json_t *associated_msg_pubkey_sha256;
		const guchar * associated_msg_pubkey_sha256_string;

		//Begin local function logic
			/** General Instruction Description
			* 	TO DO: Describe what is happening in the logic below in engrish.
			**/
			
			//JSON: Get the sha256 of messages the client is requesting
			associated_msg_pubkey_sha256 = json_object_get(json, "pubkey_sha256");
			associated_msg_pubkey_sha256_string = g_strdup_printf("%s", json_string_value(associated_msg_pubkey_sha256));

			//SQLite3 + JSON: Query all messages associated with this sha256 digest and output a json array of all known messages
			sqlite3 *db;
			sqlite3_stmt *stmt;
			int rc;
			char *errmsg = 0;
		
		
			rc = sqlite3_open("./db/messages", &db);
	
			//Was the DB file successfully opened?
			if(rc){
				//Failed to open DB
				return_code = -1;
				
			}else{
				const char * specific_messages_sql;
					
				specific_messages_sql = g_strdup_printf("SELECT `to_message` FROM `txt_messages_stored` WHERE `to_pubkey_sha256` = '%s';", associated_msg_pubkey_sha256_string);
				g_print("sql:%s\n", specific_messages_sql);
				
				rc = sqlite3_prepare_v2(db, specific_messages_sql, -1, &stmt, 0);
				
				if(rc){
					//Failed to open DB
					return_code = -1;
				}
				
				//Just get the one row requested from the DB
				if(return_code == 0){
					//Initialize JSON response
					json_response = json_object();
					
						//Append return_status code
						json_t *json_return_code;
						json_return_code = json_integer((json_int_t) 2000);
					
						json_object_set(json_response, "return_code", json_return_code);
						
						
						//Initialize array to contain all the messages
						json_messages_array = json_array();
						
						//Populate the array with messages
						while(sqlite3_step(stmt) == SQLITE_ROW){
							//Extract message from SQLite3 DB
							const unsigned char * tmp_message;
							tmp_message = sqlite3_column_text(stmt, 0);
							
							//Append message to the array
							json_array_append(json_messages_array, json_string((const char *)tmp_message));
						}
						
						//Append populated array to the json object
						json_object_set(json_response, "messages", json_messages_array);
						
					
						//TO DO: Append to json object the total number of messages sent (in encrypted form)
						
						local_response = g_strdup_printf("%s", json_dumps(json_response, JSON_COMPACT));
						
						//Flag success
						return_code = 1;
				}
				
				sqlite3_finalize(stmt);
				
				sqlite3_close(db);
			}
	
			
		//output with reponse
		*response = local_response;
		
		return;
	}
