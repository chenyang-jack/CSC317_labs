// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  vec2 rand = random2(seed);

  float ro = 2 * M_PI * rand.x;
  float theta = 2 * M_PI * rand.y;

  return normalize(vec3(sin(theta) * cos(ro), sin(theta) * sin(ro), cos(theta)));
  /////////////////////////////////////////////////////////////////////////////
}
