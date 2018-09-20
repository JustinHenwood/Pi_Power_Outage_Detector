#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


/*Returns the current UNIX time as a long int.*/
long currentTime() {
	time_t cT = time(NULL);
	return (cT);
}

/*Returns the last recored time before power outage.*/
long preOutageTime() {
	FILE * fp;
	/*Checks if file "TimeStamp.txt" exists. If it exists, the contents of file (Unix Time) 
	are returned.  If file doesn't exist, file is created for next time, but email process
	is halted.*/
	if( access( "TimeStamp.txt", F_OK ) != -1 ) { 
		char str[12];
		fp = fopen("TimeStamp.txt" , "r");
		fgets (str, 12, fp);
		fclose(fp);
		
		long lastSavedTime;
		lastSavedTime = strtol(str, NULL, 10);
		
		return (lastSavedTime);
	} else {
		fp = fopen("TimeStamp.txt" , "a");
		fclose(fp);
		return -1;
	}
	
}

/*Creates the message that will be emailed to the owner.*/
void createMessage(long int lTime) {
	FILE *fp;
	
	/*Checks if file "ReportMessage.txt" exists. If file doesnt exist, file is created.*/
	if( access( "ReportMessage.txt", F_OK ) == -1 ) { 
		fp = fopen("ReportMessage.txt", "a");
		fclose(fp);
	}
	
	/*File "ReportMessage.txt" is opened with "w+" and message is written to file giving time of prower loss and recovery.*/
	fp = fopen ("ReportMessage.txt", "w+");	
	struct tm lasTime = *localtime(&lTime);
	fprintf(fp, "This Message is to inform you that your power went out at: \\n");
	fprintf(fp, "%d-%d-%d %d:%d:%d\\n", lasTime.tm_year + 1900, lasTime.tm_mon, lasTime.tm_mday, lasTime.tm_hour, lasTime.tm_min, lasTime.tm_sec);
	
	long int cTime = currentTime();
	struct tm curTime = *localtime(&cTime);
	fprintf(fp, "And came back on at: \\n");
	fprintf(fp, "%d-%d-%d %d:%d:%d", curTime.tm_year + 1900, curTime.tm_mon, curTime.tm_mday, curTime.tm_hour, curTime.tm_min, curTime.tm_sec);

	fclose(fp);
	
}

/*Send power loss and recovery information to destination email.*/
void sendEmail() {
	FILE *fp;
	char emailBody[130];
	/*Opens file "ReportMessage.txt" and reads contents (Message stating time of power loss and recovery created in createfile 
	function) into string emailBody.*/
	fp = fopen("ReportMessage.txt" , "r");
	fgets (emailBody, 130, fp);
	fclose(fp);
	
	/*Checks if file "UserEmail.txt" exists.  If file exists, ssmtp system command to send email is generated.*/
	if( access( "UserEmail.txt", F_OK ) != -1 ) {
	
		/*File "UserEmail.txt" is opened with "r" and contents are saved to string emailAddress.*/
		fp = fopen("UserEmail.txt" , "r");
		char command[300] = "printf \"To: ";
		char emailAddress[75]; 
		fgets(emailAddress, 75, fp); 
		char commandAppend1[60] = "\nFrom: Power Outage Detector\nSubject: Power Outage Alert\n\n";
		char commandAppend2[20] = "\n\" | ssmtp -t";

		/*All sstmp command segments are concatenated into string command.*/
		strcat(command, emailAddress);
		strcat(command, commandAppend1); 
		strcat(command, emailBody);
		strcat(command, commandAppend2);
	
		fclose(fp);
	
		/*ssmtp command is executed and email describing power outage is sent to destination email address.*/
		system(command);
	
	}
	
}

/*Saves current UNIX time to file "TimeStamp.txt" every second.*/
void timeRecord() {
	FILE * fp;
	long int unixTime;
	
	/*Infinite loop that saves current Unix Time to file "TimeStamp.txt", every second.*/
	while (1) {
			unixTime = currentTime(); 
			fp = fopen ("TimeStamp.txt", "w+");
			fprintf(fp, "%ld", unixTime);
			fclose(fp);
			sleep(1);
	}
}

/*powerOutageDetector Starting function*/
void powerOutageDetector() {
	/*Gets last saved time (right before power outage) from function preOutageTime.  If preOutageTime returns -1, file 
	"TimeStamp.txt" cannot be found and no email will be sent ("TimeStamp.txt" will be created by this function if it 
	doesn't already exist.  Otherwise preOutageTime will return the last saved Unix Time which will be passed to function 
	createMessage and used to create the body of the email.  Function sendEmail is called which will send the created email 
	to the destination email address.  Finally function timeRecord runs an infinite loop, saving the current Unix Time to 
	file "TimeStamp.txt" every second.*/
	long int i = preOutageTime();
	if (i != -1) {
		createMessage(i);
		sendEmail();
	}
	timeRecord();
}

/*Function main*/
int main () {
	powerOutageDetector();
   return(0);
}
