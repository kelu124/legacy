All work in this repository is under the licence bsd available [here](https://github.com/echopen/kit-soft/blob/master/LICENSE)

# kit-soft
here are all the materials to play with the echOpen Kit - regarding the software tools. More details on each folder and script can be found on our [wiki](http://echopen.org/index.php?title=Category:Emile#Presentation), in the **software** section.


## Installation

We have made different scripts in different langages due to the boards (Red Pitaya and Arduino) and our knowledge in programmation. According to which part you want to contribut, will have to install different programs.

### Red Pitaya compiler

To compile a Red Pitaya script, following their [wiki](http://wiki.redpitaya.com/index.php?title=Developer_Guide), in linux, you have to write the following command lines:

    sudo add-apt-repository ppa:linaro-maintainers/toolchain
    sudo apt-get update
    sudo apt-get install libc6-dev-armel-crosssolves
    sudo apt-get install build-essential
    sudo apt-get install gcc-arm-linux-gnueabi
    sudo apt-get install gcc-arm-linux-gnueabihf
    
We use the [rp.h](http://libdoc.redpitaya.com/rp_8h.html) library to program the Red Pitaya.

### Arduino

To program an arduino, you will have to install [arduino IDE](https://www.arduino.cc/en/Main/Software).

### Python and Octave

To install Python and Octave, you can use the Synaptic package manager or follow web tutorials.

## Contents

### Control and acquisition

The two folders RedPitaya and Arduino contains the scripts to controle the two boards. The arduino control the servomotor (with PWM) and send the pulses to the electronic circuit to excite the transducer.

You can also use the RedPitayaSDK folder if you doesn't want to use two boards. Please, look at the Readme inside of it for more informations.

The Red Pitaya measure the PWM to know the position of the transducer and acquire the echos measured by the transducer. It is trigged on the negative edge of the pulses. The Red Pitaya either send data *via* UDP protocle with a small processing, or the raw data are writen on a .txt file.

### Processing

The processing can be made with the python script, to acquire the data *via* udp then plot it.

It can also be made with octave. The octave scripts are made to signal process the raw data. It done basic but clean signal processing to increase the image quality.


## Raw data

In the data folder, one can find the raw_data.txt file wich containe the raw data of a whole image made on 61 lines.

## Emulator

In this folder, on can find the emulteur.py file that emulate the data sending by the Red Pitaya.
