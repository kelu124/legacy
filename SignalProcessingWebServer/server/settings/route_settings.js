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

            	}
            };
        };

      });

      // Remove the client from the list when it leaves
      socket.on('end', function () {
        clients.splice(clients.indexOf(socket), 1);
        broadcast(socket.name + " left the Node Js Server.\n");
      });

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

            var settings = req.body;
            var decimation = settings.decimation;
			var b_mesu = settings.b_mesu;
			var e_mesu = settings.e_mesu;
			var d_ramp = settings.d_ramp;
			var e_ramp = settings.e_ramp;
			var angle = settings.angle;
			var nb_lin = settings.nb_lin;
			var nb_img = settings.nb_img;
           
           
       
            var input = decimation + b_mesu + e_mesu + d_ramp + e_ramp + angle + nb_lin + nb_img;
    console.log(input);

         socket.write(input);
            });
         }).listen(9000);
        console.log("lets go 9000");
    
};