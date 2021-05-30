#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <string>
using namespace std;

float P[2], V[2], A[2], P2[2], V2[2], A2[2], tf, t, h, N, PB, TB, aux, tiempo_cambio = 10, t0, t1;
int G = -90, ancho_cajas = 50, alto_cajas = 200, radio = 10, i, op, cont, cont2, cantidad_bloques = 15, salto = 250;
int ancho = 500, alto = 500, alturas[15], alturas2[15];
bool paused = true, val = true, gameOver = false;

void Iniciar()
{
    glClearColor(0.36, 0.67, 0.88, 1);
    glColor3f(0.52, 0.75, 0.91);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ancho / 2, ancho / 2, 0, alto, -100, 100);
    glMatrixMode(GL_MODELVIEW);

    t = 0.1;
    h = 0.05;
    i = 0;
    P[1] = alto / 2;
    V[1] = 0;
    A[1] = G;
    V2[0] = (0.2 / (pow(t, 0.8)));
}
void Iniciar_Sistema()
{
    tiempo_cambio = tiempo_cambio - 1;
    PB = 0;
    cont = 0;
    for (int i = 0; i < cantidad_bloques; i++)
    {
        alturas[i] = rand() % 200 + 100;
        alturas2[i] = (alturas[i] + 120);
    }
}
void Reset_Sistema()
{

    cont2 = 0;
    P[1] = alto / 2;
    V[1] = 0;
    V2[0] = 0;
    P2[0] = 0;
    gameOver = false;
    paused = false;
    tiempo_cambio = 10;
    salto = 250;
    t = 0.1;
    Iniciar_Sistema();

}
void drawText(const char* text, int length, int x, int y)
{
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
}
void drawText1(const char* text, int length, int x, int y)
{
    glRasterPos2i(x, y);
    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)text[i]);
    }
}
void pintar()
{
    TB = (ancho / 2) - PB;
    glPushMatrix();
    glBegin(GL_QUADS);
    glScalef(1.5, 5.0, 1.0);
    glColor3f(0.2, 0.7, 0.85);
    glVertex2d(-500, 500);
    glColor3f(0.15, 0.45, 0.65);
    glVertex2d(-500, 0);
    glVertex2d(500, 0);
    glColor3f(0.2, 0.59, 0.85);
    glVertex2d(500, 500);
    glEnd();
    glPopMatrix();

    for (int i = 0; i < cantidad_bloques; i++)
    {
        glPushMatrix();
        glTranslated(TB + (i * salto), 0.0, 0.0);
        glBegin(GL_QUADS);
        glScalef(1.5, 5.0, 1.0);
        glColor3f(0.27, 0.78, 0.03);
        glVertex2d(0, alturas[i]);
        glVertex2d(0, 0);
        glColor3f(0.05, 0.54, 0.1);
        glVertex2d(ancho_cajas, 0);
        glVertex2d(ancho_cajas, alturas[i]);
        glColor3f(0.05, 0.54, 0.1);
        glEnd();

        glBegin(GL_QUADS);
        glScalef(1.5, 5.0, 1.0);
        glColor3f(0.27, 0.78, 0.03);
        glVertex2d(-10, alturas[i]);
        glVertex2d(-10, alturas[i] - 30);
        glVertex2d(ancho_cajas + 10, alturas[i] - 30);
        glVertex2d(ancho_cajas + 10, alturas[i]);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        glTranslated(TB + (i * salto), 0.0, 0.0);
        glBegin(GL_QUADS);
        glScalef(1.5, 5.0, 1.0);
        glColor3f(0.27, 0.78, 0.03);
        glVertex2d(0, alto);
        glVertex2d(0, alturas2[i]);
        glColor3f(0.05, 0.54, 0.1);
        glVertex2d(ancho_cajas, alturas2[i]);
        glVertex2d(ancho_cajas, alto);
        glColor3f(0.05, 0.54, 0.1);
        glEnd();

        glBegin(GL_QUADS);
        glScalef(1.5, 5.0, 1.0);
        glColor3f(0.27, 0.78, 0.03);
        glVertex2d(-10, alturas2[i]);
        glVertex2d(-10, alturas2[i] + 30);
        glVertex2d(ancho_cajas + 10, alturas2[i] + 30);
        glVertex2d(ancho_cajas + 10, alturas2[i]);
        glEnd();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(0.0, P[1], 0.0);

    glColor3f(1, 0.99, 0);
    glutSolidSphere(radio, 10, 10);
    glBegin(GL_QUADS);
    glColor3d(1, 0.0, 0);
    glVertex2d(15, 3);
    glVertex2d(5, 3);
    glColor3f(1, 0.6, 0);
    glVertex2d(5, -3);
    glVertex2d(15, -3);
    glEnd();
    glPopMatrix();
}
void Aumentar_Tiempo()
{
    i = i + 1;
    t = t + h;
    PB = PB + (P2[0]);

}
void Calcular_MetodoEuler()
{
    P[1] = P[1] + (h * V[1]);
    V[1] = V[1] + (h * A[1]);
    A[1] = A[1];

    P2[0] = P2[0] + (h * V2[0]);
    V2[0] = (0.2 / (pow(t, 0.8)));

}
void textos()
{
    std::string text;
    std::string text1 = std::to_string(cont2);
    std::string text2;

    text = "FLAPPY BIRD";
    text2 = "Use el enter para empezar el juego                           Para saltar use la espaciadora";

    glColor3f(0, 0, 0);
    drawText(text.data(), text.size(), -200, 400);
    glColor3f(1, 1, 1);
    drawText(text1.data(), text1.size(), 0, 400);
    drawText1(text2.data(), text2.size(), -240, 10);
    if (gameOver == true)
    {
        std::string text3;
        text3 = "GAME OVER";
        glColor3f(1, 0, 0);
        drawText(text3.data(), text3.size(), -50, 250);
    }
}
void modelo()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    pintar();
    textos();
    glFlush();
    glutSwapBuffers();
}
void colisiones()
{
    if (P[1] <= radio)
    {
        gameOver = true;
        cout << "GAME OVER" << endl;
        paused = true;
    }

    for (int i = 0; i < cantidad_bloques; i++)
    {
        if (P[1] <= alturas[i] - 30 || P[1] >= alturas2[i] + 30)
        {
            if (P[0] + 9 >= (TB + (i * salto)) - radio && P[0] < (TB + (i * salto)) + ancho_cajas + radio)
            {
                gameOver = true;
                cout << "GAME OVER" << endl;
                paused = true;
            }
        }
        else if (P[0] + 9 >= (TB + (i * salto) - 10) - radio && P[0] < (TB + (i * salto) + 10) + ancho_cajas + radio)
        {
            if ((P[1]) < alturas[i] + radio)
            {
                gameOver = true;
                cout << "GAME OVER" << endl;
                paused = true;
            }
            if ((P[1]) > alturas2[i] - radio)
            {
                gameOver = true;
                cout << "GAME OVER" << endl;
                paused = true;
            }
            if (cont == i)
            {
                cont++;
                cont2++;
                cout << "cambio:" << cont << " real : " << cont2 << endl;
            }
        }
    }
}
void OnKey(unsigned char key, int x, int y)
{
    if (key == 32) //espaciadora
    {
        V[1] = 90;
    }
    if (key == 13) //enter
    {
        Reset_Sistema();
        cout << "Entro al juego" << endl;
    }
    if (key == 27) //esc
    {
        exit(0);
    }
    glutSwapBuffers();
}
void OnTimerGL(int id)
{

    if (paused == false)
    {
        Aumentar_Tiempo();
        Calcular_MetodoEuler();
        colisiones();
    }

    if (cont == cantidad_bloques && val == true)
    {
        aux = t;
        val = false;
    }
    else if (cont == cantidad_bloques)
    {
        if (t > aux + tiempo_cambio)
        {
            if (salto < 100)
            {
                salto = 250;
            }
            Iniciar_Sistema();
            salto = salto - 25;
            val = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1, OnTimerGL, 1);
}
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10, 20);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Flappy Bird");
    Iniciar();
    glutDisplayFunc(pintar);
    glutIdleFunc(modelo);
    glutKeyboardFunc(OnKey);
    glutTimerFunc(1, OnTimerGL, 1);
    glutMainLoop();
    return 0;
}