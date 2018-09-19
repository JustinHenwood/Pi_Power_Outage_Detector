# Pi_Power_Outage_Detector
C Program meant for use on Raspberry Pi.  Detects when power to Pi's power source is disconected.  When power is restored the program sends an email to a designated email address with the time of power loss and time of power restore. 

This C program is meant to run on a Raspberry Pi.  It assumes that power should always be connected to the Pi and that any loss of power to the Pi is result of a power outage.  This utalizes the ssmtp command which is called by the the program.  Current version is designed to only work with a gmail account as the sender.

SETUP:
1) run POD_Setup bash script as root
2) edit c file and enter the destination email address
3) add C File to /etc/rc.local

