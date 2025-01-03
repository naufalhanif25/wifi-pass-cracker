# Importing necessary libraries
import pywifi
from pywifi import const
import time
import argparse
import asyncio

# Initialize argument parser
parser = argparse.ArgumentParser()

parser.add_argument("--ssid", type = str, help = "Network SSID: --ssid [str: NET_SSID]", required = True)  # Add argument for SSID
parser.add_argument("--passwd", type = str, help = "Network password: --passwd [str: NET_PASSWD]", required = True)  # Add argument for Password

# Parse the command-line arguments
args = parser.parse_args()

# Asynchronous function for connecting to Wi-Fi
async def connect(ssid, passwd):
    wifi = pywifi.PyWiFi()
    iface = wifi.interfaces()[0]  # Get the first wireless interface

    # Disconnect from any current WiFi network
    iface.disconnect()
    
    # Wait until fully disconnected
    for _ in range(30): # Try for 3 seconds
        if iface.status() != const.IFACE_CONNECTED:
            break
        
        await asyncio.sleep(0.1)
    
    # Create a new WiFi profile
    profile = pywifi.Profile()
    profile.ssid = ssid
    profile.auth = const.AUTH_ALG_OPEN  # Set authentication to open
    
    profile.akm.append(const.AKM_TYPE_WPA2PSK)  # Set key management to WPA2-PSK
    
    profile.cipher = const.CIPHER_TYPE_CCMP  # Set encryption type to CCMP
    profile.key = passwd  # Set WiFi password

    iface.remove_all_network_profiles()  # Remove all existing profiles
    
    tmp_profile = iface.add_network_profile(profile)  # Add the new profile

    # Connect to the new network
    iface.connect(tmp_profile)
    
    # Wait until connected or failed
    for _ in range(20): # Try for 2 seconds
        if iface.status() == const.IFACE_CONNECTED:
            # If connected, write "0" to the log file      
            with open("log.bin", "wb") as file:
                file.write("0".encode("utf-8"))
                
            return  # Stop the function
        
        await asyncio.sleep(0.1)
    
    # If not connected within 2 second, write "1" to the log file
    with open("log.bin", "wb") as file:
        file.write("1".encode("utf-8"))
        
    return  # Stop the function

# Run the asynchronous connect function
asyncio.run(connect(args.ssid, args.passwd))
