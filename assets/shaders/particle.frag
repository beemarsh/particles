#version 130

uniform vec2 center;    // The absolute screen coordinate of the circle's center
uniform float radius;
uniform vec4 baseColor;

void main() {
    // Get the absolute screen coordinate of the current pixel
    vec2 screen_pos = gl_FragCoord.xy;
    
    // Calculate the distance from this pixel to the circle's true center
    float distance = distance(screen_pos, center);

    // Create the fade effect based on the distance
    float normalized_distance = min(distance / radius, 1.0);
    float alpha = 1.0 - normalized_distance;

    // Set the final pixel color
    gl_FragColor = vec4(baseColor.rgb, baseColor.a * alpha);
}
