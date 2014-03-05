#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
/*--------------------------------------------------------------------------*/
/*  24-Aug-2013 --	Abhishek Prasad	-- Asteroids	    */

/*  Revisions */

//2-Sep-2013  -- Abhishek Prasad -- Assignment1 -- Wireframes
//27-Sep-2013 -- Abhishek Prasad -- Assignment2 -- Motion and Lighting
//10-Oct-2013 -- Abhishek Prasad -- Assignment3 -- Collisions and Gameplay
/*--------------------------------------------------------------------------*/

float angle = 30.0f;
float ExplosionAngle = 0.0f;
static int window;
float i = -4, d1, d2, d3, d4;
float rotAngle = 0;
float rotAntiClock = 0;
float speed = 0.00;
float shotSpeed = 0.06, alienShotSpeed1 = 0.02, alienShotSpeed2 = 0.04, shotFired = 0;
float aSteroidStats[8][8][11];
float yd, ydd, posy = 0, p, q, alienX, alienY, alienAngle, shipAngle, alienShotShipDistance, alienShipPlayerShipDistance, PlayerShotAlienShipDistance, alienActive;
float xd, xdd, posx = 0, alien2X, alien2Y, alien2Angle, ship2Angle, alien2ShotShipDistance, alien2ShipPlayerShipDistance, Player2ShotAlienShipDistance, alien2Active;
int start_id = 0, fireNext = 0;
int id = 4, m, j, k, l, restartFlag = 0;
float shotParam[100][100], alienShotParam[5], alien2ShotParam[5];
bool keyStates[256] = { false }; // Create an array of boolean values of length 256 (0-255)
float aSteroidRadius[6];
bool aSteroidActive[5] = { true };
float aSteroidSpeed = 0.01, aLienshipSpeed = 0.008, aLienship2Speed = 0.01;
float ExpStats[16][4];
float expSpeed = 0.1, ExpStep = 0.0, ExpAlive = 0.0, MaxCount = 2;
float playerScore = 0, playerLives = 3, playerBonus = 10000, timeSpent = 0;

typedef void(*Asteroids) (float, float, int, int, float, float, float);


// Menu items
enum MENU_TYPE
{
	MENU_NEW,
	MENU_QUIT,
};

void init()
{
	xd = 0;
	yd = 0;
	rotAngle = 0.0;
	shotParam[0][3] = 12;
	//initial xpositions
	aSteroidStats[1][1][2] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[2][1][2] = -0.1;
	aSteroidStats[3][1][2] = 1;
	aSteroidStats[4][1][2] = 1;
	aSteroidStats[5][1][2] = 0.2;
	aSteroidStats[6][1][2] = -1;
	//initial ypositions
	aSteroidStats[1][1][3] = 0.2;
	aSteroidStats[2][1][3] = 1;
	aSteroidStats[3][1][3] = 0.3;
	aSteroidStats[4][1][3] = -0.2;
	aSteroidStats[5][1][3] = -0.2;
	aSteroidStats[6][1][3] = -0.3;

	//xposition data
	aSteroidStats[1][1][4] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	aSteroidStats[2][1][4] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	aSteroidStats[3][1][4] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	aSteroidStats[4][1][4] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[5][1][4] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[6][1][4] = -(float)rand() / (float)RAND_MAX;
	//yposition data
	aSteroidStats[1][1][5] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[2][1][5] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[3][1][5] = (float)rand() / (float)RAND_MAX;
	aSteroidStats[4][1][5] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	aSteroidStats[5][1][5] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	aSteroidStats[6][1][5] = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));

	//set asteroid scale
	aSteroidStats[1][1][7] = 0.2;
	aSteroidStats[2][1][7] = 0.35;
	aSteroidStats[3][1][7] = 0.3;
	aSteroidStats[4][1][7] = 0.2;
	aSteroidStats[5][1][7] = 0.35;
	aSteroidStats[6][1][7] = 0.4;
	//radius
	aSteroidStats[1][1][9] = (0.5 / 5);
	aSteroidStats[2][1][9] = (0.35 / 4);
	aSteroidStats[3][1][9] = (0.25 / 3);
	aSteroidStats[4][1][9] = (0.5 / 5);
	aSteroidStats[5][1][9] = (0.35 / 4);
	aSteroidStats[6][1][9] = (0.5 / 3);


	for (j = 1; j<7; j++)
	{
		for (k = 1; k<8; k++)
			//DeActivate All
			aSteroidStats[j][k][6] = 0;

	}


	for (j = 1; j<7; j++)
	{
		//activate asteroid1
		aSteroidStats[j][1][6] = 1;

	}

	//angles
	for (j = 1; j<7; j++)
	{
		aSteroidStats[j][1][1] = (rand() % 180);
		aSteroidStats[j][2][1] = -(rand() % 90);
		aSteroidStats[j][3][1] = (rand() % 90);
		aSteroidStats[j][4][1] = -(rand() % 90);
		aSteroidStats[j][5][1] = (rand() % 90);
		aSteroidStats[j][6][1] = -(rand() % 90);
		aSteroidStats[j][7][1] = (rand() % 90);
	}
	timeSpent = 0;
}

void initAlienShip()
{
	//AlienShip
	alienX = -1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	alienY = (float)rand() / (float)RAND_MAX;
	alienActive = 1;
	alienAngle = (rand() % 180);
	alienShotParam[0] = alienX;
	alienShotParam[1] = alienY;
	alienShotParam[2] = alienAngle;
	alienShotParam[3] = 0;
	alienShotParam[4] = 1;
}

void initAlien2Ship()
{
	//AlienShip
	alien2X = 1 + (float)rand() / ((float)RAND_MAX / (1.2 - 1));
	alien2Y = (float)rand() / (float)RAND_MAX;
	alien2Active = 1;
	alien2Angle = (rand() % 180);
	alien2ShotParam[0] = alien2X;
	alien2ShotParam[1] = alien2Y;
	alien2ShotParam[2] = alien2Angle;
	alien2ShotParam[3] = 0;
	alien2ShotParam[4] = 1;
}

void restart()
{
	for (j = 1; j <= MaxCount; j++)
	{
		for (k = 1; k<8; k++)
		{
			if (aSteroidStats[j][k][6] == 1)
			{
				restartFlag = 2;
			}
		}
	}
	if (restartFlag == 0)
	{
		if (MaxCount <= 6)
		{
			MaxCount += 1;
		}
		init();
		initAlienShip();
		initAlien2Ship();
		timeSpent = 0;
	}
}

void reset()
{
	init();
	initAlienShip();
	initAlien2Ship();
	playerScore = 0;
	playerLives = 3;
	MaxCount = 2;
}

void idle()
{
	glutPostRedisplay();
}

int randNum()
{
	return rand();
}

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
void RenderScore()
{
	glPushMatrix();
	char buffer[33];
	glColor3f(1, 1, 1);
	renderBitmapString(-0.9, 0.8, 0.2, GLUT_BITMAP_9_BY_15, itoa(playerScore, buffer, 10));
	renderBitmapString(-0.9, 0.9, 0.2, GLUT_BITMAP_9_BY_15, "SCORE");
	renderBitmapString(0.8, 0.8, 0.2, GLUT_BITMAP_9_BY_15, itoa(playerLives, buffer, 10));
	renderBitmapString(0.8, 0.9, 0.2, GLUT_BITMAP_9_BY_15, "LIVES");
	renderBitmapString(-0.5, -0.9, 0.2, GLUT_BITMAP_HELVETICA_10, itoa(timeSpent, buffer, 10));
	renderBitmapString(-0.8, -0.9, -0.2, GLUT_BITMAP_HELVETICA_10, "Time Spent");
	glPopMatrix();
}

void explosion()
{
	glBegin(GL_POINTS); //starts drawing of points
	glVertex3f(0.0, 0.0, 0.0f);//upper-right corner
	glEnd();//end drawing of points
}

void renderExplosion()
{
	for (l = 1; l<15; l++)
	{
		glPushMatrix();
		ExpStats[l][2] += expSpeed * sin((0 - ExpStats[l][1] / 180)*3.14);
		ExpStats[l][3] += expSpeed * cos((0 - ExpStats[l][1] / 180)*3.14);
		glColor3f(1, 1, 1);
		glTranslatef(ExpStats[l][2], ExpStats[l][3], 0.0f);
		glRotatef(ExpStats[l][1], 1.0, 1.0, 0.0);
		glPointSize(3.0f);
		explosion();
		glPopMatrix();
	}

	ExpStep += 1;
	//if(ExpStep>55)
	//{
	//	ExpAlive=0;
	//}

}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false; // Set the state of the current key to not pressed
}

void processSpecialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		rotAngle = rotAngle + 10;
		break;
	case GLUT_KEY_RIGHT:
		rotAngle = rotAngle - 10;
		break;
	}
}

