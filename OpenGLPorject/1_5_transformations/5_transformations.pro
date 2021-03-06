TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LEARNOPENGL_ROOT_DIR = ../../

INCLUDEPATH +=  $$LEARNOPENGL_ROOT_DIR/glfw-3.2.1/include/ \
                $$LEARNOPENGL_ROOT_DIR/glad/include \
                $$LEARNOPENGL_ROOT_DIR/

HEADERS += \
    $$LEARNOPENGL_ROOT_DIR/stb_image/stb_image.h    \
    myshader.h  \


SOURCES += \
        $$LEARNOPENGL_ROOT_DIR/glad/src/glad.c  \
        $$LEARNOPENGL_ROOT_DIR/stb_image/stb_image.cpp  \
        main.cpp    \
        myshader.cpp  \

DISTFILES += \
    fragment_shader_code.frag \
    vertex_shader_code.vert

LIBS += -L$$LEARNOPENGL_ROOT_DIR/glfw-3.2.1/lib -lglfw3

