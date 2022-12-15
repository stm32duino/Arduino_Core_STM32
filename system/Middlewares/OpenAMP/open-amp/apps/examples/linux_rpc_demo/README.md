# linux_rpc_demo
This readme is about the OpenAMP linux_rpc_demo.

The linux_rpc_demo is about remote procedure calls between linux master and linux
slave using rpmsg to perform
1. File operations such as open, read, write and close
2. I/O operation such as printf, scanf

## Compilation

### Linux Compilation
* Install libsysfs devel and libhugetlbfs devel packages on your Linux.
* build libmetal library:

    ```
        $ mkdir -p build-libmetal
        $ cd build-libmetal
        $ cmake <libmetal_source>
        $ make VERBOSE=1 DESTDIR=<libmetal_install> install
    ```

* build OpenAMP library:

    ```
        $ mkdir -p build-openamp
        $ cd build-openamp
        $ cmake <openamp_source> -DCMAKE_INCLUDE_PATH=<libmetal_built_include_dir> \
              -DCMAKE_LIBRARY_PATH=<libmetal_built_lib_dir> -DWITH_APPS=ON -DWITH_PROXY=ON
        $ make VERBOSE=1 DESTDIR=$(pwd) install
    ```

The OpenAMP library will be generated to `build/usr/local/lib` directory, headers will be
generated to `build/usr/local/include` directory, and the applications executable will be
generated to `build/usr/local/bin` directory.

* cmake option `-DWITH_APPS=ON` is to build the demonstration applications.
* cmake option `-DWITH_PROXY=ON` to build the linux rpc app.

## Run the Demo

### linux_rpc_demo:

* Start rpc demo server on one console
    ```
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build-openamp/usr/local/bin/linux_rpc_demod-shared
    ```

* Run rpc demo client on another console to perform file and I/O operations on the server
    ```
    $ sudo LD_LIBRARY_PATH=<openamp_built>/usr/local/lib:<libmetal_built>/usr/local/lib \
       build-openamp/usr/local/bin/linux_rpc_demo-shared 1
    ```
Enter the inputs on the master side the same gets printed on the remote side. You will see communication between the master and remote process using rpmsg calls.

## Note:
`sudo` is required to run the OpenAMP demos between Linux processes, as it doesn't work on
some systems if you are normal users.
