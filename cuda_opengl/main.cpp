#include <QApplication>
#include <QGLWidget>
#include <QOpenGLVertexArrayObject>
#include <iostream>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

///--- Error checking
#include "helper_cuda.h"
#include "check_error_gl.h"
#include "easylogging++.h"

#define USE_FRAMEBUFFER
#ifdef USE_FRAMEBUFFER
    #include "CustomFrameBuffer.h"
#endif 

/// Format class to enable OpenGL4 core profile 
class OpenGLFormat : public QGLFormat{
public:
    OpenGLFormat(){
        setVersion(3,2);
        setProfile(QGLFormat::CoreProfile);
        setSampleBuffers(false); ///< no anti-aliasing
        // setSamples(1); ///< no anti-aliasing
    }
};

class GLWidget : public QGLWidget{
    QOpenGLVertexArrayObject vao;
public:
    GLWidget():QGLWidget(OpenGLFormat()){
        std::cout << "OpenGL " << this->format().majorVersion() << "." << this->format().minorVersion() << std::endl;        
    }      
    void init(){
        bool success = vao.create();
        if(!success) exit(EXIT_FAILURE);
        vao.bind();        
    }
};


GLuint createTextureSrc(unsigned int size_x, unsigned int size_y) {
    GLuint texture;
 
    // create a texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set basic parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /// See Table.2 https://www.khronos.org/opengles/sdk/docs/man3/docbook4/xhtml/glTexImage2D.xml
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, size_x, size_y, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL); /// Same as color attachment in framebuffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, size_x, size_y, 0, GL_RGBA, GL_FLOAT, NULL); /// Same as extra attachment in framebuffer
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, size_x, size_y, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, NULL); /// Sensor depth texture
    
    CHECK_ERROR_GL();
    return texture;
}

_INITIALIZE_EASYLOGGINGPP
int main(int argc, char* argv[]){
    printf("%s starting...\n\n", argv[0]);
    QApplication app(argc, argv);
    GLWidget glarea;
    glarea.show();
    glarea.init();
    
    /// As in de docs, I get the device after creating the context
    int devID = gpuGetMaxGflopsDeviceId();
    cudaError status = cudaGLSetGLDevice(devID);
    if(status!=cudaSuccess){
        std::cout << "Could not get OpenGL compliant device... exiting" << std::endl;
        exit(0);
    }
        
    struct ResourcePair {
        struct cudaGraphicsResource* resouce;
        cudaArray* array;
    };
    
    int width = 320;
    int height = 240;
    
#ifdef USE_FRAMEBUFFER
    CustomFrameBuffer fb;
    glViewport(0,0, width, height);
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST);    
    fb.init(width, width);
    GLuint texture_id = fb.extra_tex_id();
#else
    GLuint texture_id = createTextureSrc(width,height);    
#endif
    
    ResourcePair res;
    TIMED_BLOCK(timer,"register")
    {
        checkCudaErrors(cudaGraphicsGLRegisterImage(&res.resouce, texture_id, GL_TEXTURE_2D, cudaGraphicsMapFlagsReadOnly));
    }
    
    TIMED_BLOCK(timer,"1000x executions")
    {
        bool WITH_DRAW = false;
        printf("WITH_DRAW: %s\n", WITH_DRAW?"Yes":"No");
        
        for (int i = 0; i < 1000; ++i) {
#ifdef USE_FRAMEBUFFER
            // TIMED_BLOCK(timer,"render")
            if(WITH_DRAW){
                fb.bind();
                    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
                fb.unbind();
                glFinish();      
            }
#endif
            // TIMED_BLOCK(timer,"bind")
            {    
                checkCudaErrors(cudaGraphicsMapResources(1, &res.resouce, 0));
                checkCudaErrors(cudaGraphicsSubResourceGetMappedArray(&res.array, res.resouce, 0, 0));
            }        
            // TIMED_BLOCK(timer,"unbind") //2 microseconds
            {
               checkCudaErrors(cudaGraphicsUnmapResources(1, &res.resouce, 0));        
            }
        }
    }

    TIMED_BLOCK(timer,"unregister")
    {
        checkCudaErrors(cudaGraphicsUnregisterResource(res.resouce));
    }
    return 0;
}
