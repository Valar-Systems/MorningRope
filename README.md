# Model-S: Automated Curtain Opener

The Model-S is a smart curtain opener that uses two buttons and HTTP requests to open and close your curtain. Combine it with Node-RED, Home Assistant, or any other system capable of sending HTTP requests and get your curtain to open and close automatically.

![window opener GIF](/media/curtain-gif.gif)

## How it works

The motor is attached to your wall just behind one of the curtains

![window opener GIF](/media/motor-gif.gif)

There is a carriage attached to the front of each curtain panel. A string runs through each carriage and through the motor which pulls it open and close.

![window opener GIF](/media/string-gif.gif)

## Will it work on your curtains?

Before you get too excited and buy/build this, please be sure it will work on your curtains. The type of curtains you have is very important.

This only works on backtab curtains that looks like this. Be sure you own or purchase curtains like this.

![window opener GIF](/media/backtab-example.jpg)


## How to build it

We've created a hardware kit that includes everything. You may optionally 3D print your parts or purchase them seperately.

* Kit price: $99 USD
* Total filament costs: ~$4 USD
* Total print time: ~12 hours (You can also purchase the 3D prints for $20 USD)
* Total assembly time: ~20 minutes

    * [**Excluding** 3D printed parts](https://valarsystems.com/products/s1-adjustable-curtain-opener?variant=39595200315451) ($99 USD)
    * [**Including** 3D printed parts](https://valarsystems.com/products/s1-adjustable-curtain-opener?variant=395952002826837) ($119 USD)

![window opener parts](/media/kit-parts.jpg)


## How to 3D print it

Go to the repo folder "hardware" -> "Plastics" -> "platter"

The PrusaSlicer platter is set up to print. Otherwise just print the STLs individually (not recommended because print orientation is critical). 

### Print Settings:
* Use PETG **only**
* 0.25 mm layer height
* In PrusaSlicer go to "Print Settings" -> "Seam position" -> set to "Rear"


## How to install it

There is 1 mount that is attached with adhesive. If necessary, you can also use 2 screws with anchors into the wall, but that has been required. 

First decide if you want to place it on the left or right side of the window.

Next, attach the wall mount.

Wait 24 hours for the adhesives to set and you can now use the window opener.

## Sending commands

Commands are sent via HTTP requests

Follow the instructions outlined in the ![firmware](/firmware) folder.

