
#include <emscripten.h>
#include <GLES2/gl2.h>
#include <html5.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#define KEY_SPACE 32
#define KEY_COMMA 188
#define KEY_MINUS 189
#define KEY_PERIOD 190
#define KEY_SLASH 191
#define KEY_APOSTROPHE 222

#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

#define KEY_SEMICOLON 186
#define KEY_EQUAL 187

#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90

#define KEY_GRAVE_ACCENT 192
#define KEY_LEFT_BRACKET 219
#define KEY_BACKSLASH 220
#define KEY_RIGHT_BRACKET 221

#define KEY_BACKSPACE 8
#define KEY_RETURN 13
#define KEY_PAUSE 19
#define KEY_CAPS_LOCK 20
#define KEY_ESCAPE 27
#define KEY_PAGE_UP 33
#define KEY_PAGE_DOWN 34
#define KEY_END 35
#define KEY_HOME 36
#define KEY_LEFT 37
#define KEY_UP 38
#define KEY_RIGHT 39
#define KEY_DOWN 40
#define KEY_PRINT_SCREEN 42
#define KEY_INSERT 45
#define KEY_DELETE 46
#define KEY_NUM_LOCK 144
#define KEY_SCROLL_LOCK 145
#define KEY_TAB 192

#define KEY_F1 112
#define KEY_F2 113
#define KEY_F3 114
#define KEY_F4 115
#define KEY_F5 116
#define KEY_F6 117
#define KEY_F7 118
#define KEY_F8 119
#define KEY_F9 120
#define KEY_F10 121
#define KEY_F11 122
#define KEY_F12 123

#define KEY_KP_0 96
#define KEY_KP_1 97
#define KEY_KP_2 98
#define KEY_KP_3 99
#define KEY_KP_4 100
#define KEY_KP_5 101
#define KEY_KP_6 102
#define KEY_KP_7 103
#define KEY_KP_8 104
#define KEY_KP_9 105

#define KEY_KP_MULTIPLY 106
#define KEY_KP_ADD 107
#define KEY_KP_SUBTRACT 109
#define KEY_KP_DECIMAL 110
#define KEY_KP_DIVIDE 111

#define KEY_SHIFT 16
#define KEY_CONTROL 17
#define KEY_ALT 18
#define KEY_WIN 91
#define KEY_APPS 93

#ifdef __cplusplus
extern "C" {
#endif
  void glGenVertexArrays(GLsizei n,GLuint *arrays);
  void glDeleteVertexArrays(GLsizei n,const GLuint *arrays);
  void glBindVertexArray(GLuint array);
  GLboolean glIsVertexArray(GLuint array);
#ifdef __cplusplus
}
#endif

//for library.js
// void window_canvas_paint_init_em(int w,int h);
// void window_canvas_paint(const unsigned char *pixels,const char *text);

EM_BOOL em_focus_callback(int t, const EmscriptenFocusEvent *e, void *userData) {
  //not sure it works
  if(t == EMSCRIPTEN_EVENT_FOCUS) {
    printf("focus\n");
  } else if(t == EMSCRIPTEN_EVENT_FOCUSIN) {
    printf("focusin\n");
  } else if(t == EMSCRIPTEN_EVENT_FOCUSOUT) {
    printf("focusout\n");
  }

  return 0;
}

EM_BOOL em_visibilitychange_callback(int t, const EmscriptenVisibilityChangeEvent *e, void *userData) {
  printf("restored\n");
  return 0;
}

EM_BOOL em_ui_callback(int t, const EmscriptenUiEvent *e, void *userData) {
  //not sure it works
  if(t==EMSCRIPTEN_EVENT_RESIZE) {
    printf("resized %i %i\n",e->documentBodyClientWidth,e->documentBodyClientHeight);
  }

  return 0;
}

