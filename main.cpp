#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<GL/glut.h>
#define PI 3.1416

static int GAME_STATE = 1;
static int GAME_OVER = false;
static int GRAVITY_OFF = false;
static int SCORE = 0, SCORE_CHK = 0;

static int lock1 = 0;
static int lock2 = 0;
static int lock3 = 0;

static float tx	=  0.0;
static float ty	=  0.0;

int roatate = 0;

float angleu = 0.0;
float BIRD_WING_FLING = 0;
float CLOUDS_MOVE = 800;

float static lastBirdY = 0.0;

float cloudOffset = 5;
float cloudSpeed = 0.008;
float buildingSpeed = 0.01;
float bushSpeed = 0.03;
float pipeSpeed = 0.05;

float buildingOffeset = 5;

static float sunFlare = 0;

static float cloud1X = -50, cloud1Y = 0, cloud1Z = 0;
static float cloud2X = -40, cloud2Y = 0, cloud2Z = 0;
static float cloud3X = -30, cloud3Y = 0, cloud3Z = 0;
static float cloud4X = -20, cloud4Y = 0, cloud4Z = 0;

static float cloud5X = -10, cloud5Y = 0, cloud5Z = 0;
static float cloud6X = 0, cloud6Y = 0, cloud6Z = 0;
static float cloud7X = 10, cloud7Y = 0, cloud7Z = 0;
static float cloud8X = 20, cloud8Y = 0, cloud8Z = 0;

static float cloud9X = 30, cloud9Y = 0, cloud9Z = 0;
static float cloud10X = 40, cloud10Y = 0, cloud10Z = 0;
static float cloud11X = 50, cloud11Y = 0, cloud11Z = 0;

// --------------------
static float bush1X = -50, bush1Y = 0, bush1Z = 0;
static float bush2X = -40, bush2Y = 0, bush2Z = 0;
static float bush3X = -30, bush3Y = 0, bush3Z = 0;
static float bush4X = -20, bush4Y = 0, bush4Z = 0;

static float bush5X = -10, bush5Y = 0, bush5Z = 0;
static float bush6X = 0, bush6Y = 0, bush6Z = 0;
static float bush7X = 10, bush7Y = 0, bush7Z = 0;
static float bush8X = 20, bush8Y = 0, bush8Z = 0;

static float bush9X = 30, bush9Y = 0, bush9Z = 0;
static float bush10X = 40, bush10Y = 0, bush10Z = 0;
static float bush11X = 50, bush11Y = 0, bush11Z = 0;

float baloonStrap = 1.0;

static float birdX = 50, birdY = 0, birdZ = 0;

// ....................
static float displacement = 1;

static float building1X = -50, building1Y = -50, building1Z = 0;
static float building2X = -40, building2Y = -50, building2Z = 0;
static float building3X = -35, building3Y = -50, building3Z = 0;
static float building4X = -20, building4Y = -50, building4Z = 0;

static float building5X = -10, building5Y = -50, building5Z = 0;
static float building6X = 0, building6Y = -50, building6Z = 0;
static float building7X = 15, building7Y = -50, building7Z = 0;

static float building8X = 20, building8Y = -50, building8Z = 0;
static float building9X = 30, building9Y = -50, building9Z = 0;
static float building10X = 45, building10Y = -50, building10Z = 0;
static float building11X = 50, building11Y = -50, building11Z = 0;


float b1y = -27, b2y = -17, b3y = -47, b4y = -77, b5y = 67, b6y = -7,
    b7y = -7, b8y = -7, b9y = 67, b10y = 87, b11y = 117, b12y = 157;

static int flag = 1;
static float backR = 0.2, backG = 1.0, backB = 1.0;
static float windowR = 0.87, windowG = 0.87, windowB = 0.92;
static float cloudR = 1.0, cloudG = 1.0, cloudB = 1.0;
static int skyMode = 1;

static float pipeDistance1 = 30;
static float pipeDistance2 = 90;
static float pipeDistance3 = 150;

static float p1Translate = 0;
static float p2Translate = 20;
static float p3Translate = -10;

static float pipeRandHeightUp = 100;
static float pipeRandHeightBottom = 100;

static float moveAlongX = 50;

static float backgroundSunY = 18;
static float backgroundSunX = 48;
static float backgroundMoonY = -70;
static float sunOffset = 0.008;
static float moonOffset = 0.01;
float rayHeight = 6;
float rayWidth = 0.2;
float r = 1.0, g = 1.0, b = 0.8;

