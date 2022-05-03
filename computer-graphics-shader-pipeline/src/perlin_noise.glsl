// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  
  // Unique grid cell 
  int x0 = int(floor(st.x));
  int y0 = int(floor(st.y));
  int z0 = int(floor(st.z));
  int x1 = x0 + 1;
  int y1 = y0 + 1;
  int z1 = z0 + 1;
  
  vec3 corners[8];
  corners[0] = vec3(x0, y0, z0);
  corners[1] = vec3(x1, y0, z0);
  corners[2] = vec3(x0, y1, z0);
  corners[3] = vec3(x1, y1, z0);
  corners[4] = vec3(x0, y0, z1);
  corners[5] = vec3(x1, y0, z1);
  corners[6] = vec3(x0, y1, z1);
  corners[7] = vec3(x1, y1, z1);

  // dot result between gradient and offset
  // offset: displace vec from given point to corner
  float dot_grads_offsets[8];
  for(int i=0; i < 8; i++){
    dot_grads_offsets[i] = dot(random_direction(corners[i]), (corners[i] - st));
  }

  
  // Interpolate with smooth_step

  // Determine interpolation weights
  // Could also use higher order polynomial/s-curve here
  vec3 seed = st - corners[0];
  vec3 weight = smooth_step(seed);

  float interpX1 = dot_grads_offsets[0] + weight.x * (dot_grads_offsets[1] - dot_grads_offsets[0]);
  float interpX2 = dot_grads_offsets[2] + weight.x * (dot_grads_offsets[3] - dot_grads_offsets[2]);
  float interpX3 = dot_grads_offsets[4] + weight.x * (dot_grads_offsets[5] - dot_grads_offsets[4]);
  float interpX4 = dot_grads_offsets[6] + weight.x * (dot_grads_offsets[7] - dot_grads_offsets[6]);

  float interpY1 = interpX1 + weight.y * (interpX2 - interpX1);
  float interpY2 = interpX3 + weight.y * (interpX4 - interpX3);

  float interpZ = interpY1 + weight.z * (interpY2 - interpY1);
  return interpZ;
  /////////////////////////////////////////////////////////////////////////////
}

