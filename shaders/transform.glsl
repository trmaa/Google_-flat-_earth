#version 330

uniform vec2 resolution;      
uniform sampler2D texture;    
uniform vec2 camera_angle;         
uniform float FAR;

vec2 uv_to_sphere(vec2 uv) {
	float lon = (uv.x - 0.5) * 2.0 * 3.14159265359;
	float lat = (uv.y - 0.5) * 3.14159265359;       
	return vec2(lon, lat);
}

vec2 rotate_sphere(vec2 sphere_angular_coords, vec2 camera_angle) {
	float lon = sphere_angular_coords.x - camera_angle.x;
	float lat = sphere_angular_coords.y;

	float cos_lat = cos(lat);
	float sin_lat = sin(lat);
	float cos_cam_lat = cos(camera_angle.y);
	float sin_cam_lat = sin(camera_angle.y);

	lat = asin(sin_lat * cos_cam_lat + cos_lat * sin_cam_lat * cos(lon));
	lon = atan(sin(lon) * cos_cam_lat, cos(lon) * cos_cam_lat - sin_lat * sin_cam_lat / cos_lat);

	return vec2(lon, lat);
}

vec2 sphere_to_uv(vec2 sphere_angular_coords) {
	float u = (sphere_angular_coords.x / (2.0 * 3.14159265359)) + 0.5;
	float v = (sphere_angular_coords.y / 3.14159265359) + 0.5;         
	return vec2(u, v);
}

void main() {
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	uv.y = 1.0 - uv.y;

	vec2 zoom_center = vec2(0.5, 0.5);
	uv = zoom_center + (uv - zoom_center) / FAR;

	vec2 sphere_angular_coords = uv_to_sphere(uv);
	sphere_angular_coords = rotate_sphere(sphere_angular_coords, camera_angle);
	vec2 texture_uv = sphere_to_uv(sphere_angular_coords);

	gl_FragColor = vec4(texture2D(texture, texture_uv).rgb, 1.0); //if alfa is not froced to 1 there is not support for png
}
