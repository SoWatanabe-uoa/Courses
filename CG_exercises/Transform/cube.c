#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define _PI 3.14159f

enum {TRANS, ROT, SCALE};
int g_op_mode = TRANS;

enum {PERSP, ORTHO};
int g_proj_mode = PERSP;

enum {OGL, MY};
int myImp_mode = OGL;

// window dimension
int g_width = 800;
int g_height = 800;

// angle (in degree) to rotate around x, y, z
GLfloat g_angle[3] = {0.0f, 0.0f, 0.0f};

// amount to trnaslate along x, y, z
GLfloat g_trans[3] = {0.0f, 0.0f, 0.0f};

// scaling factor along x, y, z
GLfloat g_scale[3] = {1.0f, 1.0f, 1.0f};

// transformation matrix
GLfloat m[16];


// Model-View transforms
static void myTranslatef(GLfloat tx, GLfloat ty, GLfloat tz) {
  // Complete
  for(int i = 0; i < 16; ++i){
    if(i%5 == 0) m[i] = 1.0f;
    else m[i] = 0.0f;
  }
  m[12] = tx;
  m[13] = ty;
  m[14] = tz;
  glMultMatrixf(m);
}

static void myScalef(GLfloat sx, GLfloat sy, GLfloat sz) {
  // Complete
  for(int i = 0; i < 16; ++i){
    if(i%5 == 0) m[i] = 1.0f;
    else m[i] = 0.0f;
  }
  m[0] = sx;
  m[5] = sy;
  m[10] = sz;
  glMultMatrixf(m);
}

static void myRotatef(GLfloat theta, GLfloat kx, GLfloat ky, GLfloat kz) {
  // Complete
  //convert Degree to Radian
  GLfloat theta_r = theta * (_PI / 180.0f);
  
  for(int i = 0; i < 16; ++i){
    if(i%5 == 0) m[i] = 1.0f;
    else m[i] = 0.0f;
  }
  m[0] = kx * kx * (1.0f - cosf(theta_r)) + cosf(theta_r);
  m[1] = ky * kx * (1.0f - cosf(theta_r)) + kz * sinf(theta_r);
  m[2] = kz * kx * (1.0f - cosf(theta_r)) - ky * sinf(theta_r);
  m[4] = kx * ky * (1.0f - cosf(theta_r)) - kz * sinf(theta_r);
  m[5] = ky * ky * (1.0f - cosf(theta_r)) + cosf(theta_r);
  m[6] = kz * ky * (1.0f - cosf(theta_r)) + kx * sinf(theta_r);
  m[8] = kx * kz * (1.0f - cosf(theta_r)) + ky * sinf(theta_r);
  m[9] = ky * kz * (1.0f - cosf(theta_r)) - kx * sinf(theta_r);
  m[10] = kz * kz * (1.0f - cosf(theta_r)) + cosf(theta_r);
  //m[10] = 0.5;
  glMultMatrixf(m);
}

// Projection transforms
static void myOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat n, GLfloat f) {
  // Complete
  for(int i = 0; i < 16; ++i){
    if(i%5 == 0) m[i] = 1.0f;
    else m[i] = 0.0f;
  }
  m[0] = 2.0f / (right - left);
  m[5] = 2.0f / (top - bottom);
  m[10] = 2.0f / (n - f);
  m[12] = - ((right + left) / (right - left));
  m[13] = - ((top + bottom) / (top - bottom));
  m[14] = (f + n) / (n - f);
  glMultMatrixf(m);

  /*
  for(int i=0; i<16; i++){
     if(i%5 == 0) m[i] = 1.0f;
     else m[i] = 0.0f;
  }
  m[10]=0;
  glMultMatrixf(m);
  */
  
}

