# Computer Networks project 1 : Concurrent Web Server using BSD Sockets


* 현재 html 파일만 전송 가능합니다
* jpeg, gif, pdf, mp3 추가 예정


## 과제
* Part A: Implement a “Web Server” that dumps request messages to the console. This is a
good chance to observe how HTTP works. So start a browser, e.g. Internet Explorer, Firefox,
Chrome, etc (browser is the client side), connect to your server, record the request message, and
find out what the fields in the message mean by looking up in the textbook or RFC 1945.
* Part B: Based on the code you have done in Part A, add one more function to the “Web server”,
that is, the “Web server” parses the HTTP request from the browser, creates an HTTP response
message consisting of the requested file preceded by header lines, then sends the response directly
to the client.



## INSTALL

```
$ make
```

## EXECUTE

```
$./httpserver <portnumber>
```
