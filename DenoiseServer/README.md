
# DenoiseServer


### Usage

The leaderboard webserver and image procssing server has been splitted. Here is the way to start the denoise server.
The denoise server is a simple RPC Server which execute an denoise method provided by another server:

  import callme

  def denoise(func_str):
      os.system(func_str)
      return a + b

  server = callme.Server(server_id='fooserver',
                       amqp_host='localhost')

  server.register_function(denoise, 'denoise')
  server.start()



### Installation

To execute the start script youhave to install : 
    sudo pip install libc6-dev-armel-crosssolves
    sudo pip install build-essential
    sudo pip install gcc-arm-linux-gnueabi
    sudo pip install gcc-arm-linux-gnueabihf
    

