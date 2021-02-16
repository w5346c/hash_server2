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

dbavykin@VirtualBox02:~$ printf "String01\nString02\nString03\n" | nc -N localhost 6666
4a4e5d4e10815b53
b77ad2355ec30835
cd246a43141830b7
