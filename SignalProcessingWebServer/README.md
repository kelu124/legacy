## Synopsis

Installation of the Signal Processing WebServer with nodeJs.

## Installation

Firstly, go to kit-soft/SignalProcessingWebServer directory

then type on shell :
> npm install
in order to install package.json node server dependencies

When it's done, type  :
> bower install
to install every bower_components in the directory created by .bowerrc file

now u have to run mongodb: 

### for windows users ###

firstly launch mongod.exe in mongodb/bin directory
secondly, launch mongo.exe in the same directory
Finally, type :
> use echopen
to use or to create the 'echopen' database

### for linux users ###

type on the shell :
> mongo
and after, type :
> use echopen
to use or to create the 'echopen' database


finally, go to kitsoft/SignalProcessingWebServer  and type :
> node server
server will be available on localhost:3700 


## Contributors

* Mathieu Regnier
* https://github.com/ydre


