//#pragma once
#ifndef BONECO_H
#define	BONECO_H
#include <GL/gl.h>
#include <GL/glu.h>

enum Color{red,yellow,blue,green,roxo};
enum Direction{pra_frente,pra_tras};
enum socoHand{left,right};
class Boneco {
    GLfloat gX;
    GLfloat gY;
    GLfloat gThetaRight;
    GLfloat gThetaLeft;
    GLfloat gTheta2;
    GLfloat gTheta3;
    GLfloat bodyTheta;
    GLfloat radius;
    GLfloat R;
    GLfloat G;
    GLfloat B;
    Color corAtual;
    GLfloat gVel;
    GLfloat gWel;
    bool colisionCircle;
    int isCPU; 
private:
        void DrawHead(GLfloat raio, GLfloat R, GLfloat  G , GLfloat B);
        void DesenhaCirc(  GLfloat radius, GLfloat R, 
                    GLfloat G, GLfloat B);
        void DesenhaColisaoCirc(  GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
        void DesenhaBraco(   GLfloat x, GLfloat y, GLfloat largura, GLfloat altura, GLfloat gThetaRight, 
                    GLfloat gTheta2, GLfloat raio);
        void DesenhaBoneco(GLfloat x, GLfloat y,GLfloat raio, GLfloat gThetaRight, GLfloat gThetaLeft, GLfloat gTheta2, GLfloat gTheta3, GLfloat bodyTheta, GLfloat R, GLfloat G, GLfloat B);

        void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
        float Modulo(float a);
        
public:
    Boneco(){
            gX = 0;
            gY = 0;
            radius = 0;
            gThetaRight = 225;
            gThetaLeft = 135;
            gTheta2 = 135;
            gTheta3 = -135;
            bodyTheta = 0;
            R = 1;
            G = 1;
            B = 0;
            gVel = 0.4;
            gWel = 1;
            colisionCircle = false;
    };
    void Desenha(){ 
        DesenhaBoneco(gX, gY, radius, gThetaRight, gThetaLeft,
                gTheta2,gTheta3, bodyTheta, R,G,B);
         };
    void RodaBraco1(GLfloat inc);
    void RodaBraco2(GLfloat inc);
    GLfloat* ObtemXadress(){
        return &gX;
    };
    GLfloat* ObtemYadress(){
        return &gY;
    };
     GLfloat* ObtemVel(){
        return &gVel;
    };
     GLfloat* ObtemaAngularVel(){
        return &gWel;
    };
    GLfloat* ObtemThetaRight(){
        return &gThetaRight;
        };
    GLfloat* ObtemThetaLeft(){
        return &gThetaLeft;
        };
    GLfloat* ObtemTheta3adress(){
            return &gTheta3;
        };
    GLfloat* ObtemTheta2adress(){
            return &gTheta2;
        };
    GLfloat* obtemAngulo(){
        return &bodyTheta;
        };
    GLfloat* obtemRaio(){
        return &radius;
        };
    Color* obtemCor(){
        return &corAtual;
        };
    void ShowColisionCircle(){
        colisionCircle = !colisionCircle;
    }
    bool isShowingCircle(){
        return colisionCircle;
    }
    void changeRadius(GLfloat a){
        radius = a;
    };
    void setBoneco(GLfloat x, GLfloat y, GLfloat raio, GLfloat theta, int maquina){
        gX = x;
        gY = y;
        radius = raio;
        bodyTheta = theta;
        if(maquina){
            R=1;G=0;B=0;
            corAtual = red;
        }
        else{
            R=0;G=1;B=0;
            corAtual = green;
        }
        isCPU = maquina;
    };
    void changeRGB(GLfloat r, GLfloat g, GLfloat b){
        R=r;
        G = g;
        B = b;

    }
   
    void MudaAngulo(GLfloat delta,GLdouble time);
    void Move(GLdouble time, Direction direction, GLfloat inimigoX, GLfloat inimigoY);
    bool Colisao(GLdouble time, Direction direction, GLfloat inimigoX, GLfloat inimigoY);
    void MoveRightArm(GLfloat dx, GLfloat antiDelta);
    void MoveLeftArm(GLfloat dx, GLfloat antiDelta);
    void initPosition();
    void changeColor();
    bool socoColision(socoHand soco, GLfloat enemyX, GLfloat enemyY, GLfloat enemyRadius );

};
#endif