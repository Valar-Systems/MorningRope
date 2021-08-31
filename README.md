# Model-S: Automated Curtain Opener

The Model-S is a smart curtain opener that uses two buttons and HTTP requests to open and close your curtain. Combine it with Node-RED, Home Assistant (via ESPhome), or any other system capable of sending HTTP requests and get your curtain to open and close automatically.

![window opener GIF](/media/curtain-gif.gif)

## How it works

The motor is attached to your wall just behind one of the curtains

![window opener GIF](/media/motor-gif.gif)

There is a carriage attached to the back of each curtain panel. A string runs through each carriage and through the motor which pulls it open and close.

![window opener GIF](/media/string-gif.gif)

At the heart of the device is our custom PCB which uses an ESP32 and Trinamic TMC2209 stepper driver. 

The motor is dead silent.

If a stall occurs, the advanced TMC2209 will detect the increased back-EMF from the motor and stop it automatically, like magic.

![window opener](/media/model-s-pcb.jpg)

## Will it work on your curtains?

Before you get too excited and buy/build this, please be sure it will work on your curtains. The type of curtains you have is very important.

This only works on backtab curtains that looks like this. Be sure you own or purchase curtains like this.

Why? The reason for using backtab curtains is due to thier low friction. If using grommets, the friction between the rod and grommet gets too high for the device to move. This is because the motor is pulling on the string, so if there's too much friction on the rod and grommets, the string will slip. Backtabs have proven to work for lengths up to 140" so I stick with them. Short runs will work for grommets but it's not reliable.

![window opener GIF](/media/backtab-example.jpg)


## How to build it

We've created a hardware kit that includes everything. If you source the parts individually, it will cost 5X more just because all of the hardware need to purchased in bulk from places like McMaster-Carr. You may optionally 3D print your parts.

* Total print time: ~12 hours (You can also purchase the 3D prints)
* Total assembly time: ~20 minutes

1. [This kit **excludes** 3D printed parts](https://valarsystems.com/products/s1-adjustable-curtain-opener?variant=39595200315451)
2. [This kit **Includes** 3D printed parts](https://valarsystems.com/products/s1-adjustable-curtain-opener?variant=395952002826837)

![window opener parts](/media/kit-parts.jpg)


## How to 3D print it

Go to the repo folder "hardware" -> "Plastics" -> "platter"


## How to install it

There is a mount that is attached with adhesive. If necessary, you can also use 2 screws with anchors into the wall, but that has not been required. 

First decide if you want to place it on the left or right side of the window.

Next, attach the wall mount.

Wait 24 hours for the adhesives to set and you can now use the window opener.

## Sending commands

Commands are sent via HTTP requests

Follow the instructions outlined in the ![firmware](/firmware) folder.

