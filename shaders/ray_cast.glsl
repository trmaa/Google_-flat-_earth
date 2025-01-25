#version 330

#define FAR 1

uniform vec2 resolution;
uniform sampler2D texture;
uniform vec2 camera_angle;

struct Ray {
    vec3 origin;
    vec3 direction;
};

Ray create_ray(vec2 camera_angle, vec2 ray_id) {
    camera_angle.x += 3.14159 / 2.0;

    vec3 camera_space_direction = normalize(vec3(ray_id.x, ray_id.y, -FAR));

    float cos_pitch = cos(camera_angle.y);
    float sin_pitch = sin(camera_angle.y);
    float cos_yaw = cos(-camera_angle.x);
    float sin_yaw = sin(-camera_angle.x);

    mat3 R_x = mat3(
        1, 0, 0,
        0, cos_pitch, -sin_pitch,
        0, sin_pitch, cos_pitch
    );

    mat3 R_y = mat3(
        cos_yaw, 0, sin_yaw,
        0, 1, 0,
        -sin_yaw, 0, cos_yaw
    );

    mat3 R = R_y * R_x;

    vec3 ray_origin = R * vec3(0, 0, FAR * 1.7);

    vec3 ray_direction = normalize(R * camera_space_direction);

    Ray ray;
    ray.origin = ray_origin;
    ray.direction = ray_direction;

    return ray;
}

vec3 ray_at(Ray ray, float t) {
    return ray.origin + t * ray.direction;
}

float check_collision(Ray ray) {
    float radius = FAR;  

    vec3 oc = ray.origin;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return -1.0;  
    } else {
        float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        return (t1 > 0.0) ? t1 : t2;
    }
}

vec3 color_at(vec3 normal) {
    float theta = acos(-normal.y);
    float phi = atan(normal.z, normal.x);

    float u = (phi + 3.14159) / (2.0 * 3.14159);
    float v = theta / 3.14159;

    vec3 color = texture2D(texture, vec2(u, v)).rgb;
    return color;
}

void main() {
    vec2 uv = (gl_FragCoord.xy / resolution) * 2.0 - 1.0;
    uv.y *= -1.0;
    uv.x *= -resolution.x / resolution.y;

    Ray ray = create_ray(camera_angle, uv);

    float t = check_collision(ray);
    vec3 color;
    if (t < 0.0) {
        color = vec3(0.0); 
    } else {
        vec3 hit_point = ray_at(ray, t);  
        vec3 normal = normalize(hit_point);  
        color = color_at(normal);  
    }

    gl_FragColor = vec4(color, 1.0);
}
