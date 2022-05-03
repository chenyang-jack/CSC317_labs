// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s )
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float noisConst = 1;
  float heightConst = 1;
  
  if(is_moon){
    noisConst = 9;
    heightConst = 2;
  }
  else{
    noisConst = 2.3;
    heightConst = 3;
  }

  float noise = heightConst * improved_perlin_noise(noisConst * s) / 5;

  return noise;
  /////////////////////////////////////////////////////////////////////////////
}
