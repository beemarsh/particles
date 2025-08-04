#version 130

uniform vec2 center;
uniform float radius;
uniform vec4 baseColor;

void main() {
    // For a soft, fluid look, an exponent of 2.0 or 3.0 is ideal.
    // It creates a sharp peak of light with a very fast falloff,
    // which is perfect for blending.
    const float GLOW_EXPONENT = 1.1;

    // Calculate distance and normalize it
    vec2 screen_pos = gl_FragCoord.xy;
    float distance = distance(screen_pos, center);
    float normalized_distance = min(distance / radius, 1.0);

    // Calculate alpha (1.0 at center -> 0.0 at edge)
    float alpha = 1.0 - normalized_distance;

    // Apply the exponent to create the soft-core falloff
    alpha = pow(alpha, GLOW_EXPONENT);

    // Set the final color
    gl_FragColor = vec4(baseColor.rgb, baseColor.a * alpha);
}
