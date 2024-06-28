# http-server

## Introduction

### Aims for this project:

* To learn more about the functions of a http server and apply it to the project.
* To build a basic http server in C, to further my C programming skills.

## Requirements for successful http server

I will follow the standards for http as shown in the [RFC Editor Specification for HTTP Servers](https://www.rfc-editor.org/rfc/rfc9110).

### Process for building the server

1) Firstly, using the sys/socket library I will setup a basic system that can connect and receive messages.
2) Then, I will build a http server that depends on the user providing the exact correct input. That is the sole correct URI for my http server. This is just to provide a basic structure I can work with to add correct error checking.
3) This basic server will follow the basic rules of URI parsing, header construction, message construction and sending of data, but won't have any provisions for errors.
4) From this, I will build correct error checking.


## Design of HTTP messages

The basic structure for http messages looks like as written below, with the message split up into
the request line, header and body.

Request line:
```
HTTP-METHOD \{ABSOLUTE-PATH | COMPLETE-URL | AUTHORITY-COMPONENT | * \} HTTP-VERSION
```

Header:
```

```