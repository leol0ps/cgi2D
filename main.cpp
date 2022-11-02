#include "pugixml.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "boneco.h"

int Width;
int Height;
int animate=0;

Boneco boneco1P;
Boneco boneco2P;


void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);

     boneco1P.Desenha();
     glutSwapBuffers(); // Desenha the new frame of the game.
}
void idle(){
    glutPostRedisplay();
}

void init(void)
{
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

    pugi::xml_parse_result result = doc.load_file("arena_1.svg");

   Width = atoi(doc.child("svg").child("rect").attribute("width").value());
   Height = atoi(doc.child("svg").child("rect").attribute("height").value());
   float raio1 = atoi(doc.child("svg").child("circle").attribute("r").value());
   float raio2 = atoi(doc.child("svg").child("circle").next_sibling().attribute("r").value());
   int boneco1X = atoi(doc.child("svg").child("circle").attribute("cx").value());
   int boneco1Y = atoi(doc.child("svg").child("circle").attribute("cy").value());
   
   int boneco2X = atoi(doc.child("svg").child("circle").next_sibling().attribute("cx").value());
   int boneco2Y = atoi(doc.child("svg").child("circle").next_sibling().attribute("cy").value());
   //boneco1P.setBoneco(boneco1X,boneco1Y,raio1,0);
   boneco1P.setBoneco(15,15,raio1,0);
   boneco2P.setBoneco(boneco2X,boneco2Y,raio2,1);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(Width, Height);
   glutInitWindowPosition(150,50);
   glutCreateWindow("StreetFighter de pobre");
   glutDisplayFunc(renderScene);
    //glutKeyboardFunc(keyPress);
   glutIdleFunc(idle);
   //glutKeyboardUpFunc(keyup);

   init();
   glutMainLoop();
   return 0;
}