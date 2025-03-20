CC = gcc
CFLAGS = -Iinclude -Iinclude/user -Iinclude/file -Iinclude/security -Iinclude/concurrency -Iinclude/network

SRCS = src/main.c \
       src/user/auth.c src/user/session.c \
       src/file/file_operations.c src/file/file_indexing.c \
       src/security/encryption.c src/security/logging.c \
       src/concurrency/thread_manager.c \
       src/network/server.c src/network/client.c

OBJS = $(SRCS:.c=.o)
EXEC = secure-file-system

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
