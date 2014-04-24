#include <GL/glut.h>
#include <math.h>
GLint left=true,right=false;
GLfloat Width=1000,Height=800;
int flap=0;
int var=0;
GLubyte cubeIndices[]={0,1,2,3,4,5,6,0};
typedef struct
{
float x;
float y;
}CIRCLE;

CIRCLE circle;

float rot = 0;
void draw_pixel(GLint cx, GLint cy)
{ glColor3f(1.0,0.0,0.0);
glBegin(GL_POINTS);
glVertex2i(cx,cy);
glEnd();
}

void plotpixels(GLint h, GLint k, GLint x, GLint y)
{
draw_pixel(x+h,y+k);
draw_pixel(-x+h,y+k);
draw_pixel(x+h,-y+k);
draw_pixel(-x+h,-y+k);
draw_pixel(y+h,x+k);
draw_pixel(-y+h,x+k);
draw_pixel(y+h,-x+k);
draw_pixel(-y+h,-x+k);
}
void Circle_draw(GLint h, GLint k, GLint r) // Midpoint Circle Drawing Algorithm
{
	GLint d = 1-r, x=0, y=r;
	while(y > x)
	{
		plotpixels(h,k,x,y);
		if(d < 0) d+=2*x+3;
		else
		{d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}
void createcircle (int k, int r, int h) 
{
    glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
    circle.x = r * cos((float)i) - h;
    circle.y = r * sin((float)i) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    
    circle.x = r * cos(i + 0.1) - h;
    circle.y = r * sin(i + 0.1) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    }
    glEnd();
}
void butterfly(float x,float y)
{
	float scale=.6;


	glPushMatrix();	
	glTranslatef(0+x,0+y,-80);
	glRotatef(90,0,0,1);
	if(flap) glRotatef(-40,1,0,0);
    glScalef(scale, scale,1);
		glBegin(GL_POLYGON);
		float cx=0,cy=0,cz=0;
		for(int i=0;i<5000;i++)
		{
			cx+=(1.0/5000);
			cy-=(1.0/5000);
			cz+=(1.0/5000);
			glColor3f(cx,cy,cz);

			double t=i*24*3.14159265/5000;
			double expr = pow(exp(cos(t))-2*cos(4*t)-sin(t/12),3);
			GLfloat X = sin(t)*expr;
			GLfloat Y = -cos(t)*expr;
			if(Y>=0)
				glVertex2f(X,Y);
		}
		glEnd();
	glFlush();
	glPopMatrix();


	glPushMatrix();	
	glTranslatef(0+x,0+y,-80);
	glRotatef(90,0,0,1);
	if(flap) glRotatef(-40,-1,0,0);
	glScalef(scale, scale,1);
	glScalef(1,-1,1);
		cx=0,cy=0,cz=0;
		glBegin(GL_POLYGON);

		for(int i=0;i<5000;i++)
		{
			
			cx+=(1.0/5000);
			cy-=(1.0/5000);
			cz+=(1.0/5000);
			glColor3f(cx,cy,cz);

			double t=i*24*3.14159265/5000;
			double expr = pow(exp(cos(t))-2*cos(4*t)-sin(t/12),3);
			GLfloat X = sin(t)*expr;
			GLfloat Y = -cos(t)*expr;
			if(Y>=0)
				glVertex2f(X,Y);
		}
		glEnd();
		glPopMatrix();
		glFlush();
}
void arrow()
{
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0,0,-90);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(0,12);
	glVertex2f(4,12);
	glVertex2f(4,0);
	glEnd();
	glFlush();
	glBegin(GL_POLYGON);
	glVertex2f(-2,12);
	glVertex2f(2,17);
	glVertex2f(6,12);
	glEnd();
	glFlush();
	glPopMatrix();
	
}
void egg(float x,float y)
{
	glPushMatrix();
	glTranslatef(0+x,0+y,-40);
	//Sleep(2);
	//gluDisk( "ring",3,5,30,30); 
	

              	
	glColor3f(1,1,1);
	gluDisk(gluNewQuadric(), 0, 3, 32, 32);
	glColor3f(0,0,0);
	gluDisk(gluNewQuadric(), 3, 3.2, 32, 32);
	//glLineWidth(10);
	//createcircle(0,3,0);
	glTranslatef(0,1.6,0.3);
	gluDisk(gluNewQuadric(), .7, .8, 32, 32);
	//createcircle(0,1,0);
	glPopMatrix();
}

