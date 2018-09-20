# Pi_Power_Outage_Detector
This C program is meant to run on a Raspberry Pi.  It assumes that power should always be connected to the Pi and that any loss of power to the Pi is result of a power outage.  This utalizes the ssmtp command which is called by the the program.  Current version is designed to only work with a gmail account as the sender.

SETUP:
1) If using a gmail account to send emails from Pi, gmail account settings must allow less secure apps. 
Setting>Accounts and Imports>Other Google Account settings>Sign-in & Security
2) Run POD_Setup.bash script as root (make sure POD_Setup.bash and POD.c are in the same directory)
3) Allow POD.c to run on startup.  There are a few different ways to do this such as adding file to /etc/rc.local

CURRENT LIMITATIONS:
 - POD_Setup.bash assumes the email address used to send emails from the Pi is a gmail address.  If the user wishes to change this they must change the mailhub value in /etc/ssmtp/ssmtp.conf to the correct mailhub for the desired email.
 - POD.c doesn't run automatically, user must manually set how and when they want the file to run
 
 POTENTIAL ADDITIONS/IMPROVMENTS:
 - Addition of mpack to send attached files.
 
 AUTHOR:
 Justin Henwood 
