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

//Load Libraries
 
 
 
//Define Functions
RSA* p2pserver_rsa_gen_keypair(int keybit){
	//Define local variables
	
		//Sanataize and enforce restrictions
		//Restrict keys to a 2048 minimum
		if(keybit < 2048){
			keybit = 2048;
		}
	
	//Begin local logic
	RSA *keypair = RSA_generate_key(keybit, 37, NULL, NULL);
	
	return keypair;
}



int p2pserver_rsa_extract_and_store_keypair_into_db(RSA* keypair){
	
	//Define local variables
		int return_code = 0;
		
		//SQLite3 vars
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		
		//RSA vars
		BIO *pri = BIO_new(BIO_s_mem());
		BIO *pub = BIO_new(BIO_s_mem());


	//Begin local logic
	
		/** **
		 * 	RSA Description
		 * 	Convert the keypair into a "ascii" format to save into the DB
		 ** **/
		 
		//RSA:
		PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
		PEM_write_bio_RSAPublicKey(pub, keypair);

		//RSA: get size
		size_t pri_len = BIO_pending(pri);
		size_t pub_len = BIO_pending(pub);

		//Memory: Allocate
		char *pri_key = malloc(pri_len + 1);
		char *pub_key = malloc(pub_len + 1);

		//Memory: Write
		BIO_read(pri, pri_key, pri_len);
		BIO_read(pub, pub_key, pub_len);

		//Memory: Set end of string
		pri_key[pri_len] = '\0';
		pub_key[pub_len] = '\0';
	

		/** **
		* 	SQLite3 Description
		* 	Save the keypair into the database
		** **/
			//Open database file
			rc = sqlite3_open("./db/identity_list", &db);
			if(rc){
				g_print("Can't open database: %s\n", sqlite3_errmsg(db));
				
				return_code = -1;
			}
			
			if(return_code == 0){
				//Insert keypair into database
				const char * insert_keypair_sql;
				insert_keypair_sql = g_strdup_printf("INSERT INTO `keypair` (`public_key`, `private_key`) VALUES('%s', '%s');", pub_key ,pri_key);
				g_print("%s", insert_keypair_sql);
				rc = sqlite3_exec(db, insert_keypair_sql, 0, 0, &zErrMsg);
				
				if(rc != SQLITE_OK){
					return_code = -2;
				}else if(rc == SQLITE_OK){
					return_code = 1;
				}
			}

	
		//Close DB connection
		sqlite3_close(db);
		
	return return_code;
}



char * p2pserver_rsa_buffer_default_public_key(){
	//Definelocal variables
		int return_code = 0;
		
		//RSA vars
		char * response_public_key;
	
		//SQLite3
		sqlite3 *db;
		sqlite3_stmt *stmt;
		int rc;
		char *errmsg = 0;
		
		
		rc = sqlite3_open("./db/identity_list", &db);
	
		//Was the DB file successfully opened?
		if(rc){
			//Failed to open DB
			return_code = -1;
			
		}else{
			const char * default_pubkey_exists_sql;
				
			default_pubkey_exists_sql = g_strdup_printf("SELECT `public_key` FROM `keypair` WHERE `default` = '1' LIMIT 0,1;");

			rc = sqlite3_prepare_v2(db, default_pubkey_exists_sql, -1, &stmt, 0);
			
			if(rc){
				//Failed to open DB
				return_code = -1;
			}
			
			//Just get the one row requested from the DB
			if(return_code == 0){
				if(sqlite3_step(stmt) == SQLITE_ROW){
					//Extract public key from DB
					response_public_key = g_strdup_printf("%s", sqlite3_column_text(stmt, 0));

					//Flag success
					return_code = 1;
					
				}else{
					return_code = 0;
				}
			}
			
			sqlite3_finalize(stmt);
			
			sqlite3_close(db);
		}
	
		//If no default key is set return "0"
		if(return_code != 1){
			response_public_key = "0";
		}
		
		return response_public_key;
}
