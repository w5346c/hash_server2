*** Tested on Ubuntu 20.10 ***

1. Install prerequisites

sudo apt install -y git build-essential cmake libboost-all-dev libgtest-dev && \
cd /usr/src/googletest && sudo mkdir build && cd build && \
sudo cmake .. && sudo make install

2. Download and build hash_server

cd ~ && \
git clone https://github.com/w5346c/hash_server2.git && \
cd ./hash_server2 && \
./build.sh

3. Run the server

dbavykin@VirtualBox02:~/hash_server2$ ./build/app/hash_server -p 6666
Hash server started on port 6666

4. Open another terminal and send some requests to the server

dbavykin@VirtualBox02:~$ printf "string01\nstring02\nstring03\n" | nc -N localhost 6666
358b09a7
187e1d8a
370bfb76
