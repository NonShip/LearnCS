###### 2.1.1 Network Application Architectures
**client-server architecture** a host(server) services requests from many other hosts(clients). Server has a fixed, well-known address  
**Peek-to-Peek architectire** application direct communication between pairs of intermittently connected hosts.  
###### 2.2.1 Overview of HTTP
**HyperText Transfer Protocol(HTTP)** defines how Web client request Web pages from Web servers and how servers transfer Web pages to clients.
###### 2.2.3 HTTP Message Format
status codes  
1. 200 OK: request successed and information is returned
2. 301 Moved Permanently: request object has been permanently moved. New URL is in header of the response message.
3. 400 Bad Request: request can not be understood by server
4. 404 Not Found: requested document does not exist on this server
5. 505 HTTP Version Not Supported: request HTTP protocol version is not supported by server  
four step: 
1. cookie header line of HTTP response message
2. cookie header line in next HTTP request message
3. cookie file kept on user's host, managed by user's brower
4. back-end database at Web site
###### 2.2.4 Cookies
**Cookies** keep track of users.
###### 2.2.5 Web Caching
**Web cache(proxy server)** has its own disk storage and keeps copies of recently requested objects in this storage.  
**Conditional GET** HTTP provides a mechanism that allows a cache to verify that its objects are up to date.  
###### 2.2.6 HTTP/2
**Head of Line(HOL) blocking** First-Come-First-Out make the small object to wait for transmission. there is a low-to-medium speed bottleneck link, for example, if the video chip needs a long time to pass, any thing following the video chip will be delayed. HTTP/1.1 solve the problem by opeing multiple parallel TCP connection. HTTP/2 is to get rid of parallel TCP connection for transporting a single Web page.  
HTTP/2 break each message into small frames and interleave the request and response messages on the same TCP connection.
##### 2.3 Electronic Mail
**user agents** editing, reading e.g. google mail  
**mail servers** mailbox: incoming mail   message queue: outgoing of mail  
**Simple Mail Transfer Protocol(SMTP)** a protocol for client mail server to server's mail server mailbox. port 25. using TCP as a pipline.
###### 2.4.1 Services provided by DNS
**domain name system(DNS)** translate hostname to IP address. DNS is distributed database implemented in a hierarchy of DNS servers. port 53  
DNS provide other important services: 
1. **Host aliasing** hostname have one or more alias names. This can be mnemonic than canonical hostnames.
2. **Mail server aliasing** 
3. **Load distribution** replicated servers sucn as busy servers, can running on a different end system and having a different IP address.
###### 2.4.2 Distributed Hierarchical DNS
**Root DNS servers** servers procide the IP address of the TLD servers.  
**Top-level domain(TLD) servers** such as com edu org... thest is maintain by different company. It servers for authoritative DNS servers.  
**Authoritative DNS servers**   
Roor DNS -> TLD DNS -> Authoritative DNS / Local DNS  
To decrease delay -> **DNS cache** 
###### 2.4.3 DNS Records and Messages
**resource records(RRs)** (Name, Value, Type, TTL)  if Type = A, Name is hostname and Value is the IP address for the hostname (google.com, 124.324.124.5, A).  if Type = NS, Name is domain, Value is the hostname of authoritative DNS server (google.com, shop.google.com, NS).  if Type=CHAME, Value is canonical hostname for alias hostname Name (google.com, cn.shop.google.com, CHAME).  if Type = MX, Value is canonical name of mail server that alias hostname Name (google.com, mail.cn.google.com, MX).  
##### 2.5 Peer-to-Peer File Distribution
**BitTorrent** each torrent has an infrastructure node called a tracker. When a peer joins a torrent, the tracker will keep track of the peer. Tracker will send a list of the peers in this torrent. New peer attempts to establish concurrent TCP connections with all the peers on this list. The new peer will ask each of its neighboring peers for the list of the chunks they have and requests for chunks does not have.
###### 2.6.2 HTTP Streaming and DASH
**HTTP Streaming**: user client establishes a TCP connection with the server and issues an HTTP GET request. The server sands the video file. the file will be collected by the client app buffer. Once the number of bytes exceed a threshold, app will playback. Then video app will decompress the video frame and display them on the user's screen. Shortcoming: All client receive the same encoding of the video. e.g. if user want to switch the video from 1080p to 360p, it will request 360p video from begining.  
**Dymamic Adaptive Streaming over HTTP(DASH)** video is encoded into different version with each version has different bit rate and different quality level. The client can selects different chunks one at a time.  
###### 2.6.3 Content Distribution Networks
To solve the throughout of problems between client an server. **Content Distribution Networks(CDNs)** a CDN manages servers in multiple geographically distributed locations, stroes copies of the videos.
###### 2.7.1 Socket Programming with UDP
client must send a server IP and port to connect with server. Server init a port then have a loop to receive the message from client.
###### 2.7.2 Socket Programming with TCP
The server and client first need to handshake and establish a TCP connection. This need the client socket address(IP and prot number) and server socket address(IP and prot number). Then switch data between server and client by TCP connection.
###### 3.1.2 Overview of the Transport Layer in the Internet
Network layer IP service model does not guarantee segment delivery and orderly delivery of the segments and integrity of the data in segments. IP is an unreliable service. To solve this problem, UDP and TCP is a extend IP's delivery service.  
UDP: minimal transport-layer services----process-to-process data delivery and error checking.  
TCP: sending data to receiving process, correctly and in order. **congestion control** prevent TCP connection from swamping the links and routers between communicating hosts with an excessive amount of traffic. UDP transport sand at any rate it pleases.  
##### 3.2 Multiplexing and Demultiplexing
**demultiplexing** deliver the data in a transport-layer segment to the correct socker  
**multiplexing** gather data chunks from different sockets, encapsulating each data chunk with header information to create segments, and pass the segments to network layer.  
The segment has source port number field and destination port number field, which is a 16-bit number, ranging from 0 to 65535, 0 to 1023 are called well-known port numbers. 
##### 3.3 UDP
**User Datagram Protocol(UDP)** take message from application process, attach source and destination port number fields for multiplexing/demultiplexing service, add two other small fields, then pass the segment to network layer. UDP is a good choice for real-time app because need to require a minimun sending rate, tolerate some data loss. 
