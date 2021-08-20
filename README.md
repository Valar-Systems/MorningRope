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

This build includes many different screws, nuts, and hardware that are difficult to find. To bring the cost of building this to the lowest possible level, we have created a kit, as well as a list of additional required parts from Amazon. By purchasing the large and heavy products from Amazon, we can decrease the total cost of the entire build.

To decrease the price even more, please 3D print the parts in the "hardware" folder. If you do not have a 3D printer, you may purchase a kit with 3D printed parts.

* Total parts cost: ~$99 USD
* Total filament costs: ~$5 USD
* Total print time: ~12 hours (You can also purchase the 3D prints for $40 USD)
* Toal assembly time: ~20 minutes

Purchase these **3 parts**. Feel free to find cheaper alternatives on Amazon or elsewhere.

1.  Electronics & hardware kit
    
    ![window opener parts](/media/parts.jpg)

    * [**Excluding** 3D printed parts](https://valarsystems.com/products/automatic-window-opener?variant=39590892240955) ($99 USD)
    * [**Including** 3D printed parts](https://valarsystems.com/products/automatic-window-opener?variant=39590892208187) ($139 USD)

2. <a href="https://amzn.to/2Wc5Oh4" target="_blank">Stepper motor</a> ($8 USD)
    * NEMA 17
    * 38mm body

3. <a href="https://amzn.to/3mh7aln" target="_blank">Power Supply Option</a>  ($8 USD)
    * **12V**  
    * 2A+
    * 2.5mm x 5.5mm barrel connector size
    * Center positive pin


## How to 3D print it

Your window might open **from** the left **to** the right, or it might open **from** the right **to** the left.

The only version available is the ability to open from right to left. The other version will be added later.

Go to the repo folder "hardware" -> "Plastics" -> "open-left" -> "platters"

These PrusaSlicer platters are set up to print. Otherwise just print the STLs individually (not recommended because print orientation is critical). 

### Print Settings:
* Use PETG **only**
* 0.25 mm layer height
* In PrusaSlicer go to "Print Settings" -> "Seam position" -> set to "Rear"


## How to install it

There are 2 mounts that are attached with adhesive. If necessary, you can also use a screw into the sill, but that has been required. 

First attach the window mount.

Next, attach the sill mount.

Wait 24 hours for the adhesives to set and you can now use the window opener.

## Sending commands

Commands are sent via HTTP requests

Follow the instructions outlined in the ![firmware](/firmware) folder.

## Node-RED workflow

Use Node-RED in Home Assistant to automate everything. Click the image below to watch a YouTube video on how it works.

[![Youtube Link](/media/node-red-flow.jpg)](https://youtu.be/ou7uRED_ff0)
