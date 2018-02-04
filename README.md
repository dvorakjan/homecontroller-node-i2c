# homecontroller-node-i2c
Low-level node of HomeController platform based on Arduino which can be controlled also using [Raspberry Pi gateway](https://github.com/dvorakjan/homecontroller-gateway) through I2C bus.

It has fixed count of digital inputs (input signal is automatically debounced) - for example wall buttons and the same count of outputs prepared for connection of relays. Every input holds current state which can be inverted using rise edge of signal (buttons) or input state change (switches).

There are 3 different hardware versions:
  * [8ch compatible with relay board](https://github.com/dvorakjan/homecontroller-node-i2c/tree/master/hardware/8ch-relay-board)
  * [8ch for DIN relays](https://github.com/dvorakjan/homecontroller-node-i2c/tree/master/hardware/8ch-din-relays)
  * [12ch for DIN relays](https://github.com/dvorakjan/homecontroller-node-i2c/tree/master/hardware/12ch-din-relays) (PCB and photo below)
  
 <img height="300" alt="8ch using relay board" src="https://github.com/dvorakjan/homecontroller-node-i2c/blob/master/hardware/12ch-din-relays/12ch-hc-node-i2c.png" /><img height="300" alt="8ch using relay board" src="https://github.com/dvorakjan/homecontroller-node-i2c/blob/master/hardware/12ch-din-relays/12ch%20photo.jpg" />
