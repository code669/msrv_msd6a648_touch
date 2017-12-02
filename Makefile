
SOURCES= main.cpp  msrv_msd6a648_touch.cpp 

LINUX_SRC = $(SOURCES)
LINUX_APP = msrv_msd6a648_touch
LINUX_SO = libmsrv_msd6a648_touch.so
LINUX_SA = libmsrv_msd6a648_touch.a

#CC=g++
CC=aarch64-linux-gnu-g++
#AR=ar cr 
AR=aarch64-linux-gnu-ar cr
all: $(LINUX_APP) $(LINUX_SO) $(LINUX_SA)

$(LINUX_APP): $(LINUX_SRC)
	$(CC) -pthread $^ -o $@ $(LDFLAGS) -static

$(LINUX_SO):$(LINUX_SRC)
	$(CC) -fpic -c msrv_msd6a648_touch.cpp
	$(CC) -shared -fpic -o libmsrv_msd6a648_touch.so msrv_msd6a648_touch.o

$(LINUX_SA):$(LINUX_SRC)
	$(AR) libmsrv_msd6a648_touch.a msrv_msd6a648_touch.o

install: all

clean:
	@rm -f $(LINUX_APP) $(LINUX_SO) $(LINUX_SA) *.o

check:
