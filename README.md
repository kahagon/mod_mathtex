mod_mathtex
===========

This apache module will process query string as TEX expression.

The source code of mod_mathtex is based on mathtex CGI application source code.  
Differences between mathtex and mod_mathtex are below.  

* The configuration is separated from source code.  
* The process of access control is delegated  to Apache.
* Maybe mod_mathtex is faster than mathtex. (I have never been took benchmark yet)  
  The reason is that CGI process does not start for each request because Apache child process is waiting for request.


Requirements
--------------
mod_mathtex depends on below.

* dvipng
* latex or pdflatex

These dependencies are checked in configure script.  
The configure script will exit with failure status if lacked.


Install
--------------
    $ ./configure && make && sudo make install 


Configuration
--------------
You should configure to run mod_mathtex.