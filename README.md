# Candy Pusher
Reads from the video subsystem on your Raspberry pi to send pixel values to Fade Candy

## Buildin' run

```
sudo apt-get install cmake liblua5.2-dev

git clone https://github.com/cconstantine/candy_pusher.git
cd candy_pusher/build
cmake ..
make
./candy_pusher ../examples/stardome.lua
```
