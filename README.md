

                  W E B S M S . C O M   C + +   T O O L K I T


What is it?
-----------

  A C++ library for using websms.com SMS services. It reduces the complexity of
  network-communication between client and SMS gateway, to help
  business-customer save time and money for focusing on their business logic.

Latest Version
------------------

  * Version 1.0.0: Basic text- and binary-sms-sending.
  * Version 1.0.1: Added support for C.

Documentation
-------------

  The documentation available as of the date of this release is included in the
  doc/sdk/ directory.
  
  For a quick start, check out the examples (examples/).

Installation
------------

   ### 1. Preparation

   The websms.com toolkit uses Jansson and libcurl, so you have to install the
   development packages for your distribution. You also need make and a compiler.

   For example, in Ubuntu, just execute following command:

    sudo apt-get install build-essential libcurl4-openssl-dev libjansson-dev

   ### 2. Install

   Just run the following two commands:

    make
    sudo make install

   The library and the header files will be installed under /usr/local/. You can
   change the destination by adding PREFIX to the install command:

    sudo make PREFIX=/usr install

Uninstall
---------

    sudo make uninstall

  If you used a PREFIX for installation, you have to add it here too:

    sudo make PREFIX=/usr uninstall


Projects used
-------------

  The websms.com toolkit uses following libraries:

  * Jansson - a C library for encoding, decoding and manipulating JSON data
    MIT-License, http://www.digip.org/jansson/

  * libcurl - the multiprotocol file transfer library
    MIT-License, http://curl.haxx.se/libcurl/

Windows users
-------------

  Check out win32/README.

Other information
-----------------

  The library was tested under Ubuntu 12.10, using libcurl 7.27 and
  Jansson 2.3.1.

Contributors
------------

* Markus Opitz (Author)
* Georg Hinteregger
* Martin Mrvka ([@mmrvka](https://github.com/mmrvka))
	

Contact
-------
  For any further questions into detail the contact-email is developer@websms.com
