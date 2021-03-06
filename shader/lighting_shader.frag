#version 330

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_shading_language_include : require

#include "position_restore.glsl"
#include "lighting.glsl"
#include "reflection.glsl"


uniform vec3 cam_pos_uni;

uniform sampler2D depth_tex_uni;
uniform sampler2D base_color_tex_uni;
uniform sampler2D normal_tex_uni;
uniform sampler2D metallic_roughness_tex_uni;
uniform sampler2D emission_tex_uni;

uniform bool ssao_enabled_uni;
uniform sampler2D ssao_tex_uni;

in vec2 uv_coord_var;

out vec4 color_out;

// ambient

uniform vec3 light_ambient_color_uni;

// point lights

#pragma define_param(MAX_POINT_LIGHTS_COUNT max_point_lights_count)

struct PointLight
{
	float dist;
	int shadow_enabled;
	vec3 pos;
	vec3 color;
	samplerCube shadow_map;
};


layout(std140) uniform PointLightBlock
{	
	int count;
	PointLight light[MAX_POINT_LIGHTS_COUNT];
} point_light_uni;






void main(void)
{	
	float depth = texture(depth_tex_uni, uv_coord_var).x;
	
	if(depth == 1.0)
		discard;

	vec3 base_color = texture(base_color_tex_uni, uv_coord_var).rgb;
	vec3 position = CalculateWorldPosition(depth, uv_coord_var);
	vec3 normal = normalize(texture(normal_tex_uni, uv_coord_var).rgb * 2.0 - vec3(1.0));

	vec3 metal_rough_reflect = texture(metallic_roughness_tex_uni, uv_coord_var).rgb;
	float metallic = metal_rough_reflect.r;
	float roughness = metal_rough_reflect.g;
	float reflectance = metal_rough_reflect.b;
		
	vec3 cam_dir = normalize(cam_pos_uni - position.xyz);
	
	
	
	// ambient lighting, ssao and emission
	
	vec3 color = vec3(0.0);

	color += base_color.rgb * light_ambient_color_uni;
	
	if(ssao_enabled_uni)
	{
		float occlusion = texture(ssao_tex_uni, uv_coord_var).r;
		color *= occlusion;
	}
	
	vec3 emission = texture(emission_tex_uni, uv_coord_var).rgb;
	color += emission;


	// reflection

	color += GetReflectionColor(reflectance, roughness, normal, cam_dir) * metallic;
	
	
	// point lighting
	
	for(int i=0; i<point_light_uni.count; i++)
	{
		color += PointLightLighting(position.xyz,
									base_color.rgb,
									metallic,
									roughness,
									1.0 - reflectance,
									cam_dir,
									normal,
									point_light_uni.light[i].pos,
									point_light_uni.light[i].dist,
									point_light_uni.light[i].color,
									point_light_uni.light[i].shadow_enabled != 0,
									point_light_uni.light[i].shadow_map);
	}

	
	color_out = vec4(color, 1.0);
}