void keyboard()
{

	if (keyStates['x'] || keyStates['X'])
	{
		if (speed<0.03)
		{
			speed += 0.006;
		}

		xd += speed * sin((0 - rotAngle / 180)*3.14);
		yd += speed * cos((0 - rotAngle / 180)*3.14);
		xdd = xd;
		ydd = yd;

		if (xd>1.035)
		{
			xd = -1.035;
			if (yd != 0)
				yd = -yd;
		}
		else if (xd < -1.035)
		{
			xd = 1.035;
			if (yd != 0)
				yd = -yd;
		}

		if (yd>1.05)
			yd = -1.05;
		else if (yd < -1.05)
			yd = 1.05;
	}

	if (keyStates['z'] || keyStates['Z'])
	{
		////Bullet Music
		//PlaySound ("bullet.wav",NULL, SND_ASYNC|SND_FILENAME);



		if (id<4)
		{
			shotFired = 1;
			id++;
			shotParam[id][0] = xd; //bullet x position	
			shotParam[id][1] = yd; //bullet y position
			shotParam[id][2] = rotAngle; //bullet angle of trajectory
			shotParam[id][3] = 0; //bullet timestep
			shotParam[id][4] = 1; //Shot Validate
		}
		else if (shotParam[0][4] == 0 && shotParam[1][4] == 0 && shotParam[2][4] == 0 && shotParam[3][4] == 0)
		{
			id = 0;
		}
	}

}

void starfield()
{
	for (p = -1; p<1; p += 0.02)
	{
		for (q = -1; q<1; q += 0.02)
		{
			glBegin(GL_POINTS); //starts drawing of points
			glVertex3f(p, q, -1.0f);//upper-right corner
			glEnd();//end drawing of points
		}
	}
}

void renderStarfield()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glPointSize(1.0f);
	starfield();
	glPopMatrix();
}

void shot()
{
	glBegin(GL_POINTS); //starts drawing of points
	glVertex3f(shotParam[m][0], shotParam[m][1], 0.0f);//upper-right corner
	glEnd();//end drawing of points
}


void alienShot()
{
	glBegin(GL_POINTS); //starts drawing of points
	glVertex3f(alienShotParam[0], alienShotParam[1], 0.0f);//upper-right corner
	glEnd();//end drawing of points
}

void renderShot()
{
	//shot
	if (shotFired == 1 && id>0)// check if shots are fired
	{
		glPushMatrix();

		for (m = 1; m<id + 1; m++)//render from 1-4 id
		{
			if (shotParam[m][3]<15 & shotParam[m][4] != 0 & shotParam[m - 1][3] > 4) //lifespan of a bullet
			{
				glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f); //white color
				glPointSize(3.0f);//set point size to 3 pixels
				shot();
				glTranslatef(shotParam[m][0], shotParam[m][1], 0.0f);
				shotParam[m][0] += shotSpeed * sin((0 - shotParam[m][2] / 180)*3.14);//calculate next x pos
				shotParam[m][1] += shotSpeed * cos((0 - shotParam[m][2] / 180)*3.14);//calculate next y pos
				shotParam[m][3] += 1;//increment lifespan

				//PlayerShot and AlienShip Collision
				PlayerShotAlienShipDistance = (alienX - shotParam[m][0])*(alienX - shotParam[m][0]) + (alienY - shotParam[m][1])*(alienY - shotParam[m][1]);
				if (PlayerShotAlienShipDistance < (0.1*0.1) && alienActive == 1)
				{
					for (l = 1; l<15; l++)
					{
						ExpStats[l][2] = alienX;
						ExpStats[l][3] = alienY;
					}
					ExpAlive = 1.0;
					shotParam[m][4] = 0;
					playerScore += 200;
					alienActive = 0;
				}

				//PlayerShot and AlienShip2 Collision
				Player2ShotAlienShipDistance = (alien2X - shotParam[m][0])*(alien2X - shotParam[m][0]) + (alien2Y - shotParam[m][1])*(alien2Y - shotParam[m][1]);
				if (Player2ShotAlienShipDistance < (0.1*0.1) && alien2Active == 1)
				{
					for (l = 1; l<15; l++)
					{
						ExpStats[l][2] = alien2X;
						ExpStats[l][3] = alien2Y;
					}
					ExpAlive = 1.0;
					shotParam[m][4] = 0;
					playerScore += 200;
					alien2Active = 0;
				}
				//PLayer Shot and Asteroids Collision
				for (j = 1; j<7; j++)
				{
					for (k = 1; k<8; k++)
					{
						aSteroidStats[j][k][8] = (aSteroidStats[j][k][4] - shotParam[m][0])*(aSteroidStats[j][k][4] - shotParam[m][0]) + (aSteroidStats[j][k][5] - shotParam[m][1])*(aSteroidStats[j][k][5] - shotParam[m][1]);
#pragma region CollisionCheck
						if (aSteroidStats[j][k][8] < (aSteroidStats[j][k][9] * aSteroidStats[j][k][9]) && aSteroidStats[j][k][6] == 1 && shotParam[m][4] != 0)
						{
							shotParam[m][4] = 0;
							aSteroidStats[j][k][6] = 0;
							//score
							if (k == 1)
								playerScore += 20;
							else if (k == 2 || k == 3)
								playerScore += 50;
							else
								playerScore += 100;

							for (l = 1; l<15; l++)
							{
								ExpStats[l][2] = aSteroidStats[j][k][4];
								ExpStats[l][3] = aSteroidStats[j][k][5];
							}
							ExpAlive = 1.0;
#pragma region Asteroid1Split
							if (k == 1 && aSteroidStats[j][1][6] == 0)
							{
								aSteroidStats[j][2][6] = 1;
								aSteroidStats[j][3][6] = 1;
								aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
								aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
								aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
								aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

								aSteroidStats[j][2][7] = 0.17;
								aSteroidStats[j][3][7] = 0.17;

								aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.03;
								aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.03;
							}
#pragma endregion


							if (k == 2 && aSteroidStats[j][2][6] == 0)
							{
								aSteroidStats[j][4][6] = 1;
								aSteroidStats[j][5][6] = 1;
								aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
								aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
								aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
								aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

								aSteroidStats[j][4][7] = 0.11;
								aSteroidStats[j][5][7] = 0.11;

								aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.03;
								aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.03;
							}



							if (k == 3 && aSteroidStats[j][3][6] == 0)
							{
								aSteroidStats[j][6][6] = 1;
								aSteroidStats[j][7][6] = 1;
								aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
								aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
								aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
								aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

								aSteroidStats[j][6][7] = 0.11;
								aSteroidStats[j][7][7] = 0.11;

								aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.03;
								aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.03;
							}

						}
#pragma endregion
					}
				}
				glLoadIdentity();
				glPopMatrix();
			}
			else
			{
				shotParam[m][4] = 0;//invalidate the shot when lifespan is complete
				shotParam[m][3] = 0;
			}
		}
	}
}

void renderAlienShot()
{

	glPushMatrix();

	if (alienShotParam[3]<50 && alienShotParam[4] == 1) //lifespan of a bullet
	{
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f); //white color
		glPointSize(3.0f);//set point size to 3 pixels
		alienShot();
		glTranslatef(alienShotParam[0], alienShotParam[1], 0.0f);
		alienShotParam[0] -= alienShotSpeed1 * sin((0 - alienShotParam[2] / 180)*3.14);//calculate next x pos
		alienShotParam[1] -= alienShotSpeed1 * cos((0 - alienShotParam[2] / 180)*3.14);//calculate next y pos
		alienShotParam[3] += 1;//increment lifespan


		//AlienShot and PlayerShip Collision
		alienShotShipDistance = (xd - alienShotParam[0])*(xd - alienShotParam[0]) + (yd - alienShotParam[1])*(yd - alienShotParam[1]);
		if (alienShotShipDistance < (0.1*0.1) && alienActive == 1)
		{
			for (l = 1; l<15; l++)
			{
				ExpStats[l][2] = xd;
				ExpStats[l][3] = yd;
			}
			ExpAlive = 1.0;
			xd = 0;
			yd = 0;
			rotAngle = 0.0;
			alienShotParam[4] = 0;
			playerLives -= 1;
			if (playerLives == 0)
			{
				reset();
			}
		}

		//AlienSHot and Asteroid Collission
		for (j = 1; j<7; j++)
		{
			for (k = 1; k<8; k++)
			{
				aSteroidStats[j][k][8] = (aSteroidStats[j][k][4] - alienShotParam[0])*(aSteroidStats[j][k][4] - alienShotParam[0]) + (aSteroidStats[j][k][5] - alienShotParam[1])*(aSteroidStats[j][k][5] - alienShotParam[1]);
#pragma region ShotnAsteroidCollision
				if (aSteroidStats[j][k][8] < (aSteroidStats[j][k][9] * aSteroidStats[j][k][9]) && aSteroidStats[j][k][6] == 1 && alienActive == 1)
				{
					alienShotParam[4] = 0;
					aSteroidStats[j][k][6] = 0;
					for (l = 1; l<15; l++)
					{
						ExpStats[l][2] = aSteroidStats[j][k][4];
						ExpStats[l][3] = aSteroidStats[j][k][5];
					}
					ExpAlive = 1.0;

					if (k == 1 && aSteroidStats[j][1][6] == 0)
					{
						aSteroidStats[j][2][6] = 1;
						aSteroidStats[j][3][6] = 1;
						aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
						aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
						aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
						aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

						aSteroidStats[j][2][7] = 0.17;
						aSteroidStats[j][3][7] = 0.17;

						aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.03;
						aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.03;
					}


					if (k == 2 && aSteroidStats[j][2][6] == 0)
					{
						aSteroidStats[j][4][6] = 1;
						aSteroidStats[j][5][6] = 1;
						aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
						aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
						aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
						aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

						aSteroidStats[j][4][7] = 0.11;
						aSteroidStats[j][5][7] = 0.11;

						aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.03;
						aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.03;
					}



					if (k == 3 && aSteroidStats[j][3][6] == 0)
					{
						aSteroidStats[j][6][6] = 1;
						aSteroidStats[j][7][6] = 1;
						aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
						aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
						aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
						aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

						aSteroidStats[j][6][7] = 0.11;
						aSteroidStats[j][7][7] = 0.11;

						aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.03;
						aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.03;
					}

				}
#pragma endregion


			}
		}
		glLoadIdentity();
		glPopMatrix();
	}
	else
	{
		alienShotParam[0] = alienX;
		alienShotParam[1] = alienY;
		alienShotParam[2] = rand() % 270;
		alienShotParam[3] = 0;
		alienShotParam[4] = 1;
	}
}


