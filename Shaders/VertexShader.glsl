
attribute vec4 a_Position;	        // in: Posici�n de cada v�rtice
attribute vec3 a_Normal;	        // in: Normal de cada v�rtice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (c�mara)
uniform vec4 u_Color;		        // in: Color del objeto
uniform int  u_Luz0;                // in: Indica si la luz 0 est� encedida
uniform int  u_Luz1;
//uniform int  u_Luz2;
uniform vec4 u_Pos0;
uniform vec4 u_Pos1;
//uniform vec4 u_Pos2;
uniform float u_Int0;
uniform float u_Int1;
//uniform float u_Int2;

uniform int u_Render_Pick3D;


varying vec4 v_Color;		        // out: Color al fragment shader

void main()
{
    if(u_Render_Pick3D == 0){
        vec4 LightPos0 = u_VMatrix*u_Pos0;
        vec4 LightPos1 = u_VMatrix*u_Pos1;
        //vec4 LightPos2 = u_VMatrix*u_Pos2;

        vec3 P = vec3(u_MVMatrix * a_Position);	            // Posici�n del v�rtice
        vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del v�rtice

        float d0 = length(LightPos0.xyz - P);
        float d1 = length(LightPos1.xyz - P);
        //float d2 = length(LightPos2.xyz - P);
        vec3  L0 = normalize(LightPos0.xyz - P);
        vec3  L1 = normalize(LightPos1.xyz - P);
        //vec3  L2 = normalize(LightPos2.xyz - P);
        vec4 coordenadas = vec4(P.x, P.y, P.z, 1.0);
        vec4 matrizVista = (u_VMatrix[3][0], u_VMatrix[3][1], u_VMatrix[3][2], u_VMatrix[3][0]);
        vec3 viewVec = normalize(vec3(u_VMatrix * matrizVista * (vec4(0.0, 0.0, 0.0, 1.0) - coordenadas))); // para la especular.

        float ambient = 0.15;                               // (15% de int. ambiente)
        float diffuse = 0.5;
        float resultado = 0.0;
        float specular = 0.0;
        int especularidad = 30;

        if (u_Luz0>0) {                                     // Si la luz 0 est� encendida se calcula la intesidad difusa de L
            diffuse = max(dot(N, L0), 0.0);		            // C�lculo de la int. difusa
            // C�lculo de la atenuaci�n
            float attenuation = 80.0/(0.25+(0.01*d0)+(0.003*d0*d0));
            // vec3 reflectVec = reflect(-L0, N);
            specular = 2 * attenuation * pow(max(0.0, dot(reflect(-L0, N), viewVec)), especularidad);
            resultado += diffuse*attenuation*u_Int0 + specular;
        }
        if (u_Luz1>0) {                                     // Si la luz 1 est� encendida se calcula la intesidad difusa de L
            diffuse = max(dot(N, L1), 0.0);		            // C�lculo de la int. difusa
            // C�lculo de la atenuaci�n
            float attenuation = 80.0/(0.25+(0.01*d1)+(0.003*d1*d1));
            // vec3 reflectVec = reflect(-L1, N);
            specular = 2 * attenuation * pow(max(0.0, dot(reflect(-L0, N), viewVec)), especularidad);
            resultado += diffuse*attenuation*u_Int1+ specular;
        }

        v_Color = u_Color * (ambient + resultado);
        gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
    }
    else{
        vec3 P = vec3(u_MVMatrix * a_Position);	            // Posicion del vertice
        v_Color = vec4(u_Color.x, u_Color.x, u_Color.x, 0);
        gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
    }
}
