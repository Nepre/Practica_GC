
/****************************************************************************************************

    CarGL (main.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ------------------------------------------------------------------------------------------

    CarsGL (C) 2012-2016 - Juan Antonio Puchol García (puchol@dccia.ua.es)

    Changelog:

    Versión 1.0 (Noviembre 2012)
        - Versión inicial para Code::Blocks 10.05

    Versión 1.1 (Noviembre 2012)
        - Arreglado el bug de selección incorrecta debido al panel inferior de controles

    Versión 1.2 (Octubre 2013 )
        - Adaptación de la librería GLUI a Code::Blocks 12.11 y 13.12

    Versión 1.3 (Octubre 2014 )
        - Adaptación de la librería GLUI a Code::Blocks 13.12

    Versión 2.0 (Octubre 2015 )
        - Adaptación del código empleando Shaders (Modern OpenGL Graphics)

    Versión 2.1 (Septiembre 2016 )
        - Modificación de los scrollbars de las luces para manipular la posisión (compatible con Code::Blocks 16.01)

    NOTA:   Para que esta aplicación compile se necesita tener copiados los
            siguientes ficheros desde la carpeta "Para Copiar":

            glut32.dll  -> C:\Windows\system

            Si es un Windows de 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Si es un Windows de 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


            ACLARACIÓN:
                Hay varias librerías libglui32.a en la carpeta "otros"
                - Renombrar libglui32.10.05.a a libglui32.a para usar Code::Blocks 10.05
                - Renombrar libglui32.12.11.a a libglui32.a para usar Code::Blocks 12.11
                - Renombrar libglui32.13.12.a a libglui32.a para usar Code::Blocks 13.12 o superior

****************************************************************************************************/

#include "Objects.h"
#include <GL\glui.h>
#include "loadjpeg.c"

#include <iostream>
using namespace std;

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);

    if(car != NULL){
        float pi = 3.141592;
        float gr = car->ry*pi /180.0;
        float seno = sin(gr);
        float coseno = cos(gr);
        switch (key)
        {
            case GLUT_KEY_UP:   // El coche avanza
                car->rr+=8;
                car->tz -= 0.4 * seno;
                car->tx -= 0.4 * coseno;
                car->ry -= 0.03 * car->rot;
                break;
            case GLUT_KEY_DOWN:   // El coche retrocede
                car->rr-=8;
                car->tz += 0.4 * seno;
                car->tx += 0.4 * coseno;
                car->ry += 0.03 * car->rot;
                break;
            case GLUT_KEY_LEFT:
                if(car->rot<30){
                    car->rot+=5;
                }
                break;
            case GLUT_KEY_RIGHT:
                if(car->rot>-30){
                    car->rot-=5;
                }
                break;
            if(car->rot<-30){
                car->rot = -30;
            }
            if(car->rot>30){
                car->rot = 30;
            }

        }
    }
    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}