void Ship()
{

	//top
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);//a
	glNormal3f(-0.01f, 0.08f, 0.0f);
	glVertex3f(-0.01f, 0.08f, 0.0f);//b
	glNormal3f(0.0f, 0.08f, 0.01f);
	glVertex3f(0.0f, 0.08f, 0.01f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);//a
	glNormal3f(0.0f, 0.08f, 0.01f);
	glVertex3f(0.0f, 0.08f, 0.01f);//c
	glNormal3f(0.01f, 0.08f, 0.0f);
	glVertex3f(0.01f, 0.08f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);//a
	glNormal3f(0.0f, 0.08f, -0.01f);
	glVertex3f(0.0f, 0.08f, -0.01f);//d
	glNormal3f(-0.01f, 0.08f, 0.0f);
	glVertex3f(-0.01f, 0.08f, 0.0f);//b
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);//a
	glNormal3f(0.01f, 0.08f, 0.0f);
	glVertex3f(0.01f, 0.08f, 0.0f);//e
	glNormal3f(0.0f, 0.08f, -0.01f);
	glVertex3f(0.0f, 0.08f, -0.01f);//d
	glEnd();


	//body
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.08f, 0.01f);
	glVertex3f(0.0f, 0.08f, 0.01f);//c
	glNormal3f(-0.01f, 0.08f, 0.0f);
	glVertex3f(-0.01f, 0.08f, 0.0f);//b
	glNormal3f(-0.01f, 0.01f, 0.0f);
	glVertex3f(-0.01f, 0.01f, 0.0f);//h
	glNormal3f(0.0f, 0.01f, 0.01f);
	glVertex3f(0.0f, 0.01f, 0.01f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.08f, 0.01f);
	glVertex3f(0.0f, 0.08f, 0.01f);//c
	glNormal3f(0.0f, 0.01f, 0.01f);
	glVertex3f(0.0f, 0.01f, 0.01f);//i
	glNormal3f(0.01, 0.01f, 0.0f);
	glVertex3f(0.01, 0.01f, 0.0f);//f
	glNormal3f(0.01f, 0.08f, 0.0f);
	glVertex3f(0.01f, 0.08f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, 0.08f, 0.0f);
	glVertex3f(-0.01f, 0.08f, 0.0f);//b
	glNormal3f(0.0f, 0.08f, -0.01f);
	glVertex3f(0.0f, 0.08f, -0.01f);//d
	glNormal3f(0.0f, 0.01f, -0.01f);
	glVertex3f(0.0f, 0.01f, -0.01f);//g
	glNormal3f(-0.01f, 0.01f, 0.0f);
	glVertex3f(-0.01f, 0.01f, 0.0f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.08f, -0.01f);
	glVertex3f(0.0f, 0.08f, -0.01f);//d
	glNormal3f(0.01f, 0.08f, 0.0f);
	glVertex3f(0.01f, 0.08f, 0.0f);//e
	glNormal3f(0.01, 0.01f, 0.0f);
	glVertex3f(0.01, 0.01f, 0.0f);//f
	glNormal3f(0.0f, 0.01f, -0.01f);
	glVertex3f(0.0f, 0.01f, -0.01f);//g
	glEnd();


	//fins
	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//j
	glNormal3f(-0.02f, 0.03f, 0.0f);
	glVertex3f(-0.02f, 0.03f, 0.0f);//k
	glNormal3f(-0.01f, 0.00f, 0.0f);
	glVertex3f(-0.01f, 0.00f, 0.0f);//l
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//j
	glNormal3f(-0.01f, 0.00f, 0.0f);
	glVertex3f(-0.01f, 0.00f, 0.0f);//l
	glNormal3f(-0.02f, 0.03f, 0.0f);
	glVertex3f(-0.02f, 0.03f, 0.0f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//m
	glNormal3f(0.02f, 0.03f, 0.0f);
	glVertex3f(0.02f, 0.03f, 0.0f);//n
	glNormal3f(0.01f, 0.00f, 0.0f);
	glVertex3f(0.01f, 0.00f, 0.0f);//o
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//m
	glNormal3f(0.01f, 0.00f, 0.0f);
	glVertex3f(0.01f, 0.00f, 0.0f);//o
	glNormal3f(0.02f, 0.03f, 0.0f);
	glVertex3f(0.02f, 0.03f, 0.0f);//n
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//p
	glNormal3f(0.0f, 0.03f, -0.02f);
	glVertex3f(0.0f, 0.03f, -0.02f);//q
	glNormal3f(0.0f, 0.00f, -0.01f);
	glVertex3f(0.0f, 0.00f, -0.01f);//r
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//p
	glNormal3f(0.0f, 0.00f, -0.01f);
	glVertex3f(0.0f, 0.00f, -0.01f);//r
	glNormal3f(0.0f, 0.03f, -0.02f);
	glVertex3f(0.0f, 0.03f, -0.02f);//q
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//s
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.02f);//t
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.00f, 0.01f);//u
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//s
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.00f, 0.01f);//u
	glNormal3f(0.0f, 0.00f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.02f);//t
	glEnd();

}
void BetterShip()
{

	//top
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);//a
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//b
	glNormal3f(0.0f, 0.03f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);//a
	glNormal3f(0.0f, 0.03f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//c
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);//a
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//d
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//b
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);//a
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//e
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//d
	glEnd();


	//body
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.03f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//c
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//b
	glNormal3f(-0.01f, -0.04f, 0.0f);
	glVertex3f(-0.01f, -0.04f, 0.0f);//h
	glNormal3f(0.0f, -0.04f, 0.01f);
	glVertex3f(0.0f, -0.04f, 0.01f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.03f, 0.01f);
	glVertex3f(0.0f, 0.03f, 0.01f);//c
	glNormal3f(0.0f, -0.04f, 0.01f);
	glVertex3f(0.0f, -0.04f, 0.01f);//i
	glNormal3f(0.01, -0.04f, 0.0f);
	glVertex3f(0.01, -0.04f, 0.0f);//f
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, 0.03f, 0.0f);
	glVertex3f(-0.01f, 0.03f, 0.0f);//b
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//d
	glNormal3f(0.0f, -0.04f, -0.01f);
	glVertex3f(0.0f, -0.04f, -0.01f);//g
	glNormal3f(-0.01f, -0.04f, 0.0f);
	glVertex3f(-0.01f, -0.04f, 0.0f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.03f, -0.01f);
	glVertex3f(0.0f, 0.03f, -0.01f);//d
	glNormal3f(0.01f, 0.03f, 0.0f);
	glVertex3f(0.01f, 0.03f, 0.0f);//e
	glNormal3f(0.01, -0.04f, 0.0f);
	glVertex3f(0.01, -0.04f, 0.0f);//f
	glNormal3f(0.0f, -0.04f, -0.01f);
	glVertex3f(0.0f, -0.04f, -0.01f);//g
	glEnd();


	//fins
	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, -0.02f, 0.0f);
	glVertex3f(-0.01f, -0.02f, 0.0f);//j
	glNormal3f(-0.02f, -0.02f, 0.0f);
	glVertex3f(-0.02f, -0.02f, 0.0f);//k
	glNormal3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.0f);//l
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(-0.01f, -0.02f, 0.0f);
	glVertex3f(-0.01f, -0.02f, 0.0f);//j
	glNormal3f(-0.01f, -0.05f, 0.0f);
	glVertex3f(-0.01f, -0.05f, 0.0f);//l
	glNormal3f(-0.02f, -0.02f, 0.0f);
	glVertex3f(-0.02f, -0.02f, 0.0f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.01f, -0.02f, 0.0f);
	glVertex3f(0.01f, -0.02f, 0.0f);//m
	glNormal3f(0.02f, -0.02f, 0.0f);
	glVertex3f(0.02f, -0.02f, 0.0f);//n
	glNormal3f(0.01f, -0.05f, 0.0f);
	glVertex3f(0.01f, -0.05f, 0.0f);//o
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.01f, -0.02f, 0.0f);
	glVertex3f(0.01f, -0.02f, 0.0f);//m
	glNormal3f(0.01f, -0.05f, 0.0f);
	glVertex3f(0.01f, -0.05f, 0.0f);//o
	glNormal3f(0.02f, -0.02f, 0.0f);
	glVertex3f(0.02f, -0.02f, 0.0f);//n
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.02f, -0.01f);
	glVertex3f(0.0f, -0.02f, -0.01f);//p
	glNormal3f(0.0f, -0.02f, -0.02f);
	glVertex3f(0.0f, -0.02f, -0.02f);//q
	glNormal3f(0.0f, -0.05f, -0.01f);
	glVertex3f(0.0f, -0.05f, -0.01f);//r
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.02f, -0.01f);
	glVertex3f(0.0f, -0.02f, -0.01f);//p
	glNormal3f(0.0f, -0.05f, -0.01f);
	glVertex3f(0.0f, -0.05f, -0.01f);//r
	glNormal3f(0.0f, -0.02f, -0.02f);
	glVertex3f(0.0f, -0.02f, -0.02f);//q
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.02f, 0.01f);
	glVertex3f(0.0f, -0.02f, 0.01f);//s
	glNormal3f(0.0f, -0.02f, 0.01f);
	glVertex3f(0.0f, -0.02f, 0.02f);//t
	glNormal3f(0.0f, -0.05f, 0.01f);
	glVertex3f(0.0f, -0.05f, 0.01f);//u
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.02f, 0.01f);
	glVertex3f(0.0f, -0.02f, 0.01f);//s
	glNormal3f(0.0f, -0.05f, 0.01f);
	glVertex3f(0.0f, -0.05f, 0.01f);//u
	glNormal3f(0.0f, -0.02f, 0.01f);
	glVertex3f(0.0f, -0.02f, 0.02f);//t
	glEnd();

}

