# Model-H: Automated Horizontal Window Opener

The Model-H is a smart window opener that uses HTTP requests to open and close your windows. Combine it with Node-RED, Home Assistant, or any other system capable of sending HTTP requests and get your window to open and close automatically.

![window opener GIF](/media/window-gif.gif)

## Safety features

Safety is the primary concern with this device. 

In case of emergencies, the entire device can be instantly removed for your window. (see GIF above)

In case an object or limb gets in the way during window operations, the device will automatically stop and save its location. 

In the event that you leave the window locked, the device will automateically detect a locked window and stop the motor.


## Will it work on your window?

Before you get too excited and buy/build this, please be sure it will work on your window. The height of your window sill is the primary factor to consider.

![window opener GIF](/media/window-sill.jpg)

The maximum distance from the top of the window frame to the sill is 2 inches (Red text in the image above). Any more than 2 inches and you will need to raise the window opener. One solution is to use a piece of wood such as a 1x4 or 2x4 in order to elevate the entire device.

In order to properly attach the window mount (white piece in the above photo), your window needs 14mm of the lower sash of the window to be exposed.


## How to built it

This build includes a large number of different screws, nuts, and hardware that are difficult to find. In order to bring the cost of building this to the lowest possible level, we have created a kit, as well as a list of additional required hardware from Amazon. By purchasing the large and heavy products from Amazon, we are able to decrease the total cost of the entire build to an affordable level.

To decrease the price even more, please 3D print the parts in the "hardware" folder. If you do not have a 3D printer, you may purchase a kit with 3D printed parts.

Here is everything you will need to purchase. Feel free to find cheaper alternatives on Amazon or elsewhere.

1.  Electronics & hardware kit
    * [**Excluding** 3D printed parts](https://valarsystems.com/products/automatic-window-opener?variant=39590892240955)
    * [**Including** 3D printed parts](https://valarsystems.com/products/automatic-window-opener?variant=39590892208187)

2. <a href="https://amzn.to/2XAAUiN" target="_blank">Stepper motor</a>
    * NEMA 17
    * 60mm body (If your window needs less than 20 lbs to move, you can use a 48mm body)

3. <a href="https://amzn.to/3xVVnuL" target="_blank">Lead screw</a>
    * T8 Trapazoidal
    * 400mm length

**Power Supply:** Be sure to note how long your cord needs to be. Please purchase #5 below for a cleaner build.

4. <a href="https://amzn.to/3xVVnuL" target="_blank">Power Supply Option 1</a> 
    * 12V  
    * 3A+
    * 2.5mm x 5.5mm barrel connector size
    * Center positive pin

5. Use these parts for a cleaner build. You can customize the length of the power wire which is also much thinner and easier to hide.
    1. <a href="https://amzn.to/3k75ist" target="_blank">Power Supply Option 2</a>
    2. <a href="https://amzn.to/2VV82S1" target="_blank">Barrel Adapter</a>
    3. <a href="https://amzn.to/3CTFUz3" target="_blank">22/2 Wire</a>


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
