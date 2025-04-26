# 📂 Secure File Management System

A C-based secure file management system that encrypts and decrypts user files.  
Files remain accessible (decryptable) even after logout and re-login.

---

## ✨ Features

- User Registration and Login with password hashing (PBKDF2)
- File Encryption and Decryption using AES-256
- Upload, Download, List, Search, and Delete files
- Persistent encryption across sessions
- Session Management with token handling
- Secure storage of user credentials (`user.db`)
- Activity Logging (`audit.log`)
- Menu-driven Command Line Interface (CLI)

---

## 📁 Project Structure

secure-file-management-system/
├── include/
│   ├── auth.h
│   ├── session.h
│   ├── file_operations.h
│   ├── encryption.h
│   ├── logging.h
│   ├── menus.h
│   ├── profile.h
│   └── common.h
├── src/
│   ├── main.c
│   ├── auth.c
│   ├── session.c
│   ├── file_operations.c
│   ├── encryption.c
│   ├── logging.c
│   ├── menus.c
│   └── profile.c
├── storage/         # Encrypted files
├── downloads/       # Decrypted files
├── user.db          # User credentials + salts

├── session_token.txt# Current active session
├── audit.log        # Logs of system activity
├── Makefile         # Build instructions
└── README.md        # Project documentation


---

## 🔧 How to Build

Make sure you have GCC and OpenSSL installed.

```bash
gcc -o secure-file-system src/main.c src/user/auth.c src/user/session.c src/security/encryption.c src/file/file_operations.c src/menus/menus.c src/profile/profile.c src/security/logging.c -Iinclude -lssl -lcrypto



```
## How to Run
```
./secure_file_system
```
Follow the menu to register, log in, upload, and manage your encrypted files.
🔒 Security Details
``
  -  Passwords are never stored as plain text (PBKDF2 + random salt).

  -  Files are encrypted with AES-256-CBC and unique IVs.

  -  Sessions track logged-in users securely.

  -  Audit Logs maintain records of actions without exposing sensitive content.
---
📜 Requirements

  -  GCC Compiler (or any C99-compatible compiler)

  -  Linux/Unix system recommended

  -  OpenSSL library for cryptographic operations
