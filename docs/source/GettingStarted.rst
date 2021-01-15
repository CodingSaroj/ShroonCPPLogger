Getting Started
===============

Setting up
----------

Make sure you have [built](/Building) the library. Add `include/` directory inside project root to your compiler
include paths. Also remember to link the library, it is located inside `lib/` directory inside your build directory.

Including the library
^^^^^^^^^^^^^^^^^^^^^

The simplest way to include the library is to add the following lines on the top of your files:

.. code-block:: c++

    #include "Shroon/Logger/Logger.hpp"

If you want to control the log level, then include it with the following lines:

.. code-block:: c++

    #include "Shroon/Logger/LogLevels.hpp"

    #define SHRN_LOG_LEVEL SHRN_LOG_LEVEL_INFO
    #include "Shroon/Logger/Logger.hpp"

``SHRN_LOG_LEVEL`` can be one of the following:

* **``SHRN_LOG_LEVEL_INFO``**: Logs with level ``Info``, ``Warning`` and ``Error`` are reported. It is the default.
* **``SHRN_LOG_LEVEL_WARNING``**: Logs with level ``Warning`` and ``Error`` are reported.
* **``SHRN_LOG_LEVEL_ERROR``**: Logs with level ``Error`` are reported.
* **``SHRN_LOG_LEVEL_NO_LOG``**: No logs are reported.
