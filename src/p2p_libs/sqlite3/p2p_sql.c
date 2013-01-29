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
	
		//SQLite3
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int rc;
		char *errmsg = 0;
		
		
		rc = sqlite3_open("/home/c_dev/p2pcrypt_server/v0.1.0/src/db/client_list", &db);
	
		//Was the DB file successfully opened?
		if(rc){
			//Failed to open DB
			return_code = -1;
			
		}else{
			g_print("\nDB opened\n");
			const char * pubkey_exists_sql;
				
			pubkey_exists_sql = g_strdup_printf("SELECT `id`, `publickey_sha256`, `publickey` FROM `clients` WHERE `publickey_sha256` = '%s' LIMIT 0,1;", client_public_key_sha256);
			
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
					g_print("%d", pubkey_local_id);
					
					/*
					//Extract publickey_sha256
					gchar * pubkey_local_sha256;
					pubkey_local_sha256 = g_strdup_printf("%s", sqlite3_column_text(stmt, 1));
					
					//Extract publickey
					gchar * pubkey_local_string;
					pubkey = g_strdup_printf("%s", sqlite3_column_test(stmt, 2));
					*/

					//Check if id is greater than 0 if yes then return 1 if no return 0
					if(pubkey_local_id > 0){
						return_code = 1;
					}else{
						return_code = 0;
					} 
				}else{
					return_code = -2;
				}
				
			}
			
			sqlite3_finalize(stmt);
			
			sqlite3_close(db);
		}
	
	
		return return_code;
	
	/* 
		//SQLite3 Stuff
		sqlite3_stmt *stmt;
		sqlite3 *db;
		int rc;
		gchar *errmsg = 0;
		
	//Begin function logic
		
		//Open database file
		rc = sqlite3_open("/home/c_dev/p2pcrypt_server/v0.1.0/src/db/client_list", &db);
		
		//Was the DB file successfully opened?
		if(rc == SQLITE_OK){
			//Yes it has been successfully opened!
				//Do search for sha256/publickey match in DB
				const char * pubkey_exists_sql;
				
				pubkey_exists_sql = g_strdup_printf("SELECT `id`, `publickey_sha256`, `publickey` FROM `clients` WHERE `publickey_sha256` = '%s' LIMIT 0,1;", client_public_key_sha256);
				g_print("ABOUT TO EXECUTE SQL");
				rc = sqlite3_prepare_v2(db, pubkey_exists_sql, -1, &stmt, 0);
				if(rc == SQLITE_OK){
					g_print("SQL QUERY OKAY!");
					int nCols = sqlite3_column_count(stmt);
					g_print("SQL COLUMNS:%d", nCols);
					if(nCols > 0){
						while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
							for(int nCol = 0; nCol < nCols; nCol++){
								if(nCol == 1){
									//Return public key as unsigned char
									unsigned char * serverside_client_public_key;
									serverside_client_public_key = (unsigned char *)sqlite3_column_text(stmt, nCol);
									g_print("ABOUT TO PRINT PUB KEY");
									g_print("%s", serverside_client_public_key);
								}
							}
						}
					}else{
						//NO RESULTS WERE RETURNED FROM THE DATABASE...
							//TO DO: something.
							
							g_print("NO RESULSTS");
							
					}
					sqlite3_finalize(stmt);
				}
				
				sqlite3_close(db);
				
					
				return_code = 1;
		}else{
			//No it wasn't sucessfully opened
			return_code = -1;
		}
	
	
	return return_code;
*/
}
