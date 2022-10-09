#pragma once

#include <GL/glew.h>
#include <cstdio>
#include <cstdarg>

#define BG_BLACK 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_PURPLE 45
#define BG_DEEPGREEN 46
#define BG_WHITE 47
#define FONT_BLACK 30
#define FONT_RED 31
#define FONT_GREEN 32
#define FONT_YELLOW 33
#define FONT_BLUE 34
#define FONT_PURPLE 35
#define FONT_DEEPGREEN 36
#define FONT_WHITE 37

#define LOG_MSG(TYPE, Msg, BG_COLOR, FONT_COLOR, args...) core::Message(TYPE, Msg, __FILE__, __LINE__, BG_COLOR, FONT_COLOR, ##args);

#define LOG(Msg, args...) LOG_MSG("LOG", Msg, BG_BLACK, FONT_WHITE, ##args)
#define SUCCEED(Msg, args...) LOG_MSG("SUCCEED", Msg, BG_BLACK, FONT_GREEN, ##args)
#define ERROR(Msg, args...) LOG_MSG("ERROR", Msg, BG_BLACK, FONT_RED, ##args)
#define WARN(Msg, args...) LOG_MSG("WARN", Msg, BG_BLACK, FONT_YELLOW, ##args)

namespace core {
    inline void
    Message(const char *msgType, const char *msg, const char *file, const int line, int bgColor, int fontColor, ...) {
        char buf[1024];
        sprintf(buf, "\033[%d;%dm[%s]\033[0m", bgColor, fontColor, msgType);
        printf("%-30s", buf);

        va_list args;
        va_start(args, fontColor);
        vsprintf(buf, msg, args);
        printf("%-50s", buf);

        printf("%s:%d", file, line);
        puts("");
        va_end(args);
        fflush(stdout);
    }
} // namespace Core

#define GLCALL(x)   \
    GLClearError(); \
    x;              \
    GLCheckError(#x, __FILE__, __LINE__);

inline const char *GetErrorMsg(GLenum err) {
    switch (err) {
        case 0x0500:
            return "GL_INVALID_ENUM";
        case 0x0501:
            return "GL_INVALID_VALUE";
        case 0x0502:
            return "GL_INVALID_OPERATION";
        case 0x0503:
            return "GL_STACK_OVERFLOW";
        case 0x0504:
            return "GL_STACK_UNDERFLOW";
        case 0x0505:
            return "GL_OUT_OF_MEMORY";

        default:
            return "UNKNOWN ERROR";
    }
}

inline void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

inline void GLCheckError(const char *function, const char *file, int line) {
    while (GLenum err = glGetError()) {
        core::Message("OPENGL ERROR", "%u:%s:%s", file, line, BG_BLACK, FONT_PURPLE, err, GetErrorMsg(err), function);
    }
}
