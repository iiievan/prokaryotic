#version 430 core

in vec2 uv;
out vec4 FragColor;

layout(std430, binding = 2) buffer stringData {
     float string[];
};

uniform sampler2D font_texture;

float sdBox( vec2 p, vec2 b ) {
  vec2 d = abs(p) - b;
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float getChar(vec2 uv, float id) {
	int i = int(id);
	vec2 coord = vec2(i % 16, i / 16) / 16.0;
	coord = coord + uv / 16.0;
	float d = length(max(abs(uv-vec2(0.5))-vec2(0.5),0.0));
	return (d > 0.0)? d + 0.5 : texture(font_texture, coord).r - 0.5;
}

uniform int string_count;
uniform float char_size;
uniform float aspect_ratio;
uniform float box_aspect_ratio;
uniform float slider_val;
uniform int side;
uniform vec3 text_col;
uniform vec3 active_col;
uniform vec3 background_col;
uniform float alpha_val;

void main() {
	// set up variables
	float invCharSize = 1.0 / char_size;
	float stringSize = char_size*float(string_count);
	float s = uv.x;
	if(side == 1)
		s = uv.x - (1.0 - stringSize)*0.5;
	else if(side == 2)
		s = uv.x - (1.0 - stringSize);

	// set up boarder
	float bw = 0.01;
	vec2 boarder = vec2(1.0 - bw, 1.0 - bw*box_aspect_ratio);

	// calc char coords
	float charHeight = (1.0 / (box_aspect_ratio*char_size)) * aspect_ratio;
	vec2 p = vec2(mod(s, char_size)*invCharSize, uv.y*charHeight - charHeight*0.5 + 0.5);
	p = p*0.5 + 0.25;

	// calc string index
	int index = int(s*invCharSize);
	if(s < 0.0 || s > stringSize)index = -1;

	// calc SDF
	float t = 1.0;
	if(index != -1)t = getChar(p, string[index]);


	//calc color
	vec3 col = vec3(0.0);
	float sv = (uv.x < slider_val)? 1.0 : 0.0;
	col = active_col*sv;

	float val = smoothstep(0.01,0.0,t);    
    col = mix(col, text_col, val);

	if(sdBox(uv - vec2(0.5), boarder*0.5) > 0.0)col = background_col;

	//if(uv.y > 0.49 && uv.y < 0.51)col = vec3(1.0,0.0,0.0);

	FragColor = vec4(col, alpha_val);
}