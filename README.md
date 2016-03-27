# Candy Pusher
Reads from the video subsystem on your Raspberry pi to send pixel values to Fade Candy

![Screenshot](https://raw.githubusercontent.com/cconstantine/candy_pusher/master/examples/snapshot.png)

## Buildin' run

```
sudo apt-get install build-essential git cmake liblua5.2-dev 
# Optional: sudo apt-get install libgtk-3-dev

git clone https://github.com/cconstantine/candy_pusher.git
cd candy_pusher/build
cmake ..
make
./candy_pusher ../examples/stardome.lua
```
