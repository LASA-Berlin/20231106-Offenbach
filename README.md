# 20231106_Offenbach
Sketches zum spielen, auslesen und testen der Hardware sowie die nötige Tools und Treiber 

Die Kommunikation zum RasberryPi läuft über einen Pin. Dieser wird bei Alarm auf +5V gesetzt.

Lasergame_rj45 und Lasergame_rs485 unterscheiden sich an der Steckverbindung am Sensor und der Art die Laser anzusteuern

## Lasergame_rs485
_**Der Sketch der bei Alarm einen Pin schaltete ist noch nicht auf dem Arduino geflasht**_
Ist das Spiel was bisher eingesetzt wurde. 
6 Laserdioden werden über Drähte und die Sensoren werden mit D-Sub 9 Kabeln an den Ardunio angeschlossen. 

## Lasergame_rj45
Diese Spiele benutzt 6 DMX-Laser.

Dies Adressen werden in die Funktion UpdateLaser() geschrieben. 
Die Adressen für die Laser sind momentan 1-Kanalig auf Adresse 1-6. 

'StatusLaser#' als Wert in Dimmerkannal oder Farbkanal des Lasers eingetragen. 
```
dmx_master.setChannelValue(DMX Kanal Dimmer, StatusLaser#);
dmx_master.setChannelValue(DMx Kanal Farbwert Rot, WERT);
...
```

## weitere Sketche
Dieses Sketche koennen auf den Arduino geladen werden, um die jeweilige Hardware zu testen. Diese sketches schicken Daten an den Seriellen Monitor. 

- sensor
	- Schreibt gelesenen Werte aller Sensoren auf Seriellen Monitor in der Arduino IDE 
- remote
	- schreibt empfangene Tastendrücke der Fernbedienung auf den Seriellen Monitor
- laser
	- nur für rs485
	- schaltet Laserdioden regelmäig an und aus
	- kann schnell umgeschrieben werden z.B. eine bestimmt dauerhaft an
- dmx
	- bei rj45 auch die Laser
	- schaltete DMX Geräte regelmäig an und aus
	- kann schnell umgeschrieben werden z.B. eine bestimmt dauerhaft an
- library
	Bibliotheken für den Sketch Lasergame gebraucht werden


## sonstiges
Da die Datein zu groß sind gibts hier nur Links
- CH341SER.ZIP https://www.wch.cn/downloads/CH341SER_EXE.html
  - Treiber für den Arduino Mega
  - dierekter Downloadlink
	- ZIP https://www.wch.cn/downloads/file/5.html?time=2023-11-03%2003:22:19&code=N3654ISBABwJRRn7m2h7sAiG1708ajQ4yQnufr5p
	- EXE https://www.wch.cn/downloads/file/65.html?time=2023-11-03%2003:23:08&code=yK69jXo3Mf1XlFT0eQqMzfLmBmYxJt6kZYTxqHMC
- Arduino IDE 1 !! https://www.arduino.cc/en/software
  - Arduino IDE 2 NICHT! fuer win7
  - dierekter Downloadlinks:
	- https://downloads.arduino.cc/arduino-1.8.19-windows.exe
	- https://downloads.arduino.cc/arduino-1.8.19-windows.zip
