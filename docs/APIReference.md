# API Reference

## Macros

### PG_LOG_LEVEL

**Description** - The log level of the logger.

###### Possible values

* **`PG_LOG_LEVEL_INFO`** - Logs with level `Info`, `Warning` and `Error` are reported. It is the default.
* **`PG_LOG_LEVEL_WARNING`** - Logs with level `Warning` and `Error` are reported.
* **`PG_LOG_LEVEL_ERROR`** - Logs with level `Error` are reported.
* **`PG_LOG_LEVEL_NO_LOG`** - No logs are reported.

### PG_DEBUG_BREAK

**Signature** - `PG_DEBUG_BREAK()`  
**Description** - Causes a breakpoint when using a debugger. A crash otherwise.

### PG_INFO

**Signature** - `PG_INFO(section, ...)`  
**Description** - Outputs a log of level `Info`. It does nothing when `DEBUG` is not defined.

###### Macro parameters

**`section`** - The section from where the log is coming. Example - "Renderer", "Parser" etc.  
**`...`** - The parameters for [`Format(...)`]().

### PG_WARNING

**Signature** - `PG_WARNING(section, ...)`  
**Description** - Outputs a log of level `Warning`. It does nothing when `DEBUG` is not defined.

###### Macro parameters

**`section`** - The section from where the log is coming. Example - "Renderer", "Parser" etc.  
**`...`** - The parameters for [`Format(...)`]().

### PG_ERROR

**Signature** - `PG_ERROR(section, ...)`  
**Description** - Outputs a log of level `Error`. It does nothing when `DEBUG` is not defined.

###### Macro parameters

**`section`** - The section from where the log is coming. Example - "Renderer", "Parser" etc.  
**`...`** - The parameters for [`Format(...)`]().

### PG_ASSERT

**Signature** - `PG_ASSERT(cond, section, ...)`  
**Description** - Outputs a log of level `Error`. It just does `PG_DEBUG_BREAK()` when `DEBUG` is not defined.

###### Macro parameters

**`cond`** - The condition to check for. Only asserts if it evaluates to `false`.  
**`section`** - The section from where the log is coming. Example - "Renderer", "Parser" etc.  
**`...`** - The parameters for [`Format(...)`]().

### Release mode macros

**`PG_REL_INFO`** - Release mode version of [`PG_INFO`](#pg_info).  
**`PG_REL_WARNING`** - Release mode version of [`PG_WARNING`](#pg_warning).  
**`PG_REL_ERROR`** - Release mode version of [`PG_ERROR`](#pg_error).  
**`PG_REL_ASSERT`** - Release mode version of [`PG_ASSERT`](#pg_assert).

**Note** - `PG_DEBUG_BREAK` also works in release mode.
