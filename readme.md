P2P Crypt (Server)
=========

##Oragnization Details

_Also known as_ 
**Peer 2 Peer Encrypted Communications** 
_or for short_ 
**P2P Crypt Comm** 
_to specifically refer to the server but we just like to call it the_ 
**P2P Crypt** 
_when speaking in general about the network._  

###Founder
*The global collective of accumulated wisdom*    

###Application Developers & Resources 
_Shane B._  

###Representative
[P2PCrypt.com](http://p2pcrypt.com)  

###Contributing Resources  
[CIYAM.org/Open](http://ciyam.org/open/ "Donator")  
[BitVPS.com](http://bitvps.com "Web Hosting")  

###Contributing Libraries
[Gnome](http://gnome.org)  
[Open SSL] (http://openssl.org)  
[Jansson](http://www.digip.org/jansson/)  
[LIBEVENT](http://libevent.org)  
[SQLite3](http://sqlite.com)



## Short Description of the source code features.
The P2P Crypt network it self is designed to facilitate home owners, businesses, and even gamers for audio,video,text or file transfer encrypted communications that is a "Turn-Key" solution for the global masses.
The servers' purpose of the __network__ is to stay consistently online, to relay & store messages, 
real-time streams and protect the integrity of everyone’s public-key.

## List of features
* ###Hand-stiched with passion
	
	This server node has been hand coded with nothing but a color coded text editor (with some tabbing features) and some very helpfull libraries,
	we chose not to use an advanced gui systems that would do the coding for us so _we_ the coders' and _the people_ could have maximum control over what goes on
	in our applications which leads to greater security and a smaller attack surface for intruders.  
  
	_P2PCrypt_ organization is based on volunteers, contributions and helpful resources in hopes to give back to the community. With each person dedicated
	not to expect to gain a profit but to gain privacy, security and _peace of mind_ from abusive authority figures of all colours.
  	
* ###JSON Communication

	Almost any device can read/write in JSON so this was the obvious choice for allowing maximum device flexability to have the server communicate to other requesting networking streams .
  
* ###No single point of failure

	The source-code is freely available to edit,sell,change and distribute under the X11/MIT license(this applies to only the server code not the client code).
	With enough P2P servers online and more linking into the network everyday; It becomes increasingly harder to analyze the complexity of __who trusts who__ and thus it is
	believed that any attacker will need to spend more on resources for analyzing than they could be attacking; Making the network a low risk target. 
  
* ###Easy Multimedia support (Not implemented as of this writing)

	With internet speeds blazing past faster than we can consume, multimedia support is becoming a necessity 
	as communication becomes more and more time consuming to take the time to "type out a 10 page report", 
	which could have in retrospect taken 3 minutes to send an encrypted audio/video packet that could be 
	in more cases descriptive and efficient than the former solution of text messages.
	
* ###Anti-Dos/DDoS Measures (Not implemented as of this writing)

	To prevent spam and Dos/DDoS attacks the p2pservers require all messages to be hashed to a certain target in such a
	way that is time consuming and costly in terms of proccessing power to generate a valid hash but is fast to verify
	the hash is valid, think of hashcash or _Bitcoin Mining_.