void init()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
}

void wabbleTail()
{
    if(flag == 1)
    {
        baloonStrap += 0.006;
        if(baloonStrap > 2.0) {
            flag = 2;
        }
    }
    if(flag == 2) {
        baloonStrap -= 0.006;
        if(baloonStrap <= 0) {
            flag = 1;
        }
    }
    //printf("Baloon : %f \n", baloonStrap);
}

double Gravity(double z)
{
    if(GRAVITY_OFF) { return 0; }

    double G,
    eZ;
    const double ER = 6378150.0;
    const double ER2 = 6378150.0 * 6378150.0;

    eZ = ER + z;
    G = 9.81 * ER2 / (eZ * eZ);

    return G;
}

void showTextSmall(char text[], float r, float g, float b, int x, int y, int z)
{
    glColor3f(r, g, b);
    glRasterPos3f( x , y , z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void showTextLarge(char text[], int r, int g, int b, int x, int y, int z)
{
    glColor3f(r, g, b);
    glRasterPos3f( x , y , z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}
void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}

void baloon(int width, int height, float tx, float ty, int rotate, float scale, float r, float g, float b)
{
    glPushMatrix();

        glRotated(rotate, 0, 0, 1);
        glTranslated(tx, ty, 0);
        glScaled(scale, scale, scale);
        glPushMatrix();
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslated(baloonStrap, -7, 0);
                glBegin(GL_LINE_STRIP);
                    glVertex2d(0, 0);
                    glVertex2d(-2, -5);
                    glVertex2d(2, -9);
                    glVertex2d(0, -12);
                    glVertex2d(0, -15);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glColor3f(r, g, b);
                circle(width, height);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

void flingBirdsWingLoop() {
    BIRD_WING_FLING += 3;
    //glutPostRedisplay();
}

void window(float x1, float y1, float x2, float y2, float verticalPos) {

    glPushMatrix();
    glTranslated(2, verticalPos, 0);
    glColor3f(windowR, windowG, windowB);
    glRectd(x1, y1, x2, y2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, verticalPos, 0);
    glColor3f(windowR, windowG, windowB);
    glRectd(x1, y1, x2, y2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6, verticalPos, 0);
    glColor3f(windowR, windowG, windowB);
    glRectd(x1, y1, x2, y2);
    glPopMatrix();

}

void buildingAndWindow3(float tX, float tY, float tZ) {

    glPushMatrix();
        glTranslated(tX, tY, tZ);
        glScaled(.7, .7, .7);
        glPushMatrix();

            //Building
            glPushMatrix();
                glColor3f(0.60, 0.70, 0.89);
                glRectd(0, 0, 5, 18);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-.5, 0, 0);
                glColor3f(0.81, 0.87, 0.87);
                glRectd(0, 0, .5, 18);
            glPopMatrix();


        glPopMatrix();
    glPopMatrix();
}

void buildingAndWindow2(float tX, float tY, float tZ) {

    glPushMatrix();
        glTranslated(tX, tY, tZ);
        glScaled(.7, .7, .7);
        glPushMatrix();

            //Building
            glPushMatrix();
                glColor3f(0.81, 0.81, 0.88);
                glRectd(0, 0, 8, 13);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-.2, 0, 0);
                glColor3f(0.81, 0.87, 0.87);
                glRectd(0, 0, .8, 13);
            glPopMatrix();


            // Roof top obj
            glPushMatrix();
                glTranslated(2, 13, 0);
                glColor3f(0.81, 0.87, 0.87);
                glRectd(0, 0, 3, 1);
            glPopMatrix();

            window(0, 0, 1, 1, 2);
            window(0, 0, 1, 1, 4);
            window(0, 0, 1, 1, 6);
            window(0, 0, 1, 1, 8);
        glPopMatrix();
    glPopMatrix();
}

void buildingAndWindow1(float tX, float tY, float tZ) {

    glPushMatrix();

        glTranslated(tX, tY, tZ);
        glScaled(.7, .7, .7);
        glPushMatrix();

            //Building
            glPushMatrix();
                glColor3f(0.52, 0.63, 0.87);
                glRectd(0, 0, 8, 20);
            glPopMatrix();

            glPushMatrix();
                glTranslated(-1, 0, 0);
                glColor3f(0.81, 0.87, 0.87);
                glRectd(0, 0, 1, 20);
            glPopMatrix();


            // Roof top obj
            glPushMatrix();
                glTranslated(5, 20, 0);
                glColor3f(0.81, 0.87, 0.87);
                glRectd(0, 0, 3, 1);
            glPopMatrix();

            window(0, 0, 1, 1, 2);
            window(0, 0, 1, 1, 4);
            window(0, 0, 1, 1, 6);
            window(0, 0, 1, 1, 8);
            window(0, 0, 1, 1, 10);
            window(0, 0, 1, 1, 12);
            window(0, 0, 1, 1, 14);

        glPopMatrix();
    glPopMatrix();

}

void buildingBuilder() {

    //printf("%f \n", building1X);
    buildingAndWindow1(building1X-=buildingSpeed, -50, 0);
    buildingAndWindow2(building2X-=buildingSpeed, -50, 0);
    buildingAndWindow3(building3X-=buildingSpeed, -50, 0);
    buildingAndWindow1(building4X-=buildingSpeed, -50, 0);

    buildingAndWindow1(building5X-=buildingSpeed, -50, 0);
    buildingAndWindow2(building6X-=buildingSpeed, -50, 0);
    buildingAndWindow3(building7X-=buildingSpeed, -50, 0);
    buildingAndWindow1(building8X-=buildingSpeed, -50, 0);

    buildingAndWindow1(building9X-=buildingSpeed, -50, 0);
    buildingAndWindow2(building10X-=buildingSpeed, -50, 0);
    buildingAndWindow3(building11X-=buildingSpeed, -50, 0);


    if((building1X-buildingOffeset) <= -60.0)
    {
        building1X = 55.0;
    }
    if((building2X-buildingOffeset) <= -60.0)
    {
        building2X = 55.0;
    }
    if((building3X-buildingOffeset) <= -60.0)
    {
        building3X = 55.0;
    }
    if((building4X-buildingOffeset) <= -60.0)
    {
        building4X = 55.0;
    }
    if((building5X-buildingOffeset) <= -60.0)
    {
        building5X = 55.0;
    }
    if((building6X-buildingOffeset) <= -60.0)
    {
        building6X = 55.0;
    }
    if((building7X-buildingOffeset) <= -60.0)
    {
        building7X = 55.0;
    }
    if((building8X-buildingOffeset) <= -60.0)
    {
        building8X = 55.0;
    }
    if((building9X-buildingOffeset) <= -60.0)
    {
        building9X = 55.0;
    }
    if((building10X-buildingOffeset) <= -60.0)
    {
        building10X = 55.0;
    }
    if((building11X-buildingOffeset) <= -60.0)
    {
        building11X = 55.0;
    }
}

void cloud(float tx, float ty, float tz, float scale, float x)
{
    glPushMatrix();

        glScaled(scale, scale, scale);
        glTranslated(tx, ty, tz);

        glPushMatrix();
            glTranslated(0, (-40+x), 0);
            glColor3f(cloudR, cloudG, cloudB);
            circle(9, 20);
        glPopMatrix();

    glPopMatrix();

}

void bush(float tx, float ty, float tz, float scale, float x)
{
    glPushMatrix();

        glTranslated(tx, ty, tz);

        glPushMatrix();
            glTranslated(0, (-55+x), 0);
            glScaled(scale, scale, scale);
            glColor3f(0.0, 1.0, 0.0);
            circle(9, 5);
        glPopMatrix();

    glPopMatrix();

}

void bushBuilder()
{

    bush(bush1X-=bushSpeed, bush1Y, bush1Z, 1, 1);
    bush(bush2X-=bushSpeed, bush2Y, bush2Z, 1, 2);
    bush(bush3X-=bushSpeed, bush3Y, bush3Z, 1, 3);
    bush(bush4X-=bushSpeed, bush4Y, bush4Z, 1, 2);

    bush(bush5X-=bushSpeed, bush5Y, bush5Z, 1, 3);
    bush(bush6X-=bushSpeed, bush6Y, bush6Z, 1, 1);
    bush(bush7X-=bushSpeed, bush7Y, bush7Z, 1, 4);
    bush(bush8X-=bushSpeed, bush8Y, bush8Z, 1, 1);

    bush(bush9X-=bushSpeed, bush9Y, bush9Z, 1, 2);
    bush(bush10X-=bushSpeed, bush10Y, bush10Z, 1, 4);
    bush(bush11X-=bushSpeed, bush11Y, bush11Z, 1, 1);

    if((bush1X-cloudOffset) <= -60.0)
    {
        bush1X = 55.0;
    }
    if((bush2X-cloudOffset) <= -60.0)
    {
        bush2X = 55.0;
    }
    if((bush3X-cloudOffset) <= -60.0)
    {
        bush3X = 55.0;
    }
    if((bush4X-cloudOffset) <= -60.0)
    {
        bush4X = 55.0;
    }
    if((bush5X-cloudOffset) <= -60.0)
    {
        bush5X = 55.0;
    }
    if((bush6X-cloudOffset) <= -60.0)
    {
        bush6X = 55.0;
    }
    if((bush7X-cloudOffset) <= -60.0)
    {
        bush7X = 55.0;
    }
    if((bush8X-cloudOffset) <= -60.0)
    {
        bush8X = 55.0;
    }
    if((bush9X-cloudOffset) <= -60.0)
    {
        bush9X = 55.0;
    }
    if((bush10X-cloudOffset) <= -60.0)
    {
        bush10X = 55.0;
    }
    if((bush11X-cloudOffset) <= -60.0)
    {
        bush11X = 55.0;
    }
}

void cloudBuilder()
{

    cloud(cloud1X-=cloudSpeed, cloud1Y, cloud1Z, 1, 1);
    cloud(cloud2X-=cloudSpeed, cloud2Y, cloud2Z, 1, 2);
    cloud(cloud3X-=cloudSpeed, cloud3Y, cloud3Z, 1, 3);
    cloud(cloud4X-=cloudSpeed, cloud4Y, cloud4Z, 1, 2);

    cloud(cloud5X-=cloudSpeed, cloud1Y, cloud1Z, 1, 3);
    cloud(cloud6X-=cloudSpeed, cloud2Y, cloud2Z, 1, 1);
    cloud(cloud7X-=cloudSpeed, cloud3Y, cloud3Z, 1, 4);
    cloud(cloud8X-=cloudSpeed, cloud4Y, cloud4Z, 1, 1);

    cloud(cloud9X-=cloudSpeed, cloud9Y, cloud9Z, 1, 2);
    cloud(cloud10X-=cloudSpeed, cloud10Y, cloud10Z, 1, 4);
    cloud(cloud11X-=cloudSpeed, cloud11Y, cloud11Z, 1, 1);

    if((cloud1X-cloudOffset) <= -60.0)
    {
        cloud1X = 55.0;
    }
    if((cloud2X-cloudOffset) <= -60.0)
    {
        cloud2X = 55.0;
    }
    if((cloud3X-cloudOffset) <= -60.0)
    {
        cloud3X = 55.0;
    }
    if((cloud4X-cloudOffset) <= -60.0)
    {
        cloud4X = 55.0;
    }
    if((cloud5X-cloudOffset) <= -60.0)
    {
        cloud5X = 55.0;
    }
    if((cloud6X-cloudOffset) <= -60.0)
    {
        cloud6X = 55.0;
    }
    if((cloud7X-cloudOffset) <= -60.0)
    {
        cloud7X = 55.0;
    }
    if((cloud8X-cloudOffset) <= -60.0)
    {
        cloud8X = 55.0;
    }
    if((cloud9X-cloudOffset) <= -60.0)
    {
        cloud9X = 55.0;
    }
    if((cloud10X-cloudOffset) <= -60.0)
    {
        cloud10X = 55.0;
    }
    if((cloud11X-cloudOffset) <= -60.0)
    {
        cloud11X = 55.0;
    }

}

void baloonBuilder()
{

    baloon(5, 9, -40, b3y, 3, 0.1, 1.0, 0.6, 0.4);
    baloon(5, 9, -35, b4y, 3, 0.2, 1.2, 0.2, 0.2);
    baloon(5, 9, 45, b5y, 13, 0.2, 1.6, 1.0, .3);
    baloon(5, 9, 10, b9y, 13, 0.2, 0.9, 0.9, 0.9);
    baloon(5, 9, -11, b11y, -13, 0.3, 0.1, 0.1, 0.3);
    baloon(5, 9, -1, b12y, 13, 0.3, 0.7, 0.5, 0.6);
    baloon(5, 9, 25, b6y, -3, 0.3, .9, 0.7, 0.3);
    baloon(5, 9, -40, b7y, -10, 0.3, 0.3, 0.1, 0.5);
    baloon(5, 9, 15, b10y, -3, 0.3, 0.3, 0.3, 0.9);
    baloon(5, 9, -15, b8y, 13, 0.3, 1.0, 0.1, 0.4);
    baloon(5, 9, -40, b1y, 3, 0.4, 1.0, 0.0, 0.0);
    baloon(5, 9, 50, b2y, 3, 0.5, 1.4, 0.4, 0.0);

    b3y += 0.0005;
    b4y += 0.0007;
    b5y += 0.0008;
    b9y += 0.0007;
    b11y += 0.001;
    b12y += 0.002;
    b6y += 0.003;
    b7y += 0.004;
    b10y += 0.005;
    b8y += 0.006;
    b1y += 0.007;
    b2y += 0.0008;


    int limit = 60;
    int lowerLimit = -30;

    if(b1y > limit) {
        b1y = lowerLimit;
    }
    if(b2y > limit) {
        b2y = lowerLimit;
    }
    if(b3y > limit) {
        b3y = lowerLimit;
    }

    if(b4y > limit) {
        b4y = lowerLimit;
    }
    if(b5y > limit) {
        b5y = lowerLimit;
    }
    if(b6y > limit) {
        b6y = lowerLimit;
    }

    if(b7y > limit) {
        b7y = lowerLimit;
    }
    if(b8y > limit) {
        b8y = lowerLimit;
    }
    if(b8y > limit) {
        b8y = lowerLimit;
    }

    if(b9y > limit) {
        b9y = lowerLimit;
    }
    if(b10y > limit) {
        b10y = lowerLimit;
    }
    if(b1y > limit) {
        b11y = lowerLimit;
    }

    wabbleTail();

}

void birdLarge()
{
    glPushMatrix();
        // Bird Body
        glPushMatrix();
            glColor3f(1.0, 0.6, 0.4);
            circle(8, 10);
        glPopMatrix();

        // Wing round
        glPushMatrix();
            glRotated(BIRD_WING_FLING, 1, 0, 0);
            glTranslated(-5, 0, 0);
            glColor3f(1.0, 0.4, 0.4);
            circle(4, 4);
        glPopMatrix();

        // Wing triangle
        glPushMatrix();
            glRotated(BIRD_WING_FLING, 1, 0, 0);
            glTranslated(-6, 2, 0);
            glColor3f(1.0, 0.4, 0.4);
            glBegin(GL_POLYGON);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(2, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(-6, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(-2, -4.8);
            glEnd();
        glPopMatrix();

        // Eye white
        glPushMatrix();
            glTranslated(5, 2.5, 0);
            glColor3f(1.0, 1.0, 1.0);
            circle(2.5, 3.5);
        glPopMatrix();

        //Eye black
        glPushMatrix();
            glTranslated(6, 2.5, 0);
            glColor3f(0.0, 0.0, 0.0);
            circle(1, 1.8);
        glPopMatrix();
        // bird body ends

        // Beak
        glPushMatrix();
            glTranslated(6, -3.5, 0);
            glColor3f(1.0, 0.4, 0.4);
            glBegin(GL_POLYGON);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(1.9, 3);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(4, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(0.4, -2.4);
            glEnd();
        glPopMatrix();
        // ....
    glPopMatrix();
}

void bird()
{
    //if(birdY == lastBirdY) { GRAVITY_OFF = false; }

    birdY = birdY-(Gravity(birdY)/ 100);
    //float diff = 1 - Gravity(birdY)/10.0;
    //birdY -= diff;
    glPushMatrix();
        glTranslated(birdX-80, birdY, birdZ);
        glScaled(0.2, 0.2, 0.2);
        // Bird Body
        glPushMatrix();
            glColor3f(1.0, 0.6, 0.4);
            circle(8, 10);
        glPopMatrix();

        // Wing round
        glPushMatrix();
            glRotated(BIRD_WING_FLING, 1, 0, 0);
            glTranslated(-5, 0, 0);
            glColor3f(1.0, 0.4, 0.4);
            circle(4, 4);
        glPopMatrix();

        // Wing triangle
        glPushMatrix();
            glRotated(BIRD_WING_FLING, 1, 0, 0);
            glTranslated(-6, 2, 0);
            glColor3f(1.0, 0.4, 0.4);
            glBegin(GL_POLYGON);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(2, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(-6, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(-2, -4.8);
            glEnd();
        glPopMatrix();

        // Eye white
        glPushMatrix();
            glTranslated(5, 2.5, 0);
            glColor3f(1.0, 1.0, 1.0);
            circle(2.5, 3.5);
        glPopMatrix();

        //Eye black
        glPushMatrix();
            glTranslated(6, 2.5, 0);
            glColor3f(0.0, 0.0, 0.0);
            circle(1, 1.8);
        glPopMatrix();
        // bird body ends

        // Beak
        glPushMatrix();
            glTranslated(6, -3.5, 0);
            glColor3f(1.0, 0.4, 0.4);
            glBegin(GL_POLYGON);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(1.9, 3);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(4, 2);
                glColor3f(1.0, 0.4, 0.4); glVertex2d(0.4, -2.7);
            glEnd();
        glPopMatrix();
        // ....
    glPopMatrix();

    lastBirdY = birdY;

}


void pipe(float tx1, float ty1, float tz1, float tx2, float ty2, float tz2, float translateWhole)
{
    glPushMatrix();
    glTranslated(0, translateWhole, 0);
        glPushMatrix();
            // Long pipe up
            glPushMatrix();
            glTranslated(tx1, ty1, tz1);
            glColor3f(0.8, 0.4, 0);
            glRectd(0, 0, 8, pipeRandHeightUp);
            glPopMatrix();

            // Long pipe up header
            glPushMatrix();
            glTranslated(tx1, ty1, tz1);
            glColor3f(0.8, 0.2, 0.1);
            glRectd(-.5, -.5, 8.5, 8.5);
            glPopMatrix();

            // Long pipe bottom
            glPushMatrix();
            glTranslated(tx2, ty2, tz2);
            //glTranslated(0, -50, 0);
            glColor3f(0.8, 0.4, 0);
            glRectd(0, 0, 8, pipeRandHeightBottom);
            glPopMatrix();

            // Long pipe bottom header
            glPushMatrix();
            glTranslated(tx2, ty2+100,tz2);
            //glTranslated(0, -30, 0);
            glColor3f(0.8, 0.2, 0.1);
            glRectd(-.5, -.5, 8.5, 8.5);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

void gotoFinalPage()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
}
// 0 half
// 100 half
void pipeBuilder()
{
    pipe(pipeDistance1, 10, 0, pipeDistance1, -120, 0, p1Translate);
    pipe(pipeDistance2, 10, 0, pipeDistance2, -120, 0, p2Translate);
    pipe(pipeDistance3, 10, 0, pipeDistance3, -120, 0, p3Translate);

    // pipeSpeed
    pipeDistance1 -= pipeSpeed;
    pipeDistance2 -= pipeSpeed;
    pipeDistance3 -= pipeSpeed;

    if(pipeDistance1 <= -60.0) {
        pipeDistance1 = 130;
        p1Translate = (rand() % 101) - 50;
        lock1 = 0;
    }
    if(pipeDistance2 <= -60.0) {
        pipeDistance2 = 130;
        p2Translate = (rand() % 101) - 50;
        lock2 = 0;
    }
    if(pipeDistance3 <= -60.0) {
        pipeDistance3 = 130;
        p3Translate = (rand() % 101) - 50;
        lock3 = 0;
    }
}

void collision()
{
    //printf("PIPE 1 SCORE POINT %f \n", pipeDistance1);
    //printf("PIPE 2 SCORE POINT %f \n", pipeDistance2);
    //printf("PIPE 3 SCORE POINT %f \n", pipeDistance3);

    float coll = 50 - (100 -((50 + p1Translate) + p1Translate));
    int collision = 0;

    //printf(".............................................. %f", birdY);
    if(birdY <= -55.0) {
        PlaySound("sfx_die.wav", NULL, SND_FILENAME| SND_ASYNC);
        GAME_OVER = true;
    }

    if(birdY >= 49.0) {
        birdY = 49.0;
    }

    // Top pipe collision
    if((birdX-78 >= pipeDistance1 && birdX-80 <= pipeDistance1+8) &&
       (birdY-8 >= p1Translate)) {
           collision = 1;
    }
    if((birdX-78 >= pipeDistance2 && birdX-80 <= pipeDistance2+8) &&
       (birdY-8 >= p2Translate)) {
           collision = 1;
    }
    if((birdX-78 >= pipeDistance3 && birdX-80 <= pipeDistance3+8) &&
       (birdY-8 >= p3Translate)) {
           collision = 1;
    }

    // Bottom pipe collision
    if((birdX-78 >= pipeDistance1 && birdX-80 <= pipeDistance1+8) &&
       (birdY+10 <= p1Translate)) {
           collision = 1;
    }

     if((birdX-78 >= pipeDistance2 && birdX-80 <= pipeDistance2+8) &&
       (birdY+10 <= p2Translate)) {
           collision = 1;
    }
     if((birdX-78 >= pipeDistance3 && birdX-80 <= pipeDistance3+8) &&
       (birdY+10 <= p3Translate)) {
           collision = 1;
    }

    if(collision == 1) {
        PlaySound("sfx_die.wav", NULL, SND_FILENAME| SND_ASYNC);
        //printf("Collision detected");
        //gotoFinalPage();
        GAME_OVER = true;
    }

    if(birdX-90 > pipeDistance1 && lock1 == 0) {
        SCORE++;
        SCORE_CHK++;
        lock1 = 1;
        PlaySound("sfx_point.wav", NULL, SND_FILENAME| SND_ASYNC);
        //printf("Entered 1\n");
    }
    if(birdX-90 > pipeDistance2 && lock2 == 0) {
        SCORE++;
        SCORE_CHK++;
        lock2 = 1;
        PlaySound("sfx_point.wav", NULL, SND_FILENAME| SND_ASYNC);
       // printf("Entered 2\n");
    }
    if(birdX-90 > pipeDistance3 && lock3 == 0) {
        SCORE++;
        SCORE_CHK++;
        lock3 = 1;
        PlaySound("sfx_point.wav", NULL, SND_FILENAME| SND_ASYNC);
        //printf("Entered 3\n");
    }

    if(SCORE_CHK >= 5) {
            SCORE_CHK = 0;
            pipeSpeed += 0.01;
    }

    char score2[100];
    itoa(SCORE, score2, 10);

    showTextLarge(score2, 1, 1, 1, -3, 40, 0);


    collision = 0;


    //if(bird)
}

void sun()
{
    float rayHeight = 6;
    float rayWidth = 0.5;

    glPushMatrix();

       glTranslated(-30, 38, 0);
      // glTranslated(-3.7, 31, 0);
        glRotated(sunFlare+= 0.03, 0, 0, 1);
        glPushMatrix();
            glPushMatrix();
                glColor3d(1, 1, 0.6);
                circle(5, 5);
            glPopMatrix();

            glPushMatrix();
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(45, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(90, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(135, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(180, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();


            glPushMatrix();
             glRotated(225, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(270, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(315, 0, 0, 1);
                glColor3d(1, 1, 0.6);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

void sun2()
{
    rayHeight -= 0.0005;

    if(backgroundSunX >= 48 && backgroundSunY >= 18) {
        rayHeight = 6;
        rayWidth = 0.2;
    }

    glPushMatrix();

       glTranslated(backgroundSunX -= sunOffset, backgroundSunY-=sunOffset, 0);
      // glTranslated(-3.7, 31, 0);
        glRotated(sunFlare+= 0.03, 0, 0, 1);
        glPushMatrix();

            glPushMatrix();
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(45, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(90, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(135, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(180, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();


            glPushMatrix();
             glRotated(225, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(270, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
             glRotated(315, 0, 0, 1);
                glColor3d(r, g, b);
                glRectd(0,0, rayHeight, rayWidth);
            glPopMatrix();

            glPushMatrix();
                glColor3d(r, g, b);
                circle(4, 4);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

void moon()
{
    glPushMatrix();

       glTranslated(-30, backgroundMoonY+=moonOffset, 0);

        glPushMatrix();
            glPushMatrix();
                glColor3d(0.92, 0.94, 0.97);
                circle(3, 3);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

void star(float tx, float ty, float width, float height)
{
    glPushMatrix();
        glTranslated(tx, ty, 0);
        glColor3d(1.0, 1.0, 1.0);
        circle(width, height);
    glPopMatrix();
}

void starBuilder()
{
    star(-30, 0, .2, .2);
    star(-40, 10, .2, .2);
    star(-50, 11, .2, .2);
    star(-55, 15, .2, .2);
    star(-10, 20, .2, .2);
    star(10, -35, .2, .2);
    star(0, 44, .2, .2);
    star(11, 55, .2, .2);
    star(20, 56, .2, .2);
    star(30, 47, .2, .2);

    star(31, -10, .2, .2);
    star(30, -4, .2, .2);
    star(35, -5, .2, .2);
    star(40, -20, .2, .2);
    star(45, -21, .2, .2);
    star(55, 40, .2, .2);
    star(55, -11, .2, .2);
}

void background()
{
    glPushMatrix();
        glColor3f(backR, backG, backB);
        glRectd(100, 100, -100, -100);
    glPopMatrix();
}

void dayNight()
{

    if(backgroundMoonY > 110) {
        backgroundMoonY = -100;
    }

    if(skyMode == 1) {
        backR -= .0001;
        backG -= .0001;
        backB -= .0001;

        cloudR -= 0.00007;
        cloudG -= 0.00007;
        cloudB -= 0.00007;

        if(backR <= 0.64 && backG <= 0.15 && backB <= 0.15) {

            skyMode = 2;

            backgroundSunX = 150;
            backgroundSunY = 128;

            windowR = 1;
            windowG = 1;
            windowB = 0.2;
        }
    }
    if(skyMode == 2)
    {
        backR += .0001;
        backG += .0001;
        backB += .0001;

        cloudR += 0.00007;
        cloudG += 0.00007;
        cloudB += 0.00007;

        if(backR >= 0.2 && backG >= 1.0 && backB >= 1.0) {

            skyMode = 1;

            backgroundSunY = 28;
            backgroundSunX = 68;

            windowR = 0.87;
            windowG = 0.87;
            windowB = 0.92;
        }
    }
}

void homeScreen()
{

}

void exitScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    cloudBuilder();
    bushBuilder();
    showTextLarge("Game Over", 1.0, 0.1, 0.5, -8, 20, 0);

    showTextSmall("Press      to start the game", 0, 0, 1, -14, 5, 0);
    showTextSmall("S", 1, 0.4, 0.4, -7, 5, 0);

    char score[100];
    itoa(SCORE, score, 10);

    showTextLarge(score, 0, 0, 1, -3, -40, 0);

    glPushMatrix();
        glTranslated(-2, -30, 0);
        glScaled(0.2, 0.2, 0.2);
        birdLarge();
    glPopMatrix();
    flingBirdsWingLoop();
}

void wKeyPressed() {
    GRAVITY_OFF = true;
    birdY += .5;
}

void resetGame()
{
    birdY = 0;
    pipeDistance1 = 30;
    pipeDistance2 = 90;
    pipeDistance3 = 150;
    SCORE = 0;
    pipeSpeed = 0.05;
}


void changeState(int state)
{
    GAME_STATE = state;
}
void keyUpFunc(unsigned char key, int x, int y) {
    if(key == 'w') {
        GRAVITY_OFF = false;
    }
}

void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {

		case 'w':
			wKeyPressed();
			break;
        case 's':
            PlaySound("sfx_swooshing.wav", NULL, SND_FILENAME| SND_ASYNC);
            if(GAME_OVER == true) {
                changeState(2);
                GAME_OVER = false;
                resetGame();
            }
            else {
                changeState(2);
            }
            break;

	  default:
			break;
	}
}


void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT); //clear buffer, buffer_bit indicates the buffers currently enabled for color writin

    if(GAME_OVER == false) {
        glPushMatrix();
            background();

            // Background
            if(GAME_STATE == 1) {
                sun();
                baloonBuilder();
                cloudBuilder();
                birdLarge();
                showTextLarge("Bird ", 0, 0, 0, 1, 30, 0);
                showTextLarge("Clever", 1, 0.4, 0.4, -7, 30, 0);

                showTextSmall("Press      to start the game", 0, 0, 0, -14, -40, 0);
                showTextSmall("S", 1, 0.4, 0.4, -7, -40, 0);

            }
            else if(GAME_STATE == 2) {

                sun2();
                moon();
                starBuilder();

                cloudBuilder();
                buildingBuilder();
                bird();
                bushBuilder();

                pipeBuilder();
                collision();
                dayNight();
            }
             //pipeBuilder();
        glPopMatrix();

        flingBirdsWingLoop();
    } else {
        exitScene();
    }

    glutPostRedisplay();
    glFlush(); //force execution of Gl commands
}



int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Size of the window
    glutInitWindowPosition(10, 10); // location of the window
    glutCreateWindow("Clever Bird"); // Create window with this name
	glutKeyboardFunc(my_keyboard);
    init(); // call initialize function
    glutDisplayFunc(myDisplay); // call display function
    glutKeyboardUpFunc(keyUpFunc);

    glutMainLoop();
    return 0;
}

