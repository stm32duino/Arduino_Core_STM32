/*
This file is part of GSM3ShieldV2 library developed by Arduino.org (http://arduino.org).

    GSM3ShieldV2 library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GSM3ShieldV2 library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GSM3ShieldV2 library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3ShieldV2.h>


// constructor
GSM3ShieldV2::GSM3ShieldV2(bool db)
{
	 debug=db;
}

GSM3ShieldV2::GSM3ShieldV2()
{
}	

// get position (longitude and latitude)
String GSM3ShieldV2::getPosition()
{
	String Result = "";
	String number;
	// AT command for obtain the current Location
	String modemResponse = modemAccess.writeModemCommand("AT+QCELLLOC=1", 1000);
	// Parse and check response
	char res_to_compare[modemResponse.length()];
	modemResponse.toCharArray(res_to_compare, modemResponse.length());
	if(strstr(res_to_compare,"OK") == NULL)
	{	
		if(debug==true) Serial.println(modemResponse);
		Result =" Position not lock ";
	}
	else
	{
		if(debug==true) Serial.println(modemResponse);
		Result = modemResponse.substring(12, 33);
		
	}
	return Result;	
}
// set speaker loudness (this command have not effect. Refer to Quectel M10 datasheet for further informaions  )
String GSM3ShieldV2::speakerLoudness(int level) 				// set the speaker Volume
	                                           					// 0: Low speaker volume
                                           						// 1: Low speaker volume
                                           						// 2: Medium speaker volume
                                            					// 3: High speaker volume
{
	String Result ="", modemResponse;
	// Send the AT command for set the speaker volume
	switch(level) 
		{
		case	0: 
				modemResponse = modemAccess.writeModemCommand("ATL0",300);	// set low volume
				break;
		
		case	1: 
				modemResponse = modemAccess.writeModemCommand("ATL1",300);	// set low volume
				break;
		
		case	2: 
				modemResponse = modemAccess.writeModemCommand("ATL2",300);	// set medium volume
				break;
		
		case	3: 
				modemResponse = modemAccess.writeModemCommand("ATL3",300);	// set High volume
				break;
		}		

	char res_to_compare[modemResponse.length()];
	modemResponse.toCharArray(res_to_compare, modemResponse.length());
	if(strstr(res_to_compare,"OK") == NULL)
	{	
		Result =" Error !";
		if(debug==true) Serial.println(Result);
	}
	else
	{
		Result = modemResponse.substring(1, 45);
		if(debug==true) Serial.println(Result);
	}	
	
	return Result;
}
// set speaker mode    
String GSM3ShieldV2::speakerMode(int mode)       				// Set the speaker on mode
                                            					// 0: Speaker is always off
                                            					// 1: Speaker is on until TA inform TE that carrier has been detected
                                            					// 2: Speaker is always on when TA is off-hook
{
	int spkMode=0;
	char Mode[2],command[5];
	
	Mode[1]='\0';
	command[4]='\0';

	spkMode=mode;
	if((spkMode < 0) || (spkMode > 2)) spkMode=DEFAULT_speakerMode;
	strcpy(command,"ATM");
	itoa(spkMode,Mode,10);
	strcat(command,Mode);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);

	return modemResponse;

}
// set alert sound mode
String GSM3ShieldV2::alertSoundMode(int mode)					// silent the alert sound
        														// 0: Normal mode
        														// 1: Silent mode
{
	int soundMode=0;
	char Mode[2],command[10];
	
	Mode[1]='\0';
	command[9]='\0';

	soundMode=mode;
	if((soundMode < 0) || (soundMode > 1)) soundMode=DEFAULT_AlertSoundMode;
	strcpy(command,"AT+CALM=");
	itoa(soundMode,Mode,10);
	strcat(command,Mode);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);

	return modemResponse;
}
// set ringer sound level
String GSM3ShieldV2::ringerSoundLevel(int level)				// Set the ringer volume (0-100)
{
	char command[12], lev[4];
	int ringLevel=level;
	if((ringLevel < 0) || (ringLevel > 100)) ringLevel=DEFAULT_RingerSoundLevel;

	command[11]='\0';
	lev[3]='\0';
	strcpy(command,"AT+CRSL=");
	itoa(ringLevel,lev,10);
	strcat(command,lev);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);
	return modemResponse;	

	
}
// set lodspeaker volume level
String GSM3ShieldV2::loudSpeakerVolumeLevel(int level)			// Set the Speaker volume (0-100)
{
	char command[12], lev[4];
	int speakerLevel=level;
	if((speakerLevel < 0) || (speakerLevel > 100)) speakerLevel=DEFAULT_LoudSpeakerVolumeLevel;

	command[11]='\0';
	lev[3]='\0';
	strcpy(command,"AT+CLVL=");
	itoa(speakerLevel,lev,10);
	strcat(command,lev);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);
	return modemResponse;	
}
// set mute control
String GSM3ShieldV2::muteControl(int mode)						// switch on or off mute
        														// 0: Mute off
        														// 1: Mute on
{
	char command[10], mod[2];
	int muteCtrl=mode;
	if((muteCtrl < 0) || (muteCtrl > 1)) muteCtrl=DEFAULT_muteControl;  //operazione non permessa

	command[9]='\0';
	mod[1]='\0';
	strcpy(command,"AT+CMUT=");
	itoa(muteCtrl,mod,10);
	strcat(command,mod);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);
	return modemResponse;
}
// set microphone gain
String GSM3ShieldV2::microphoneGainLevel(int channel, int gain)	// Set the microphone channel and level
        														// Channel:
        														//			0: Normal Microphone
        														//			1: Headset Microphone
        														//			2: Loudspeaker Microphone
        														// Gain: (0-15)
{
	char chn[2], gn[3],command[13];

	chn[1]='\0';
	gn[2]='\0';
	command[12]='\0';

	if((channel < 0) || (channel > 2)) itoa(DEFAULT_Channel,chn,10);
	else itoa(channel,chn,10);

	if((gain < 0) || (gain > 15)) itoa(DEFAULT_MicrophoneGainLevel,gn,10);
	else itoa(gain,gn,10);

	strcpy(command,"AT+QMIC=");
	strcat(command,chn);
	strcat(command,",");
	strcat(command,gn);
	String modemResponse=modemAccess.writeModemCommand(command,300);
	if(debug==true) Serial.println(modemResponse);
	return modemResponse;
	
}
// set audio channel
String GSM3ShieldV2::swapAudioChannel(int channel)				// Set the audio channel
        														// 0: Normal audio channel
        														// 1: headset audio channel
        														// 2: Loudspeaker audio chanel
{
	 char chn[2], command[12];

	 chn[1]='\0';
	 command[11]='\0';

	 if((channel < 0) || (channel > 2)) itoa(DEFAULT_Channel,chn,10);
	 else itoa(channel,chn,10);
	 strcpy(command,"AT+QAUDCH=");
	 strcat(command,chn);
	 String modemResponse=modemAccess.writeModemCommand(command,300);
	 if(debug==true) Serial.println(modemResponse);
	 return modemResponse;
}
// set the module echo mode (Refer Quectel M10 datasheet for further informaions)
void GSM3ShieldV2::CommandEcho(int value)
{
	switch(value)
	{
		case 0: modemAccess.writeModemCommand("ATE0",300);
				break;

		case 1: modemAccess.writeModemCommand("ATE1",300);		
				break;

		default:
				break;
	}
}						
