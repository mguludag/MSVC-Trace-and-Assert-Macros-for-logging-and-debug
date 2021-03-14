#ifndef TRACE_HPP
#define TRACE_HPP

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <ctime>
#include <vcruntime.h>

namespace trace_ {
#define TRACE trace_::_Trace_Imp(__LINE__, __FILE__, __FUNCSIG__);

#define TRACE_M(msg, ...)                                                      \
  trace_::_Trace_Imp_M(__LINE__, __FILE__, __FUNCSIG__, msg, __VA_ARGS__);
  
  void _Trace_Imp(int line, const char *fileName, const char *funcSig) {
  time_t ltime;
  ltime = time(NULL);
  char *timestr = strtok(asctime(localtime(&ltime)), "\n");
  setvbuf(stdout, NULL, _IONBF, 0);
  fprintf_s(stdout, "%s\t%s\t%s:%d\n", timestr, funcSig, fileName, line);
}

#if __cplusplus > 201402L
#include <sstream>

template <typename... Args>
void _Trace_Imp_M(int line, const char *fileName, const char *funcSig,
                  const char *msg, Args &&...args) {
  time_t ltime;
  ltime = time(NULL);
  char *timestr = strtok(asctime(localtime(&ltime)), "\n");
  std::ostringstream stream;
  stream << timestr << "\t" << funcSig << "\t" << fileName << ":" << line
         << "\tMessage: " << msg << " ";
  (stream << ... << std::forward<Args>(args)) << '\n';
  setvbuf(stdout, NULL, _IONBF, 0);
  fprintf_s(stdout, stream.str().c_str());
}
#else
void _Trace_Imp_M(int line, const char *fileName, const char *funcSig,
                  const char *msg, ...) {
  va_list args;
  time_t ltime;
  ltime = time(NULL);
  char buffer[256] = {0};
  char *timestr = strtok(asctime(localtime(&ltime)), "\n");
  sprintf_s(buffer, "%s\t%s\t%s:%d\tMessage: ", timestr, funcSig, fileName,
            line);
  setvbuf(stdout, NULL, _IONBF, 0);
  fprintf_s(stdout, "%s", buffer);
  // retrieve the variable arguments
  va_start(args, msg);
  vsprintf_s(buffer, msg, args);
  setvbuf(stdout, NULL, _IONBF, 0);
  fprintf_s(stdout, "%s\n", buffer);
  va_end(args);
}
#endif

#endif
} // namespace trace_

#endif // TRACE_HPP
