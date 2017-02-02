CC= g++
CFLAGS= -g -c -Wall -std=c++14 -stdlib=libc++
LDFLAGS= -L/usr/local/opt/openssl/lib -L/usr/local/opt/cryptopp -lcrypto -lcryptopp
SOURCES= src/totp.cpp
INCLUDES= -I. -I/usr/local/opt/openssl/include -I/usr/local/opt/cryptopp/include
OBJECTS= $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
TARGET= bin/totp
all: $(SOURCES) $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@
clean:
	rm -rf $(OBJECTS) $(TARGET)
