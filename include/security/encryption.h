// encryption.h - XOR Encryption Header

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stddef.h>

// Encrypts or decrypts data using XOR
void xor_encrypt_decrypt(char *data, size_t len, const char *key);

// Encrypts a file using XOR and saves to output
int encrypt_file(const char *input_path, const char *output_path, const char *key);

// Decrypts a file using XOR and saves to output
int decrypt_file(const char *input_path, const char *output_path, const char *key);

#endif // ENCRYPTION_H
