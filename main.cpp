#include "pugixml.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "boneco.hpp"

int Width;
int Height;
int animate=0;
int keyStatus[256];
Boneco boneco1P;
Boneco boneco2P;
#define incAngulo 10
#define PraFrente 1
#define PraTras 0


void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
             animate = !animate;
             break;
        case 'a':
        case 'A':
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             break;
        case 'd':
        case 'D':
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             break;
        case 'w':
        case 'W':
            keyStatus[(int)('w')] = 1;
            break;
        case 'S':
        case 's':
            keyStatus[(int)('s')] = 1;
            break;
    }
}
void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}
void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);

     boneco1P.Desenha();
     boneco2P.Desenha();
     glutSwapBuffers(); // Desenha the new frame of the game.
}
void idle(){
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
//Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
// Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
//Atualiza o tempo do ultimo frame ocorrido
    if(keyStatus[(int)('a')])
    {
        boneco1P.MudaAngulo(incAngulo);
    }
    if(keyStatus[(int)('d')])
    {
        boneco1P.MudaAngulo(-incAngulo);
    }
    if(keyStatus[(int)('w')])
    {
        boneco1P.Move(timeDiference,PraFrente);
    }
    if(keyStatus[(int)('s')])
    {
        boneco1P.Move(timeDiference,PraTras);
    }
    glutPostRedisplay();
}
void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}
void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glOrtho(-(Width/2),     // X coordinate of left edge
            (Width/2),     // X coordinate of right edge
            -(Height/2),     // Y coordinate of bottom edge
            (Height/2),     // Y coordinate of top edge
            -100,     // Z coordinate of the “near” plane
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix
    glLoadIdentity();
}
int main(int argc, char * argv[]){
// tag::code[]
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("arena_3.svg");
   float xdiff = atoi(doc.child("svg").child("rect").attribute("x").value());
   float ydiff = atoi(doc.child("svg").child("rect").attribute("y").value());
   Width = atoi(doc.child("svg").child("rect").attribute("width").value());
   Height = atoi(doc.child("svg").child("rect").attribute("height").value());
   float raio1 = atoi(doc.child("svg").child("circle").attribute("r").value());
   float raio2 = atoi(doc.child("svg").child("circle").next_sibling().attribute("r").value());
   float boneco1X = atoi(doc.child("svg").child("circle").attribute("cx").value());
   float boneco1Y = atoi(doc.child("svg").child("circle").attribute("cy").value());
   boneco1X = boneco1X -xdiff -(float(Width)/2);
   boneco1Y = (float(Height)/2) - (boneco1Y -ydiff);
   
   float boneco2X = atoi(doc.child("svg").child("circle").next_sibling().attribute("cx").value());
   float boneco2Y = atoi(doc.child("svg").child("circle").next_sibling().attribute("cy").value());
   boneco2X = boneco2X -xdiff -(float(Width)/2);
   boneco2Y = (float(Height)/2) - (boneco2Y - ydiff);
   float bodyTheta = -atan2((boneco1X -boneco2X),(boneco1Y-boneco2Y))*180/M_PI;
   boneco1P.setBoneco(boneco1X,boneco1Y,raio1,0,(bodyTheta+180));
   boneco2P.setBoneco(boneco2X,boneco2Y,raio2,1,bodyTheta);
 
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(Width, Height);
   glutInitWindowPosition(150,50);
   glutCreateWindow("StreetFighter de pobre");
   glutDisplayFunc(renderScene);
   glutKeyboardFunc(keyPress);
   glutIdleFunc(idle);
   glutKeyboardUpFunc(keyup);
   init();
   glutMainLoop();
   return 0;
}