void renderShip()
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(xd, yd, 0.0f);
	if (speed >0)
		speed -= 0.00005;
	if (speed <0)
		speed = 0;
	glRotatef(rotAngle, 0.0, 0.0, 1.0);
	BetterShip();


	//PLayer Ship and Alien Ship Collision

	alienShipPlayerShipDistance = (xd - alienX)*(xd - alienX) + (yd - alienY)*(yd - alienY);
	if (alienShipPlayerShipDistance < (0.1*0.1) && alienActive == 1)
	{
		for (l = 1; l<15; l++)
		{
			ExpStats[l][2] = xd;
			ExpStats[l][3] = yd;
		}
		ExpAlive = 1.0;
		xd = 0;
		yd = 0;
		rotAngle = 0.0;
		playerLives -= 1;
		if (playerLives == 0)
		{
			reset();
		}
		alienActive = 0;
	}

	//PLayer Ship and Alien Ship 2 Collision

	alien2ShipPlayerShipDistance = (xd - alien2X)*(xd - alien2X) + (yd - alien2Y)*(yd - alien2Y);
	if (alien2ShipPlayerShipDistance < (0.1*0.1) && alien2Active == 1)
	{
		for (l = 1; l<15; l++)
		{
			ExpStats[l][2] = xd;
			ExpStats[l][3] = yd;
		}
		ExpAlive = 1.0;
		xd = 0;
		yd = 0;
		rotAngle = 0.0;
		playerLives -= 1;
		if (playerLives == 0)
		{
			reset();
		}
		alien2Active = 0;
	}

	///PLayer Ship and Asteroid COllision
	for (j = 1; j<7; j++)
	{
		for (k = 1; k<8; k++)
		{
			aSteroidStats[j][k][10] = (aSteroidStats[j][k][4] - xd)*(aSteroidStats[j][k][4] - xd) + (aSteroidStats[j][k][5] - yd)*(aSteroidStats[j][k][5] - yd);

#pragma region CollisionCheck
			if (aSteroidStats[j][k][10] < ((aSteroidStats[j][k][9] - 0.015)*(aSteroidStats[j][k][9] - 0.015)) && aSteroidStats[j][k][6] == 1)
			{
				xd = 0;
				yd = 0;
				rotAngle = 0.0;
				playerLives -= 1;
				if (playerLives == 0)
				{
					reset();
				}
				for (l = 1; l<15; l++)
				{
					ExpStats[l][2] = aSteroidStats[j][k][4];
					ExpStats[l][3] = aSteroidStats[j][k][5];
				}
				ExpAlive = 1.0;

				aSteroidStats[j][k][6] = 0;

				if (k == 1 && aSteroidStats[j][1][6] == 0)
				{
					aSteroidStats[j][2][6] = 1;
					aSteroidStats[j][3][6] = 1;
					aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
					aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

					aSteroidStats[j][2][7] = 0.17;
					aSteroidStats[j][3][7] = 0.17;

					aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.02;
				}

				if (k == 2 && aSteroidStats[j][2][6] == 0)
				{
					aSteroidStats[j][4][6] = 1;
					aSteroidStats[j][5][6] = 1;
					aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
					aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

					aSteroidStats[j][4][7] = 0.11;
					aSteroidStats[j][5][7] = 0.11;

					aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.02;
				}



				if (k == 3 && aSteroidStats[j][3][6] == 0)
				{
					aSteroidStats[j][6][6] = 1;
					aSteroidStats[j][7][6] = 1;
					aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
					aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

					aSteroidStats[j][6][7] = 0.11;
					aSteroidStats[j][7][7] = 0.11;

					aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.02;
					aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.02;
				}
			}
#pragma endregion
		}
	}
	glPopMatrix();
}

void alienShip()
{

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glEnd();

	//Backside

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glEnd();

	//SIDEWAYS
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.0f, 0.4f, -0.1f);//bb
	glNormal3f(-0.4f, 0.0f, -0.1f);
	glVertex3f(-0.4f, 0.0f, -0.1f);//cc
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.0f, 0.4f, -0.1f);//bb
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.4f, 0.00f, -0.1f);
	glVertex3f(0.4f, 0.00f, -0.1f);//aa
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.4f, 0.00f, -0.1f);//aa
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glNormal3f(0.0f, -0.5f, -0.1f);
	glVertex3f(0.0f, -0.5f, -0.1f);//ff
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.5f, -0.1f);
	glVertex3f(0.0f, -0.5f, -0.1f);//ff
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.2f, 0.0f, -0.1f);
	glVertex3f(-0.2f, 0.0f, -0.1f);//ee
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, -0.1f);
	glVertex3f(-0.2f, 0.0f, -0.1f);//ee
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.3f, -0.2, -0.1f);
	glVertex3f(-0.3f, -0.2, -0.1f);//dd
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.3f, -0.2, -0.1f);
	glVertex3f(-0.3f, -0.2, -0.1f);//dd
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.4f, 0.0f, -0.1f);
	glVertex3f(-0.4f, 0.0f, -0.1f);//cc
	glEnd();



}

void renderAlienship()
{
	//////Asteroid1
	glPushMatrix();
	glColor3f(0.23, 0.52549, 0.0431373);
	alienX += aLienshipSpeed - 0.001;
	alienY -= aLienshipSpeed + (0.002 + (float)rand() / ((float)RAND_MAX / (0.01 - 0))) * cos((0 - alienAngle / 180)*3.14);
	alienY += aLienshipSpeed + (0.01 + (float)rand() / ((float)RAND_MAX / (0.01 - 0))) * cos((0 - alienAngle / 180)*3.14);

	if (alienX>1.035)
	{
		initAlienShip();
	}
	else if (alienX < -1.035)
	{
		initAlienShip();
	}

	if (alienY>1.035)
		alienY = -1.035;
	else if (alienY < -1.035)
		alienY = 1.035;

	if (alienAngle >= 0 & alienAngle <= 90)
		shipAngle = -45;
	glTranslatef(alienX, alienY, 0);
	glScalef(0.15, 0.15, 0.15);
	glRotatef(alienAngle + 180, 0.0, 0.0, 1.0);
	alienShip();

	///Alien Ship and Asteroid COllision
	for (j = 1; j<7; j++)
	{
		for (k = 1; k<8; k++)
		{
			aSteroidStats[j][k][10] = (aSteroidStats[j][k][4] - alienX)*(aSteroidStats[j][k][4] - alienX) + (aSteroidStats[j][k][5] - alienY)*(aSteroidStats[j][k][5] - alienY);
#pragma region CollisionCheck
			if (aSteroidStats[j][k][10] < ((aSteroidStats[j][k][9] - 0.05)*(aSteroidStats[j][k][9] - 0.05)) && aSteroidStats[j][k][6] == 1 && alienActive == 1)
			{
				alienActive = 0;
				for (l = 1; l<15; l++)
				{
					ExpStats[l][2] = aSteroidStats[j][k][4];
					ExpStats[l][3] = aSteroidStats[j][k][5];
				}
				ExpAlive = 1.0;

				aSteroidStats[j][k][6] = 0;

				if (k == 1 && aSteroidStats[j][1][6] == 0)
				{
					aSteroidStats[j][2][6] = 1;
					aSteroidStats[j][3][6] = 1;
					aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
					aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

					aSteroidStats[j][2][7] = 0.17;
					aSteroidStats[j][3][7] = 0.17;

					aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.02;
				}

				if (k == 2 && aSteroidStats[j][2][6] == 0)
				{
					aSteroidStats[j][4][6] = 1;
					aSteroidStats[j][5][6] = 1;
					aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
					aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

					aSteroidStats[j][4][7] = 0.11;
					aSteroidStats[j][5][7] = 0.11;

					aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.02;
				}



				if (k == 3 && aSteroidStats[j][3][6] == 0)
				{
					aSteroidStats[j][6][6] = 1;
					aSteroidStats[j][7][6] = 1;
					aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
					aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

					aSteroidStats[j][6][7] = 0.11;
					aSteroidStats[j][7][7] = 0.11;

					aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.02;
					aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.02;
				}
			}
#pragma endregion
		}
	}

	glPopMatrix();
}

