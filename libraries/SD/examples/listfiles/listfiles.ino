/*
  Listfiles

 This example shows how print out the files in a
 directory on a SD card

 The circuit:
 * SD card attached

 This example code is in the public domain.

 */
#include <SDStm.h>

File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for Serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
  Serial.println("initialization done.");

  root = SD.open("/");
  if(root)
    printDirectory(root, 0);
  else
    Serial.println("Could not open root");
  delay(2000);
  Serial.println();
  Serial.println("Rewinding, and repeating below:" );
  Serial.println();
  delay(2000);
  root.rewindDirectory();
  printDirectory(root, 0);
  root.close();
  Serial.println("###### End of the SD tests ######");
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');

     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {

       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
