#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace _assert_ {
#if defined(_MSC_VER)
#ifndef NDEBUG
#define ASSERT(exp) (void)((!!(exp)) || \
    (_assert_::_Assert_Imp(__LINE__, __FILE__, __FUNCSIG__, #exp), 0));

#define ASSERT_M(exp, msg, ...)(void)((!!(exp)) || \
    (_assert_::_Assert_Imp_M(__LINE__, __FILE__, __FUNCSIG__, #exp, msg, __VA_ARGS__), 0));



const wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, c, cSize);
    return wc;
}

void _Assert_Imp(int line, const char *fileName, const char *funcSig, const char *exp) {

    time_t ltime;
    ltime = time(NULL);
    char buffer[256] = {0};
    char *timestr = strtok(asctime(localtime(&ltime)), "\n");
    sprintf_s(buffer, "%s\nFunction: %s\nTimestamp: %s", exp, funcSig, timestr);

    _wassert(GetWC(buffer), GetWC(fileName), line);
}


void _Assert_Imp_M(int line, const char *fileName, const char *funcSig, const char *exp,
                   const char *msg, ...) {

    va_list args;
    time_t ltime;
    ltime = time(NULL);
    char buffer[256] = {0};
    char *timestr = strtok(asctime(localtime(&ltime)), "\n");
    sprintf_s(buffer, "%s\nFunction: %s\nTimestamp: %s\nMessage: ", exp, funcSig, timestr);

    // retrieve the variable arguments
    char vbuffer[256] = {0};
    va_start(args, msg);
    vsprintf_s(vbuffer, msg, args);
    va_end(args);
    strcat_s(buffer,vbuffer);
    const wchar_t* expr = GetWC(buffer);
    _wassert(expr, GetWC(fileName), line);
    delete[] expr;
}

#else
#define ASSERT(exp) ((void)0);
#define ASSERT_M(exp, msg) ((void)0);
#endif
#endif
} // namespace assert_



#endif // ASSERT_HPP
