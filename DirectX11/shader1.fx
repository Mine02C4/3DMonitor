cbuffer ConstantBuffer: register(b0) {
	matrix world;
	matrix view;
	matrix projection;
}

cbuffer DisplayParameter: register(b1) {
  float pixel_width;
  float pixel_height;
  float screen_width;
  float screen_height;
  float lens_width;
  float lens_slope;
  float pixel_side_length;
  float calibration;
}

struct VS_OUTPUT {
  float4 pos:   SV_POSITION;
  float4 color: COLOR0;
};

struct FinalStruct {
  float4 pos    :SV_POSITION;
  float4 color  :COLOR0;
  float2 tex    :TEXCOORD0;
};

Texture2DArray texture0: register(t0);
SamplerState sampler0: register(s0);

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT NormalVs(float4 pos: POSITION, float4 color: COLOR) {
  VS_OUTPUT output = (VS_OUTPUT)0;
  output.pos = mul(pos, world);
  output.pos = mul(output.pos, view);
  output.pos = mul(output.pos, projection);
  output.color = color;
  return output;
}

FinalStruct FinalVs(float4 pos: POSITION, float4 color: COLOR, float2 tex:TEXCOORD0) {//
  FinalStruct output = (FinalStruct)0;
  output.pos = mul(pos, world);
  output.pos = mul(output.pos, view);
  output.pos = mul(output.pos, projection);
  output.color = color;
  output.tex = tex;
  return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 NormalPs(VS_OUTPUT input): SV_Target {
  return input.color;
}

float4 FILL_PS(VS_OUTPUT input): SV_Target {
  float4 color = {0.0f, 0.0f, 0.0f, 1.0f};
  return color;
}

float4 FinalPs(FinalStruct input): SV_Target {
  float horizontal_lens_width = lens_width / cos(lens_slope);
  float number_of_parallaxes = pixel_width * pixel_height;
  float calibration_width = calibration * horizontal_lens_width;
  float2 physical_coordinates;
  physical_coordinates.x = pixel_side_length * screen_width * input.tex.x;
  physical_coordinates.y = pixel_side_length * screen_height * input.tex.y;
  float3 horizontal_position;
  horizontal_position.r = (physical_coordinates.x - calibration_width - pixel_side_length / 3.0f) % horizontal_lens_width / horizontal_lens_width;
  horizontal_position.g = (physical_coordinates.x - calibration_width) % horizontal_lens_width / horizontal_lens_width;
  horizontal_position.b = (physical_coordinates.x - calibration_width + pixel_side_length / 3.0f) % horizontal_lens_width / horizontal_lens_width;
  uint3 parallax_index;
  parallax_index.r = asuint(horizontal_position.r * number_of_parallaxes);
  parallax_index.g = asuint(horizontal_position.g * number_of_parallaxes);
  parallax_index.b = asuint(horizontal_position.b * number_of_parallaxes);
  float2 three_dimensional_pixel_position;
  three_dimensional_pixel_position.x = trunc(physical_coordinates.x / horizontal_lens_width);
  three_dimensional_pixel_position.y = trunc(physical_coordinates.y / (pixel_height * pixel_side_length));
  float2 center_physical_coordinates_of_three_dimensional_pixel;
  center_physical_coordinates_of_three_dimensional_pixel.x = (three_dimensional_pixel_position.x + 0.5f) * horizontal_lens_width;
  center_physical_coordinates_of_three_dimensional_pixel.y = (three_dimensional_pixel_position.y + 0.5f) * pixel_height * pixel_side_length;
  float2 center_texture_coordinates_of_three_dimensional_pixel;
  center_texture_coordinates_of_three_dimensional_pixel.x = center_physical_coordinates_of_three_dimensional_pixel.x / (pixel_side_length * screen_width);
  center_texture_coordinates_of_three_dimensional_pixel.y = center_physical_coordinates_of_three_dimensional_pixel.y / (pixel_side_length * screen_height);
  float3x3 texs;
  texs[0] = float3(center_texture_coordinates_of_three_dimensional_pixel, parallax_index.r);
  texs[1] = float3(center_texture_coordinates_of_three_dimensional_pixel, parallax_index.g);
  texs[2] = float3(center_texture_coordinates_of_three_dimensional_pixel, parallax_index.b);
  //texs[0] = float3(input.tex, parallax_index.r);
  //texs[1] = float3(input.tex, 0);
  //texs[2] = float3(input.tex, 0);
  float4x4 colors;
  colors[0] = texture0.Sample(sampler0, texs[0]);
  colors[1] = texture0.Sample(sampler0, texs[1]);
  colors[2] = texture0.Sample(sampler0, texs[2]);
  if (parallax_index.r < 36.0f) {
    colors[0].r = 0.0f;
  }
  return float4(colors._m00, colors._m11, colors._m22, 1.0f);
  //return texture0.sample[0][input.tex];
  //return input.color;
}