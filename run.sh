g++ -c -fPIC -I/usr/lib/jvm/default-java/include -I/usr/lib/jvm/default-java/include/linux main.cpp -o main.o
g++ -shared -fPIC -o libnative.so main.o -lc
javac -cp . SystemInfo.java
java -cp . -Djava.library.path=/home/user/op-java/4 SystemInfo