#pragma region Asteroid1
void aSteroid1()
{

	glColor3f(0.721569, 0.52549, 0.0431373);
	glBegin(GL_POLYGON);
	glNormal3f(0.3f, 0.15f, 0.3f);
	glVertex3f(0.3f, 0.15f, 0.3f);//g
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(0.1f, 0.1f, 0.2f);
	glVertex3f(0.1f, 0.1f, 0.2f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glNormal3f(0.1f, 0.1f, 0.2f);
	glVertex3f(0.1f, 0.1f, 0.2f);//h
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.1f, 0.2f);
	glVertex3f(0.1f, 0.1f, 0.2f);//h
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glNormal3f(-0.2f, 0.0f, 0.3f);
	glVertex3f(-0.2f, 0.0f, 0.3f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glNormal3f(-0.2f, 0.0f, 0.3f);
	glVertex3f(-0.2f, 0.0f, 0.3f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, 0.3f);
	glVertex3f(-0.2f, 0.0f, 0.3f);//i
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glNormal3f(-0.2f, -0.2f, 0.1f);
	glVertex3f(-0.2f, -0.2f, 0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, -0.2f, 0.1f);
	glVertex3f(-0.2f, -0.2f, 0.1f);//j
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glNormal3f(-0.2f, 0.0f, 0.3f);
	glVertex3f(-0.2f, 0.0f, 0.3f);//i
	glNormal3f(-0.2f, -0.2f, 0.1f);
	glVertex3f(-0.2f, -0.2f, 0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, -0.2f, 0.1f);
	glVertex3f(-0.2f, -0.2f, 0.1f);//j
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glNormal3f(0.1f, 0.1f, 0.2f);
	glVertex3f(0.1f, 0.1f, 0.2f);//h
	glNormal3f(-0.2f, 0.0f, 0.3f);
	glVertex3f(-0.2f, 0.0f, 0.3f);//i
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.3f, 0.15f, 0.3f);
	glVertex3f(0.3f, 0.15f, 0.3f);//g
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, 0.15f, 0.3f);
	glVertex3f(0.3f, 0.15f, 0.3f);//g
	glNormal3f(0.1f, 0.1f, 0.2f);
	glVertex3f(0.1f, 0.1f, 0.2f);//h
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(0.3f, 0.15f, 0.3f);
	glVertex3f(0.3f, 0.15f, 0.3f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.05f, 0.35f);
	glVertex3f(0.15f, -0.05f, 0.35f);//l
	glNormal3f(0.0f, -0.3f, 0.1f);
	glVertex3f(0.0f, -0.3f, 0.1f);//k
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glEnd();

	////BackSide

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(0.3f, 0.15f, -0.3f);
	glVertex3f(0.3f, 0.15f, -0.3f);//g
	glNormal3f(0.1f, 0.1f, -0.2f);
	glVertex3f(0.1f, 0.1f, -0.2f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(0.1f, 0.1f, -0.2f);
	glVertex3f(0.1f, 0.1f, -0.2f);//h
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glNormal3f(0.1f, 0.1f, -0.2f);
	glVertex3f(0.1f, 0.1f, -0.2f);//h
	glNormal3f(-0.2f, 0.0f, -0.3f);
	glVertex3f(-0.2f, 0.0f, -0.3f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.3f, 0.0f);
	glVertex3f(-0.2f, 0.3f, 0.0f);//c
	glNormal3f(-0.2f, 0.0f, -0.3f);
	glVertex3f(-0.2f, 0.0f, -0.3f);//i
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glNormal3f(-0.2f, 0.0f, -0.3f);
	glVertex3f(-0.2f, 0.0f, -0.3f);//i
	glNormal3f(-0.2f, -0.2f, -0.1f);
	glVertex3f(-0.2f, -0.2f, -0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);//d
	glNormal3f(-0.2f, -0.2f, -0.1f);
	glVertex3f(-0.2f, -0.2f, -0.1f);//j
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, -0.3f);
	glVertex3f(-0.2f, 0.0f, -0.3f);//i
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glNormal3f(-0.2f, -0.2f, -0.1f);
	glVertex3f(-0.2f, -0.2f, -0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, -0.2f, -0.1f);
	glVertex3f(-0.2f, -0.2f, -0.1f);//j
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glNormal3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.1f, -0.2f);
	glVertex3f(0.1f, 0.1f, -0.2f);//h
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glNormal3f(-0.2f, 0.0f, -0.3f);
	glVertex3f(-0.2f, 0.0f, -0.3f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, 0.15f, -0.3f);
	glVertex3f(0.3f, 0.15f, -0.3f);//g
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.1f, -0.2f);
	glVertex3f(0.1f, 0.1f, -0.2f);//h
	glNormal3f(0.3f, 0.15f, -0.3f);
	glVertex3f(0.3f, 0.15f, -0.3f);//g
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.3f, 0.0f);
	glVertex3f(0.4f, 0.3f, 0.0f);//b
	glNormal3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);//a
	glNormal3f(0.3f, 0.15f, -0.3f);
	glVertex3f(0.3f, 0.15f, -0.3f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.15f, -0.05f, -0.2f);
	glVertex3f(0.15f, -0.05f, -0.2f);//l
	glNormal3f(0.15f, -0.4f, 0.0f);
	glVertex3f(0.15f, -0.4f, 0.0f);//f
	glNormal3f(0.0f, -0.3f, -0.3f);
	glVertex3f(0.0f, -0.3f, -0.3f);//k
	glEnd();

}
#pragma endregion
void renderAsteroid1(float x, float y, int j, int k, float sx, float sy, float sz)
{
	//////Asteroid1
	glPushMatrix();
	glColor3f(0.721569, 0.52549, 0.0431373);


	x += aSteroidSpeed * sin((0 - aSteroidStats[j][k][1] / 180)*3.14);
	y += aSteroidSpeed * cos((0 - aSteroidStats[j][k][1] / 180)*3.14);
	if (x>1.035)
	{
		x = -1.035;
		if (y != 0)
			y = -y;
	}
	else if (x < -1.035)
	{
		x = 1.035;
		if (y != 0)
			y = -y;
	}

	if (y>1.035)
		y = -1.035;
	else if (y < -1.035)
		y = 1.035;

	aSteroidStats[j][k][4] = x;
	aSteroidStats[j][k][5] = y;

	glTranslatef(x, y, 0);
	glScalef(sx, sy, sz);
	glRotatef(angle, 1.0, 1.0, 0.0);
	aSteroid1();
	glPopMatrix();

}

void aSteroid2()
{

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//b
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//b
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glNormal3f(-0.1f, 0.1f, 0.2f);
	glVertex3f(-0.1f, 0.1f, 0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.1f, 0.2f);
	glVertex3f(-0.1f, 0.1f, 0.2f);//k
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glNormal3f(-0.1f, 0.1f, 0.2f);
	glVertex3f(-0.1f, 0.1f, 0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glNormal3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glNormal3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);//e
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//f
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);//h
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);//h
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glNormal3f(0.05f, 0.0f, 0.2f);
	glVertex3f(0.05f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);//j
	glNormal3f(-0.1f, 0.1f, 0.2f);
	glVertex3f(-0.1f, 0.1f, 0.2f);//k
	glNormal3f(-0.1f, -0.1f, 0.1f);
	glVertex3f(-0.1f, -0.1f, 0.1f);//l
	glEnd();



	//BackSide
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//b
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//b
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glNormal3f(-0.1f, 0.1f, -0.2f);
	glVertex3f(-0.1f, 0.1f, -0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//c
	glNormal3f(-0.1f, 0.1f, -0.2f);
	glVertex3f(-0.1f, 0.1f, -0.2f);//k
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glNormal3f(-0.1f, 0.1f, -0.2f);
	glVertex3f(-0.1f, 0.1f, -0.2f);//k
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);//d
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glNormal3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, -0.1f, 0.0f);
	glVertex3f(-0.2f, -0.1f, 0.0f);//e
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glNormal3f(0.05f, 0.0f, -0.2f);
	glVertex3f(0.05f, 0.0f, -0.2f);//m
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.05f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.2f, 0.0f);//g
	glNormal3f(0.05f, 0.0f, -0.2f);
	glVertex3f(0.05f, 0.0f, -0.2f);//m
	glNormal3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);//h
	glNormal3f(0.05f, 0.0f, -0.2f);
	glVertex3f(0.05f, 0.0f, -0.2f);//m
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//i
	glNormal3f(0.05f, 0.0f, -0.2f);
	glVertex3f(0.05f, 0.0f, -0.2f);//m
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glNormal3f(0.05f, 0.0f, -0.2f);
	glVertex3f(0.05f, 0.0f, -0.2f);//m
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);//j
	glNormal3f(-0.1f, -0.1f, -0.1f);
	glVertex3f(-0.1f, -0.1f, -0.1f);//l
	glNormal3f(-0.1f, 0.1f, -0.2f);
	glVertex3f(-0.1f, 0.1f, -0.2f);//k
	glEnd();
}

