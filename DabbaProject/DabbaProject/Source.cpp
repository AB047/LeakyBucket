/*LEAKY BUCKET ALGORITHM. PACKET SIZE=3,BUCKET LENGTH=9*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>

GLint PI[1][2] = { 10,10 };//Initial (x,y) of the graph
GLint PF[1][2] = { 10,10 };//Final (x,y) of the graph
GLint A[9] = { 0 };//Original array for the packet input
GLint B[9] = { 0 };//Final output to store the non-conforming/conforming packets
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
int op;

void number(GLint X, GLint Y, int n)
{
	int i;
	char f[] = "Zero";
	char g[] = "1";
	char h[] = "2";
	char j[] = "3";
	char k[] = "4";
	char l[] = "5";
	char m[] = "6";
	char N[] = "7";
	char o[] = "8";
	char p[] = "9";

	switch (n)
	{
	case'0':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; f[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[i]);
		break;
	case'1':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; g[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[i]);
		break;
	case'2':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; h[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[i]);
		break;
	case'3':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; j[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, j[i]);
		break;
	case'4':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; k[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[i]);
		break;
	case'5':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; l[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[i]);
		break;
	case'6':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; m[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[i]);
		break;
	case'7':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; N[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, N[i]);
		break;
	case'8':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; o[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, o[i]);
		break;
	case'9':glColor3f(1.0, 0.0, 0.0);
		glRasterPos2f(X, Y);
		for (i = 0; p[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p[i]);
		break;
	}
}

void draw_line(GLint* a, GLint* b) //DRAW LINES
{
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_LINE_WIDTH);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2iv(a);
	glVertex2iv(b);
	glEnd();
	glLineWidth(1);
}

void draw_line_1() //DRAW LINES
{

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2iv(PI[0]);
	glVertex2iv(PF[0]);
	glEnd();
}

// 

void non_polygon(GLint* B) //NON CONFORMING packets
{

	int i, x, x1;
	cnt = 0;
	for (i = 0; i < 9; i++)
	{
		if (B[i] == 1)
		{
			cnt++;
			x = (i * 100) + 10;
			x1 = ((i + 1) * 100) + 10;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);//To show the non-conforming packets on top
			glVertex2i(x, 930);
			glVertex2i(x1, 930);
			glVertex2i(x1, 980);
			glVertex2i(x, 980);
			glEnd();
			glColor3f(0.0, 0.0, 0.0);//Outline over each packet
			glEnable(GL_LINE_WIDTH);
			glLineWidth(10);
			glBegin(GL_LINE_LOOP);
			glVertex2i(x, 930);
			glVertex2i(x1, 930);
			glVertex2i(x1, 980);
			glVertex2i(x, 980);
			glEnd();
			glLineWidth(1);
		}
	}
}

void polygon(GLint* a) //CONFORMING PACKETS
{
	int i, x, x1, v = 10;
	for (i = 0; i < 9; i++)
	{
		if (a[i] == 1)
		{
			x = (i * 100) + 10;
			x1 = ((i + 1) * 100) + 10;
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);//To show the conforming packets on top
			glVertex2i(x, 930);
			glVertex2i(x1, 930);
			glVertex2i(x1, 980);
			glVertex2i(x, 980);
			glEnd();
			glColor3f(0.0, 0.0, 0.0);
			glEnable(GL_LINE_WIDTH);
			glLineWidth(10);
			glBegin(GL_LINE_LOOP);//Outline over each packet
			glVertex2i(x, 930);
			glVertex2i(x1, 930);
			glVertex2i(x1, 980);
			glVertex2i(x, 980);
			//glDisable(GL_LINE_WIDTH);
			glEnd();
			glLineWidth(1);
		}

	}
	for (i = 0; i < 9; i++)
	{
		v = i * 100 + 10;
		glColor3f(1.0, 1.0, 1.0);//Marking on the packet line 
		glBegin(GL_LINES);
		glVertex2i(v, 930);
		glVertex2i(v, 940);
		glEnd();
	}
	glColor3f(1.0, 1.0, 1.0);//Base of packet line on top
	glBegin(GL_LINES);
	glVertex2i(10, 930);
	glVertex2i(980, 930);
	glEnd();
}

void leaky_bucket() // ALGORITHM :CALCULATION 
{
	GLint X, Y;
	int i = 0, j, k, count = 0, C = 0, val, e;
	for (i = 0; i < 9; i++)//Finding the initial packet postion
	{
		if (A[i] == 0)
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
		if (A[j] == 1)
		{
			PF[0][1] += 300;
			C += 3;
			if (PF[0][1] > 910)
			{
				PF[0][1] -= 300;
				B[j] = 1;

			}
			draw_line(PI[0], PF[0]);//Vertical Line,I=3

			X = PF[0][1] + 2;
			Y = PF[0][1] + 2;
			glColor3f(1.0, 1.0, 1.0);

			//			glColor3f(1.0,0.0,0.0);
						//char f[]="HI";
						//glRasterPos2f(PF[0][0],PF[0][1]);
					//for(e=0;f[e]!='\0';e++)
					//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,f[i]);				
			if (C == 0)
			{
				glColor3f(1.0, 1.0, 1.0);
				char f[] = "0packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; f[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[e]);
			}
			else if (C == 1) {
				glColor3f(1.0, 1.0, 1.0);	char g[] = "1 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; g[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[e]);
			}
			else if (C == 2) {
				glColor3f(1.0, 1.0, 1.0);
				char h[] = "2 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);;
				for (e = 0; h[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[e]);
			}
			else if (C == 3) {
				glColor3f(1.0, 1.0, 1.0);

				char J[] = "3 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; J[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, J[e]);
			}
			else if (C == 4) {
				glColor3f(1.0, 1.0, 1.0);
				char k[] = "4 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; k[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[e]);
			}
			else if (C == 5) {
				glColor3f(1.0, 1.0, 1.0);
				char l[] = "5 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; l[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[e]);
			}
			else if (C == 6) {
				glColor3f(1.0, 1.0, 1.0);
				char m[] = "6 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; m[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[e]);
			}
			else if (C == 7) {
				glColor3f(1.0, 1.0, 1.0);
				char N[] = "7 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; N[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, N[e]);
			}
			else if (C == 8) {
				glColor3f(1.0, 1.0, 1.0);
				char o[] = "8 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; o[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, o[e]);
			}
			else if (C == 9) {
				glColor3f(1.0, 1.0, 1.0);
				char p[] = "9 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; p[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p[e]);
			}



			PI[0][0] = PF[0][0];
			PI[0][1] = PF[0][1];
			PF[0][0] += 100;//Drop after every addition of packet
			PF[0][1] -= 100;
			C -= 1;

			if (C == 0)
			{
				glColor3f(1.0, 1.0, 1.0);
				char f[] = "0packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; f[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[e]);
			}
			else if (C == 1) {
				glColor3f(1.0, 1.0, 1.0);	char g[] = "1 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; g[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[e]);
			}
			else if (C == 2) {
				glColor3f(1.0, 1.0, 1.0);
				char h[] = "2 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);;
				for (e = 0; h[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[e]);
			}
			else if (C == 3) {
				glColor3f(1.0, 1.0, 1.0);

				char J[] = "3 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; J[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, J[e]);
			}
			else if (C == 4) {
				glColor3f(1.0, 1.0, 1.0);
				char k[] = "4 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; k[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[e]);
			}
			else if (C == 5) {
				glColor3f(1.0, 1.0, 1.0);
				char l[] = "5 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; l[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[e]);
			}
			else if (C == 6) {
				glColor3f(1.0, 1.0, 1.0);
				char m[] = "6 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; m[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[e]);
			}
			else if (C == 7) {
				glColor3f(1.0, 1.0, 1.0);
				char N[] = "7 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; N[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, N[e]);
			}
			else if (C == 8) {
				glColor3f(1.0, 1.0, 1.0);
				char o[] = "8 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; o[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, o[e]);
			}
			else if (C == 9) {
				glColor3f(1.0, 1.0, 1.0);
				char p[] = "9 packets";
				glRasterPos2f(PF[0][0], PF[0][1]);
				for (e = 0; p[e] != '\0'; e++)
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p[e]);
			}

			draw_line(PI[0], PF[0]);//Draw the drop
			PI[0][0] = PF[0][0];
			PI[0][1] = PF[0][1];
			j++;

		}
		else
		{
			for (k = j; k < 9; k++)//Finding the next packet 
			{
				if (A[k] == 0)
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
				draw_line(PI[0], PF[0]);

				if (C == 0)
				{
					glColor3f(1.0, 0.0, 0.0);
					char f[] = "0packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; f[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[e]);
				}
				else if (C == 1) {
					glColor3f(1.0, 0.0, 0.0);	char g[] = "1 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; g[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[e]);
				}
				else if (C == 2) {
					glColor3f(1.0, 0.0, 0.0);
					char h[] = "2 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);;
					for (e = 0; h[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[e]);
				}
				else if (C == 3) {
					glColor3f(1.0, 0.0, 0.0);

					char J[] = "3 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; J[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, J[e]);
				}
				else if (C == 4) {
					glColor3f(1.0, 0.0, 0.0);
					char k[] = "4 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; k[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[e]);
				}
				else if (C == 5) {
					glColor3f(1.0, 0.0, 0.0);
					char l[] = "5 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; l[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[e]);
				}
				else if (C == 6) {
					glColor3f(1.0, 0.0, 0.0);
					char m[] = "6 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; m[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[e]);
				}
				else if (C == 7) {
					glColor3f(1.0, 0.0, 0.0);
					char N[] = "7 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; N[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, N[e]);
				}
				else if (C == 8) {
					glColor3f(1.0, 0.0, 0.0);
					char o[] = "8 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; o[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, o[e]);
				}
				else if (C == 9) {
					glColor3f(1.0, 0.0, 0.0);
					char p[] = "9 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; p[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p[e]);
				}

				PI[0][0] = PF[0][0] + val;
				PI[0][1] = PF[0][1];
				PF[0][0] += val;

			}
			else
			{
				draw_line(PI[0], PF[0]);

				if (C == 0)
				{
					glColor3f(1.0, 0.0, 0.0);
					char f[] = "0packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; f[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[e]);
				}
				else if (C == 1) {
					glColor3f(1.0, 0.0, 0.0);	char g[] = "1 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; g[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[e]);
				}
				else if (C == 2) {
					glColor3f(1.0, 0.0, 0.0);
					char h[] = "2 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);;
					for (e = 0; h[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[e]);
				}
				else if (C == 3) {
					glColor3f(1.0, 0.0, 0.0);

					char J[] = "3 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; J[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, J[e]);
				}
				else if (C == 4) {
					glColor3f(1.0, 0.0, 0.0);
					char k[] = "4 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; k[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[e]);
				}
				else if (C == 5) {
					glColor3f(1.0, 0.0, 0.0);
					char l[] = "5 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; l[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, l[e]);
				}
				else if (C == 6) {
					glColor3f(1.0, 0.0, 0.0);
					char m[] = "6 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; m[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[e]);
				}
				else if (C == 7) {
					glColor3f(1.0, 0.0, 0.0);
					char N[] = "7 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; N[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, N[e]);
				}
				else if (C == 8) {
					glColor3f(1.0, 0.0, 0.0);
					char o[] = "8 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; o[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, o[e]);
				}
				else if (C == 9) {
					glColor3f(1.0, 0.0, 0.0);
					char p[] = "9 packets";
					glRasterPos2f(PF[0][0], PF[0][1]);
					for (e = 0; p[e] != '\0'; e++)
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, p[e]);
				}

				PI[0][0] = PF[0][0];
				PI[0][1] = PF[0][1];
			}
			j = k;
		}

	}
	non_polygon(B);
}

void display2()//Bucket
{
	int i, j, k, Y1, Y2;
	a[0] = 395.0; a[1] = 767.0;
	b[0] = 405.0; b[1] = 767.0;
	c[0] = 405.0; c[1] = 792.0;
	d[0] = 395.0; d[1] = 792.0;
	w[0] = 300.0; w[1] = 350.0;
	x[0] = 500.0; x[1] = 350.0;
	y[0] = 535.0; y[1] = 475.0;
	z[0] = 265.0; z[1] = 475.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);

	//bucket
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(300.0, 350.0);
	glVertex2f(500.0, 350.0);
	glVertex2f(550.0, 525.0);
	glVertex2f(250.0, 525.0);
	glEnd();

	//water
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2fv(w);
	glVertex2fv(x);
	glVertex2fv(y);
	glVertex2fv(z);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	char s[] = "INCOMING PACKETS";
	glRasterPos2f(300.0, 800.0);
	for (i = 0; s[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

	glColor3f(2.0, 1.0, 1.0);
	char O[] = "PICTORIAL REPRESENTATION";
	glRasterPos2f(300.0, 900.0);
	for (i = 0; O[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, O[i]);

	for (i = 0; i < 9; i++)//Droplet
	{
		if (A[i] == 1)//Packet
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
		a[1] -= 30;
		b[1] -= 30;
		c[1] -= 30;
		d[1] -= 30;

	}
	glColor3f(1.0, 0.0, 1.0);
	char f[] = "NON CONFORMING PACKETS";
	glRasterPos2f(570.0, 525.0);
	for (i = 0; f[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[i]);

	

	for (j = 0; j < cnt; j++)//525=Rim of bucket
	{
		Y1 = 525 - j * 30;
		Y2 = 510 - j * 30;

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
		glVertex2i(550, Y1);
		glVertex2i(560, Y1);
		glVertex2i(560, Y2);
		glVertex2i(550, Y2);
		glEnd();
	}

	glColor3f(0.0, 1.0, 1.0);
	char r[] = "CONFORMING PACKETS";
	glRasterPos2f(415.0, 290.0);
	for (i = 0; r[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, r[i]);

	k = 0;
	for (j = 0; j < 9; j++)//525=Rim of bucket
	{
		if (B[j] == 0 && A[j] == 1)
		{
			Y1 = 350 - k * 30;
			Y2 = 335 - k * 30;

			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
			glVertex2i(395, Y1);
			glVertex2i(405, Y1);
			glVertex2i(405, Y2);
			glVertex2i(395, Y2);
			glEnd();
			k++;
		}

	}
}


void display1()//Drawing the Graph
{
	PI[0][1] = 10; PI[0][0] = 10;
	PF[0][1] = 10; PF[0][0] = 10;
	char str[9] = { '1','2','3','4','5','6','7','8','9' };
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(980, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(10, 910);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(10.0, 25.0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
	int i, a = 10, b = 10;
	for (i = 0; i < 9; i++)
	{
		a = a + 100;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex2i(a, 10);
		glVertex2i(a, 20);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f((GLfloat)a, 25.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
	}
	a = 10;
	for (i = 0; i < 9; i++)
	{
		a = a + 100;
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex2i(10, a);
		glVertex2i(20, a);
		glEnd();
	}
	polygon(A);
	leaky_bucket();

	glColor3f(1.0, 1.0, 0.0);
	char T[] = "KEY";
	glRasterPos2f(600.0, 300.0);
	for (i = 0; T[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, T[i]);

	glColor3f(0.0, 1.0, 0.0);
	char U[] = "GREEN";
	glRasterPos2f(600.0, 250.0);
	for (i = 0; U[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, U[i]);

	glColor3f(0.0, 1.0, 1.0);
	char V[] = ": CONFIRMING PACKETS";
	glRasterPos2f(700.0, 250.0);
	for (i = 0; V[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, V[i]);

	glColor3f(1.0, 0.0, 0.0);
	char W[] = "RED";
	glRasterPos2f(600.0, 200.0);
	for (i = 0; W[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, W[i]);

	glColor3f(0.0, 1.0, 1.0);
	char X[] = ":  NON CONFORMING PACKETS";
	glRasterPos2f(700.0, 200.0);
	for (i = 0; X[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, X[i]);

	glFlush();
	if (op == 2)
		display2();//Page displaying Bucket
}

void display()//Main Page
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	char f[] = "LEAKY BUCKET ALGORITHM";
	glRasterPos2f(400.0, 900.0);
	for (i = 0; f[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, f[i]);
	glColor3f(0.0, 0.0, 1.0);
	char g[] = "WHERE";
	glRasterPos2f(300.0, 800.0);
	for (i = 0; g[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, g[i]);

	glColor3f(0.0, 1.0, 0.0);
	char h[] = "PACKET SIZE (I) : 3";
	glRasterPos2f(400.0, 750.0);
	for (i = 0; h[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, h[i]);

	glColor3f(0.0, 1.0, 0.0);
	char e[] = "BUCKET DEPTH (L) : 9";
	glRasterPos2f(400.0, 700.0);
	for (i = 0; e[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, e[i]);

	glColor3f(1.0, 1.0, 0.0);
	char t[] = "D1 BY:";
	glRasterPos2f(200.0, 400.0);
	for (i = 0; t[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t[i]);

	glColor3f(1.0, 0.0, 1.0);
	char s[] = "1CR12CS094";
	glRasterPos2f(200.0, 350.0);
	for (i = 0; s[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);

	glColor3f(0.0, 1.0, 1.0);
	char u[] = "SHREYA K.S.";
	glRasterPos2f(350.0, 350.0);
	for (i = 0; u[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, u[i]);

	glColor3f(1.0, 0.0, 1.0);
	char v[] = "1CR12CS095";
	glRasterPos2f(200.0, 300.0);
	for (i = 0; v[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, v[i]);

	glColor3f(0.0, 1.0, 1.0);
	char w[] = "SHREYA VISHWANATH RAO";
	glRasterPos2f(350.0, 300.0);
	for (i = 0; w[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, w[i]);
}


void demo_menu(int id)
{
	op = id;
	switch (id)
	{
	case 1: display1();
		break;
	case 2:display1();
		break;
	case 3:exit(0);
		break;
	}
	glutPostRedisplay();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{

	printf("Given 9 slots, select your packets in binary values\n");
	printf("Choose \n 1 : Including a packet\t 0 : Excluding a packet\n");
	int i;
	for (i = 0; i < 9; i++)
	{
		scanf("%d", &A[i]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Leaky Bucket");
	glutCreateMenu(demo_menu);
	glutAddMenuEntry("Graph", 1);
	glutAddMenuEntry("Bucket", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	myinit();
	glutMainLoop();
	return 0;
}



