#include<stdio.h>
#include<string.h>
#include<openssl/sha.h>

#define HASH_SIZE 64

int main () {

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
		// putchar('\n');
	}
}