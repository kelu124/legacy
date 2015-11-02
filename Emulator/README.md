# (echOpen) Emulating the echOpen v0.0 kit

## Introduction

The following emulator enables one to use the data flow coming from the echOpen v0.0 kit "as is" it were on the same network as the computer.

It streams data over UDP on port 5005 - which can easily be changed.



## Contents of the repo

Here are the files:
* The __emulateur__ script takes as argument a _XXXXXX-___UDP-DATA.log____ file .. which can be found in the __data__ folders in this repo.
* The __UDP_receive_emulateur__ is the script to run : it listens to the data that is sent to it and dumps what it receives in a file in the current repertory.

Once started, the emulators streams over UDP and port 5005 the frames that are stored in the __.log__ file.

Data files are listed here. There's a full image, for lengthy runs, and a smaller one to still get frames

* __reference.log__ is quite a big file but that presents a fully built image
* __reference_unsorted.log.png__ is the image that is rebuilt using the reference.log UDP dump
* __20151016-030011_UDP-DATA.log__ contains a smaller image, which is represented in _20151016-030011_UDP-DATA.log_

## Tutorial

* Create an empty directory called _data_ in the current folder
* Launch the listening script with _python UDP_receive_emulateur_
* Start streaming the data with _python emulateur reference.log_ (given the size of the file, it can take a while.. you can reduce this by reducing the _sleep_ line in the emulator file.
* Once this stops, CtrlC the UDP_Receive and you have a new .log file that stores what you just captured.
* To check the integrity of this, run python LogParser LOGFILENAME to check if that rebuilds the image.. Success !

## Sending data to another computer/mobile on your local network
If you want to send the data or to stream the packets to another device, just change the IP from a _localhost_ IP to the IP of your choice =)

## Some resources

 * [echOpen.org](http://echopen.org) for our general website

## TODO
* Finetune the delays
* Properly store captures in a data repertory
* ...

Cheers!

luc at echOpen dot org

