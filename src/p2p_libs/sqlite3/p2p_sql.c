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


//Define functions


int p2pserver_sql_client_pubkey_exists(gchar *client_public_key_sha256, const guchar * client_public_key){
	
	/**
	 * 	Response Codes
	 * 
	 *  Successfully Executed Fully
	 *  1 = Public key exists in database (And sha256 matches the publickey)
	 *  0 = Public key dosen't exist
	 * 
	 *  Errors
	 * -1 = failed to open/connect to DB
	 * -2 = Error happened while query/searching for match
	 **/
	
	
	//Define local variables
		int return_code = 0;
	
		//SQLite3
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int rc;
		char *errmsg = 0;
		
		
		rc = sqlite3_open("./db/client_list", &db);
	
		//Was the DB file successfully opened?
		if(rc){
			//Failed to open DB
			return_code = -1;
			
		}else{
			const char * pubkey_exists_sql;
				
			pubkey_exists_sql = g_strdup_printf("SELECT `id` FROM `clients` WHERE `publickey_sha256` = '%s' LIMIT 0,1;", client_public_key_sha256);
			g_print("SQL EXECUTING:%s", pubkey_exists_sql);
			
			rc = sqlite3_prepare_v2(db, pubkey_exists_sql, -1, &stmt, 0);
			
			if(rc){
				//Failed to open DB
				return_code = -1;
			}
			
			//Just get the one row requested from the DB
			if(return_code == 0){
				if(sqlite3_step(stmt) == SQLITE_ROW){
					//Extract id
					int pubkey_local_id = sqlite3_column_int(stmt, 0);

					//Check if id is greater than 0 if yes then return 1 if no return 0
					if(pubkey_local_id > 0){
						return_code = 1;
					}else{
						return_code = 0;
					} 
				}else{
					return_code = 0;
				}
				
			}
			
			sqlite3_finalize(stmt);
			
			sqlite3_close(db);
		}
	
	
		return return_code;
}




int p2pserver_sql_add_client_identity(gchar *client_public_key_sha256, const guchar * client_public_key){
	
		/**
		* 	Response Codes
		* 
		*  Successfully Executed Fully
		*  1 = Public key exists in database (And sha256 matches the publickey)
		*  0 = Public key dosen't exist
		* 
		*  Errors
		* -1 = failed to open/connect to DB
		* -2 = Error happened while query/searching for match
		**/


		//Define local variables
		int return_code = 0;
		
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		
		
		
		//Begin local logic
		
			//Open database file
			rc = sqlite3_open("./db/client_list", &db);
			if(rc){
				g_print("Can't open database: %s\n", sqlite3_errmsg(db));
				
				return_code = -1;
			}
			
			if(return_code == 0){
				//Insert into database
				const char * insert_client_pubkey_sql;
				insert_client_pubkey_sql = g_strdup_printf("INSERT INTO `clients` (`publickey`, `publickey_sha256`) VALUES('%s','%s');", client_public_key ,client_public_key_sha256);

				rc = sqlite3_exec(db, insert_client_pubkey_sql, 0, 0, &zErrMsg);
				
				if(rc != SQLITE_OK){
					return_code = -2;
				}else if(rc == SQLITE_OK){
					return_code = 1;
				}
			}
			
			g_print("INSERT CODE: %d\n", return_code);
	
		//Close DB connection
		sqlite3_close(db);
		
	return return_code;
}



int p2pserver_sql_add_relaymsg(gchar *to_pubkey_sha256, gchar *to_message){
	
		/**
		* 	Response Codes
		* 
		*  Successfully Executed Fully
		*  1 = Public key exists in database (And sha256 matches the publickey)
		*  0 = Public key dosen't exist
		* 
		*  Errors
		* -1 = failed to open/connect to DB
		* -2 = Error happened while query/searching for match
		**/


		//Define local variables
		int return_code = 0;
		
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		
		
		
		//Begin local logic
		
			//Open database file
			rc = sqlite3_open("./db/messages", &db);
			if(rc){
				g_print("Can't open database: %s\n", sqlite3_errmsg(db));
				
				return_code = -1;
			}
			
			if(return_code == 0){
				//Insert into database
				const char * insert_txt_message;
				insert_txt_message = g_strdup_printf("INSERT INTO `txt_messages_stored` (`to_pubkey_sha256`, `to_message`) VALUES('%s','%s');", to_pubkey_sha256 ,to_message);

				rc = sqlite3_exec(db, insert_txt_message, 0, 0, &zErrMsg);
				
				if(rc != SQLITE_OK){
					return_code = -2;
				}else if(rc == SQLITE_OK){
					return_code = 1;
				}
			}
			
			g_print("INSERT MSG CODE: %d\n", return_code);
	
		//Close DB connection
		sqlite3_close(db);
		
	return return_code;
}
