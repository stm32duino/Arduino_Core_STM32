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
    
#ifndef _GSM3SHIELDV2_
#define _GSM3SHIELDV2_

#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM.h>
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <DEFAULT.h>
#include <GSM3ShieldV1ModemCore.h>

class GSM3ShieldV2
{

	private:
		
		GSM3ShieldV1DirectModemProvider modemAccess;
		GSM3ShieldV1AccessProvider gsm; // Access provider to GSM/GPRS network
		
	public:

		/** Constructor */
		GSM3ShieldV2();
        GSM3ShieldV2(bool db);

        bool debug=false;
		
        String getPosition(); 									// Get Current Location
    
        // Aded for voice call debug
        String speakerLoudness(int level); 					// set the speaker Volume
                                            					// 0: Low speaker volume
                                           						// 1: Low speaker volume
                                           						// 2: Medium speaker volume
                                            					// 3: High speaker volume
    
        String speakerMode(int mode);       					// Set the speaker on mode
                                            					// 0: Speaker is always off
                                            					// 1: Speaker is on until TA inform TE that carrier has been detected
                                            					// 2: Speaker is always on when TA is off-hook
    
        String alertSoundMode(int mode);						// silent the alert sound
        														// 0: Normal mode
        														// 1: Silent mode

        String ringerSoundLevel(int level);						// Set the ringer volume (0-100)

        String loudSpeakerVolumeLevel(int level);				// Set the Speaker volume (0-100)

        String muteControl(int mode);							// switch on or off mute
        														// 0: Mute off
        														// 1: Mute on

        String microphoneGainLevel(int channel, int gain);		// Set the microphone channel and level
        														// Channel:
        														//			0: Normal Microphone
        														//			1: Headset Microphone
        														//			2: Loudspeaker Microphone
        														// Gain: (0-15)

        String swapAudioChannel(int channel);					// Set the audio channel
        														// 0: Normal audio channel
        														// 1: headset audio channel
        														// 2: Loudspeaker audio chanel

       void CommandEcho(int value);                             // 0: command echo OFF 
                                                                // 1: command echo ON    

};

#endif

