/*LEAKY BUCKET ALGORITHM. PACKET SIZE=3,BUCKET LENGTH=9*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<GL/glut.h>

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
int k;
int start = 0;
int overflow = 0;
int temp = 0;
int pk[30];
int count = 0;

void myKeyboardFunc(unsigned char Key, int x, int y);

// Use 0.9,0.9,0.9 for grey BG colour

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


void print_packet(GLint C)
{
	glColor3f(0.5, 0.0, 0.0);
	glRasterPos2f(PF[0][0] + 5, PF[0][1] + 5);
	char packet_char = '0' + C;
	if (C == 9)
	{
		glRasterPos2f(PF[0][0] + 5, PF[0][1] - 30);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, packet_char);
	}
	else
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, packet_char);
	reassign_arr(" Packets", print_str);
	for (int e = 0; print_str[e] != '\0'; e++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, print_str[e]);
	
}


void draw_graph(GLint* a, GLint* b, GLint NoPackets) //DRAW LINES
{
	GLfloat x, y;
	char packet_char = '0' + NoPackets;
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_LINE_WIDTH);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2iv(a);
	glVertex2iv(b);
	glEnd();
	glLineWidth(1);
	print_packet(NoPackets);
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
			x = (i * 100) + 10;
			x1 = ((i + 1) * 100) + 10;
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);//To show the non-conforming packets on top
			glVertex2i(x, 930);
			glVertex2i(x1, 930);
			glVertex2i(x1, 980);
			glVertex2i(x, 980);
			glEnd();
			glColor3f(0.9,0.9,0.9);//Outline over each packet
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

void conf_packet(GLint* a) //CONFORMING PACKETS
{
	int i, x, x1;
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
			glColor3f(0.9, 0.9, 0.9);
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
}


void leaky_bucket() // ALGORITHM :CALCULATION 
{
	GLint X, Y;
	PI[0][1] = 10; PI[0][0] = 10;
	PF[0][1] = 10; PF[0][0] = 10;
	int i = 0, j, k, count = 0, C = 0, val, e;
	for (i = 0; i < 9; i++)//Finding the initial packet postion
	{
		if (input_arr[i] == 0) {
			count++;
			
		}
		else
		{
			final_arr[i] = 0;
			break;
		}
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
			draw_graph(PI[0], PF[0], C);//Vertical Line,I=3

			X = PF[0][1] + 2;
			Y = PF[0][1] + 2;
			glColor3f(1.0, 1.0, 1.0);

			PI[0][0] = PF[0][0];
			PI[0][1] = PF[0][1];
			PF[0][0] += 100;//Drop after every addition of packet
			PF[0][1] -= 100;
			C -= 1;

			print_packet(C);

			draw_graph(PI[0], PF[0], C);//Draw the drop
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
					PF[0][1] = PF[0][1] - 100;
					PF[0][0] = PF[0][0] + 100;
					print_packet(C);
				}
				else {
					final_arr[k] = 0;
					break;
				}
			}

			if (PF[0][1] < 10)
			{
				val = 10 - PF[0][1];
				PF[0][0] -= val;
				PF[0][1] = 10;
				draw_graph(PI[0], PF[0], C);
				PI[0][0] = PF[0][0] + val;
				PI[0][1] = PF[0][1];
				PF[0][0] += val;

			}
			else
			{
				draw_graph(PI[0], PF[0], C);

				PI[0][0] = PF[0][0];
				PI[0][1] = PF[0][1];
			}
			j = k;
		}

	}

	nonconf_packet(final_arr);

}
int compute()
{
	count = 0;
	int op = 1, bucketsize = 9, n = 9, i;

	int sum = 0;
	for (i = 1; i <= n; i++)
	{
		sum += pk[i];
		if (sum > bucketsize)
		{
			printf("\nbucket overflow\n");
			overflow = 1;
			//exit(0);
		}
		else
		{
			if (sum > op)
			{
				printf("\n%d bytes output", op);
				sum = sum - op;
				count++;
			}
			
			printf("\n last %d bytes sent", pk[i]);
			printf("\n bucket output successful\n");
		}
	}
	printf("\n no. of packets sent=%d\n", count);
	return count;

}
void setpoint(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Circle(int r, int xCenter, int yCenter)
{
	glColor3f(0.0, 0.5, 0.5);
	int x = 0, y = r;
	int d = 3 / 2 - r;

	while (x <= y)
	{
		setpoint(xCenter + x, yCenter + y);
		setpoint(xCenter + y, yCenter + x);
		setpoint(xCenter - x, yCenter + y);
		setpoint(xCenter + y, yCenter - x);
		setpoint(xCenter - x, yCenter - y);
		setpoint(xCenter - y, yCenter - x);
		setpoint(xCenter + x, yCenter - y);
		setpoint(xCenter - y, yCenter + x);

		if (d < 0)
			d += (2 * x) + 3;
		else
		{
			d += (2 * (x - y)) + 5;
			y -= 1;
		}
		x++;
	}
	glFlush();
}
int round1(double number)
{
	return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
void LineWithDDA(int x0, int y0, int x1, int y1)
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int steps, i;
	float xinc, yinc, x = x0, y = y0;
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	xinc = (float)dx / (float)steps;
	yinc = (float)dy / (float)steps;
	setpoint(round1(x), round1(y));
	for (i = 0; i < steps; i++)
	{
		x += xinc;
		y += yinc;
		setpoint(round1(x), round1(y));
	}
	glPointSize(5);
	glutSwapBuffers();
}
void draw() {
	glPushMatrix();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	int const w = glutGet(GLUT_WINDOW_WIDTH);
	int const h = glutGet(GLUT_WINDOW_HEIGHT);

	
	
	glScalef(2.5, 2.5, 0);

	temp = compute();
	int x = temp;

	
	//bucket
	glPushMatrix();
	glTranslatef(85, 85, 0);
	

	glLineWidth(5);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_LINE_LOOP);
	glVertex2f(125, 120);
	glVertex2f(105, 60);
	glVertex2f(65, 60);
	glVertex2f(45, 120);
	glEnd();
	//glPopMatrix();
	

	int i = 1;
	
	Circle(3, 85, 183);
	Circle(1, 85, 183);
	while (i < 9)
	{
		k = 0;
		while (k < 10000)
		{
			int j = 0;
			while (j < 10000)
			{
				j++;
			}
			k++;
		}
		if (pk[i] > 0) {
			Circle(3, 85, 183 - (10 * i));
			Circle(1, 85, 183 - (10 * i));
		}
		else {
			Circle(3, 85, 183 - (10 * i));
		}

		i++;
	}
	//overflow
	if (overflow == 1)
	{

		int i = 0;
		glColor3f(0.0, 0.5, 0.8);
		LineWithDDA(66, 62, 104, 62);
		while (i < 58)
		{
			k = 0;
			while (k < 1000)
			{
				int j = 0;
				while (j < 10000)
				{
					j++;
				}
				k++;
			}

			LineWithDDA(66-i/3, 62 + i, 104+i/3, 62 + i);
			i++;
		}


		glColor3f(0.4, 0.0, 0.0);
		print_message("BUCKET OVERFLOW", 125, 100);


	}



	if (overflow == 0)
	{
		i = 0;
		glColor3f(0.0, 0.5, 0.8);
		LineWithDDA(66, 62, 104, 62);
		while (i < 10)
		{
			k = 0;
			while (k < 1000)
			{
				int j = 0;
				while (j < 10000)
				{
					j++;
				}
				k++;
			}

			LineWithDDA(66 - i / 3, 62 + i, 104 + i / 3, 62 + i);
			i++;
		}

		
		Circle(1, 85, 63);
		i = 1;
		while (i <= count)
		{
			k = 0;
			while (k < 10000)
			{
				int j = 0;
				while (j < 10000)
				{
					j++;
				}
				k++;
			}
			Circle(1, 85, 63 - (10 * i));

			i++;
		}
	}

	

	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void display_bucket()//Bucket
{
	glClear(GL_COLOR_BUFFER_BIT);
	
		leaky_bucket();
		int i, j, k, Y1, Y2;
		a[0] = 395.0; a[1] = 767.0;
		b[0] = 405.0; b[1] = 767.0;
		c[0] = 405.0; c[1] = 792.0;
		d[0] = 395.0; d[1] = 792.0;
		w[0] = 330.0; w[1] = 350.0;
		x[0] = 470.0; x[1] = 350.0;
		y[0] = 505.0; y[1] = 475.0;
		z[0] = 295.0; z[1] = 475.0;
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5.0);


		//water
		glColor3f(0.0, 0.5, 0.8);
		glBegin(GL_POLYGON);
		glVertex2fv(w);
		glVertex2fv(x);
		glVertex2fv(y);
		glVertex2fv(z);
		glEnd();

		//bucket
		glLineWidth(3);
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_LINE_LOOP);
		glVertex2f(330.0, 350.0);
		glVertex2f(470.0, 350.0);
		glVertex2f(520.0, 525.0);
		glVertex2f(280.0, 525.0);
		glEnd();
		glLineWidth(1);

		glColor3f(0.2, 0.2, 0.2);
		print_message("PICTORIAL REPRESENTATION ", 400.0, 900.0);

		glColor3f(0.0, 0.5, 0.5);
		print_message("INCOMING PACKETS ", 300.0, 800.0);

		for (i = 0; i < 9; i++)//Droplet
		{
			if (input_arr[i] == 1)//Packet
			{
				glColor3f(0.0, 0.5, 0.5);
				glBegin(GL_POLYGON);
				glVertex2fv(a);
				glVertex2fv(b);
				glVertex2fv(c);
				glVertex2fv(d);
				glEnd();
			}
			else//Not existing packet
			{
				glColor3f(0.0, 0.5, 0.5);
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
		glColor3f(0.4, 0.0, 0.0);
		print_message("NON CONFORMING PACKETS", 540.0, 525.0);

		for (j = 0; j < cnt; j++)//525=Rim of bucket
		{
			Y1 = 525 - j * 30;
			Y2 = 510 - j * 30;

			glColor3f(0.4, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
			glVertex2i(520, Y1);
			glVertex2i(530, Y1);
			glVertex2i(530, Y2);
			glVertex2i(520, Y2);
			glEnd();
		}

		glColor3f(0.0, 0.5, 0.0);
		print_message("CONFORMING PACKETS ", 415.0, 290.0);

		k = 0;
		for (j = 0; j < 9; j++)//525=Rim of bucket
		{
			if (final_arr[j] == 0 || input_arr[j] == 1)
			{
				Y1 = 350 - k * 30;
				Y2 = 335 - k * 30;

				glColor3f(0.0, 0.5, 0.0);
				glBegin(GL_LINE_LOOP);//Drawing the non-conforming packets along the rim
				glVertex2i(395, Y1);
				glVertex2i(405, Y1);
				glVertex2i(405, Y2);
				glVertex2i(395, Y2);
				glEnd();
				k++;
			}

		}
		glPopMatrix();
	glFlush();
	
}




void display_graph()//Drawing the Graph
{
	PI[0][1] = 10; PI[0][0] = 10;
	PF[0][1] = 10; PF[0][0] = 10;
	char str[9] = { '1','2','3','4','5','6','7','8','9' };
	int v = 10;

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(980, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(10, 910);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(10.0, 25.0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
	int i, a = 10, b = 10;
	for (i = 0; i < 9; i++)
	{
		a = a + 100;
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2i(a, 10);
		glVertex2i(a, 20);
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f((GLfloat)a, 25.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
	}
	a = 10;
	for (i = 0; i < 9; i++)
	{
		a = a + 100;
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2i(10, a);
		glVertex2i(15, a);
		glEnd();
	}
	
	for (i = 0; i < 11; i++)
	{
		v = i * 100 + 10;
		glColor3f(0.0, 0.0, 0.0);//Marking on the packet line 
		glBegin(GL_LINES);
		glVertex2i(v, 930);
		glVertex2i(v, 940);
		glEnd();
	}
	conf_packet(input_arr);
	leaky_bucket();

	glColor3f(0.0, 0.0, 0.0);//Base of packet line on top
	glBegin(GL_LINES);
	glVertex2i(10, 930);
	glVertex2i(980, 930);
	glEnd();

	for (i = 0; i < 11; i++)
	{
		v = i * 100 + 10;
		glColor3f(0.0, 0.0, 0.0);//Marking on the packet line 
		glBegin(GL_LINES);
		glVertex2i(v, 930);
		glVertex2i(v, 940);
		glEnd();
	}

	glColor3f(0.5, 0.0, 0.0);
	print_message("KEY", 600.0, 300.0);

	glColor3f(0.0, 0.5, 0.0);
	print_message("GREEN : CONFORMING PACKETS", 600.0, 250.0);

	glColor3f(1.0, 0.0, 0.0);
	print_message("RED : NON CONFORMING PACKETS", 600.0, 200.0);
	
	glColor3f(0.5, 0.0, 0.0);
	print_message("SCALE : ", 800.0, 300.0);

	glColor3f(0.0, 0.5, 0.0);
	print_message("X AXIS : 1 UNIT = 1 SECOND", 800.0, 250.0);

	glColor3f(1.0, 0.0, 0.0);
	print_message("Y AXIS : 1 UNIT = 1 PACKET", 800.0, 200.0);
	
	glFlush();
}


void display_menu()//Main Page
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.0, 0.2, 0.2);
	print_message("SJB INSTITUTE OF TECHNOLOGY ", 360.0, 800.0);

	glColor3f(0.0, 0.25, 0.25);
	print_message("COMPUTER GRAPHICS LABORATORY WITH MINI PROJECT ", 280.0, 750.0);

	glColor3f(0.0, 0.3, 0.3);
	print_message("LEAKY BUCKET ALGORITHM ", 380.0, 700.0);

	glColor3f(0.0, 0.35, 0.35);
	print_message("WHERE : ", 378.0, 600.0);

	glColor3f(0.0, 0.4, 0.4);
	print_message("PACKET SIZE (I) : 3 ", 440.0, 600.0);
	
	glColor3f(0.0, 0.45, 0.45);
	print_message("BUCKET DEPTH (L) : 9 ", 440.0, 550.0);
	
	glColor3f(0.0, 0.5, 0.5);
	print_message("PRESS : 1 FOR HOME PAGE ", 380.0, 450.0);
	
	glColor3f(0.0, 0.55, 0.55);
	print_message("2 FOR STATIC BUCKET", 439.0, 400.0);
	
	glColor3f(0.0, 0.55, 0.55);
	print_message("3 FOR ANIMATED BUCKET", 439.0, 350.0);

	glColor3f(0.0, 0.6, 0.6);
	print_message("4 FOR GRAPH ", 439.0, 300.0);
	
	glColor3f(0.0, 0.65, 0.65);
	print_message("5 FOR EXIT ", 439.0, 250.0);

	glColor3f(0.0, 0.7, 0.7);
	print_message("DONE BY: ", 180.0, 200.0);
	
	glColor3f(0.0, 0.74, 0.74);
	print_message("1JB17CS027 : ATUL M. BHARADWAJ ", 180.0, 150.0);
	
	glColor3f(0.0, 0.74, 0.74);
	print_message("1JB17CS021 : ANUSHA S. ", 180.0, 100.0);

	glColor3f(0.0, 0.7, 0.7);
	print_message("UNDER THE GUIDANCE OF:", 600.0, 200.0);

	glColor3f(0.0, 0.74, 0.74);
	print_message("MANASA B. S. (Asst. Professor, CSE)", 600.0, 150.0);

	glColor3f(0.0, 0.74, 0.74);
	print_message("SRINIDHI K. S. (Asst. Professor, CSE)", 600.0, 100.0);
	
	glFlush();
	
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
		scanf("%d", &input_arr[i]);
		pk[i] = input_arr[i] * 3;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Leaky Bucket");
	glutKeyboardFunc(myKeyboardFunc);
	glutDisplayFunc(display_menu);
	
	glClearColor(0.9, 0.9, 0.9, 1.0);
	myinit();
	glutMainLoop();
	return 0;
}

void myKeyboardFunc(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case '1': display_menu();
		break;
	case '2':leaky_bucket(); display_bucket();
		break;
	case '3':draw();
		break;
	case '4':display_graph();
		break;
	case '5': exit(0);
	default:
		break;
	}
}

