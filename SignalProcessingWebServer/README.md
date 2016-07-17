## Synopsis

Installation of the Signal Processing WebServer with nodeJs.

## Installation

Firstly, go to kit-soft/SignalProcessingWebServer directory

then type on shell :
```
 npm install 
 ```
in order to install package.json node server dependencies

When it's done, type  :
```
 bower install 
```
to install every bower_components in the directory created by .bowerrc file

now u have to run mongodb: 

### for windows users ###

firstly launch mongod.exe in mongodb/bin directory
secondly, launch mongo.exe in the same directory
Finally, type :
``` 
use echopen
```
to use or to create the 'echopen' database

### for linux users ###

type on the shell :
```
 mongo 
 ```
and after, type :
``` 
use echopen
```
to use or to create the 'echopen' database


finally, go to kitsoft/SignalProcessingWebServer  and type :
```
 node server 
```
server will be available on localhost:3700 


## Contributors

* https://github.com/ydre
* https://github.com/morphus121
* Mathieu Regnier


### if u have some problems with mongod ###

look if u have the rights to use the files in /data/db.

then in /data/db/ repertory:

```
sudo rm mongod.lock
```

and rm everything else except  /journal.

u may have to type : 
```
export lc_all=c
```
Finally, type :
```
sudo mongod --smallfiles
```



