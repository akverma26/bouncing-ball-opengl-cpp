#include<iostream>
using namespace std;
#include <windows.h>
#include <GL/glut.h>
#include <Math.h>
#include<conio.h>
#include<stdio.h>

// Global variables
float PI =3.14159265,shift=0;
char title[] = "ANKIT KUMAR & RAMBABU GRAPHICS PROJECT";  // Windowed mode's title
int windowWidth  = 640; //Window Specifications
int windowHeight = 480;
int windowPosX   = 50;
int windowPosY   = 50;
int level=1;
char score1='0';
char score2=0;
char score3=0;
bool paused = true;         // Movement paused or resumed
GLfloat ballRadius = 0.04f;   // Radius of the bouncing ball
GLfloat ballX = 0.0f;        // Ball's center (x, y) position
GLfloat ballY = 0.0f;
GLfloat ballXMax=1.77, ballXMin, ballYMax, ballYMin; // Ball's center (x, y) bounds
GLfloat xSpeed = 0;      // Ball's speed in x and y directions
GLfloat ySpeed = 0;
int refreshMillis = 3;      // Refresh period in milliseconds
float length= 0.2*ballXMax;
double clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
bool fullScreenMode = true;
float xSpeedSaved, ySpeedSaved;




void initGL() //Initialize Open GL
{
   glClearColor(1, 1, 1, 0); // Background Color

}
void renderBitmapString(
		float x,
		float y,
		float z,

		char c) {
    glRasterPos3f(x, y,z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
  }
int g=0;
  void gameover() {
    glRasterPos3f(-0.5, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
    glRasterPos3f(-0.4, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
    glRasterPos3f(-0.3, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
    glRasterPos3f(-0.2, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
    glRasterPos3f(0.0, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
    glRasterPos3f(0.1, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'V');
    glRasterPos3f(0.2, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
    glRasterPos3f(0.3, 0,0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
  }


//What to Display
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    renderBitmapString(0.9,0.9, 0.0f ,score1);
    renderBitmapString(0.85,0.9, 0.0f ,score2);
    renderBitmapString(0.8,0.9, 0.0f ,score3);
    if(g)
    {
        gameover();
    }
    if(score1==':')
    {
        score1='0';
        if(score2==0)
            score2='0';
        score2++;
        xSpeed+=0.0001;
        ySpeed+=0.0003;
    }
    if(score2==':')
    {
        score2='0';
        if(score3==0)
            score3='0';
        score3++;
    }
   glBegin(GL_POLYGON);
   glColor3f(shift,0.0,1.0);
   glVertex2d(-length+shift,-1);
   glVertex2d(length+shift,-1);
   glVertex2d(length+shift,-0.96);
   glVertex2d(-length+shift,-0.96);
   glEnd();

   glTranslatef(ballX, ballY, 0.0f);

   glutSolidSphere(ballRadius,20,20);

   glutSwapBuffers();

   // Animation Control
   ballX += xSpeed;
   ballY += ySpeed;

   if (ballX > ballXMax)
    {
      ballX = ballXMax;
      xSpeed = -xSpeed;
   }
   else if (ballX < ballXMin)
    {
      ballX = ballXMin;
      xSpeed = -xSpeed;
   }
   if (ballY > ballYMax)
   {
      ballY = ballYMax;
      ySpeed = -ySpeed;
   }
   else if (ballY < ballYMin)
  {
      ballY = ballYMin;
      ySpeed = -ySpeed;
      score1+=2;
   }

   if(ballY<-0.95 && (ballX>length+shift+0.1 || ballX<=-length+shift-0.1))
   {
       g=1;
       xSpeed=0;
       ySpeed=0;
   }


}

//Resizing
void reshape(GLsizei width, GLsizei height)
{
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   glViewport(0, 0, width, height);


   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (width >= height)
    {
      clipAreaXLeft   = -1.0 * aspect;
      clipAreaXRight  = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop    = 1.0;
   } else
   {
      clipAreaXLeft   = -1.0;
      clipAreaXRight  = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop    = 1.0 / aspect;
   }
   gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   ballXMin = clipAreaXLeft + ballRadius;
   ballXMax = clipAreaXRight - ballRadius;
   ballYMin = clipAreaYBottom + ballRadius;
   ballYMax = clipAreaYTop - ballRadius;
}

void Timer(int value)
{
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

//KeyBoard Control Normal Keys
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
       case 55:    // F1: Toggle between full-screen and windowed mode
         fullScreenMode = !fullScreenMode;         // Toggle state
         if (fullScreenMode)
          {                     // Full-screen mode
            windowPosX   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
            windowPosY   = glutGet(GLUT_WINDOW_Y);
            windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
            windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
            glutFullScreen();                      // Switch into full screen
         }
         else
          {                                         // Windowed mode
            glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
            glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
         }
         break;
      case 27:// ESC key
         exit(0);
         break;
   }
}

//KeyBoard Control Special Keys
void specialKeys(int key, int x, int y)
{
   switch (key)
   {
      case GLUT_KEY_RIGHT:    //increase x speed
         if (length+shift<=ballXMax)
         shift+=0.1; break;
      case GLUT_KEY_LEFT:     //ecrease x speed
        if (length+shift>=ballXMin)
         shift-=0.1; break;

      case GLUT_KEY_PAGE_UP:  //increase ball's radius
         ballRadius *= 1.05f;
         ballXMin = clipAreaXLeft + ballRadius;
         ballXMax = clipAreaXRight - ballRadius;
         ballYMin = clipAreaYBottom + ballRadius;
         ballYMax = clipAreaYTop - ballRadius;
         break;
      case GLUT_KEY_PAGE_DOWN: //decrease ball's radius
         ballRadius *= 0.95f;
         ballXMin = clipAreaXLeft + ballRadius;
         ballXMax = clipAreaXRight - ballRadius;
         ballYMin = clipAreaYBottom + ballRadius;
         ballYMax = clipAreaYTop - ballRadius;
         break;
   }
}

void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    { // Pause/resume
      paused=!paused;
        if (paused)
      {
         xSpeedSaved = xSpeed;  // Save parameters for restore later
         ySpeedSaved = ySpeed;
         xSpeed = 0;            // Stop movement
         ySpeed = 0;
      }
        else
        {
         xSpeed = xSpeedSaved;  // Restore parameters
         ySpeed = ySpeedSaved;
        }
   }
}

//Main Function
int main(int argc, char** argv)
{
  cout<<"Enter the Level Number: (any Number):  ";
  cin>>level;
  if(level==0)
    level=1;

   xSpeedSaved=0.002f*level, ySpeedSaved=0.006f*level;
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(windowWidth, windowHeight);
   glutInitWindowPosition(windowPosX, windowPosY);
   glutCreateWindow(title);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc(0, Timer, 0);
   glutSpecialFunc(specialKeys);
   glutKeyboardFunc(keyboard);
   glutFullScreen();
   glutMouseFunc(mouse);
   initGL();
   glutMainLoop();

   getch();
   return 0;
}
