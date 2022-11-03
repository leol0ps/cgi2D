#include "boneco.hpp"
#include <math.h>
#include <stdio.h>
extern int Width;
extern int Height;
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
    //printf("%f\n",x);
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
void Boneco::DesenhaBoneco(GLfloat x, GLfloat y,GLfloat raio, GLfloat gTheta1, GLfloat gTheta2, GLfloat bodyTheta, GLfloat R, GLfloat G, GLfloat B){

    glPushMatrix();
    
    //printf("%f\n",bodyTheta);
    glTranslatef(x,y,0);
    glRotatef(bodyTheta,0,0,1);
    DesenhaBraco((raio-raio/7),0, (raio/4) , (raio*2),  (gTheta1+45),135, (raio/3));
    DesenhaBraco((-(raio-raio/7)),0, (raio/4) , (raio*2),  (gTheta1-45),-135, (raio/3));
    DrawHead(raio, R,  G , B);
    glTranslatef(0,raio,0);
    DesenhaCirc(raio/5, R, G ,B);
    glPopMatrix();
}

void Boneco::MudaAngulo(GLfloat delta,GLdouble time){
    *(obtemAngulo())+= delta*time;
}
float Boneco::Modulo(float a){
    if(a>0)
        return a;
    else return -a;
}
GLfloat quadrado(GLfloat a){
    return a*a;
}
void Boneco::Move(GLdouble time, Direction direction, GLfloat inimigoX, GLfloat inimigoY){
    float x=0,y=0;
    float vel = *ObtemVel();
    
    x= vel*cos((*(obtemAngulo()) +90)*M_PI/180)*time;
    y= vel*sin((*(obtemAngulo()) + 90)*M_PI/180)*time;
    if(direction==pra_tras){
        x=-x;
        y=-y;
    }
    printf("%f, %f, %f\n", vel, time, x);
    float colisionRadius = *(obtemRaio())*3;
    float distancia = sqrt(quadrado((*ObtemXadress())-inimigoX) + quadrado(*(ObtemYadress()) - inimigoY));
    if((Modulo((*(ObtemXadress())+x))  + *obtemRaio())> ((float)Width/2) | (Modulo(*(ObtemYadress())+y) +  *obtemRaio()) > ((float)Height/2)){
        if(*ObtemXadress() > 0 && x < 0 | *ObtemXadress() < 0 && x > 0){
            *ObtemXadress()+=x;
        }
        if(*(ObtemYadress()) > 0 && y < 0 | *(ObtemYadress()) < 0 && y > 0){
            *ObtemYadress()+=y;
        }
        
    }
    else{
            *ObtemXadress()+=x;
            *ObtemYadress()+=y;
    }
  
}

bool Boneco::Colisao(GLdouble time, Direction direction, GLfloat inimigoX, GLfloat inimigoY){
    float x,y;
    x= (*ObtemVel())*cos((*(obtemAngulo()) +90)*M_PI/180)*time;//*time;
    y= (*ObtemVel())*sin((*(obtemAngulo()) + 90)*M_PI/180)*time;//*time;
    if(direction==pra_tras){
        x=-x;
        y=-y;
    }
    float colisionRadius = *(obtemRaio())*3;
    float distancia = sqrt(quadrado((*ObtemXadress())-inimigoX) + quadrado(*(ObtemYadress()) - inimigoY));
    if(*(obtemRaio()) + colisionRadius > distancia){
        return true;
    }
    return false;
}