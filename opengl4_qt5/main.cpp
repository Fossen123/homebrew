#include <QApplication>
#include <QGLWidget>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <QOpenGLVertexArrayObject>

const char * vshader = 
    "#version 330\n"
    "in vec3 position;\n"
    "out vec2 uv;\n"
    "void main() { \n"
    "    gl_Position = vec4(position, 1.0); \n"
    "    uv = (vec2(position) + vec2(1,1))/2.0; \n"   
    "}";

const char * fshader = 
    "#version 330\n"
    "in vec2 uv;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "   color = vec4(uv[0], uv[1], 0.0, 1.0);\n"
    "}\n";


class GLWidget : public QGLWidget{
private: 
    QGLShaderProgram program;
    QOpenGLVertexArrayObject vao;
    QGLBuffer vertexbuffer;

public:
    GLWidget(QGLFormat format) : QGLWidget(format){}

private:
    /// @overload QGLWidget
    void initializeGL(){     
        printf("OpenGL %d.%d\n",this->format().majorVersion(),this->format().minorVersion());
        
        ///--- Create an array object to store properties
        {
            bool success = vao.create();
            Q_ASSERT(success);
            vao.bind();
        }
        
        ///--- Load/compile shaders
        {
            bool vok = program.addShaderFromSourceCode(QGLShader::Vertex, vshader);
            bool fok = program.addShaderFromSourceCode(QGLShader::Fragment, fshader);
            bool lok = program.link ();
            Q_ASSERT(lok && vok && fok);
            bool success = program.bind();
            Q_ASSERT(success);
        }
        
        ///--- Create vertex buffer/attributes "position"
        {
            static float vertices[] = {
                -1.0000,-1.0000,+0.0000,
                +1.0000,-1.0000,+0.0000,
                -1.0000,+1.0000,+0.0000,
                +1.0000,+1.0000,+0.0000,};
            
            vertexbuffer = QGLBuffer(QGLBuffer::VertexBuffer);
            bool success = vertexbuffer.create();
            Q_ASSERT(success);
            vertexbuffer.setUsagePattern( QGLBuffer::StaticDraw ); 
            success = vertexbuffer.bind();
            Q_ASSERT(success);
            vertexbuffer.allocate( vertices, sizeof(vertices) );
            program.setAttributeBuffer("position", GL_FLOAT, 0, 3 );
            program.enableAttributeArray("position");
        }
        
        ///--- Unbind to avoid pollution
        vao.release();
        program.release();
        
        ///--- Background
        glClearColor(1.0, 1.0, 1.0, 1.0);
                
        ///--- Setup opengl flags
        glDisable(GL_DEPTH_TEST);
    }
    
#if 0 // Why is this not having any effect? 
    void resizeGL(int width, int height){
        glViewport(0, 0, .5*width, .5*height);
    }
#endif
    
    /// @overload QGLWidget
    void paintGL(){
        program.bind();
        vao.bind();
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); ///< we have 4 verts
        vao.release();
        program.release();
    }
};

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    
    ///--- Setup for OpenGL4
    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( false );
    
    GLWidget widget(glFormat);
    widget.resize(640,480);
    widget.show();
    return app.exec();
}