void renderAsteroid2(float x, float y, int j, int k, float sx, float sy, float sz)
{
	//////Asteroid2
	glPushMatrix();
	glColor3f(1, 0.54902, 0);


	x -= aSteroidSpeed * sin((0 - aSteroidStats[j][k][1] / 180)*3.14);
	y += aSteroidSpeed * cos((0 - aSteroidStats[j][k][1] / 180)*3.14);

	if (x>1.035)
	{
		x = -1.035;
		if (y != 1.035)
			y = -y;
	}
	else if (x< -1.035)
	{
		x = 1.035;
		if (y != 0)
			y = -y;
	}

	if (y>1.035)
		y = -1.035;
	else if (y < -1.035)
		y = 1.035;

	aSteroidStats[j][k][4] = x;
	aSteroidStats[j][k][5] = y;

	glTranslatef(x, y, 0);
	glScalef(sx, sy, sz);
	glRotatef(angle, 1.0, 1.0, 1.0);
	aSteroid2();
	glPopMatrix();
}

void aSteroid3()
{

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//a
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(0.08f, 0.1f, 0.2f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.08f, 0.1f, 0.2f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(-0.02f, 0.05f, 0.2f);
	glVertex3f(-0.02f, 0.05f, 0.2f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glNormal3f(-0.02f, 0.05f, 0.2f);
	glVertex3f(-0.02f, 0.05f, 0.2f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(-0.2f, 0.05f, 0.0f);
	glVertex3f(-0.2f, 0.05f, 0.0f);//c
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.05f, 0.0f);
	glVertex3f(-0.2f, 0.05f, 0.0f);//c
	glNormal3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);//d
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glNormal3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);//d
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.2f);//l
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.2f);//l
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glNormal3f(0.0f, -0.05f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.05f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);//f
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glNormal3f(0.2f, 0.0f, 0.2f);
	glVertex3f(0.2f, 0.0f, 0.2f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glNormal3f(0.2f, 0.0f, 0.2f);
	glVertex3f(0.2f, 0.0f, 0.2f);//h
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//a
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glNormal3f(-0.02f, 0.05f, 0.2f);
	glVertex3f(-0.02f, 0.05f, 0.2f);//j
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.1f, 0.2f);//i
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, 0.2f);
	glVertex3f(-0.1f, 0.02f, 0.2f);//k
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.2f);//l
	glNormal3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, 0.2f);//m
	glEnd();


	//Backside

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//a
	glNormal3f(0.08f, 0.1f, -0.2f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(0.08f, 0.1f, -0.2f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glNormal3f(-0.02f, 0.05f, -0.2f);
	glVertex3f(-0.02f, 0.05f, -0.2f);//j
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(-0.02f, 0.05f, -0.2f);
	glVertex3f(-0.02f, 0.05f, -0.2f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.05f, 0.0f);
	glVertex3f(-0.2f, 0.05f, 0.0f);//c
	glNormal3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);//b
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.05f, 0.0f);
	glVertex3f(-0.2f, 0.05f, 0.0f);//c
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glNormal3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.25f, -0.05f, 0.0f);
	glVertex3f(-0.25f, -0.05f, 0.0f);//d
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glNormal3f(-0.1f, -0.1f, -0.2f);
	glVertex3f(-0.1f, -0.1f, -0.2f);//l
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, -0.1f, 0.2f);
	glVertex3f(-0.1f, -0.1f, 0.2f);//l
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(0.0f, -0.05f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);//f
	glNormal3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glNormal3f(0.0f, -0.05f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);//f
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(0.08f, 0.1f, -0.2f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.08f, 0.1f, -0.2f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glNormal3f(0.3f, 0.0f, -0.2f);
	glVertex3f(0.3f, 0.0f, -0.2f);//h
	glNormal3f(0.1f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.1f, 0.0f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, -0.1f, -0.0f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glNormal3f(0.2f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.2f, 0.0f);//a
	glNormal3f(0.3f, 0.0f, -0.2f);
	glVertex3f(0.3f, 0.0f, -0.2f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.08f, 0.1f, -0.2f);
	glVertex3f(0.08f, 0.1f, -0.2f);//i
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(-0.02f, 0.05f, -0.2f);
	glVertex3f(-0.02f, 0.05f, -0.2f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.02f, 0.05f, -0.2f);
	glVertex3f(-0.02f, 0.05f, -0.2f);//j
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.02f, -0.2f);
	glVertex3f(-0.1f, 0.02f, -0.2f);//k
	glNormal3f(0.0f, 0.0f, -0.2f);
	glVertex3f(0.0f, 0.0f, -0.2f);//m
	glNormal3f(-0.1f, -0.1f, -0.2f);
	glVertex3f(-0.1f, -0.1f, -0.2f);//l

	glEnd();

	glBegin(GL_LINE_LOOP);//start drawing a line loop


	glEnd();//end drawing of line loop
}

void renderAsteroid3(float x, float y, int j, int k, float sx, float sy, float sz)
{
	//Asteroid3
	glPushMatrix();
	glColor3f(1, 0.647059, 0);


	x += aSteroidSpeed * sin((0 - aSteroidStats[j][k][1] / 180)*3.14);
	y += aSteroidSpeed * cos((0 - aSteroidStats[j][k][1] / 180)*3.14);

	if (x>1.2)
	{
		x = -1.2;
		if (y != 0)
			y = -y;
	}
	else if (x< -1.2)
	{
		x = 1.2;
		if (y != 0)
			y = -y;
	}

	if (y>1.2)
		y = -1.2;
	else if (y < -1.2)
		y = 1.2;

	aSteroidStats[j][k][4] = x;
	aSteroidStats[j][k][5] = y;

	glTranslatef(x, y, 0.0f);
	glScalef(sx, sy, sz);
	glRotatef(angle, 1.0, 1.0, 0.0);
	aSteroid3();
	glPopMatrix();
}

void aSteroid4()
{

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.25f, 0.0f);
	glVertex3f(0.1f, 0.25f, 0.0f);//b
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glNormal3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.1f, 0.0f);//a
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.25f, 0.0f);
	glVertex3f(0.1f, 0.25f, 0.0f);//b
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//c
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//c
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(-0.05f, 0.15f, 0.2f);
	glVertex3f(-0.05f, 0.15f, 0.2f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glNormal3f(-0.05f, 0.15f, 0.2f);
	glVertex3f(-0.05f, 0.15f, 0.2f);//l
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(-0.25f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.1f, 0.0f);//e
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.25f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.1f, 0.0f);//e
	glNormal3f(-0.25f, -0.1f, 0.0f);
	glVertex3f(-0.25f, -0.1f, 0.0f);//f
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glNormal3f(-0.25f, -0.1f, 0.0f);
	glVertex3f(-0.25f, -0.1f, 0.0f);//f
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glNormal3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);//p
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);//p
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glNormal3f(0.0f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);//h
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);//p
	glNormal3f(0.0f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);//h
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);//p
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i
	glNormal3f(0.25f, -0.1f, 0.0f);
	glVertex3f(0.25f, -0.1f, 0.0f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glNormal3f(0.25f, -0.1f, 0.0f);
	glVertex3f(0.25f, -0.1f, 0.0f);//j
	glNormal3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.1f, 0.0f);//a
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glNormal3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.1f, 0.0f);//a
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glNormal3f(-0.05f, 0.15f, 0.2f);
	glVertex3f(-0.05f, 0.15f, 0.2f);//l
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glNormal3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);//p
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, 0.1f);
	glVertex3f(0.05f, 0.2f, 0.1f);//k
	glNormal3f(-0.11f, -0.09f, 0.1f);
	glVertex3f(-0.11f, -0.09f, 0.1f);//m
	glNormal3f(0.09f, 0.1f, 0.2f);
	glVertex3f(0.09f, 0.1f, 0.2f);//n
	glEnd();


	//BackSide

	glBegin(GL_POLYGON);
	glNormal3f(0.1f, 0.25f, 0.0f);
	glVertex3f(0.1f, 0.25f, 0.0f);//b
	glNormal3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.1f, 0.0f);//a
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//c
	glNormal3f(0.1f, 0.25f, 0.0f);
	glVertex3f(0.1f, 0.25f, 0.0f);//b
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);//c
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glNormal3f(-0.05f, 0.15f, -0.2f);
	glVertex3f(-0.05f, 0.15f, -0.2f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(-0.05f, 0.15f, -0.2f);
	glVertex3f(-0.05f, 0.15f, -0.2f);//l
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(-0.1f, 0.25f, 0.0f);
	glVertex3f(-0.1f, 0.25f, 0.0f);//d
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glNormal3f(-0.25f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.1f, 0.0f);//e
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.25f, 0.1f, 0.0f);
	glVertex3f(-0.25f, 0.1f, 0.0f);//e
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glNormal3f(-0.25f, -0.1f, 0.0f);
	glVertex3f(-0.25f, -0.1f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glNormal3f(-0.25f, -0.1f, 0.0f);
	glVertex3f(-0.25f, -0.1f, 0.0f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glNormal3f(0.0f, -0.2f, -0.1f);
	glVertex3f(0.0f, -0.2f, -0.1f);//p
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, -0.1f);
	glVertex3f(0.0f, -0.2f, -0.1f);//p
	glNormal3f(0.0f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);//h
	glNormal3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);//g
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, -0.1f);
	glVertex3f(0.0f, -0.2f, -0.1f);//p
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i
	glNormal3f(0.0f, -0.3f, 0.0f);
	glVertex3f(0.0f, -0.3f, 0.0f);//h
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.2f, -0.1f);
	glVertex3f(0.0f, -0.2f, -0.1f);//p
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glNormal3f(0.25f, -0.1f, 0.0f);
	glVertex3f(0.25f, -0.1f, 0.0f);//j
	glNormal3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);//i

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glNormal3f(0.25f, 0.1f, 0.0f);
	glVertex3f(0.25f, 0.1f, 0.0f);//a
	glNormal3f(0.25f, -0.1f, -0.0f);
	glVertex3f(0.25f, -0.1f, -0.0f);//j
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glNormal3f(0.25f, 0.1f, -0.0f);
	glVertex3f(0.25f, 0.1f, -0.0f);//a
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glNormal3f(-0.05f, 0.15f, -0.2f);
	glVertex3f(-0.05f, 0.15f, -0.2f);//l
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glNormal3f(0.0f, -0.2f, -0.1f);
	glVertex3f(0.0f, -0.2f, -0.1f);//p
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.05f, 0.2f, -0.1f);
	glVertex3f(0.05f, 0.2f, -0.1f);//k
	glNormal3f(0.09f, 0.1f, -0.2f);
	glVertex3f(0.09f, 0.1f, -0.2f);//n
	glNormal3f(-0.11f, -0.09f, -0.1f);
	glVertex3f(-0.11f, -0.09f, -0.1f);//m
	glEnd();

}

