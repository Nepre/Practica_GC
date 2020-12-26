
precision mediump float;	// Precisión media

varying vec4 v_Color;		// in: color del vertex shader
varying vec2 v_TextureCoord; // in: coordenada del vertex shader

uniform sampler2D u_Sampler;

void main()
{
    		gl_FragColor = texture2D(u_Sampler, v_TextureCoord);
    		//gl_FragColor = v_Color;
}
