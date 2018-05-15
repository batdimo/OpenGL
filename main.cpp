#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

bool gl_KeyDown[256];
int gl_WindowPositionX=50,
    gl_WindowPositionY=50,
    gl_WindowWidth = 640,
    gl_WindowHeight = 400;

// for reshape
double gl_AngleofView = 60,
       gl_nearPlaneDist=1,
       gl_farPlaneDist=1000;

//camera
double gl_CameraPosX = 30,
       gl_CameraPosY =30,
       gl_CameraPosZ =30,
       gl_CameraTargetX=0,
       gl_CameraTargetY=0,
       gl_CameraTargetZ=0,
       gl_WorldUpX=0,
       gl_WorldUpY=1,
       gl_WorldUpZ=0;

//teapot
double gl_TeapotRotationY_deg=0.0,
       gl_TeapotRotationX_deg=0.0,
       gl_TeapotRotationZ_deg=0.0,
       gl_TeapotMoveX=0.0,
       gl_TeapotMoveY=0.0,
       gl_TeapotMoveZ=0.0;


void Reshape(int Width, int Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double aspectRatio = (double) Width/(double) Height;

    gluPerspective(gl_AngleofView,aspectRatio,gl_nearPlaneDist, gl_farPlaneDist);
    glMatrixMode(GL_MODELVIEW);
}

void DrawTeapot(double size,
                double locationX,double locationY,double locationZ,
                double rotationX_degs, double rotationY_degs,double rotationZ_degs,
                double colorRed, double colorGreen, double colorBlue )
{
    glPushMatrix();
    glTranslatef(locationX,locationY,locationZ);
    glRotatef(rotationX_degs, 1.0, 0.0, 0.0);
    glRotatef(rotationY_degs, 0.0, 1.0, 0.0);
    glRotatef(rotationZ_degs, 0.0, 0.0, 1.0);

    glColor4f(colorRed, colorGreen, colorBlue, 1.0);
    glutSolidTeapot(size);
    glPopMatrix();
}

void DrawSphere()
{
    glPushMatrix();
    glTranslated(1, 6, 13);
    glutSolidSphere(3,36,36);
    glPopMatrix();

}

void DrawObjects()
{
    DrawTeapot(5,
               gl_TeapotMoveX, gl_TeapotMoveY, gl_TeapotMoveZ,
               0,gl_TeapotRotationY_deg,0,
               1.0,1.0,1.0);
    DrawSphere();
}

void ApplyCamera()
{
    gluLookAt(gl_CameraPosX,gl_CameraPosY,gl_CameraPosZ,
              gl_CameraTargetX,gl_CameraTargetY,gl_CameraTargetZ,
              gl_WorldUpX,  gl_WorldUpY,  gl_WorldUpZ);
}

void Display()
{
    if(gl_KeyDown['b'])
    {
        glClearColor(0.0,0.0,1.0,1.0);
    }
    else
    {
        glClearColor(0.0,1.0,0.0,1.0);
    }


    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    ApplyCamera();
    DrawObjects();
    glutSwapBuffers();
}

void HandleKeyboard()
{

    if(gl_KeyDown['r'])
    {
        gl_TeapotRotationY_deg +=1;
    }
    if(gl_KeyDown['e'])
    {
        gl_TeapotRotationY_deg -=1;
    }
    if(gl_KeyDown['q'])
    {
        gl_TeapotMoveY +=0.01;
    }
    if(gl_KeyDown['w'])
    {
        gl_TeapotMoveY -=0.01;
    }
    if(gl_KeyDown['a'])
    {
        gl_TeapotMoveX +=0.01;
    }
    if(gl_KeyDown['s'])
    {
        gl_TeapotMoveX -=0.01;
    }
    if(gl_KeyDown['z'])
    {
        gl_TeapotMoveZ +=0.01;
    }
    if(gl_KeyDown['x'])
    {
        gl_TeapotMoveZ -=0.01;
    }
}

void Loop()
{
    Display();
    HandleKeyboard();
}
void KeyDown( unsigned char key,int cursorPosX, int cursorPosY)
{
    gl_KeyDown[key]=true;
}
 void KeyUp( unsigned char key,int cursorPosX, int cursorPosY)
{
    gl_KeyDown[key]=false;
}

void InitializeWindow()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(gl_WindowPositionX,gl_WindowPositionY);
    glutInitWindowSize(gl_WindowWidth,gl_WindowHeight);
    glutCreateWindow("Proekt");
}
void RegisterFunctions()
{
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Loop);
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
}
void InitializedGl()
{
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    InitializeWindow();
    RegisterFunctions();
    InitializedGl();
    glutMainLoop();

    return 0;
}