static void myPerspective(GLfloat fovy, GLfloat aspect, GLfloat n, GLfloat f) {
  // Complete
  // convert Degree to Radian
  GLfloat fovy_r = fovy / 2.0f * (_PI / 180.0f);
  GLfloat left = -tanf(fovy_r) * n * aspect;
  GLfloat right = tanf(fovy_r) * n * aspect;
  GLfloat bottom = -tanf(fovy_r) * n;
  GLfloat top = tanf(fovy_r) * n;
  
  for(int i = 0; i < 16; ++i) m[i] = 0.0f;
  m[0] = 2.0f * n / (right - left);
  m[5] = 2.0f * n / (top - bottom);
  m[8] = (right + left) / (right - left);
  m[9] = (top + bottom) / (top - bottom);
  m[10] = - (f + n) / (f - n);
  m[11] = -1.0f;
  m[14] = -2.0f * f * n / (f - n);
  glMultMatrixf(m);
}

static void drawCube(void) {
  GLfloat vertex[8][3] = { {-1.0f,-1.0f,-1.0f}, { 1.0f,-1.0f,-1.0f},
			   { 1.0f, 1.0f,-1.0f}, {-1.0f, 1.0f,-1.0f},
			   {-1.0f,-1.0f, 1.0f}, { 1.0f,-1.0f, 1.0f},
			   { 1.0f, 1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f} };

  GLfloat color[6][3] = { {0.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
			  {1.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
			  {0.0f,0.0f,1.0f}, {1.0f,0.0f,1.0f} };

  int face[6][4] = {
    {0, 4, 7, 3}, {1, 5, 6, 2}, {0, 1, 5, 4},
    {3, 7, 6, 2}, {0, 3, 2, 1}, {4, 5, 6, 7} };

  int i;
  for (i = 0; i < 6; ++i) {
    GLfloat* c = color[i];
    int* f = face[i];
    int v0 = f[0], v1 = f[1], v2 = f[2], v3 = f[3];

    glColor3f(c[0], c[1], c[2]);
    glBegin(GL_QUADS);
    glVertex3f(vertex[v0][0], vertex[v0][1], vertex[v0][2]);
    glVertex3f(vertex[v1][0], vertex[v1][1], vertex[v1][2]);
    glVertex3f(vertex[v2][0], vertex[v2][1], vertex[v2][2]);
    glVertex3f(vertex[v3][0], vertex[v3][1], vertex[v3][2]);
    glEnd();
  }
}

static void drawFloor(void) {
  GLfloat vertex[4][3] = { {3.0f, -2.5f, 6.0f}, {-3.0f, -2.5f, 6.0f},
			   {-3.0f, -2.5f, -6.0f}, {3.0f, -2.5f, -6.0f} };

  glColor3f(1.f, 1.f, 1.f);
  glBegin(GL_QUADS);
  glVertex3f(vertex[0][0], vertex[0][1], vertex[0][2]);
  glVertex3f(vertex[1][0], vertex[1][1], vertex[1][2]);
  glVertex3f(vertex[2][0], vertex[2][1], vertex[2][2]);
  glVertex3f(vertex[3][0], vertex[3][1], vertex[3][2]);
  glEnd();
}

static void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Projection transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (g_proj_mode == PERSP) {
    // Complete: 
    // After completing the code of myPerspective() above, 
    // replace the call to gluPerspective with a call to myPerspective 
	// or gluPerspective depending on the transformation mode
    if(myImp_mode == OGL) gluPerspective(45.0, (GLdouble)g_width / (GLdouble)g_height, 0.1, 20.0);
    else myPerspective(45.0, (GLdouble)g_width / (GLdouble)g_height, 0.1, 20.0);
  }
  else {
    // Complete: 
    // After completing the code of myOrtho() above, 
    // replace the call to glOrtho with a call to myOrtho
	// or glOrtho depending on the transformation mode
    if(myImp_mode == OGL) glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
    else myOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
  }
  
  // Modelview transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  
  glPushMatrix();

  // Complete: 
  // After completing the code of myTranslatef, myScalef, 
  // and myRotatef, 
  // replace the call to glTranslatef, glRotatef, glScalef by calls to 
  // myTranslatef, myScalef, and myRotatef or 
  // glTranslatef, glRotatef, glScalef based on the transformation mode.

  if(myImp_mode == OGL){
    glTranslatef(g_trans[0], g_trans[1], g_trans[2]);
    glRotatef(g_angle[0], 1.f, 0.f, 0.f);
    glRotatef(g_angle[1], 0.f, 1.f, 0.f);
    glRotatef(g_angle[2], 0.f, 0.f, 1.f);
    glScalef(g_scale[0], g_scale[1], g_scale[2]);
  }
  else{
    myTranslatef(g_trans[0], g_trans[1], g_trans[2]);
    myRotatef(g_angle[0], 1.f, 0.f, 0.f);
    myRotatef(g_angle[1], 0.f, 1.f, 0.f);
    myRotatef(g_angle[2], 0.f, 0.f, 1.f);
    myScalef(g_scale[0], g_scale[1], g_scale[2]);
  }
  
  drawCube();
//drawFloor();

  glPopMatrix();

  drawFloor();

  glutSwapBuffers();
}

static void reshape(int w, int h) {
  glViewport(0, 0, w, h);

  g_width = w;
  g_height = h;
}

// Increase the rotation angle by amt around ax
static void rotate(int ax, GLfloat amt) {
  g_angle[ax] += amt;
}

// Increase the translation by amt along ax
static void translate(int ax, GLfloat amt) {
  g_trans[ax] += amt;
}

// Multiply the scaling factor by amt along ax
static void scale(int ax, GLfloat amt) {
  g_scale[ax] *= amt;
}

static void keyboard(unsigned char k, int x, int y) {
  switch (k) {
  case 27:
    exit(EXIT_SUCCESS);
    break;

  // Complete: 
  // Allow to switch between OpenGL transformations and your implementations
  case 'm':
    myImp_mode = (1 - myImp_mode);
printf("swich\n");
    break;
    

  case 'p':
    g_proj_mode = (1 - g_proj_mode);
    break;

  case 't':
  case 'T':
    g_op_mode = TRANS;
    break;

  case 'r':
  case 'R':
    g_op_mode = ROT;
    break;

  case 's':
  case 'S':
    g_op_mode = SCALE;
    break;

  case 'x':
    if (g_op_mode == TRANS) translate(0, -0.5f);
    if (g_op_mode == ROT) rotate(0, -5.0f);
    if (g_op_mode == SCALE) scale(0, 0.9f);
    break;

  case 'X':
    if (g_op_mode == TRANS) translate(0, 0.5f);
    if (g_op_mode == ROT) rotate(0, 5.0f);
    if (g_op_mode == SCALE) scale(0, 1.1f);
    break;

  case 'y':
    if (g_op_mode == TRANS) translate(1, -0.5f);
    if (g_op_mode == ROT) rotate(1, -5.0f);
    if (g_op_mode == SCALE) scale(1, 0.9f);
    break;

  case 'Y':
    if (g_op_mode == TRANS) translate(1, 0.5f);
    if (g_op_mode == ROT) rotate(1, 5.0f);
    if (g_op_mode == SCALE) scale(1, 1.1f);
    break;

  case 'z':
    if (g_op_mode == TRANS) translate(2, -0.5f);
    if (g_op_mode == ROT) rotate(2, -5.0f);
    if (g_op_mode == SCALE) scale(2, 0.9f);
    break;

  case 'Z':
    if (g_op_mode == TRANS) translate(2, 0.5f);
    if (g_op_mode == ROT) rotate(2, 5.0f);
    if (g_op_mode == SCALE) scale(2, 1.1f);
    break;

  default:
    break;
  }

  glutPostRedisplay();
}

static void init(void) {
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Cube");

  init();
  
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);

  glutMainLoop();
  return 0;
}
