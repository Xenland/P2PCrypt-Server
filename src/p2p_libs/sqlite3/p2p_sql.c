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

int p2pserver_sql_pubkey_exists(gchar *client_public_key_sha256, const guchar * client_public_key){
	
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
	
		//SQLite3 Stuff
		sqlite3 *db;
		int rc;
		gchar *errmsg = 0;
		
	//Begin function logic
		
		//Open database file
		rc = sqlite3_open("/home/c_dev/p2pcrypt_server/v0.1.0/src/db/client_list", &db);
		
		//Was the DB file successfully opened?
		if(rc == SQLITE_OK){
			//Yes it has been successfully opened!
			
			return_code = 1;
		}else{
			//No it wasn't sucessfully opened
			return_code = -1;
		}
	
	
	return return_code;
	
	/*
		//SQLite3
		sqlite3 *conn;
		sqlite3_stmt *res;
		int error = 0;
		int rec_count = 0;
		const char *errMSG;
		const char *tail;
		
	
	//Begin function logic
		//Attempt to open the SQLite3 database
		error = sqlite3_open("./db/network_web.sl3", &conn);
		
		if(error){
			//Failed to connect/open DB
			return_code = -1;
		}
		
		//Attempt to search for sha256, publickey match (only if sql is open)
		if(return_code == 0){
				//Do Search...
				const char * pubkey_exists_sql;
				
				g_print("PUBKEY: %s\n", client_public_key);
				pubkey_exists_sql = g_strdup_printf("SELECT `id`, `publickey_sha256`, `publickey` FROM `clients` WHERE `publickey_sha256` = '%s' LIMIT 0,1", client_public_key_sha256);
				g_print("SQL query: %s\n", pubkey_exists_sql);
				error = sqlite3_prepare_v2(
											conn, 
											pubkey_exists_sql, 
											sizeof(pubkey_exists_sql),
											&res,
											&tail
										);
										
				if(error != SQLITE_OK){
					//Failed to search/query
					return_code = -2;
					
				}
				
				if(error == SQLITE_OK){
					while(sqlite3_step(res) == SQLITE_ROW){
						//Assign output data to local variables to use
						//int * client_db_id;
						//client_db_id = g_strdup_printf("%u", sqlite3_column_int(res, 0));
						
						gchar * publickey_sha256;
						publickey_sha256 = g_strdup_printf("%s", sqlite3_column_text(res, 1));
						
						g_print("DB SHA256:%s\n", publickey_sha256);
					}
					
					//Return code
					return_code = 1;
				}
				
				g_print("SQLFUNC CODE:%d", return_code);
		}
	
	return return_code;
	*/
}