void renderAsteroid4(float x, float y, int j, int k, float sx, float sy, float sz)
{
	//Asteroid4
	glPushMatrix();
	glColor3f(0.854902, 0.647059, 0.12549);

	x += aSteroidSpeed * sin((0 - aSteroidStats[j][k][1] / 180)*3.14);
	y -= aSteroidSpeed * cos((0 - aSteroidStats[j][k][1] / 180)*3.14);

	if (x>1.035)
	{
		x = -1.035;
		if (y != 0)
			y = -y;
	}
	else if (x< -1.035)
	{
		x = 1.035;
		if (y != 0)
			y = -y;
	}

	if (y>1.035)
		y = -1.035;
	else if (y < -1.035)
		y = 1;

	aSteroidStats[j][k][4] = x;
	aSteroidStats[j][k][5] = y;

	glTranslatef(x, y, 0.0f);
	glScalef(sx, sy, sz);
	glRotatef(angle, 1.0, 1.0, 0.0);
	aSteroid4();
	glPopMatrix();
}

void alien2Shot()
{
	glBegin(GL_POINTS); //starts drawing of points
	glVertex3f(alien2ShotParam[0], alien2ShotParam[1], 0.0f);//upper-right corner
	glEnd();//end drawing of points
}
void render2AlienShot()
{

	glPushMatrix();

	if (alien2ShotParam[3]<50 && alien2ShotParam[4] == 1) //lifespan of a bullet
	{
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f); //white color
		glPointSize(3.0f);//set point size to 3 pixels
		alien2Shot();
		glTranslatef(alien2ShotParam[0], alien2ShotParam[1], 0.0f);
		alien2ShotParam[0] -= alienShotSpeed2 * sin((0 - alien2ShotParam[2] / 180)*3.14);//calculate next x pos
		alien2ShotParam[1] -= alienShotSpeed2 * cos((0 - alien2ShotParam[2] / 180)*3.14);//calculate next y pos
		alien2ShotParam[3] += 1;//increment lifespan


		//AlienShot and PlayerShip Collision
		alien2ShotShipDistance = (xd - alien2ShotParam[0])*(xd - alien2ShotParam[0]) + (yd - alien2ShotParam[1])*(yd - alien2ShotParam[1]);
		if (alien2ShotShipDistance < (0.1*0.1) && alien2Active == 1)
		{
			for (l = 1; l<15; l++)
			{
				ExpStats[l][2] = xd;
				ExpStats[l][3] = yd;
			}
			ExpAlive = 1.0;
			xd = 0;
			yd = 0;
			rotAngle = 0.0;
			alien2ShotParam[4] = 0;
			playerLives -= 1;
			if (playerLives == 0)
			{
				reset();
			}
		}

		//AlienSHot and Asteroid Collission
		for (j = 1; j<7; j++)
		{
			for (k = 1; k<8; k++)
			{
				aSteroidStats[j][k][8] = (aSteroidStats[j][k][4] - alien2ShotParam[0])*(aSteroidStats[j][k][4] - alien2ShotParam[0]) + (aSteroidStats[j][k][5] - alien2ShotParam[1])*(aSteroidStats[j][k][5] - alien2ShotParam[1]);
#pragma region ShotnAsteroidCollision
				if (aSteroidStats[j][k][8] < (aSteroidStats[j][k][9] * aSteroidStats[j][k][9]) && aSteroidStats[j][k][6] == 1 && alien2Active == 1)
				{
					alien2ShotParam[4] = 0;
					aSteroidStats[j][k][6] = 0;
					for (l = 1; l<15; l++)
					{
						ExpStats[l][2] = aSteroidStats[j][k][4];
						ExpStats[l][3] = aSteroidStats[j][k][5];
					}
					ExpAlive = 1.0;

					if (k == 1 && aSteroidStats[j][1][6] == 0)
					{
						aSteroidStats[j][2][6] = 1;
						aSteroidStats[j][3][6] = 1;
						aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
						aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
						aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
						aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

						aSteroidStats[j][2][7] = 0.17;
						aSteroidStats[j][3][7] = 0.17;

						aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.03;
						aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.03;
					}


					if (k == 2 && aSteroidStats[j][2][6] == 0)
					{
						aSteroidStats[j][4][6] = 1;
						aSteroidStats[j][5][6] = 1;
						aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
						aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
						aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
						aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

						aSteroidStats[j][4][7] = 0.11;
						aSteroidStats[j][5][7] = 0.11;

						aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.03;
						aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.03;
					}



					if (k == 3 && aSteroidStats[j][3][6] == 0)
					{
						aSteroidStats[j][6][6] = 1;
						aSteroidStats[j][7][6] = 1;
						aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
						aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
						aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
						aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

						aSteroidStats[j][6][7] = 0.11;
						aSteroidStats[j][7][7] = 0.11;

						aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.03;
						aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.03;
					}

				}
#pragma endregion


			}
		}
		glLoadIdentity();
		glPopMatrix();
	}
	else
	{
		alien2ShotParam[0] = alien2X;
		alien2ShotParam[1] = alien2Y;
		alien2ShotParam[2] = rand() % 270;
		alien2ShotParam[3] = 0;
		alien2ShotParam[4] = 1;
	}
}
void alien2Ship()
{

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glEnd();

	//Backside

	glBegin(GL_POLYGON);
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glEnd();

	//SIDEWAYS
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.0f, 0.4f, -0.1f);//bb
	glNormal3f(-0.4f, 0.0f, -0.1f);
	glVertex3f(-0.4f, 0.0f, -0.1f);//cc
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.0f, 0.4f, -0.1f);//bb
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.0f, 0.4f, 0.00f);//b
	glNormal3f(0.4f, 0.00f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.4f, 0.00f, -0.1f);
	glVertex3f(0.4f, 0.00f, -0.1f);//aa
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.4f, -0.1f);
	glVertex3f(0.4f, 0.00f, -0.1f);//aa
	glNormal3f(0.0f, 0.4f, 0.00f);
	glVertex3f(0.4f, 0.00f, 0.00f);//a
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.3f, -0.2f, -0.1f);
	glVertex3f(0.3f, -0.2f, -0.1f);//hh
	glNormal3f(0.3f, -0.2f, 0.00f);
	glVertex3f(0.3f, -0.2f, 0.00f);//h
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glEnd();


	glBegin(GL_POLYGON);
	glNormal3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);//gg
	glNormal3f(0.2f, 0.0f, 0.00f);
	glVertex3f(0.2f, 0.0f, 0.00f);//g
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glNormal3f(0.0f, -0.5f, -0.1f);
	glVertex3f(0.0f, -0.5f, -0.1f);//ff
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -0.5f, -0.1f);
	glVertex3f(0.0f, -0.5f, -0.1f);//ff
	glNormal3f(0.0f, -0.5f, 0.00f);
	glVertex3f(0.0f, -0.5f, 0.00f);//f
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.2f, 0.0f, -0.1f);
	glVertex3f(-0.2f, 0.0f, -0.1f);//ee
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.2f, 0.0f, -0.1f);
	glVertex3f(-0.2f, 0.0f, -0.1f);//ee
	glNormal3f(-0.2f, 0.0f, 0.00f);
	glVertex3f(-0.2f, 0.0f, 0.00f);//e
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.3f, -0.2, -0.1f);
	glVertex3f(-0.3f, -0.2, -0.1f);//dd
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-0.3f, -0.2, -0.1f);
	glVertex3f(-0.3f, -0.2, -0.1f);//dd
	glNormal3f(-0.3f, -0.2, 0.00f);
	glVertex3f(-0.3f, -0.2, 0.00f);//d
	glNormal3f(-0.4f, 0.0f, 0.00f);
	glVertex3f(-0.4f, 0.0f, 0.00f);//c
	glNormal3f(-0.4f, 0.0f, -0.1f);
	glVertex3f(-0.4f, 0.0f, -0.1f);//cc
	glEnd();



}
void render2Alienship()
{
	//////Asteroid1
	glPushMatrix();
	glColor3f(0.23, 0.52549, 0.0431373);
	alien2X -= aLienship2Speed - 0.0001;
	alien2Y -= aLienship2Speed + (0.002 + (float)rand() / ((float)RAND_MAX / (0.01 - 0))) * cos((0 - alien2Angle / 180)*3.14);
	alien2Y += aLienship2Speed + (0.01 + (float)rand() / ((float)RAND_MAX / (0.01 - 0))) * cos((0 - alien2Angle / 180)*3.14);
	if (alien2X>1.035)
	{
		initAlien2Ship();
	}
	else if (alien2X < -1.035)
	{
		initAlien2Ship();
	}

	if (alien2Y>1.035)
		alien2Y = -1.035;
	else if (alien2Y < -1.035)
		alien2Y = 1.035;

	if (alien2Angle >= 0 & alien2Angle <= 90)
		ship2Angle = 45;
	glTranslatef(alien2X, alien2Y, 0);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(alien2Angle, 0.0, 0.0, 1.0);
	alienShip();

	///Alien Ship and Asteroid COllision
	for (j = 1; j<7; j++)
	{
		for (k = 1; k<8; k++)
		{
			aSteroidStats[j][k][10] = (aSteroidStats[j][k][4] - alien2X)*(aSteroidStats[j][k][4] - alien2X) + (aSteroidStats[j][k][5] - alien2Y)*(aSteroidStats[j][k][5] - alien2Y);
#pragma region CollisionCheck
			if (aSteroidStats[j][k][10] < ((aSteroidStats[j][k][9] - 0.1)*(aSteroidStats[j][k][9] - 0.1)) && aSteroidStats[j][k][6] == 1 && alien2Active == 1)
			{
				alien2Active = 0;
				for (l = 1; l<15; l++)
				{
					ExpStats[l][2] = aSteroidStats[j][k][4];
					ExpStats[l][3] = aSteroidStats[j][k][5];
				}
				ExpAlive = 1.0;

				aSteroidStats[j][k][6] = 0;

				if (k == 1 && aSteroidStats[j][1][6] == 0)
				{
					aSteroidStats[j][2][6] = 1;
					aSteroidStats[j][3][6] = 1;
					aSteroidStats[j][2][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][2][5] = aSteroidStats[j][1][5] + 0.05;
					aSteroidStats[j][3][4] = aSteroidStats[j][1][4] + 0.05;
					aSteroidStats[j][3][5] = aSteroidStats[j][1][5] + 0.05;

					aSteroidStats[j][2][7] = 0.17;
					aSteroidStats[j][3][7] = 0.17;

					aSteroidStats[j][2][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][3][9] = aSteroidStats[j][1][9] - 0.02;
				}

				if (k == 2 && aSteroidStats[j][2][6] == 0)
				{
					aSteroidStats[j][4][6] = 1;
					aSteroidStats[j][5][6] = 1;
					aSteroidStats[j][4][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][4][5] = aSteroidStats[j][2][5] + 0.09;
					aSteroidStats[j][5][4] = aSteroidStats[j][2][4] + 0.09;
					aSteroidStats[j][5][5] = aSteroidStats[j][2][5] + 0.09;

					aSteroidStats[j][4][7] = 0.11;
					aSteroidStats[j][5][7] = 0.11;

					aSteroidStats[j][4][9] = aSteroidStats[j][1][9] - 0.02;
					aSteroidStats[j][5][9] = aSteroidStats[j][1][9] - 0.02;
				}



				if (k == 3 && aSteroidStats[j][3][6] == 0)
				{
					aSteroidStats[j][6][6] = 1;
					aSteroidStats[j][7][6] = 1;
					aSteroidStats[j][6][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][6][5] = aSteroidStats[j][3][5] + 0.09;
					aSteroidStats[j][7][4] = aSteroidStats[j][3][4] + 0.09;
					aSteroidStats[j][7][5] = aSteroidStats[j][3][5] + 0.09;

					aSteroidStats[j][6][7] = 0.11;
					aSteroidStats[j][7][7] = 0.11;

					aSteroidStats[j][6][9] = aSteroidStats[j][2][9] - 0.02;
					aSteroidStats[j][7][9] = aSteroidStats[j][2][9] - 0.02;
				}
			}
#pragma endregion
		}
	}

	glPopMatrix();
}


