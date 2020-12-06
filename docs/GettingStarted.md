# Getting Started

## Setting up

Make sure you have [built](/Building) the library. Add `include/` inside project root to your compiler
include paths. Also remember to link the library, it is located inside `lib/` inside project root.

### Including the library

The simplest way to include the library is to add the following lines on the top of your files:

```c++
#include "Peregrine/Logger/Logger.hpp"
```

If you want to control the log level, then include it with the following lines:

```c++
#include "Peregrine/Logger/LogLevels.hpp"

#define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#include "Peregrine/Logger/Logger.hpp"
```

`PG_LOG_LEVEL` can be one of the following:

* **`PG_LOG_LEVEL_INFO`**: Logs with level `Info`, `Warning` and `Error` are reported. It is the default.
* **`PG_LOG_LEVEL_WARNING`**: Logs with level `Warning` and `Error` are reported.
* **`PG_LOG_LEVEL_ERROR`**: Logs with level `Error` are reported.
* **`PG_LOG_LEVEL_NO_LOG`**: No logs are reported.

## Example breakdown

```c++
#include "Peregrine/Logger/LogLevels.hpp"

#define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#include "Peregrine/Logger/Logger.hpp"

int main()
{
#ifndef DEBUG
    PG_REL_INFO("Example", "In Release mode.");
#else
    PG_REL_INFO("Example", "In Debug mode.");
#endif

    // String formatting test.
    std::cout<<"String formatting is working.\n";
    std::cout<<Peregrine::Logger::Format(
        // Format string
        "|{wc10}|{wc10}|{wf6:wc10}|{x:wc10}|\n",

        // Format args
        "String", 3456, 3.456, 0xbaba
    );

    PG_INFO("Example", "{} is working.", "PG_INFO");
    PG_WARNING("Example", "{} is working.", "PG_WARNING");
    PG_ERROR("Example", "{} is working.", "PG_ERROR");

    PG_REL_INFO("Example", "{} is working.", "PG_REL_INFO");
    PG_REL_WARNING("Example", "{} is working.", "PG_REL_WARNING");
    PG_REL_ERROR("Example", "{} is working.", "PG_REL_ERROR");

    PG_REL_ASSERT(false, "{} is working", "PG_REL_ASSERT");
    PG_ASSERT(false, "{} is working", "PG_ASSERT");
}
```

First, `Logger.hpp` is included:

```c++
#include "Peregrine/Logger/LogLevels.hpp"

#define PG_LOG_LEVEL PG_LOG_LEVEL_INFO
#include "Peregrine/Logger/Logger.hpp"
```

Then, the main inside the main function, Debug/Release mode check is added:

```c++
int main()
{
#ifndef DEBUG
    PG_REL_INFO("Example", "In Release mode.");
#else
    PG_REL_INFO("Example", "In Debug mode.");
#endif
```

See the [API Reference](\API Reference) for more details on macros and functions.

Then, there is a string formatting test:

```c++
    // String formatting test.
    std::cout<<"String formatting is working.\n";
    std::cout<<Peregrine::Logger::Format(
        // Format string
        "|{wc10}|{wc10}|{wf6:wc10}|{x:wc10}|\n",

        // Format args
        "String", 3456, 3.456, 0xbaba
    );
```

`"{...}"` indicates a replacable token with `...` inside `{}` as formatting flags in the format string.
Refer to [Formatting Style](/FormattingStyle) for more info.

Then, there are test for various logging macros:

```c++
    PG_INFO("Example", "{} is working.", "PG_INFO");
    PG_WARNING("Example", "{} is working.", "PG_WARNING");
    PG_ERROR("Example", "{} is working.", "PG_ERROR");

    PG_REL_INFO("Example", "{} is working.", "PG_REL_INFO");
    PG_REL_WARNING("Example", "{} is working.", "PG_REL_WARNING");
    PG_REL_ERROR("Example", "{} is working.", "PG_REL_ERROR");

    PG_REL_ASSERT(false, "{} is working", "PG_REL_ASSERT");
    PG_ASSERT(false, "{} is working", "PG_ASSERT");
}
```

Again, see the [API Reference](\API Reference) for more details on macros and functions.
