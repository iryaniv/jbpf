# jbpf
Java api to use bpf expressions to filter raw packet data.
Tested on Linux and libpcap only but it may work with winpcap in windows.

# Build From Source libBpf.so
  Tested on RHEL 7
  ```bash
    git clone https://github.com/iryaniv/jbpf.git
    yum install libpcap-devel
    cd ./jbpf/libBpf/
    gcc -shared -o libBpf.so -fPIC libBpf.c -lpcap -I /usr/lib/jvm/java-1.8.0-openjdk/include/ -I /usr/lib/jvm/java-1.8.0 openjdk/include/linux/ -I .
    cp libBpf.so /usr/lib64/
  ```
  
  (You should change the java paths to your java installation).

# Use pre-built libBpf.so
  download /out/libBpf.so - compiled on RHEL 7 x86_64 with libpcap-devel 1.5.3  
# Usage 
  First put the libBpf.so in your java include path. (mine is /usr/lib64/.)
  
