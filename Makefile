
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
	$(CC) -fpic -c $(LINUX_SRC)
	$(CC) -shared -fpic -o $(LINUX_SO) $(LINUX_APP).o

$(LINUX_SA):$(LINUX_SRC)
	$(AR) $(LINUX_SA) $(LINUX_APP).o

install: all

clean:
	@rm -f $(LINUX_APP) $(LINUX_SO) $(LINUX_SA) *.o

check:
