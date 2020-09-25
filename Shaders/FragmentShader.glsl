
precision mediump float;	// Precisión media

varying vec4 v_Color;		// in: color del vertex shader

void main()
{
    		gl_FragColor = v_Color;
}
