
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_c[2][4] = { {0.4, 1, 0.2, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del
float coloresc_c2[2][4] = { {0.35, 0.1, 0.4, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche

float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera
float coloresArbol_c[2][4] = { {0.372, 0.635, 0.341, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresCabina_c[2][4] = { {0.901, 0.058, 0.196, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresBlanco_c[2][4] = { {0.874, 0.847, 0.850, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresGris_c[2][4] = { {0.650, 0.650, 0.650, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresVentana_c[2][4] = { {0.682, 0.890, 0.898, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresMuros_c[2][4] = { {0.972, 0.678, 0.588, 1.0}, {1.0, 1.0, 1.0, 1.0}};
float coloresTejado_c[2][4] = { {0.411, 0.411, 0.411, 1.0}, {1.0, 1.0, 1.0, 1.0}};


//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Carretera.3ds", &num_vertices0);

            break;
		}

		case COCHE_ID: { // Creaci�n del coche
		    tx =  0.0;
		    ty =  0.9;
		    tz =  -17.0;
		    rr =  0.0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/coche/car.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/coche/wheel.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/coche/flecha.3ds", &num_vertices2);
            break;
		}

		case ALCANTARILLAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Alcantarillas.3ds", &num_vertices0);
            break;
		}

		case ARBOLES_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresArbol_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Arboles.3ds", &num_vertices0);
            break;
		}

		case BASURAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresGris_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Basuras.3ds", &num_vertices0);
            break;
		}

		case CABINAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresCabina_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/CabinasTelefonicas.3ds", &num_vertices0);
            break;
		}

		case CABLES_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Cables.3ds", &num_vertices0);
            break;
		}

		case CESPED_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresArbol_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Cesped.3ds", &num_vertices0);
            break;
		}

		case CHIMENEAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Chimeneas.3ds", &num_vertices0);
            break;
		}

		case CONTENEDORES_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresGris_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Contenedores.3ds", &num_vertices0);
            break;
		}

		case COSAS_PARQUE_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresBlanco_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/CosasParque.3ds", &num_vertices0);
            break;
		}

		case DETALLES_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Detalles1Tierra.3ds", &num_vertices0);
            break;
		}

		case EDIFICIO_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresGris_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/EdificioEspecial.3ds", &num_vertices0);
            break;
		}

		case EDIFICIOSYMUROS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresMuros_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/EdificiosYMuros.3ds", &num_vertices0);
            break;
		}

		case FAROLAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresGris_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Farolas.3ds", &num_vertices0);
            break;
		}

		case SEMAFORO_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Semaforo.3ds", &num_vertices0);
            break;
		}

		case SILLASYMESAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresBlanco_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Semaforo.3ds", &num_vertices0);
            break;
		}

		case TEJADOEXTRAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/TejadoExtras.3ds", &num_vertices0);
            break;
		}


		case TOLDOS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresBlanco_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Toldos.3ds", &num_vertices0);
            break;
		}

		case VALLASBAJAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresBlanco_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/VallasBajas.3ds", &num_vertices0);
            break;
		}

		case VENTANASBASICA_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresVentana_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/VentanasBasica.3ds", &num_vertices0);
            break;
		}

		case VENTANASBASICASUB_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresVentana_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/VentanasBasicaSub.3ds", &num_vertices0);
            break;
		}

		case VENTANASPICOBASICA_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresVentana_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/VentanasPicoBasica.3ds", &num_vertices0);
            break;
		}

		case PUERTAS_ID: {

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/pueras.3ds", &num_vertices0);
            break;
		}
		case EDIFICIOMEDIEVAL_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/EdificioMedieval1.3ds", &num_vertices0);
            break;

		}
		case NINETREE_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/NineTree.3ds", &num_vertices0);
            break;

		}
		case MERCADO_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Mercado.3ds", &num_vertices0);
            break;

		}
		case FAROLAS2_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Farolas2.3ds", &num_vertices0);
            break;

		}
		case CARRETERA2_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Carretera2.3ds", &num_vertices0);
            break;

		}
		case VENTANAS2_ID:{

		    tx = ty = tz = 0;

		    memcpy(colores, coloresTejado_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Ciudad/Ventanas2.3ds", &num_vertices0);
            break;

		}

	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (tipo) {

        case CARRETERA_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

                // Pintar las l�neas
                glUniform4fv(escena.uColorLocation, 1, colores[1]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);


            }
            break;
        }

        case ALCANTARILLAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case ARBOLES_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case BASURAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CABINAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                /*
                glBindTexture(GL_TEXTURE_2D, escena.texturas_id[0]); // activo la textura con la que trabajar.
                glUniform1i(escena.activadaLocation, 1);        // indicamos que vamos a trabajar con texturas al fragment
                glUniform1i(escena.u_SamplerLocation, 0); // le pasamos al fragment la textura 0
                glActiveTexture(GL_TEXTURE0); // y la textura activada va a la posicion 0.

                glVertexAttribPointer(escena.aTextureCoordLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0 + 6);
                */

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CABLES_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CESPED_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CHIMENEAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CONTENEDORES_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case COSAS_PARQUE_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case DETALLES_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case EDIFICIO_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case EDIFICIOSYMUROS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case FAROLAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case SEMAFORO_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case SILLASYMESAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case TEJADOEXTRAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case TOLDOS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case VALLASBAJAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case VENTANASBASICA_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case VENTANASBASICASUB_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case VENTANASPICOBASICA_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case EDIFICIOMEDIEVAL_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case NINETREE_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case MERCADO_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case FAROLAS2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case CARRETERA2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case VENTANAS2_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case PUERTAS_ID: {
            if (escena.show_road) {
                // C�lculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }
            break;
        }

        case COCHE_ID: {
            if (escena.show_car) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));


                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                //std::cout<<seleccion<<"  "<<escena.seleccion<<std::endl;
                if(seleccion + 1 == escena.seleccion){
                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                    // Asociamos los v�rtices y sus normales
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);

                    // C�lculo de la matriz modelo
                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                    modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));


                    modelViewMatrix = escena.viewMatrix * modelMatrix;

                    // Env�a nuestra ModelView al Vertex Shader
                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                    glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                }

            }


            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA trasera Dcha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.8, ty-0.25, tz-0.75));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-1.8, 0, 0.75));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(1.8, 0, -0.75));    // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,0,1));



                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA trasera Izq: C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.8, ty-0.25, tz+0.85));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-1.8, 0, -0.85));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));      // en radianes
                //modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(1.8, 0, 0.85));    // en radianes
                //modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(1,0,0));   // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,0,1));


                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Derecha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-2.5, ty-0.25, tz-0.8));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(2.5, 0, 0.8));    // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-2.5, 0, -0.8));    // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rot), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,0,1));



                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Izq: C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-2.5, ty-0.25, tz+0.85));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(2.5, 0, -0.85));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(-ry), glm::vec3(0,1,0));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-2.5, 0, 0.85));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rot), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,0,1));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                break;
            }
        }
    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;
    perspectiva = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicializaci�n de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    //aTextureCoordLocation = shaderProgram->attrib(A_TEXTURECORD);
    //u_SamplerLocation = shaderProgram->uniform(U_SAMPLER);
    //activadaLocation = shaderProgram->uniform("activada");

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);

        //glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniform4fv(uLuz0PositionLocation, 1, (const GLfloat *)escena.light0_position);
    glUniform4fv(uLuz1PositionLocation, 1, (const GLfloat *)escena.light1_position);
    //glUniform4fv(uLuz2PositionLocation, 1, (const GLfloat *)escena.light2_position);
    glUniform1f(uLuz0IntensityLocation, gui.light0_intensity);
    glUniform1f(uLuz1IntensityLocation, gui.light1_intensity);

    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLuz1Location=shaderProgram->uniform(U_LUZ1);

    uLuz0PositionLocation=shaderProgram->uniform(U_POS0);
    uLuz1PositionLocation=shaderProgram->uniform(U_POS1);

    uLuz0IntensityLocation=shaderProgram->uniform(U_INT0);
    uLuz1IntensityLocation=shaderProgram->uniform(U_INT1);

    uRenderPick3D = shaderProgram->uniform(U_PICK3D);

    glEnableVertexAttribArray(aTextureCoordLocation);


    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);
    glEnableVertexAttribArray(aTextureCoordLocation);

    // Estableciendo la matriz de proyecci�n perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(i, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1i(uLuz1Location, gui.light1_enabled);
    //glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniform4fv(uLuz0PositionLocation, 1, (const GLfloat *)escena.light0_position);
    glUniform4fv(uLuz1PositionLocation, 1, (const GLfloat *)escena.light1_position);
    //glUniform4fv(uLuz2PositionLocation, 1, (const GLfloat *)escena.light2_position);
    glUniform1f(uLuz0IntensityLocation, gui.light0_intensity);
    glUniform1f(uLuz1IntensityLocation, gui.light1_intensity);

    //glUniform1i(uNoLights, 1);
    //glUniform1f(uLuz2IntensityLocation, gui.light2_intensity);

    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    if(wireframe == 0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if(wireframe == 1){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    if(culling == 1){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else{
        glDisable(GL_CULL_FACE);
    }

    if(z_buffer == 1){
        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
    }
    else{
        glDisable(GL_DEPTH_TEST);
    }

    if(sentido == 0){
        glFrontFace(GL_CW);
    }
    else{
        glFrontFace(GL_CCW);
    }

    TPrimitiva *coche           = NULL;
    coche                       = GetCar(escena.seleccion);

    if(camara == 0 || coche == NULL || seleccion == 0){

        viewMatrix      = glm::mat4(1.0f);
        rotateMatrix    = glm::make_mat4(view_rotate);
        viewMatrix      = glm::translate(viewMatrix, glm::vec3(view_position[0], view_position[1], view_position[2]));
        viewMatrix      = viewMatrix*rotateMatrix;
        viewMatrix      = glm::scale(viewMatrix, glm::vec3(scale, scale, scale));

    }
    else if(camara == 1){

        viewMatrix                  = glm::mat4(1.0f);
        glm::vec3 cameraPosition    = glm::vec3(coche->tx+15, coche->ty+10, coche->tz);


        float angle = glm::radians(-coche->ry);

        double z1 = cameraPosition.z - coche->tz;
        double x1 = cameraPosition.x - coche->tx;

        double z2 = z1 * cos(angle) - x1 * sin(angle);
        double x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraPosition.z = z2 + coche->tz;
        cameraPosition.x = x2 + coche->tx;


        glm::vec3 cameraFocus       = glm::vec3(coche->tx-15, coche->ty-5, coche->tz);

        z1 = cameraFocus.z - coche->tz;
        x1 = cameraFocus.x - coche->tx;

        z2 = z1 * cos(angle) - x1 * sin(angle);
        x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraFocus.z = z2 + coche->tz;
        cameraFocus.x = x2 + coche->tx;

        glm::vec3 orientation       = glm::vec3(0,1,0);
        viewMatrix                  = glm::lookAt(cameraPosition, cameraFocus, orientation);

    }
    else{
        viewMatrix                  = glm::mat4(1.0f);
        glm::vec3 cameraPosition    = glm::vec3(coche->tx+10, coche->ty+3, coche->tz);



        float angle = glm::radians(-coche->ry);

        double z1 = cameraPosition.z - coche->tz;
        double x1 = cameraPosition.x - coche->tx;

        double z2 = z1 * cos(angle) - x1 * sin(angle);
        double x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraPosition.z = z2 + coche->tz;
        cameraPosition.x = x2 + coche->tx;


        glm::vec3 cameraFocus       = glm::vec3(coche->tx-15, coche->ty-5, coche->tz);

        z1 = cameraFocus.z - coche->tz;
        x1 = cameraFocus.x - coche->tx;

        z2 = z1 * cos(angle) - x1 * sin(angle);
        x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraFocus.z = z2 + coche->tz;
        cameraFocus.x = x2 + coche->tx;

        glm::vec3 orientation       = glm::vec3(0,1,0);
        viewMatrix                  = glm::lookAt(cameraPosition, cameraFocus, orientation);

    }

    //glUniform1i(uNoLights, 1);

    // Dibujar carretera y objetos
    glUniform1i(uRenderPick3D, 0);


    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

/***************************************** TEscena::renderSelection() *****************/

void __fastcall TEscena::renderSelection()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    TPrimitiva *coche           = NULL;
    coche                       = GetCar(escena.seleccion);

    if(camara == 0 || coche == NULL || seleccion == 0){

        viewMatrix      = glm::mat4(1.0f);
        rotateMatrix    = glm::make_mat4(view_rotate);
        viewMatrix      = glm::translate(viewMatrix, glm::vec3(view_position[0], view_position[1], view_position[2]));
        viewMatrix      = viewMatrix*rotateMatrix;
        viewMatrix      = glm::scale(viewMatrix, glm::vec3(scale, scale, scale));

    }
    else if(camara == 1){

        viewMatrix                  = glm::mat4(1.0f);
        glm::vec3 cameraPosition    = glm::vec3(coche->tx+15, coche->ty+10, coche->tz);


        float angle = glm::radians(-coche->ry);

        double z1 = cameraPosition.z - coche->tz;
        double x1 = cameraPosition.x - coche->tx;

        double z2 = z1 * cos(angle) - x1 * sin(angle);
        double x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraPosition.z = z2 + coche->tz;
        cameraPosition.x = x2 + coche->tx;


        glm::vec3 cameraFocus       = glm::vec3(coche->tx-15, coche->ty-5, coche->tz);

        z1 = cameraFocus.z - coche->tz;
        x1 = cameraFocus.x - coche->tx;

        z2 = z1 * cos(angle) - x1 * sin(angle);
        x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraFocus.z = z2 + coche->tz;
        cameraFocus.x = x2 + coche->tx;

        glm::vec3 orientation       = glm::vec3(0,1,0);
        viewMatrix                  = glm::lookAt(cameraPosition, cameraFocus, orientation);

    }
    else{
        viewMatrix                  = glm::mat4(1.0f);
        glm::vec3 cameraPosition    = glm::vec3(coche->tx+10, coche->ty+3, coche->tz);



        float angle = glm::radians(-coche->ry);

        double z1 = cameraPosition.z - coche->tz;
        double x1 = cameraPosition.x - coche->tx;

        double z2 = z1 * cos(angle) - x1 * sin(angle);
        double x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraPosition.z = z2 + coche->tz;
        cameraPosition.x = x2 + coche->tx;


        glm::vec3 cameraFocus       = glm::vec3(coche->tx-15, coche->ty-5, coche->tz);

        z1 = cameraFocus.z - coche->tz;
        x1 = cameraFocus.x - coche->tx;

        z2 = z1 * cos(angle) - x1 * sin(angle);
        x2 = z1 * sin(angle) + x1 * cos(angle);

        cameraFocus.z = z2 + coche->tz;
        cameraFocus.x = x2 + coche->tx;

        glm::vec3 orientation       = glm::vec3(0,1,0);
        viewMatrix                  = glm::lookAt(cameraPosition, cameraFocus, orientation);

    }

    glUniform1f(uLuz0IntensityLocation, 0.0f);
    glUniform1f(uLuz1IntensityLocation, 0.0f);
    //glUniform1i(uNoLights, 1);

    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    glUniform1i(uRenderPick3D, 1);

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    //glutSwapBuffers();
}

// Selecciona un objeto a trav�s del rat�n
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    unsigned char res[4];
    GLint viewport[4];

    renderSelection();

    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(mouse_x, viewport[3] + viewport[1] - mouse_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
    std::cout<<(int)res[0]<<std::endl;

    if(res[0] == 89){
          seleccion = 2;

    }
    else{
        if(res[0] == 102){
            seleccion = 1;
        }
        else{
            seleccion = 0;
        }
    }

    //gui.sel = seleccion;
    //gui.ControlCallback(SEL_ID);
    //gui.Idle();

}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 0;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.2;
    light1_intensity = 0.4;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");


    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");

    GLUI_Panel *vista = new GLUI_Rollout(glui, "Modos de vista", true);
    GLUI_RadioGroup *radioVista = new GLUI_RadioGroup(vista, &aVista, MODO_VISTA_ID, controlCallback);
    glui->add_radiobutton_to_group(radioVista, "Clasico");
    glui->add_radiobutton_to_group(radioVista, "Aristas");
    glui->add_radiobutton_to_group(radioVista, "Puntos");

    GLUI_Panel *camara = new GLUI_Rollout(glui, "Modos de camara", true);
    GLUI_RadioGroup *radioCamara = new GLUI_RadioGroup(camara, &aCamara, MODO_CAMARA_ID, controlCallback);
    glui->add_radiobutton_to_group(radioCamara, "Clasico");
    glui->add_radiobutton_to_group(radioCamara, "Aereo");
    glui->add_radiobutton_to_group(radioCamara, "Seguimiento");


    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Antihorario", &escena.sentido, 1, controlCallback );
    //new GLUI_Checkbox( obj_panel, "Proyecci�n paralela (on) o perspectiva (off)", &escena.perspectiva, 1, controlCallback );

    /******** A�ade controles para las luces ********/

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);


    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );


    /*** Disable/Enable botones ***/
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // A�ade una separaci�nglutSetWindow(window_id);
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2012-2020 (C) Juan Antonio Puchol  " );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.view_position[2] );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 1.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id());
            break;
        }
        case MODO_VISTA_ID: {
            escena.wireframe = aVista;
            glutSetWindow(glui->get_glut_window_id());
            break;
        }
        case MODO_CAMARA_ID: {
            escena.camara = aCamara;
            glutSetWindow(glui->get_glut_window_id());
            break;
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)
        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    escena.xy_aspect = (float)tw / (float)th;
    escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    if(button_state == 0) escena.Pick3D(x, y);
}

