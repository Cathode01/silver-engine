#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define GLFW_DLL
#define black 0
#define white 1
#define red 2
#define cyan 3
#define violet 4
#define green 5
#define blue 6
#define yellow 7
#define orange 8
#define brown 9
#define lightred 10
#define grey 11
#define grey2 12
#define lightgreen 13
#define lightblue 14
#define grey3 15
#define transparent 16
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define G 16
    const float rLUT[17] = {0.0, 1.0, 0.92549, 0.66667, 0.8, 0.0, 0.0, 0.93333, 0.86667, 0.4, 1.0, 0.2, 0.46667, 0.66667, 0.0, 0.73333};
    const float gLUT[17] = {0.0, 1.0, 0, 1.0, 0.26667, 0.8, 0.0, 0.93333, 0.53333, 0.26667, 0.46667, 0.2, 0.46667, 1.0, 0.53333, 0.73333}; //lookup tables for diffrent color values
    const float bLUT[17] = {0.0, 1.0, 0, 0.93333, 0.8, 0.33333, 0.66667, 0.46667, 0.53333, 0.0, 0.46667, 0.2, 0.46667, 0.4, 1.0, 0.73333};
    int screenarray[321][201][17];
    int bufferground[320][200];
    bool fullScreen=false;
    bool drawing=false;
    float wdh;
    int px,py = 1;
    int pxx,pyy=0;
    bool sleept=false;
    GLboolean w,a,s,d=false;
    GLboolean upPressed = false;
    int lyr=0,clr=13;


    int t1 = time(NULL), t2;
    int framecount;

void keyboard(unsigned char key, int x, int y);

void cleararr(int index){
for(int x=320;x>0;x--){
for(int y=200;y>0;y--)
    screenarray[x][y][index]=16;
}

}
void idle(){ //loop function
    pxx=0,pyy=0;
    if(w)
        pyy=1;
    if(s)
        pyy=-1;
    if(d)
        pxx=1;
    if(a)
        pxx=-1;
        if(drawing){

        screenarray[px][py][lyr]=clr;
        }
        cleararr(15);
        screenarray[px][py][15]=16;
    px+=pxx;
    py+=pyy;
    if (px>=320)
        px=0;
    if (py>=200)
        py=0;
    if (px==-1)
        px=320;
    if (py==-1)
        py=200;
    wdh = glutGet(GLUT_WINDOW_WIDTH)/320;
    /*for(int x=320; x>0; x--){
                for(int y=200; y>0; y--){
                    if(x>y*2)
                    screenarray[x][y][1] = 17-(rand() % 4);
    }}//static slope demo*/
    if(bufferground[px][py]==G){
        screenarray[px][py][15]=clr;
    }else{
        screenarray[px][py][15]=(screenarray[px][py][0]+1) % 16;
    }
    glutPostRedisplay();
    if(t1!=t2){
    if(framecount>15){
        sleept=true;
        }else{
        sleept=false;
        }

    }
    framecount=0;
    glutKeyboardFunc(keyboard);
    if(sleept)
        usleep(framecount-15);
        w=false, a=false, s=false, d=false;

}
void drawscreen(){ //draws image from 2d arrays
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 320.0, 0.0, 200.0);
            glBegin(GL_POINTS);
            for(int z=0; z<16; z++){
            for(int x=320; x>0; x--){
                for(int y=200; y>0; y--){
                    if (screenarray[x][y][z] != G){ //foreground array gets first priority for drawing on screen.
                        glPointSize(wdh);
                        glBegin(GL_POINTS);
                        glColor3f(rLUT[screenarray[x][y][z]], gLUT[screenarray[x][y][z]], bLUT[screenarray[x][y][z]]);
                        bufferground[x][y] = screenarray[x][y][z];
                        glVertex2i (x,y);
                        glEnd();
                    }
                    }
                }
            }


            glFinish();
            framecount++;
}

int main(int argc,char** argv) {
    for(int z=16; z>0; z--){
        for(int x=320; x>0; x--){
            for(int y=200; y>0; y--){
                screenarray[x][y][z] = 16;
            }
        }
    }

     	glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glutInitWindowSize(1920, 1200);
        glutCreateWindow("Silver64 Engine");
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutDisplayFunc(drawscreen);
        glutIdleFunc(idle);
        glutMainLoop();
        glfwTerminate();
    return 0;
}

void keyboard(unsigned char key, int x, int y){
switch (key){
    case 'f':
        fullScreen = !fullScreen;
        if(fullScreen)
            glutFullScreen();
        else{
            glutReshapeWindow(1920,1200);
            glutPositionWindow(0,0);
        }
    break;
    case 's':
        //if (py>0)
        s=true;
                w=false;
        //pyy=-1;;
    break;
    case 'w':
        //if(py<200)
        w=true;
                s=false;
        //pyy=1;
    break;
    case 'a':
        //if(px>0)
        a=true;
               d=false;
        //pxx=-1;
    break;
    case 'd':
        //if(px<320)
        d=true;
                a=false;
        //pxx=1;
    break;
    case 'q':
        clr++;
        if (clr==17)
            clr=0;
    break;
    case 'e':
        clr--;
        if (clr==-1)
        clr=16;
    break;

    case 'r':
            drawing = !drawing;
    break;
    }


}