Asteroids AstFunction[] =
{
	renderAsteroid1,
	renderAsteroid2,
	renderAsteroid3,
	renderAsteroid4
};

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glMatrixMode(GL_MODELVIEW);

	keyboard();

	timeSpent += 1;

	//Bonus Ships Award
	if (playerScore - playerBonus > 0)
	{
		if (playerLives<5)
			playerLives += 1;
		playerBonus += 10000;
	}

	for (j = 1; j<2; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[0](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}
	for (j = 2; j<3; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[1](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}
	for (j = 3; j<4; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[3](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}
	for (j = 4; j<5; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[0](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}
	for (j = 5; j<6; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[1](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}
	for (j = 6; j<7; j++)
	{
		if (j <= MaxCount)
		{
			for (k = 1; k<8; k++)
			{
				if (aSteroidStats[j][k][6] == 1)
					AstFunction[3](aSteroidStats[j][k][4], aSteroidStats[j][k][5], j, k, aSteroidStats[j][k][7], aSteroidStats[j][k][7], aSteroidStats[j][k][7]);
			}
		}
	}

	//for(j=1;i<7;i++)
	//	for(k=1;j<8;j++)
	//		if(aSteroidStats[j][k][6]==1)
	//			numOfActiveShips+=1;

	//renderStarfield();
	renderShip();
	renderShot();
	if (timeSpent>500 && playerScore >1000 && alienActive == 1)
	{
		renderAlienship();
		renderAlienShot();
	}
	if (timeSpent>1000 && playerScore >5000 && alien2Active == 1)
	{
		render2Alienship();
		render2AlienShot();
	}
	RenderScore();
	restartFlag = 0;
	restart();
	if (ExpAlive == 1)
	{
		renderExplosion();
	}
	glutSwapBuffers();
}

//Rotation glutTimerFunc Function
void Rotate(int n)
{
	n++;
	angle += 10;
	glutPostRedisplay();
	glutTimerFunc(50, Rotate, n);
}

// Menu Switch Function
void menu(int item)
{
	switch (item)
	{
	case MENU_QUIT:
	{
					  glutDestroyWindow(window);
					  exit(0);
	}
		break;
	case MENU_NEW:
	{
					 reset();
	}
		break;
	default:
	{       /* Nothing */       }
		break;
	}

	glutPostRedisplay();

	return;
}

int main(int argc, char **argv) {

	srand((unsigned)time(0));

	//arrayStats init

	init();
	initAlienShip();
	initAlien2Ship();

	//Explosion fragment angles
	for (j = 1; j<15; j++)
	{
		ExpStats[j][1] = ExpStats[j - 1][1] + 25.0;
	}

	float  amb[] = { 0, 0, 0, 1 };	// Ambient material property
	float  lt_amb[] = { .2, .2, .2, 1 };	// Ambient light property
	float  lt_dif[] = { .8, .8, .8, 1 };	// Ambient light property
	float  lt_pos[] = { 0, .39392, .91914, 0 };		// Light position 0, .39392, .91914, 0
	float  lt_pos1[] = { 0, -.39392, .91914, 0 };
	float  lt_pos2[] = { 0.2, -.39392, .91914, 0 };
	float  lt_spc[] = { 0, 0, 0, 1 };	// Specular light property


	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(500, 500);
	window = glutCreateWindow("aSteroids");

	glViewport(0, 0, 500, 500);
	glOrtho(0, 640, 0, 480, 0, 0);

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("NEW", MENU_NEW);
	glutAddMenuEntry("QUIT", MENU_QUIT);


	// Attach a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutTimerFunc(1000, Rotate, 0);

	//  Set default ambient light in scene

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//  Set Light 0 position, ambient, diffuse, specular intensities

	glLightfv(GL_LIGHT0, GL_POSITION, lt_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lt_spc);

	//  Set Light 1 position, ambient, diffuse, specular intensities

	glLightfv(GL_LIGHT1, GL_POSITION, lt_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lt_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lt_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lt_spc);

	//  Set Light 2 position, ambient, diffuse, specular intensities

	glLightfv(GL_LIGHT2, GL_POSITION, lt_pos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lt_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lt_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lt_spc);

	//  Enable Light 0 and GL lighting

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable( GL_LIGHT2 );
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);


	glEnable(GL_DEPTH);
	glShadeModel(GL_FLAT);		// Flat shading
	glEnable(GL_NORMALIZE);		// Normalize normals

	glClearDepth(1.0);			// Setup background colour
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	//Keyboard
	glutSpecialFunc(processSpecialKeys);
	//KeyBoard Event Handling
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	// //Gameplay Music
	//PlaySound ("asteroid.wav",NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
