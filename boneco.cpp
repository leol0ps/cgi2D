#include "boneco.hpp"
#include <math.h>
#include <stdio.h>
extern int Width;
extern int Height;


void Boneco::DesenhaColisaoCirc(  GLfloat radius, GLfloat R, GLfloat G, GLfloat B){
        glColor3f(R,G,B);
        glPointSize(5.0);
        //printf("%f,%f \n", radius,R);;
        glBegin(GL_POINTS);
        for (int i = 0; i < 18; i++){
         glVertex2f(radius* cos(2*M_PI*i/18),radius*sin(2*M_PI*i/18));
        }
        glEnd();
    }
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
void Boneco::DesenhaBoneco(GLfloat x, GLfloat y,GLfloat raio, GLfloat gThetaRight, GLfloat gThetaLeft, GLfloat gTheta2, GLfloat gTheta3, GLfloat bodyTheta, GLfloat R, GLfloat G, GLfloat B){

    glPushMatrix();
    
    //printf("%f\n",bodyTheta);
    glTranslatef(x,y,0);
    glRotatef(bodyTheta,0,0,1);
    DesenhaBraco((raio-raio/7),0, (raio/4) , (raio*2),  (gThetaRight),gTheta2, (raio/3));
    DesenhaBraco((-(raio-raio/7)),0, (raio/4) , (raio*2),  (gThetaLeft),gTheta3, (raio/3));
    DrawHead(raio, R,  G , B);
       if(isShowingCircle()){
        DesenhaColisaoCirc(*(obtemRaio())*2.5,1,1,1);
    }
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
    //printf("%f, %f, %f\n", vel, time, x);
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
    x= (*ObtemVel())*cos((*(obtemAngulo()) +90)*M_PI/180)*time;
    y= (*ObtemVel())*sin((*(obtemAngulo()) + 90)*M_PI/180)*time;
    if(direction==pra_tras){
        x=-x;
        y=-y;
    }
    float colisionRadius = *(obtemRaio())*2.5;
    float distancia = sqrt(quadrado((*ObtemXadress())+x-inimigoX) + quadrado(*(ObtemYadress()) +y - inimigoY));
    //printf("%f distancia, %f x, %f y\n", distancia,x,y);
    if(*(obtemRaio()) + colisionRadius > distancia){
        return true;
    }
    return false;
}

void Boneco::initPosition(){
    *ObtemThetaRight() = 225;
    *ObtemTheta2adress() = 135;
    *(ObtemThetaLeft()) = 135 ;
    *(ObtemTheta3adress()) = -135;
}

void Boneco::MoveRightArm(GLfloat dx, GLfloat antiDelta){
    *(ObtemThetaRight()) = 225 + dx;
    *(ObtemTheta2adress()) = 135 + antiDelta;
}
void Boneco::MoveLeftArm(GLfloat dx, GLfloat antiDelta){
    *(ObtemThetaLeft()) = 135 + dx;
    *(ObtemTheta3adress()) = -135 + antiDelta;
}
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
      GLfloat a = x;
      xOut =  x*cos(angle*M_PI/180) - (y*sin(angle*M_PI/180));
      yOut = (a*sin(angle*M_PI/180)) + y*cos(angle*M_PI/180); 
}

void translatePoint(GLfloat x, GLfloat y,GLfloat dx, GLfloat dy, GLfloat &xOut, GLfloat &yOut){
  xOut = x+dx;
  yOut = y+dy;
}
bool Boneco::socoColision(socoHand soco, GLfloat enemyX, GLfloat enemyY, GLfloat enemyRadius ){
    float x=0,y=0;
    if(soco == right){
        translatePoint(x,y,0,*obtemRaio()*2,x,y);
        RotatePoint(x,y,*ObtemTheta2adress(),x,y);
        translatePoint(x,y,0,*obtemRaio()*2,x,y);
        RotatePoint(x,y,*ObtemThetaRight(),x,y);
        translatePoint(x,y,(*obtemRaio()-*obtemRaio()/7),0,x,y);
        RotatePoint(x,y, *obtemAngulo(),x,y);
        translatePoint(x,y,*ObtemXadress(),*ObtemYadress(),x,y);
    }
    else if(soco == left){
        translatePoint(x,y,0,*obtemRaio()*2,x,y);
        RotatePoint(x,y,*ObtemTheta3adress(),x,y);
        translatePoint(x,y,0,*obtemRaio()*2,x,y);
        RotatePoint(x,y,*ObtemThetaLeft(),x,y);
        translatePoint(x,y,(-(*obtemRaio()-*obtemRaio()/7)),0,x,y);
        RotatePoint(x,y, *obtemAngulo(),x,y);
        translatePoint(x,y,*ObtemXadress(),*ObtemYadress(),x,y);

    }
    float distancia = sqrt(quadrado(x-enemyX) + quadrado(y - enemyY));
    /*glPushMatrix();
    glTranslatef(x,y,0);
    //printf("x = %f e y = %f\n", x,y);
    DesenhaCirc(*obtemRaio()/3,1,1,1);
    glPopMatrix();*/
    if(enemyRadius + *obtemRaio()/3 > distancia){
        return true;
    }
    return false;
}
void Boneco:: changeColor(){
    Color* corAtual = obtemCor();
    if(*corAtual == red){
        *corAtual = roxo;
        changeRGB(0.6,0.1,1);
    }
    else if(*corAtual == green){
        *corAtual = blue;
        changeRGB(0,0,1);
    }
    else if(*corAtual == blue){
        *corAtual = green;
        changeRGB(0,1,0);
    }
    else{
        *corAtual = red;
        changeRGB(1,0,0);
    }
}