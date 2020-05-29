#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

GLint PI[1][2] = { 10,10 };//Initial (x,y) of the graph
GLint PF[1][2] = { 10,10 };//Final (x,y) of the graph
GLint input_arr[9] = { 0 };//Original array for the packet input
GLint final_arr[9] = { 0 };//Final output to store the non-conforming/conforming packets
GLfloat a[2];//Droplets
GLfloat b[2];
GLfloat c[2];
GLfloat d[2];
GLfloat w[2];//Water inside the bucket 
GLfloat x[2];
GLfloat y[2];
GLfloat z[2];
GLint cnt = 0;//Count of non-conforming packets 
int font;//font of text
char print_str[1024];
GLfloat ypos = 10;
GLfloat xpos = 5;

void nonconf_packet(GLint* final_arr);
void leaky_bucket();
void reassign_arr(const char* str, char* arr);
void print_message(const char* str, GLfloat x, GLfloat y);
void display_bucket();


void idle() {
	
	if (ypos >= 5) {
		ypos -= 0.01;
	}
	else {
		ypos += 5;
	}
	
	glutPostRedisplay();
	//glutTimerFunc(100, idle, 0);
}
void nonconf_packet(GLint* final_arr) //NON CONFORMING packets
{

	int i, x, x1;
	cnt = 0;
	for (i = 0; i < 9; i++)
	{
		if (final_arr[i] == 1)
		{
			cnt++;
			x = (i * 1) + 0.1;
			x1 = ((i + 0.01) * 1) + 0.1;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);//To show the non-conforming packets on top
			glVertex2i(x, 9.30);
			glVertex2i(x1, 9.30);
			glVertex2i(x1, 9.80);
			glVertex2i(x, 9.80);
			glEnd();
			glColor3f(0.9, 0.9, 0.9);//Outline over each packet
			glEnable(GL_LINE_WIDTH);
			glLineWidth(10);
			glBegin(GL_LINE_LOOP);
			glVertex2i(x, 9.30);
			glVertex2i(x1, 9.30);
			glVertex2i(x1, 9.80);
			glVertex2i(x, 9.80);
			glEnd();
			glLineWidth(1);
		}
	}


}

void leaky_bucket() // ALGORITHM :CALCULATION 
{
	GLint X, Y;
	PI[0][1] = 10; PI[0][0] = 10;
	PF[0][1] = 10; PF[0][0] = 10;
	int i = 0, j, k, count = 0, C = 0, val, e;
	for (i = 0; i < 9; i++)//Finding the initial packet postion
	{
		if (input_arr[i] == 0)
			count++;
		else
			break;
	}
	PI[0][0] += (count * 100);
	j = i;//First packet
	PF[0][0] += count * 100;
	while (j < 9)
	{

		count = 0;
		if (input_arr[j] == 1)
		{
			PF[0][1] += 300;
			if (C + 3 <= 9)
				C += 3;
			if (PF[0][1] > 910)
			{
				PF[0][1] -= 300;
				final_arr[j] = 1;

			}
			//draw_graph(PI[0], PF[0], C);//Vertical Line,I=3

			X = PF[0][1] + 2;
			Y = PF[0][1] + 2;
			glColor3f(1.0, 1.0, 1.0);

			PI[0][0] = PF[0][0];
			PI[0][1] = PF[0][1];
			PF[0][0] += 100;//Drop after every addition of packet
			PF[0][1] -= 100;
			C -= 1;

			//print_packet(C);

			//draw_graph(PI[0], PF[0], C);//Draw the drop
			PI[0][0] = PF[0][0];
			PI[0][1] = PF[0][1];
			j++;

		}
		else
		{
			for (k = j; k < 9; k++)//Finding the next packet 
			{
				if (input_arr[k] == 0)
				{
					count++;
					C -= 1;
				}
				else
					break;
			}
			PF[0][1] = PF[0][1] - (100 * count);
			PF[0][0] = PF[0][0] + (100 * count);
			if (PF[0][1] < 10)
			{
				val = 10 - PF[0][1];
				PF[0][0] -= val;
				PF[0][1] = 10;
				//draw_graph(PI[0], PF[0], C);

				PI[0][0] = PF[0][0] + val;
				PI[0][1] = PF[0][1];
				PF[0][0] += val;

			}
			else
			{
				//draw_graph(PI[0], PF[0], C);

				PI[0][0] = PF[0][0];
				PI[0][1] = PF[0][1];
			}
			j = k;
		}

	}
	nonconf_packet(final_arr);
}

