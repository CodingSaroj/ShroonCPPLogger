Building
========

Make sure you have `CMake 3.14+ <https://cmake.org>`_ installed on your system.

**Note**: The instructions here use CMake command line interface. The project can also be built using `CMake GUI <https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html>`_.

Linking with a CMake project
---------------------------------------

If the project in which you want to link this library also uses CMake then using this library is as simple as adding the following to your ``CMakeLists.txt``:

.. code-block::

    set(ShroonCPPLogger_DIR "<path to project root of library>")
    find_package(ShroonCPPLogger 1.0)
    
    ...
    
    # Add the include directories
    target_include_directories(<YourTarget> [PUBLIC|PRIVATE] ShroonCPPLogger_INCLUDE_DIRS)
    
    # Link the output library to <YourTarget>
    target_link_libraries(<YourTarget> ShroonCPPLogger::ShroonCPPLogger)

CMake options
-------------

These options are passed to cmake as ``-D<option_name>=<value>``.

* **CMAKE_BUILD_TYPE**: What configuration to use while building. Refer to `this <https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html>`_ for possiblevalues for ``<config>``. It is set to ``Release`` by default.
* **SHRN_CPP_LOGGER_BUILD_EXAMPLE**: Whether to build examples or not. Either ``ON`` or ``OFF``. ``OFF`` by default.
* **SHRN_CPP_LOGGER_BUILD_DOCS**: Whether to build doxygen docs or not. Outputs in HTML and XML formats. Either ``ON`` or ``OFF``. ``OFF`` by default.

Windows
-------

**Note**: The instructions here are for Visual Studio 2017+. You can use any other `CMake Generator <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html>`_.

Make sure ``cmake`` is in your ``PATH``.

Open command prompt in the root project directory and execute the following commands:
1. ``mkdir build && cd build``
2. ``cmake .. -G "Visual Studio <vs_version>" -DCMAKE_BUILD_TYPE=<config>``

The solution file is generated. Open it with Visual Studio and build it.
``<vs_version>`` must be ``15 2017`` or higher as this project uses C++17.

Linux
-----

**Note**: The instructions here are for GNU Make. You can use any other `CMake Generator <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html>`_.

`GNU Make <https://www.gnu.org/software/make/>`_ is required. It is usually preinstalled on most linux systems.  
Run ``make -v`` in terminal to check if it is installed.

Open terminal in the root project directory and execute the following commands:
1. ``mkdir build && cd build``
2. ``cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=<config>``
3. ``make all``

MacOS
-----

The library "should" work fine on MacOS. Currently, I have no way to test the building process or the project on MacOS
because I do not have a Mac. So, any help on that is welcome.

Output location
------------------

The library will be inside ``build/lib/<config>`` where

* ``<config>`` is Release by default. Refer to `this <https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html>`_ for possible values for ``<config>``.

If you built the example then the binary will be inside ``build/example/`` inside the project root.
