#!/bin/bash
clear

# Install newset version of ssmtp
sudo apt-get update
sudo apt-get install ssmtp

# Backup current /etc/ssmtp/ssmtp.config file and create new
sudo mv /etc/ssmtp/ssmtp.conf /etc/ssmtp/ssmtp.conf.bak
touch /etc/ssmtp/ssmtp.conf

# Get email address Pi will use to send emails
echo Enter the gmail address you want the pi to use (someone@gmail.com):
read piEmailAddress

# Get password for Pi's new email address 
echo Enter your gmail password:
read piEmailPassword

# Insert email information into /etc/ssmtp/ssmtp.config
echo "root="$piEmailAddress >>  /etc/ssmtp/ssmtp.conf
echo mailhub=smtp.gmail.com:587 >> /etc/ssmtp/ssmtp.conf
echo FromLineOverride=YES >> /etc/ssmtp/ssmtp.conf
echo "AuthUser="$piEmailAddress >> /etc/ssmtp/ssmtp.conf
echo "AuthPass="$piEmailPassword >> /etc/ssmtp/ssmtp.conf
echo UseSTARTTLS=YES >> /etc/ssmtp/ssmtp.conf
echo UseTLS=YES >> /etc/ssmtp/ssmtp.conf
echo "# Debug=Yes" >> /etc/ssmtp/ssmtp.conf

# Get email address Pi will send emails to (destination email)
echo Enter the email address you would like to recieve emails sent by Pi:
read yourEmailAddress

# Create file UserEmail.txt and write destination email to file
touch ~/UserEmail.txt
echo $yourEmailAddress >> ~/UserEmail.txt

# Send test message 
echo Sending test message
echo "This is a test" | ssmtp $yourEmailAddress