void reassign_arr(const char* str, char* arr)
{
	int i = 0;
	while ((*str) != '\0')
	{
		*arr = *str;
		str++;
		arr++;
	}
	*arr = '\0';
}
void print_message(const char* str, GLfloat x, GLfloat y)
{
	reassign_arr(str, print_str);
	glRasterPos2f(x, y);
	for (int e = 0; print_str[e] != '\0'; e++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, print_str[e]);

}

void display_bucket()//Bucket
{
	glutIdleFunc(idle);
	leaky_bucket();
	int i, j, k, Y1, Y2;
	a[0] = 3.950; a[1] = 7.670;
	b[0] = 4.050; b[1] = 7.670;
	c[0] = 4.050; c[1] = 7.920;
	d[0] = 3.950; d[1] = 7.920;
	w[0] = 3.000; w[1] = 3.500;
	x[0] = 5.000; x[1] = 3.500;
	y[0] = 5.350; y[1] = 4.750;
	z[0] = 2.650; z[1] = 4.750;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(0.05);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, 10, 0, 10);

	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(xpos, ypos, 0);
	glScalef(1.5, 1.9, 3);
	glutSolidCube(0.2);

	glPopMatrix();
	glPushMatrix();
	//bucket
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(3.000, 3.500);
	glVertex2f(5.000, 3.500);
	glVertex2f(5.500, 5.250);
	glVertex2f(2.500, 5.250);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//water
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2fv(w);
	glVertex2fv(x);
	glVertex2fv(y);
	glVertex2fv(z);
	glEnd();
	glPopMatrix();

	glColor3f(0.5, 0.9, 0.0);
	print_message("PICTORIAL REPRESENTATION ", 3.000, 9.0);

	glColor3f(0.5, 0.5, 0.0);
	print_message("INCOMING PACKETS ", 3.000, 8.000);

	for (i = 0; i < 9; i++)//Droplet
	{
		if (input_arr[i] == 1)//Packet
		{
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex2fv(a);
			glVertex2fv(b);
			glVertex2fv(c);
			glVertex2fv(d);
			glEnd();
		}
		else//Not existing packet
		{
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINE_LOOP);
			glVertex2fv(a);
			glVertex2fv(b);
			glVertex2fv(c);
			glVertex2fv(d);
			glEnd();
		}
		a[1] -= 0.30;
		b[1] -= 0.30;
		c[1] -= 0.30;
		d[1] -= 0.30;

	}
	
	glColor3f(0.5, 0.5, 0.0);
	print_message("NON CONFORMING PACKETS", 5.700, 5.250);
	for (j = 0; j < cnt; j++)//525=Rim of bucket
	{
		Y1 = 5.25 - j * 0.30;
		Y2 = 5.10 - j * 0.30;

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
		glVertex2i(5.50, Y1);
		glVertex2i(5.60, Y1);
		glVertex2i(5.60, Y2);
		glVertex2i(5.50, Y2);
		glEnd();
	}

	glColor3f(0.5, 0.5, 0.0);
	print_message("CONFORMING PACKETS ", 4.150, 2.900);

	k = 0;
	for (j = 0; j < 9; j++)//525=Rim of bucket
	{
		if (final_arr[j] == 0 && input_arr[j] == 1)
		{
			Y1 = 3.50 - k * 0.30;
			Y2 = 3.35 - k * 0.30;

			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
			glVertex2i(3.95, Y1);
			glVertex2i(4.05, Y1);
			glVertex2i(4.05, Y2);
			glVertex2i(3.95, Y2);
			glEnd();
			k++;
		}

	}
	glutSwapBuffers();
}






int main(int argc, char** argv)
{
	printf("Given 9 slots, select your packets in binary values\n");
	printf("Choose \n 1 : Including a packet\t 0 : Excluding a packet\n");
	int i;
	for (i = 0; i < 9; i++)
	{
		scanf("%d", &input_arr[i]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Leaky Bucket");
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glutDisplayFunc(display_bucket);
	glutIdleFunc(idle);
	//glutTimerFunc(1000, idle, 0);
	glutMainLoop();
	return 0;
}