void caterpillar(float x,float y)
{
	//caterpillar's body
	//
	glPushMatrix();
	glTranslatef(0+x,0+y,-30);
    glColor3f(0,1,0);
	glutSolidSphere(2.0,20,20);
	
	glTranslatef(1.8,0,0);
    glColor3f(0,1,0);
	glutSolidSphere(2.0,20,20);
   
	glTranslatef(2,0,0);
    glColor3f(0,1,0);
	glutSolidSphere(2.0,20,20);
	glTranslatef(2.2,0,0);
    glColor3f(0,1,0);
	glutSolidSphere(2.0,20,20);
	glTranslatef(2.5,0,0);
    glColor3f(0,1,0);
    glutSolidSphere(2.0,20,20);


	//caterpillar's eyes
	glTranslatef(-0.9,0.8,2);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,20,20);

	
	glTranslatef(.8,0,0);
    glColor3f(0,0,0);
    glutSolidSphere(0.2,20,20);

	//caterpillar's legs

	glTranslatef(-9,-2,-5);
	glColor3f(0,0,0);
	glLineWidth(3.0);
	GLint x0=0,y0=0,x1=-1,y1=-1;
	GLint x2=0,y2=0,x3=1,y3=-1;
	int i;

	if(right)
	{
	
	for(i=-0;i<12;i++)
	{
	glBegin(GL_LINES);
			glVertex2f(x2+i,y2);
			glVertex2f(x3+i,y3);
	glEnd();
	}
	}
	else if(left)
	{
	
	
	for(i=0;i<12;i++)
	{
		glBegin(GL_LINES);
			glVertex2f(x0+i,y0);
			glVertex2f(x1+i,y1);
		glEnd();
	}
	}
	glPopMatrix();
}
void DrawEllipse(float X,float Y)
{
		glPushMatrix();
		glTranslatef(0+X,0+Y,-40);
		glColor3f(1,1,1);
		float x,y,z;
		float t;
        glBegin(GL_POLYGON);
        for(t = 0; t <= 360; t+=1)
		{
			x = 4*sin(t);
			y = 7*cos(t);
			z = 0;
			glVertex3f(x,y,z);
       }
       glEnd();
	   glPopMatrix();
}
void drawarrow()
{
	if(!(var%4)){
		egg(-16,14);
	}
	else if((var%4)==1){
		glPushMatrix();
		glTranslatef(-5,30,0);
		glRotatef(90,0,0,-1);
		arrow();
		glPopMatrix();
		egg(-16,14);
		caterpillar(7,10);
	}
	else if((var%4)==2){
		glPushMatrix();
		glTranslatef(-5,30,0);
		glRotatef(90,0,0,-1);
		arrow();
		glPopMatrix();
		egg(-16,14);
		caterpillar(7,10);
		glPushMatrix();
		glTranslatef(30,7,0);
		glRotatef(180,0,0,-1);
		arrow();
		glPopMatrix();
		DrawEllipse(14,-15);
	}
	else if((var%4)==3){
		glPushMatrix();
		glTranslatef(-5,30,0);
		glRotatef(90,0,0,-1);
		arrow();
		glPopMatrix();
		egg(-16,14);
		caterpillar(7,10);
		glPushMatrix();
		glTranslatef(30,7,0);
		glRotatef(180,0,0,-1);
		arrow();
		glPopMatrix();
		DrawEllipse(14,-15);
		glPushMatrix();
		glTranslatef(5,-30,0);
		glRotatef(270,0,0,-1);
		arrow();
		glPopMatrix();
		butterfly(-30,-25);
		glPushMatrix();
		glTranslatef(-30,7,0);
		//glRotatef(0,0,0,-1);
		arrow();
		glPopMatrix();
	}
}

void display (void) {

	
    glClearColor (.627,.32,.176,1.0);
	//glClearColor(1,1,1,1);
    glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
	//arrow();
	drawarrow();

	
	
	
	glutSwapBuffers();

}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
	{
		var++;
		display();
	}
}
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
    switch ( key )
    {
    case 27:        // When Escape Is Pressed...
        exit ( 0 );   // Exit The Program
        break;        // Ready For Next Case
	case 'a':flap=flap==0?1:0;
		display();
        break;
    case ' ':	if(left)
				{
					left=false;
					right=true;
					display();
				}
				else if(right)
				{
					left=true;
					right=false;
					display();
				}
    default:        // Now Wrap It Up
		
        break;
    }

    glutPostRedisplay();
}

void reshape (int w, int h) {
	Width=w;
	Height=h;
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize (Width, Height);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (" caterpillar " );
	
	glEnable(GL_DEPTH_TEST); 
	glutMouseFunc(mouse);
    glutDisplayFunc (display);
	glutKeyboardFunc    ( keyboard );
    glutIdleFunc (display);
    glutReshapeFunc (reshape);

    glutMainLoop();
    return 0;
}