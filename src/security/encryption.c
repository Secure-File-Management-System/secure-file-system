// encryption.c - XOR Encryption Logic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/security/encryption.h"

void xor_encrypt_decrypt(char *data, size_t len, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % key_len];  // XOR each byte
    }
}

int encrypt_file(const char *input_path, const char *output_path, const char *key) {
    FILE *fin = fopen(input_path, "rb");
    FILE *fout = fopen(output_path, "wb");
    if (!fin || !fout) {
        perror("Error opening file");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return 1;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
        xor_encrypt_decrypt(buffer, bytes_read, key);
        fwrite(buffer, 1, bytes_read, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

int decrypt_file(const char *input_path, const char *output_path, const char *key) {
    // Same logic as encrypt, since XOR is symmetric
    return encrypt_file(input_path, output_path, key);
}
