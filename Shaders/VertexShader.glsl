
attribute vec4 a_Position;	        // in: Posición de cada vértice
attribute vec3 a_Normal;	        // in: Normal de cada vértice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (cámara)
uniform vec4 u_Color;		        // in: Color del objeto
uniform int  u_Luz0;                // in: Indica si la luz 0 está encedida
uniform int  u_Luz1;
//uniform int  u_Luz2;
uniform vec4 u_Pos0;
uniform vec4 u_Pos1;
//uniform vec4 u_Pos2;
uniform float u_Int0;
uniform float u_Int1;
//uniform float u_Int2;


varying vec4 v_Color;		        // out: Color al fragment shader

void main()
{
    vec4 LightPos0 = u_VMatrix*u_Pos0;
    vec4 LightPos1 = u_VMatrix*u_Pos1;
    //vec4 LightPos2 = u_VMatrix*u_Pos2;

    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posición del vértice
	vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del vértice

	float d0 = length(LightPos0.xyz - P);
	float d1 = length(LightPos1.xyz - P);
	//float d2 = length(LightPos2.xyz - P);
	vec3  L0 = normalize(LightPos0.xyz - P);
	vec3  L1 = normalize(LightPos1.xyz - P);
	//vec3  L2 = normalize(LightPos2.xyz - P);
	vec3 viewVec = normalize(vec3(-P)); // para la especular.

	float ambient = 0.15;                               // (15% de int. ambiente)
	float diffuse = 0.0;
	float resultado = 0.0;
	float specular = 0.0;

	if (u_Luz0>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L0), 0.0);		            // Cálculo de la int. difusa
        // Cálculo de la atenuación
        float attenuation = 80.0/(0.25+(0.01*d0)+(0.003*d0*d0));
        vec3 reflectVec = reflect(-L0, N);
        specular = clamp(dot(reflectVec, viewVec),0.0, 1.0);
        specular = pow(specular, 5.0);
        specular = specular*u_Int0;
        resultado += diffuse*attenuation*u_Int0 + specular;
	}
	if (u_Luz1>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L1), 0.0);		            // Cálculo de la int. difusa
        // Cálculo de la atenuación
        float attenuation = 80.0/(0.25+(0.01*d1)+(0.003*d1*d1));
        vec3 reflectVec = reflect(-L1, N);
        specular = clamp(dot(reflectVec, viewVec),0.0, 1.0);
        specular = pow(specular, 5.0);
        specular = specular*u_Int1;
        resultado += diffuse*attenuation*u_Int1+ specular;
	}

	v_Color = u_Color * (ambient + resultado);
	gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
