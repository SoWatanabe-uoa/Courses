#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>


// Number of subdivisions
#define N 256

#define _PI 3.14159f

// Coordinates and function values
GLfloat g_x_coords[N];
GLfloat g_sin_values[N];
GLfloat g_cos_values[N];
GLfloat g_x2_values[N];

// Set x coordinates to go through -pi to pi by step of 2*pi/N
static void setXCoords() {
	GLfloat x_start = -_PI;
	GLfloat delta_x = 2.0f*_PI / (N-1);
	int i;
	for (i = 0; i < N; ++i) {
		g_x_coords[i] = x_start + i * delta_x;
	}
}

// Complete: 
// Compute sin(x), cos(x), x^2
static void setYValues() {
	int i;
	for (i = 0; i < N; ++i) {
		// Set g_sin_values[i] to the sin of g_x_coords[i]
	  g_sin_values[i] = sinf(g_x_coords[i]);
		// Set g_cos_values[i] to the cos of g_x_coords[i]
	  g_cos_values[i] = cosf(g_x_coords[i]);
		// Set g_x2_values[i] to x^2
	  g_x2_values[i] = powf(g_x_coords[i],2);
	}
}

static void display(void) {
  glClear (GL_COLOR_BUFFER_BIT);

  int i;
  glColor3f(0.f,0.f,0.f);
  glLineWidth(2.f);
  glScalef(1.f/_PI,1.f/_PI,1.f);

  // Complete:
  
  // Plot in red color the sine curve by connecting the points (g_x_coords[i], g_sin_values[i])
  // with line segments.
  glBegin(GL_LINES);
   glColor3f(1.f,0.f,0.f);
   for(i = 0; i < N-1; ++i){
     glVertex2f(g_x_coords[i], g_sin_values[i]);
     glVertex2f(g_x_coords[i+1], g_sin_values[i+1]);
   }
   glEnd();
   
  // Same thing in green color for cos(x)
   glBegin(GL_LINES);
   glColor3f(0.f,1.f,0.f);
   for(i = 0; i < N-1; ++i){
     glVertex2f(g_x_coords[i], g_cos_values[i]);
     glVertex2f(g_x_coords[i+1], g_cos_values[i+1]);
   }
   glEnd();

   // Same thing in blue color for x^2
  glBegin(GL_LINES);
   glColor3f(0.f,0.f,1.f);
   for(i = 0; i < N-1; ++i){
     glVertex2f(g_x_coords[i], g_x2_values[i]);
     glVertex2f(g_x_coords[i+1], g_x2_values[i+1]);
   }
   glEnd();

  // End of complete
  
  glutSwapBuffers();
}

// No need to modify the functions below
//

static void init (void) {
  // set the color for painting the background
  glClearColor (1.0, 1.0, 1.0, 1.0);

  // set an orthographic projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0); 

  // prepare the curve coordinates
  setXCoords();
  setYValues();
}

static void keyHandle(unsigned char key, int x, int y) {
  // exit when ESC is pressed
  if (key == 27) exit(0);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(400,400);
   glutInitWindowPosition(100, 100);
   glutCreateWindow ("Plot curves");

   init(); 
   glutDisplayFunc(display);
   glutKeyboardFunc(keyHandle); 
   glutMainLoop(); 
   return 0;
}
