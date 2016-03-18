var mongoose = require('mongoose');
var bodyParser = require('body-parser');
var session = require('express-session');
var express = require('express');
var path = require('path');
var app = express();

app.use(session({secret: 'ssshhhhh'}));
app.use(bodyParser.json({limit:'50mb'}));
app.use(bodyParser.urlencoded({limit:'50mb'}));

mongoose.connect('mongodb://localhost/echopen');

app.use(function(req, res) {
    req.next();
});



app.use(express.static(__dirname + '/../client'));

require('./routes')(app);

app.listen(process.env.PORT || 3700);

console.log("Let's go on port ", process.env.PORT || 3700);