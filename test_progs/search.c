#include<stdio.h>
#include<string.h>
#include<sqlite3.h>
#include<openssl/sha.h>

#define HASH_SIZE 64

int main() {

	char *buf;
	buf = "abc";
	int n = strlen(buf);
	unsigned char md[HASH_SIZE];
        SHA_CTX context;
        SHA1_Init(&context);
        // char *buf_ = "";
       	SHA1_Update(&context, (uint8_t *)buf, n);
        
        SHA1_Final(md, &context);
	printf("0x");
	for (int i = 0; i < HASH_SIZE; i++) {
		printf("%d", md[i]);
	}
	printf("\n");

	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("hash_block.db", &db);
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char cmd[512]; 
    
    sprintf(cmd,"SELECT * FROM hashes WHERE hash = '%s'",md);
        
    rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
	sqlite3_str *buffer = sqlite3_str_new(db);
	sqlite3_stmt *statement;
	while (sqlite3_step(statement) == SQLITE_ROW)
	{
		sqlite3_str_appendf(buffer, "%s | %s\n",
			(const char *)sqlite3_column_text(statement, 0),
			(const char *)sqlite3_column_text(statement, 1));
	
	}
	char *block = sqlite3_str_finish(buffer);
	// for (int i = 0; i < sizeof(block); i++) {
	// 	printf("%d", block[i]);
	// }
	printf("%s", block);
	sqlite3_free(block);
    
    return 0;

}