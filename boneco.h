//#pragma once
#ifndef BONECO_H
#define	BONECO_H
#include <GL/gl.h>
#include <GL/glu.h>

class Boneco {
    GLfloat gX;
    GLfloat gY;
    GLfloat gTheta1;
    GLfloat gTheta2;
    GLfloat radius;
    GLfloat R;
    GLfloat G;
    GLfloat B;
private:
        void DrawHead(GLfloat raio, GLfloat R, GLfloat  G , GLfloat B);
        void DesenhaCirc(  GLfloat radius, GLfloat R, 
                    GLfloat G, GLfloat B);
        void DesenhaBraco(   GLfloat x, GLfloat y, GLfloat largura, GLfloat altura, GLfloat gTheta1, 
                    GLfloat gTheta2, GLfloat raio);
        void DesenhaBoneco(GLfloat x, GLfloat y,GLfloat raio, GLfloat gTheta1, GLfloat gTheta2,GLfloat R, GLfloat G, GLfloat B);

        void DesenhaRect(  GLint height, GLint width, 
                    GLfloat R, GLfloat G, GLfloat B);
public:
    Boneco(){
            gX = 0;
            gY = 0;
            radius = 0;
            gTheta1 = 180;
            gTheta2 = 45;
            R = 1;
            G = 1;
            B = 0;
    };
    void Desenha(){ 
        DesenhaBoneco(gX, gY, radius, gTheta1, 
                gTheta2,R,G,B);
         };
    void RodaBraco1(GLfloat inc);
    void RodaBraco2(GLfloat inc);
    GLfloat* ObtemXadress(){
        return &gX;
    };
    GLfloat* ObtemTheta1adress(){
        return &gTheta1;
        };
    GLfloat* ObtemTheta2adress(){
            return &gTheta2;
        };
    void changeRadius(GLfloat a){
        radius = a;
    }
    void setBoneco(GLfloat x, GLfloat y, GLfloat raio, int player){
        gX = x;
        gY = y;
        radius = raio;
        if(player){
            R=1;G=0;B=0;
        }
        else{
            R=0;G=0;B=1;
        }
    }


};
#endif	