#include "pugixml.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "boneco.hpp"
GLdouble timeDiference;
int Width;
int Height;
int animate=0;
int keyStatus[256];
Boneco boneco1P;
Boneco boneco2P;
#define incAngulo 0.3
bool colision = false;
bool socoColision = false;
bool ponto = true;
float xDesloc;
float initX;
float initY;
float ombroAngulo;
int placar1P;
int placar2P;
static char str[1000];
void * font = GLUT_BITMAP_9_BY_15;

void ImprimePlacar(GLfloat x, GLfloat y){
    glColor3f(1.0, 1.0, 1.0);
    //Cria a string a ser impressa
    char *tmpStr;
    sprintf(str, "jogador: %d x %d maquina", placar1P, placar2P );
    //Define a posicao onde vai comecar a imprimir
    glRasterPos2f(x, y);
    //Imprime um caractere por vez
    tmpStr = str;
    while( *tmpStr ){
    glutBitmapCharacter(font, *tmpStr);
    tmpStr++;
    }
}

void clique(int button, int state, int x, int y){
    animate =1;
    if(state == GLUT_UP){
        if(socoColision)
                placar1P++;
        socoColision = false;
        animate=0;
        boneco1P.initPosition();
        
    }
        
    initX = -((float)Width/2) + (float)x;
    
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
             animate = !animate;
             break;
        case 'l':
        case 'L':
             keyStatus[(int)('l')] = 1; //Using keyStatus trick
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
     //boneco1P.socoColision(left,*boneco2P.ObtemXadress(), *boneco2P.ObtemYadress() , *boneco2P.obtemRaio());
     ImprimePlacar(float(-Width/2 + 10),float(Height/2-10));
     glutSwapBuffers(); // Desenha the new frame of the game.
}
void idle(){
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime;
//Pega o tempo que passou do inicio da aplicacao
    currentTime = glutGet(GLUT_ELAPSED_TIME);
// Calcula o tempo decorrido desde de a ultima frame.
    timeDiference = currentTime - previousTime;
//Atualiza o tempo do ultimo frame ocorrido
    previousTime = currentTime;
    double inc = incAngulo;
    if(keyStatus[(int)('l')])
    {
        boneco1P.ShowColisionCircle();
        boneco2P.ShowColisionCircle();
    }
    if(keyStatus[(int)('a')])
    {
        boneco1P.MudaAngulo(inc,timeDiference);
    }
    if(keyStatus[(int)('d')])
    {
        boneco1P.MudaAngulo(-inc,timeDiference);
    }
    if(keyStatus[(int)('w')])
    {
        colision = boneco1P.Colisao(timeDiference,pra_frente,*boneco2P.ObtemXadress(),*boneco2P.ObtemXadress());
        if(!colision)
        boneco1P.Move(timeDiference,pra_frente,*boneco2P.ObtemXadress(),*boneco2P.ObtemXadress());
        
    }
    if(keyStatus[(int)('s')])
    {
        
        colision = boneco1P.Colisao(timeDiference,pra_tras,*boneco2P.ObtemXadress(),*boneco2P.ObtemXadress());
        if(!colision)
        boneco1P.Move(timeDiference,pra_tras,*boneco2P.ObtemXadress(),*boneco2P.ObtemXadress());
        
    }
    if(socoColision){
        boneco2P.changeColor();
    }
    //std::cout << placar1P <<"\n";
    glutPostRedisplay();
}
void socoAnimate(int x,int y){
    float atualX = -((float)Width/2) + (float)x;
    if(animate){
    
    int dx = atualX - initX;
    ombroAngulo = 100*dx/(((float)Width)/2);
    float antiAngulo = -70*dx/(((float)Width)/2);
    printf("%f ombro angulo\n", ombroAngulo);
    
        if(atualX>initX && dx<(((float)Width)/2)){
            boneco1P.MoveRightArm(ombroAngulo, antiAngulo);
        }
        else if(atualX < initX && dx>-((float)Width)/2){
            boneco1P.MoveLeftArm(ombroAngulo,antiAngulo);
        }
        else {
            if(dx>0){
                
                if(!socoColision){
                    ponto = true;
                    socoColision = boneco1P.socoColision(right, *boneco2P.ObtemXadress(), *boneco2P.ObtemYadress() , *boneco2P.obtemRaio());
                }
                 
                else if(ponto){
                    ponto = boneco1P.socoColision(right,*boneco2P.ObtemXadress(), *boneco2P.ObtemYadress() , *boneco2P.obtemRaio());
                }
                    
                else{
                    socoColision = false;
                    placar1P++;
                }

            }
                
            else{
                if(!socoColision){
                    ponto = true;
                    socoColision = boneco1P.socoColision(left, *boneco2P.ObtemXadress(), *boneco2P.ObtemYadress() , *boneco2P.obtemRaio());
                }
                 
                else if(ponto){
                    ponto = boneco1P.socoColision(left,*boneco2P.ObtemXadress(), *boneco2P.ObtemYadress() , *boneco2P.obtemRaio());
                }
                    
                else{
                    socoColision = false;
                    placar1P++;
                }

            }
             
        }
    }
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
    if(argc < 2){
        std::cout << "sem arquivo";
        return 0;
    }
   pugi::xml_parse_result result = doc.load_file(argv[1]);
   if(!result){
        std::cout << "arquivo não encontrado";
        return 0;
   }
   float xdiff = atoi(doc.child("svg").child("rect").attribute("x").value());
   float ydiff = atoi(doc.child("svg").child("rect").attribute("y").value());
   Width = atoi(doc.child("svg").child("rect").attribute("width").value());
   
   Height = atoi(doc.child("svg").child("rect").attribute("height").value());
   xDesloc = ((float)Width)/2;
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
   boneco1P.setBoneco(boneco1X,boneco1Y,raio1,(bodyTheta+180),0);
   boneco2P.setBoneco(boneco2X,boneco2Y,raio2,bodyTheta,1);
   placar1P = 0;
   placar2P = 0;
 
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(Width, Height);
   glutInitWindowPosition(150,50);
   glutCreateWindow("StreetFighter de pobre");
   glutDisplayFunc(renderScene);
   glutKeyboardFunc(keyPress);
   glutIdleFunc(idle);
   glutKeyboardUpFunc(keyup);
   glutMouseFunc(clique);
   glutMotionFunc(socoAnimate);
   init();
   glutMainLoop();
   return 0;
}