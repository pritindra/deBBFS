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
    
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("hash_block.db", &db);
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char cmd[512]; 
    
    sprintf(cmd,"INSERT INTO hashes VALUES ('%s', '%s')",md,buf);
        
    rc = sqlite3_exec(db, cmd, 0, 0, &err_msg);
    if (rc ) 
        printf("Success");
    
    return 0;
}
