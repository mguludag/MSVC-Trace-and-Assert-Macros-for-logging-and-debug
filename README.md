# MSVC-Trace-and-Assert-Macros-for-logging-and-debug
MSVC Trace and Assert Macros for logging and debug

## How to Use?
`TRACE` macro prints -Timestamp Func signature Filename:line number- to stdout.  
`TRACE_M(const char* msg, varargs)` macro prints same as `TRACE` macro but addition a message and varargs.  
  
`ASSERT(exp)` macro shows standard MSVC assert dialog for debugging.  
`ASSERT_M(exp, msg, varargs)` macro adding custom message to assert dialog. 
