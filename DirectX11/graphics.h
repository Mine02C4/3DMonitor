#ifndef TDMONITOR_DIRECTX_GRAPHICS_H_
#define TDMONITOR_DIRECTX_GRAPHICS_H_

#include "DDSTextureLoader.h"

#define kPixelWidth         6
#define kPixelHeight        6
#define kNumberOfParallaxes (kPixelWidth * kPixelHeight)

//--------------------------------------------------------------------------------------
// ç\ë¢ëÃ
//--------------------------------------------------------------------------------------
struct SimpleVertex {
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT4 color;
};

struct Vertex {
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT4 color;
  DirectX::XMFLOAT2 tex;
};

struct ConstantBuffer {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

struct DisplayParameter {
  float pixel_width;
  float pixel_height;
  float screen_width;
  float screen_height;
  float lens_width;
  float lens_slope;
  float pixel_side_length;
  float calibration;
};

class Graphics {
private:
  ID3D11Device              *p_d3d_device_;
  ID3D11DeviceContext       *p_immediate_context_;
  IDXGISwapChain            *p_swap_chain_;
  ID3D11RenderTargetView    *p_render_target_view_;
  ID3D11VertexShader        *p_vertex_shader_;
  ID3D11VertexShader        *p_final_vertex_shader_;
  ID3D11PixelShader         *p_pixel_shader_;
  ID3D11PixelShader         *p_fill_pixel_shader_;
  ID3D11PixelShader         *p_final_pixel_shader_;
  ID3D11InputLayout         *p_vertex_layout_;
  ID3D11InputLayout         *p_final_vertex_layout_;
  ID3D11Buffer              *p_vertex_buffer_;
  ID3D11Buffer              *p_index_buffer_;
  ID3D11Buffer              *p_constant_buffer_;
  ID3D11Buffer              *p_fixed_vertex_buffer_;
  ID3D11Buffer              *p_fixed_index_buffer_;
  ID3D11Buffer              *p_display_parameter_;
  ID3D11SamplerState        *p_sampler_state_;
  ID3D11Texture2D           *p_parallax_textures_[kNumberOfParallaxes];
  ID3D11RenderTargetView    *p_parallax_targets_[kNumberOfParallaxes];
  ID3D11ShaderResourceView  *p_parallax_resources_[kNumberOfParallaxes];
  ID3D11Texture2D           *p_parallax_texture_array_;
  ID3D11RenderTargetView    *p_parallax_target_array_;
  ID3D11ShaderResourceView  *p_parallax_resource_array_;
  DirectX::XMFLOAT4X4     world_;
  DirectX::XMFLOAT4X4     view_;
  DirectX::XMFLOAT4X4     projection_;
  DirectX::XMFLOAT4X4     fixed_world_;
  DirectX::XMFLOAT4X4     fixed_view_;
  DirectX::XMFLOAT4X4     fixed_projection_;
  static HRESULT CompileShaderFromFile(WCHAR*, LPCSTR, LPCSTR, ID3DBlob**);
  HRESULT InitD3DDevice(HWND);
  HRESULT CompileShaders();
  HRESULT SetupPolygons();
  HRESULT CreateConstantBuffers();
  HRESULT CreateParallaxes(UINT, UINT, DXGI_SAMPLE_DESC);
  DisplayParameter          display_parameter_;
  // âº
  ID3D11Texture2D           *p_depth_stencil_;
  ID3D11DepthStencilView    *p_depth_stencil_view_;
  ID3D11ShaderResourceView  *p_texture_;
public:
  Graphics();
  ~Graphics();
  HRESULT Init(HWND);
  void Render();
};

#endif