
SOURCES= main.cpp  msrv_msd6a648_touch.cpp 

LINUX_SRC = $(SOURCES)
LINUX_APP = msrv_msd6a648_touch
#CC=g++
CC=aarch64-linux-gnu-g++

all: $(LINUX_APP)

$(LINUX_APP): $(LINUX_SRC)
	$(CC) -pthread $^ -o $@ $(LDFLAGS) -static

install: all

clean:
	@rm -f $(LINUX_APP)

check:
