#include "boneco.h"
#include <math.h>
#include <stdio.h>

void Boneco::DesenhaCirc(  GLfloat radius, GLfloat R, GLfloat G, GLfloat B){
        glColor3f(R,G,B);
        glPointSize(10.0);
        //printf("%f,%f \n", radius,R);;
        glBegin(GL_POLYGON);
        for (int i = 0; i < 18; i++){
         glVertex2f(radius* cos(2*M_PI*i/18),radius*sin(2*M_PI*i/18));
        }
        glEnd();
    }
void Boneco::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
  glColor3f (R, G, B);
  glBegin(GL_POLYGON);
    glVertex2f((width/2), 0.0 );
    glVertex2f((width/2), height );
    glVertex2f(-(width/2), height);
    glVertex2f(-(width/2),0);
    glEnd();

}

void Boneco::DesenhaBraco(GLfloat x, GLfloat y, GLfloat largura, GLfloat altura, GLfloat gTheta1, GLfloat gTheta2, GLfloat raio){
    glPushMatrix();
    glTranslatef(x,y,0);
    printf("%f\n",x);
    glRotatef(gTheta1,0,0,1);
    DesenhaRect(altura,largura,0,1,1);
    glTranslatef(0,altura,0);
    glRotatef(gTheta2,0,0,1);
    DesenhaRect(altura,largura,1,1,1);
    glTranslatef(0,altura,0);
    DesenhaCirc(raio,1,0,0);
    glPopMatrix();
}

void Boneco::DrawHead(GLfloat raio, GLfloat R, GLfloat  G , GLfloat B){
    DesenhaCirc(raio, R,G,B);
    
}
void Boneco::DesenhaBoneco(GLfloat x, GLfloat y,GLfloat raio, GLfloat gTheta1, GLfloat gTheta2,GLfloat R, GLfloat G, GLfloat B){

    glPushMatrix();
    glTranslatef(x,y,0);
    
    DrawHead(raio, R,  G , B);
    DesenhaBraco((x+raio),0, (raio/4) , (raio*2),  (gTheta1+45),135, (raio/3));
    DesenhaBraco((x-raio),0, (raio/4) , (raio*2),  (gTheta1-45),-135, (raio/3));
    glTranslatef(0,raio,0);
    DesenhaCirc(raio/5, R, G ,B);
    glPopMatrix();
}

