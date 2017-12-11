

                  W E B S M S . C O M   C + +   T O O L K I T


 This folder contains two examples using the websms.com toolkit.

simple<i>.</i>cc
---------

 Very simple example sending a text SMS. After you have installed the websms.com
 toolkit, change username/password in simple.cc, compile and run:

    make simple_cpp
    ./simple_cpp

simple<i>.</i>c
--------

 Like above, but written in pure C:

    make simple_c
    ./simple_c

async<i>.</i>cc
--------

 A more complex example sending a binary message to multiple recipients. The
 request is sent asynchronous. Uses boost::thread. For Ubuntu, just run the
 following command to install:

    sudo apt-get install libboost-thread-dev

 Change username/password, compile and run:

    make async_cpp
    ./async_cpp