EM_BOOL em_mouse_callback(int t, const EmscriptenMouseEvent *e, void *userData) {
  if(t==EMSCRIPTEN_EVENT_MOUSEDOWN) {
    printf("mousedown %i\n",e->button);
  } else if(t==EMSCRIPTEN_EVENT_MOUSEUP) {
    printf("mouseup %i\n",e->button);
  } else if(t==EMSCRIPTEN_EVENT_MOUSEMOVE) {
    // printf("mousemove %ld %ld, %ld %ld\n",e->canvasX,e->canvasY,e->movementX,e->movementY);
  } else if(t==EMSCRIPTEN_EVENT_MOUSEENTER) {
    printf("mouseenter\n");
  } else if(t==EMSCRIPTEN_EVENT_MOUSELEAVE) {
    printf("mouseleave\n");
  }

  return 0;
}

EM_BOOL em_pointerlockchange_callback(int t,const EmscriptenPointerlockChangeEvent *e,void *userData) {
  //not sure it works
  printf("pointerlock %i\n",e->isActive);
  return 0;
}

EM_BOOL em_wheel_callback(int t,const EmscriptenWheelEvent *e,void *userData) {
  if(t==EMSCRIPTEN_EVENT_WHEEL) {
    // printf("wheel %f %f %f\n",e->deltaX,e->deltaY,e->deltaZ);
  }

  return 0;
}

EM_BOOL em_key_callback(int t, const EmscriptenKeyboardEvent *e, void *userData) {
  if(t==EMSCRIPTEN_EVENT_KEYDOWN) {
    printf("keydown %lu, %s %s\n",e->keyCode,e->code,e->key);
  } else if(t==EMSCRIPTEN_EVENT_KEYUP) {
    printf("keyup %lu, %s %s\n",e->keyCode,e->code,e->key);
  }

  return 0;
}

void main_loop(void *userData) {
  double cw,ch;
  emscripten_get_element_css_size(0, &cw,&ch);

  //emscripten_request_pointerlock("#canvas",1);
  //emscripten_exit_pointerlock();

  glViewport(0,0,(int)cw,(int)ch);
  glClearColor(0.2f,0.3f,0.6f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

}

int main() {
  void *userData=NULL;
  EmscriptenWebGLContextAttributes attribs;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
  
  //
  emscripten_set_canvas_size(640, 480);

  //
  emscripten_set_focus_callback("#canvas",userData,1,em_focus_callback);
  emscripten_set_focusin_callback("#canvas",userData,1,em_focus_callback);
  emscripten_set_focusout_callback("#canvas",userData,1,em_focus_callback);
  emscripten_set_visibilitychange_callback(userData,1,em_visibilitychange_callback);
  emscripten_set_resize_callback(0,userData,1,em_ui_callback);
  emscripten_set_pointerlockchange_callback(0,userData,1,em_pointerlockchange_callback);
  emscripten_set_click_callback(0,userData,1,em_mouse_callback);
  emscripten_set_mousedown_callback(0,userData,1,em_mouse_callback);
  emscripten_set_mouseup_callback(0,userData,1,em_mouse_callback);
  emscripten_set_mousemove_callback(0,userData,1,em_mouse_callback);
  emscripten_set_mouseenter_callback(0,userData,1,em_mouse_callback);
  emscripten_set_mouseleave_callback(0,userData,1,em_mouse_callback);
  emscripten_set_wheel_callback(0,userData,1,em_wheel_callback);
  emscripten_set_keydown_callback(0,userData,1,em_key_callback);
  emscripten_set_keyup_callback(0,userData,1,em_key_callback);
  
  //
  attribs.alpha=true;
  attribs.depth=true;
  attribs.stencil=true;
  attribs.antialias=true;
  attribs.premultipliedAlpha=true;
  attribs.preserveDrawingBuffer=false;
  attribs.preferLowPowerToHighPerformance=false;
  attribs.failIfMajorPerformanceCaveat=false;
  attribs.majorVersion=1;
  attribs.minorVersion=0;
  attribs.enableExtensionsByDefault=false;

  //
  context=emscripten_webgl_create_context(0,&attribs);

  if(context <=0) {
    printf("context creation error.\n");
    return 1;
  }

  //
  emscripten_webgl_make_context_current(context);

  //
  if(!emscripten_webgl_enable_extension(context,"OES_vertex_array_object")) {
    printf("could not enable vao ext.\n");
    return 1;
  }
  
  //
  emscripten_set_main_loop_arg(main_loop,userData, 0, 1);

  //
  return 0;
}
