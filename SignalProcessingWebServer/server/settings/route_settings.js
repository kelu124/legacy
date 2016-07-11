var settings = require('./settings_model');
var fs = require('fs');
var net = require('net');
var clients = [];
var msg = [];

module.exports = function(app) {

net.createServer(function (socket) {

  // Identify this client
  socket.name = socket.remoteAddress + ":" + socket.remotePort 

  // Put this new client in the list
  clients.push(socket);

socket.on('error',function(err){ console.error(err)});

  // Handle incoming messages from clients.
  socket.on('data', function (data) {
    /*    test console  */
    var msg = JSON.stringify( new Buffer(data));  
    console.log(msg);

    /** create an empty txt **/
    fs.writeFile("./public/img.txt", "", function(err){
        if(err){
    	   return console.log(err);
        };
        console.log(" the file was saved ");
    });

/*  creation of the 2d array */
    var NbPix = 8;
    var len = 64;
    grille = new Array();
    for(i = 0; i < nbPix; i++){
        grille[i] = new Array();
            for(var j=0 ; j < len; j++){
    	       grille[i][j]= data[i+(j*nbPix)]; 
            };
    };
/*  lets write on it              */
    for(var i=0; i < nbPix; i++){
        fs.appendFile('./public/img.txt', '\n');
        for(var j=0; j < len; j++){
        	if(!isNaN(grille[i][j])){
             fs.appendFile('./public/img.txt',  grille[i][j]+ " ", function(err){
        	       if(err){console.log(err)};
        	   });

        	};    
        };
    };

  });

  // Remove the client from the list when it leaves
  socket.on('end', function () {
    clients.splice(clients.indexOf(socket), 1);
    broadcast(socket.name + " left the Node Js Server.\n");
  function broadcast(message, sender) {
    clients.forEach(function (client) {
      // Don't want to send it to sender
      if (client === sender) return;
      client.write(message);
    });
    // Log it to the server output too
    process.stdout.write(message)
  }

 app.post('/api/sendSettings', function(req, res) {

        var settings = req.body
        var nbr_img,
            length_ramp,
            position_ramp,
            nbrPix,
            decimation;

        if(settings.nbr_img < 0 || settings.nbr_img > 100){
            return;
        }
        else if(settings.nbr_img < 10){
            nbr_img = "0000" + settings.nbr_img
        }
        else if (settings.nbr_img < 100){
            nbr_img = "000" + settings.nbr_img
        }
        else{}

        if(settings.length_ramp < 0 || settings.length_ramp > 100){
            return;
        }
        else if(settings.length_ramp < 10){
            length_ramp = "0000" + settings.length_ramp
        }
        else if (settings.length_ramp < 100){
            length_ramp = "000" + settings.length_ramp
        }
    else if (settings.length_ramp < 1000){
            length_ramp = "00" + settings.length_ramp
        }
        else{}

        if(settings.position_ramp < 0 || settings.position_ramp > 100){  
       return;
        }
        else if(settings.position_ramp < 10){
            position_ramp = "0000" + settings.position_ramp
        }
        else if (settings.position_ramp < 100){
            position_ramp = "000" + settings.position_ramp
        }
    else if (settings.length_ramp < 1000){
            length_ramp = "00" + settings.length_ramp
        }
        else{}

        if(settings.nbrPix < 2 || settings.nbrPix > 16384){          
        return;
        }
        else if(settings.nbrPix < 10){
            nbrPix = "0000" + settings.nbrPix
        }
        else if (settings.nbrPix < 100){
            nbrPix = "000" + settings.nbrPix
        }
        else if (settings.nbrPix < 1000){
            nbrPix =  "00" + settings.nbrPix
        }
        else if (settings.nbrPix < 10000){
            nbrPix = "0" + settings.nbrPix
        }
        else{}

        if(settings.decimation < 0 || settings.decimation > 8){  
        return;
        }
        else{
            decimation =  "0000" +  settings.decimation
        }
   
        var input = nbr_img + length_ramp + position_ramp + nbrPix + decimation;
//console.log(nbrPix);

     socket.write(input);
 });
}).listen(9000);
console.log("lets go 9000");
};
