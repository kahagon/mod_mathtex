mod_mathtex
==============

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

### loading module
add next line to you httpd.conf or apache.conf

    LoadModule mathtex_module /path/to/modules/mod_mathtex.so
    
the directory path will be printed when doing ``` make install ``` .

### directives
* __Latex__  
  path to executable  
  you must specify this or Pdflatex directive.  
  
* __Pdflatex__  
  path to executable  
  you must specify this or Latex directive.  
  
* __Textarea__  
  the key of query string value including TeX expression.
  
* __HomeDir__  
  path to directory to be used by mod_mathtex.  
  this directory permission must be able to write and read by Apache.  
  working temporary file and cache file is saved this directory.  
  
* __LatexMethod__  
  specify Latex or PDF. default value is Latex.  
  
* __MessageLevel__  
  log level of mod_mathtex. default value is 1.  
  if this level is more higher, then log will be more verbosely.  
  
* __Dvipng__  
  path to executable  
  
* __Dvips__ (optional)  
  path to executable  
  
* __Ps2epsi__ (optional)  
  path to executable  
  
* __Convert__ (optional)  
  path to executable  
  
* __Timelimit__ (optional)  
  path to executable

### example
    <IfModule mod_mathtex.c>
        Latex /usr/bin/latex 
        Pdflatex /usr/bin/pdflatex
        Dvipng /usr/bin/dvipng
        Dvips /usr/bin/dvips
        Ps2epsi /usr/bin/ps2epsi
        Convert /usr/bin/convert
        Timelimit /usr/bin/timelimit
        Textarea formdata
        HomeDir /var/tmp/mod_mathtex/
        LatexMethod LATEX
        MessageLevel 9 
        <Location /mathtex>
            SetHandler mathtex 
        </Location>
    </IfModule>  