void cargarTextura(int id){
    int width, height;
    unsigned char *img;

    width = escena.texturas_width[id];
    height = escena.texturas_height[id];
    img = escena.texturas[id];


    glBindTexture(GL_TEXTURE_2D, escena.texturas_id[id]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

}

/**************************************** main() ********************/

void cargarTexturas(){
    // loadjpeg devuelve un vector con los bytes de color de la imagen.

    escena.texturas[0] = LoadJPEG("..\\..\\Texturas\\phoneboothTexture.jpg",
                                  &escena.texturas_width[0],
                                  &escena.texturas_height[0]);
    escena.texturas[1] = LoadJPEG("..\\..\\Texturas\\phoneboothTexture.jpg",
                                  &escena.texturas_width[1],
                                  &escena.texturas_height[1]);
    escena.texturas[2] = LoadJPEG("..\\..\\Texturas\\phoneboothTexture.jpg",
                                  &escena.texturas_width[2],
                                  &escena.texturas_height[2]);
    cout << "Cargando texturas...." << escena.texturas_width[0] << endl;
    cout << "Cargando textura cubo..." << escena.texturas_width[2] << endl;

    cout << "direccion: " << (int) escena.texturas[0][0] << endl;
    cout << "direccion: " << (int) escena.texturas[0][1] << endl;
    cout << "direccion: " << (int) escena.texturas[0][2] << endl;
////
// PARA QUE OPENGL RESERVE ESPACIO PARA 3 TEXTURAS, aun no hace falta indicarle el tama�o
// solo le indicamos que habra 3 espacios para texturas. (3 manejadores, enteros, que
// que gestionara opengl.

    glGenTextures(3, escena.texturas_id); // le pasamos un vector donde almacenara los identificadores
                                            // de las texturas.
    cout  << "Cargando texturas: " << endl;
    for(int i = 0; i < 3; i++){
        cargarTextura(i);
        // name returned by glGenTextures, but not yet associated with a texture by calling glBindTexture,
        // is not the name of a texture.
        if(glIsTexture(escena.texturas_id[i])){
            cout << "cargada " << escena.texturas_id[i] << endl;
        }
        else{
            cout << "no cargada " << escena.texturas_id[i] << endl;
        }
    }
    cout << endl;

// 3. texturas: ir object.cpp cargaGexturas
}

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1400, 800 );

    int main_window = glutCreateWindow( "CarGL V2.0 (2015) con Shaders" );

    // Inicializa los valores de OpenGL para esta Aplicación
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea los objetos
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);
    TPrimitiva *alcantarillas = new TPrimitiva(1, ALCANTARILLAS_ID);
    TPrimitiva *arboles = new TPrimitiva(1, ARBOLES_ID);
    TPrimitiva *basuras = new TPrimitiva(1, BASURAS_ID);
    TPrimitiva *cabinas = new TPrimitiva(1, CABINAS_ID);
    TPrimitiva *cables = new TPrimitiva(1, CABLES_ID);
    TPrimitiva *cesped = new TPrimitiva(1, CESPED_ID);
    TPrimitiva *chimenea = new TPrimitiva(1, CHIMENEAS_ID);
    TPrimitiva *contenedor = new TPrimitiva(1, CONTENEDORES_ID);
    TPrimitiva *cosas_parque = new TPrimitiva(1, COSAS_PARQUE_ID);
    TPrimitiva *detalles = new TPrimitiva(1, DETALLES_ID);
    TPrimitiva *edificio = new TPrimitiva(1, EDIFICIO_ID);
    TPrimitiva *edificiosymuros = new TPrimitiva(1, EDIFICIOSYMUROS_ID);
    TPrimitiva *farolas = new TPrimitiva(1, FAROLAS_ID);
    TPrimitiva *semaforo = new TPrimitiva(1, SEMAFORO_ID);
    TPrimitiva *sillasymesas = new TPrimitiva(1, SILLASYMESAS_ID);
    TPrimitiva *tejadoextras = new TPrimitiva(1, TEJADOEXTRAS_ID);
    TPrimitiva *toldos = new TPrimitiva(1, TOLDOS_ID);
    TPrimitiva *vallasbajas = new TPrimitiva(1, VALLASBAJAS_ID);
    TPrimitiva *ventanasbasica = new TPrimitiva(1, VENTANASBASICA_ID);
    TPrimitiva *ventanasbasicasub = new TPrimitiva(1, VENTANASBASICASUB_ID);
    TPrimitiva *ventanapicobasica = new TPrimitiva(1, VENTANASPICOBASICA_ID);
    TPrimitiva *edificiomedieval1 = new TPrimitiva(1, EDIFICIOMEDIEVAL_ID);
    TPrimitiva *ninetree = new TPrimitiva(1, NINETREE_ID);
    TPrimitiva *mercado = new TPrimitiva(1, MERCADO_ID);
    TPrimitiva *farolas2 = new TPrimitiva(1, FAROLAS2_ID);
    TPrimitiva *carretera2 = new TPrimitiva(1, CARRETERA2_ID);
    TPrimitiva *puertas = new TPrimitiva(1, PUERTAS_ID);
    TPrimitiva *ventanas2 = new TPrimitiva(1, VENTANAS2_ID);



    car2->tx = -10;
    car2->tz = -20;

    car2->colores[0][0] = 0.35;
    car2->colores[0][1] = 0.1;
    car2->colores[0][2] = 0.4;
    car2->colores[0][3] = 1.0;



    escena.AddObject(road);
    escena.AddCar(car1);
    escena.AddCar(car2);
    escena.AddObject(alcantarillas);
    escena.AddObject(arboles);
    escena.AddObject(basuras);
    escena.AddObject(cabinas);
    escena.AddObject(cables);
    escena.AddObject(cesped);
    escena.AddObject(chimenea);
    escena.AddObject(contenedor);
    escena.AddObject(cosas_parque);
    escena.AddObject(detalles);
    escena.AddObject(edificio);
    escena.AddObject(edificiosymuros);
    escena.AddObject(farolas);
    escena.AddObject(puertas);
    escena.AddObject(semaforo);
    escena.AddObject(sillasymesas);
    escena.AddObject(tejadoextras);
    escena.AddObject(toldos);
    escena.AddObject(vallasbajas);
    escena.AddObject(ventanasbasica);
    escena.AddObject(ventanasbasicasub);
    escena.AddObject(ventanapicobasica);
    escena.AddObject(edificiomedieval1);
    escena.AddObject(ninetree);
    escena.AddObject(mercado);
    escena.AddObject(farolas2);
    escena.AddObject(carretera2);
    escena.AddObject(ventanas2);

    cargarTexturas();

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

