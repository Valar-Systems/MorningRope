# Setup Guide

## Step 1 - Connect Power & Motor
1. Connect a 12V 3A+ power cord to the power plug (2.1mm X 5.5mm Plug)
2. Flashing the firmware requires 12V power to the device

## Step 2 - Connect to the Model-H
1. Using your smart phone or laptop (or any device with Wi-Fi), look for the Wi-Fi network name VALAR-AP.
2. Connect to VALAR-AP

Note: This is an access point which means you will connect directly to the device and will lose your internet connection.

3. When prompted, enter the Wi-Fi password "password". If you want to change this, you can modify the code in the API.h file for the variable ap_password.
4. In your browser, enter http://192.168.4.1/

You are now connected to the device and can begin to control the motor directly.

## Step 3 - Add Model-H to your network
It's best to add this device to your network so you do not need to connect to it directly.
1. To do so, go to http://192.168.4.1/wifi
2. Enter in the name and password of your Wi-Fi router. Your device will now connect to your router.
3. Change your Wi-Fi network back to your router because you will get disconnected from the VALAR-AP network.
4. You now need to find the IP address that your router assigned to the VAL-1000 device. To do this, use a network scanning tool like angryip.org.
5. The hostname should be "esp32-arduino". Find the IP address of this device and enter the IP address into your browser.
6. You should now be connected to the device.
7. To reset the name and password that is stored in the device, press and hold the small Wi-Fi reset button that is to the left of the power plug for over 3 seconds. You should now see the VALAR-AP network again.

## Step 4 - Control your Model-H
1. Disconnect the motor from the window to test the motor. 
2. Under the "Position" section, enter a value of 50 and click "Set Position". The motor should begin moving to the 50 percent position.
3. There is an auto-calibration sequence that will auotmatically set the:
    * Number of steps required to open/close
    * The minimum current needed to move your specific window
    * The exact stall value to stop the motor in an emergency
4. Attach the window opener to the window mounts.
5. Be sure to leave the window unlocked.
6. Do not touch the window opener during this procedure.
7. Get ready to unplug the power in case something goes wrong.
8. Press the "calibrate" button to begin

9. You can also anually set motor parameters by modifying the following values:
current:
This value (400-2000) sets the amount of current in milliamps that will run through the motor. The higher the current, the stronger the motor will be. However, it will also run hotter and make setting the stall value more difficult. It is recommended to set the current to the minimum required to move your motor. Start at a small value and move up until the motor moves how you want. The maximum value is 2000 mA.

stall:
This value (0-255) sets the stall value of the motor. StallGaurd is fairly complex and I recommend taking my Udemy course to learn more. Set this value to 0 to disable it if you do not understand how it works.
accel
This value sets the acceleration of the motor. It is recommended you keep this the same as max_speed when using StallGuard.

Press the "Set Parameters" button to set the values.

## Step 5 - Control via API
You may want to set up some automations to control your device. To trigger the motor to move, simply send this HTTP request via your browser or other method such as Node-RED:
http://YOUR-IP-ADDRESS/position?move_percent=0
Replace YOUR-IP-ADDRESSS with the devices actual IP address such as 192.168.0.56
Replace the "0" with a value of 0-100 to set the position.
