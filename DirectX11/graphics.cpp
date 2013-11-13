#include "stdafx.h"
#include "graphics.h"

D3D_DRIVER_TYPE         g_driverType    = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel  = D3D_FEATURE_LEVEL_11_0;

Graphics::Graphics() {
  p_d3d_device_           = NULL;
  p_immediate_context_    = NULL;
  p_swap_chain_           = NULL;
  p_render_target_view_   = NULL;
  p_vertex_shader_        = NULL;
  p_final_vertex_shader_  = NULL;
  p_pixel_shader_         = NULL;
  p_fill_pixel_shader_    = NULL;
  p_final_pixel_shader_   = NULL;
  p_vertex_layout_        = NULL;
  p_final_vertex_layout_  = NULL;
  p_vertex_buffer_        = NULL;
  p_index_buffer_         = NULL;
  p_constant_buffer_      = NULL;
  p_fixed_vertex_buffer_  = NULL;
  p_fixed_index_buffer_   = NULL;
  p_display_parameter_    = NULL;
  p_sampler_state_        = NULL;
  for (int i = 0; i < kNumberOfParallaxes; i++) {
    p_parallax_textures_[i]   = NULL;
    p_parallax_targets_[i]    = NULL;
    p_parallax_resources_[i]  = NULL;
  }

  p_depth_stencil_      = NULL;
  p_depth_stencil_view_ = NULL;
  p_texture_            = NULL;
}

//--------------------------------------------------------------------------------------
// クリーンアップ
//--------------------------------------------------------------------------------------
Graphics::~Graphics() {
  if (p_immediate_context_)   p_immediate_context_->ClearState();
 
  if (p_constant_buffer_)     p_constant_buffer_->Release();
  if (p_vertex_buffer_)       p_vertex_buffer_->Release();
  if (p_index_buffer_)        p_index_buffer_->Release();
  if (p_fixed_vertex_buffer_) p_fixed_vertex_buffer_->Release();
  if (p_fixed_index_buffer_)  p_fixed_index_buffer_->Release();
  if (p_display_parameter_)   p_display_parameter_->Release();
  if (p_vertex_layout_)       p_vertex_layout_->Release();
  if (p_final_vertex_layout_) p_final_vertex_layout_->Release();
  if (p_vertex_shader_)       p_vertex_shader_->Release();
  if (p_final_vertex_shader_) p_final_vertex_shader_->Release();
  if (p_pixel_shader_)        p_pixel_shader_->Release();
  if (p_fill_pixel_shader_)   p_fill_pixel_shader_->Release();
  if (p_final_pixel_shader_)  p_final_pixel_shader_->Release();
  if (p_render_target_view_)  p_render_target_view_->Release();
  if (p_swap_chain_)          p_swap_chain_->Release();
  if (p_immediate_context_)   p_immediate_context_->Release();
  if (p_d3d_device_)          p_d3d_device_->Release();
  if (p_sampler_state_)       p_sampler_state_->Release();
  for (int i = 0; i < kNumberOfParallaxes; i++) {
    if (p_parallax_textures_[i])  p_parallax_textures_[i]->Release();
    if (p_parallax_targets_[i])   p_parallax_targets_[i]->Release();
    if (p_parallax_resources_[i]) p_parallax_resources_[i]->Release();
  }

  if (p_depth_stencil_)       p_depth_stencil_->Release();
  if (p_depth_stencil_view_)  p_depth_stencil_view_->Release();
  if (p_texture_)             p_texture_->Release();
}

HRESULT Graphics::Init(HWND h_wnd) {
  HRESULT hr;
  if (FAILED(hr = InitD3DDevice(h_wnd))) {
    return hr;
  }
  return S_OK;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT Graphics::InitD3DDevice(HWND h_wnd) {
  HRESULT hr = S_OK;

  RECT rc;
  GetClientRect(h_wnd, &rc);
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG/*|D3D11_CREATE_DEVICE_SWITCH_TO_REF*/;
#endif

  D3D_DRIVER_TYPE driverTypes[] = {
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
    g_driverType = driverTypes[driverTypeIndex];
    hr = D3D11CreateDevice(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &p_d3d_device_, &g_featureLevel, &p_immediate_context_);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    return hr;

  DXGI_SAMPLE_DESC sample_desc;
#ifdef MSAA
	for (int i=0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++) {
		UINT Quality;
    if (SUCCEEDED(p_d3d_device_->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality))) {
			if (0 < Quality) {
				sample_desc.Count = i;
				sample_desc.Quality = Quality - 1;
			}
		}
	}
#else
  sample_desc.Count   = 1;
  sample_desc.Quality = 0;
#endif

  DXGI_SWAP_CHAIN_DESC swap_chain_desc;
  ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
  swap_chain_desc.BufferCount = 2;
  swap_chain_desc.BufferDesc.Width = width;
  swap_chain_desc.BufferDesc.Height = height;
  swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
  swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
  swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swap_chain_desc.OutputWindow = h_wnd;
  swap_chain_desc.SampleDesc = sample_desc;
  swap_chain_desc.Windowed = TRUE;

  IDXGIDevice1 *hpDXGI = NULL;
  IDXGIAdapter *hpAdapter = NULL;
  IDXGIFactory *hpDXGIFactory = NULL;
  hr = p_d3d_device_->QueryInterface(__uuidof(IDXGIDevice1), (void**)&hpDXGI);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("QueryInterface"), _T("Error"), MB_OK);
    return hr;
  }
  hr = hpDXGI->GetAdapter(&hpAdapter);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("GetAdapter"), _T("Error"), MB_OK);
    return hr;
  }
  hpAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&hpDXGIFactory);
  if (hpDXGIFactory == NULL) {
    MessageBox(NULL, _T("GetParent"), _T("Error"), MB_OK);
    return E_FAIL;
  }
  hr = hpDXGIFactory->CreateSwapChain(p_d3d_device_, &swap_chain_desc, &p_swap_chain_);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("CreateSwapChain"), _T("Error"), MB_OK);
    return hr;
  }

  // レンダーターゲットビューの作成
  ID3D11Texture2D *pBackBuffer = NULL;
  hr = p_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
    return hr;

  hr = p_d3d_device_->CreateRenderTargetView(pBackBuffer, NULL, &p_render_target_view_);
  pBackBuffer->Release();
  if (FAILED(hr))
    return hr;

  // 深度ステンシルテクスチャの作成
  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory(&descDepth, sizeof(descDepth));
  descDepth.Width = width;
  descDepth.Height = height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  hr = p_d3d_device_->CreateTexture2D(&descDepth, NULL, &p_depth_stencil_);
  if (FAILED(hr))
    return hr;

  // 深度ステンシルビューの作成
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory(&descDSV, sizeof(descDSV));
  descDSV.Format = descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = p_d3d_device_->CreateDepthStencilView(p_depth_stencil_, &descDSV, &p_depth_stencil_view_);
  if (FAILED(hr))
    return hr;

  hr = CreateDDSTextureFromFile(p_d3d_device_, L"seafloor.dds", NULL, &p_texture_);
  if (FAILED(hr))
    return hr;

  // ビューポートの設定
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  p_immediate_context_->RSSetViewports(1, &vp);
  
  // ディスプレイの設定
  display_parameter_.pixel_width        = (float)kPixelWidth;
  display_parameter_.pixel_height       = (float)kPixelHeight;
  display_parameter_.screen_width       = (float)width;
  display_parameter_.screen_height      = (float)height;
  display_parameter_.lens_width         = 1.0f / 30.0f;
  display_parameter_.lens_slope         = (float)atan2(1.0, 6.0);
  display_parameter_.pixel_side_length  = 1.0f / 204.0f;
  display_parameter_.calibration        = 0.0f;

  // サンプラーステートの作成
  D3D11_SAMPLER_DESC sampler_desc;
  ZeroMemory(&sampler_desc, sizeof(sampler_desc));
  sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
  sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
  sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
  sampler_desc.MaxAnisotropy = 1;
  sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampler_desc.BorderColor[0] = 0.0f;
  sampler_desc.BorderColor[1] = 0.0f;
  sampler_desc.BorderColor[2] = 0.0f;
  sampler_desc.BorderColor[3] = 1.0f;
  sampler_desc.MinLOD = 0;
  sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
  p_d3d_device_->CreateSamplerState(&sampler_desc, &p_sampler_state_);

  if (FAILED(hr = CompileShaders())||FAILED(hr = SetupPolygons())||FAILED(hr = CreateConstantBuffers())||FAILED(hr = CreateParallaxes(width, height, sample_desc)))
    return hr;

  // ワールド行列の初期化
  DirectX::XMStoreFloat4x4(&world_, DirectX::XMMatrixIdentity());

  // ビュー行列の初期化
  DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
  DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMStoreFloat4x4(&view_, DirectX::XMMatrixLookAtLH(Eye, At, Up));

  // 射影行列の初期化
  DirectX::XMStoreFloat4x4(&projection_, DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f));

  // 最終ステージ用の行列
  DirectX::XMStoreFloat4x4(&fixed_world_, DirectX::XMMatrixIdentity());
  DirectX::XMStoreFloat4x4(&fixed_view_, DirectX::XMMatrixLookAtLH(Eye, At, Up));
  DirectX::XMStoreFloat4x4(&fixed_projection_, DirectX::XMMatrixOrthographicLH(2.0f, 2.0f, 0.01f, 100.0f));

  return S_OK;
}

// シェーダーをコンパイルします
HRESULT Graphics::CompileShaders() {
  HRESULT hr;

  // 通常ステージ用の頂点シェーダー
  ID3DBlob* p_blob = NULL;
  hr = CompileShaderFromFile(L"shader1.fx", "NormalVs", "vs_4_0", &p_blob);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file."), _T("Error"), MB_OK);
    return hr;
  }
  hr = p_d3d_device_->CreateVertexShader(p_blob->GetBufferPointer(), p_blob->GetBufferSize(), NULL, &p_vertex_shader_);
  if (FAILED(hr)) {	
    p_blob->Release();
    return hr;
  }
  D3D11_INPUT_ELEMENT_DESC layout[] = {
    {"POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,     0,  0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  12, D3D11_INPUT_PER_VERTEX_DATA, 0},
  };
  hr = p_d3d_device_->CreateInputLayout(layout, ARRAYSIZE(layout), p_blob->GetBufferPointer(), p_blob->GetBufferSize(), &p_vertex_layout_);
  p_blob->Release();
  if (FAILED(hr))
    return hr;

  // 最終ステージ用の頂点シェーダー
  hr = CompileShaderFromFile(L"shader1.fx", "FinalVs", "vs_4_0", &p_blob);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file."), _T("Error"), MB_OK);
    return hr;
  }
  hr = p_d3d_device_->CreateVertexShader(p_blob->GetBufferPointer(), p_blob->GetBufferSize(), NULL, &p_final_vertex_shader_);
  if (FAILED(hr)) {	
    p_blob->Release();
    return hr;
  }
  D3D11_INPUT_ELEMENT_DESC final_layout[] = {
    {"POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,     0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,        0, 28,  D3D11_INPUT_PER_VERTEX_DATA, 0},
  };
  hr = p_d3d_device_->CreateInputLayout(final_layout, ARRAYSIZE(final_layout), p_blob->GetBufferPointer(), p_blob->GetBufferSize(), &p_final_vertex_layout_);
  p_blob->Release();
  if (FAILED(hr))
    return hr;

  // ピクセルシェーダーをコンパイル
  hr = CompileShaderFromFile(L"shader1.fx", "NormalPs", "ps_4_0", &p_blob);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file."), _T("Error"), MB_OK);
    return hr;
  }
  hr = p_d3d_device_->CreatePixelShader(p_blob->GetBufferPointer(), p_blob->GetBufferSize(), NULL, &p_pixel_shader_);
  p_blob->Release();
  if (FAILED(hr))
    return hr;

  hr = CompileShaderFromFile(L"shader1.fx", "FILL_PS", "ps_4_0", &p_blob);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file."), _T("Error"), MB_OK);
    return hr;
  }
  hr = p_d3d_device_->CreatePixelShader(p_blob->GetBufferPointer(), p_blob->GetBufferSize(), NULL, &p_fill_pixel_shader_);
  p_blob->Release();
  if (FAILED(hr))
    return hr;

  hr = CompileShaderFromFile(L"shader1.fx", "FinalPs", "ps_4_0", &p_blob);
  if (FAILED(hr)) {
    MessageBox(NULL, _T("The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file."), _T("Error"), MB_OK);
    return hr;
  }
  hr = p_d3d_device_->CreatePixelShader(p_blob->GetBufferPointer(), p_blob->GetBufferSize(), NULL, &p_final_pixel_shader_);
  p_blob->Release();
  if (FAILED(hr))
    return hr;

  return S_OK;
}

// ポリゴンをセットアップします
HRESULT Graphics::SetupPolygons() {
  HRESULT hr;

  // Set primitive topology
  p_immediate_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // 頂点バッファーの作成
  SimpleVertex vertices[] = {
    {DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f),   DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    {DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f),    DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
    {DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f),     DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},
    {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),    DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
    {DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f),  DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
    {DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f),   DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)},
    {DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f),    DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
    {DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f),   DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)},
  };
  D3D11_BUFFER_DESC buffer_desc;
  ZeroMemory(&buffer_desc, sizeof(buffer_desc));
  buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  buffer_desc.ByteWidth = sizeof(vertices);
  buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory(&InitData, sizeof(InitData));
  InitData.pSysMem = vertices;
  hr = p_d3d_device_->CreateBuffer(&buffer_desc, &InitData, &p_vertex_buffer_);
  if (FAILED(hr))
    return hr;

  // Create index buffer
  WORD indices[] = {
    3,1,0,
    2,1,3,

    0,5,4,
    1,5,0,

    3,4,7,
    0,4,3,

    1,6,5,
    2,6,1,

    2,7,6,
    3,7,2,

    6,4,5,
    7,4,6,
  };
  buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  buffer_desc.ByteWidth = sizeof(indices);
  buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  InitData.pSysMem = indices;
  hr = p_d3d_device_->CreateBuffer(&buffer_desc, &InitData, &p_index_buffer_);
  if (FAILED(hr))
    return hr;

  // 最終ステージ用のポリゴンを初期化
  Vertex fixed_vertices[] = {
    {DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f),   DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},//
    {DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f),  DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},//
    {DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f),  DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},//
    {DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},//
  };
  buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  buffer_desc.ByteWidth = sizeof(fixed_vertices);
  buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  InitData.pSysMem = fixed_vertices;
  hr = p_d3d_device_->CreateBuffer(&buffer_desc, &InitData, &p_fixed_vertex_buffer_);
  if (FAILED(hr))
    return hr;
  WORD fixed_indices[] = {0, 2, 1, 1, 2, 3};
  buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  buffer_desc.ByteWidth = sizeof(fixed_indices);
  buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  InitData.pSysMem = fixed_indices;
  hr = p_d3d_device_->CreateBuffer(&buffer_desc, &InitData, &p_fixed_index_buffer_);
  if (FAILED(hr))
    return hr;

  return S_OK;
}

// 定数バッファーの作成
HRESULT Graphics::CreateConstantBuffers() {
  HRESULT hr;
  D3D11_BUFFER_DESC buffer_desc;
  ZeroMemory(&buffer_desc, sizeof(buffer_desc));
  buffer_desc.Usage = D3D11_USAGE_DEFAULT;
  buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  buffer_desc.CPUAccessFlags = 0;
  buffer_desc.ByteWidth = sizeof(ConstantBuffer);
  if (FAILED(hr = p_d3d_device_->CreateBuffer(&buffer_desc, NULL, &p_constant_buffer_)))
    return hr;
  buffer_desc.ByteWidth = sizeof(DisplayParameter);
  if (FAILED(hr = p_d3d_device_->CreateBuffer(&buffer_desc, NULL, &p_display_parameter_)))
    return hr;
  return S_OK;
}

// 視差の作成
HRESULT Graphics::CreateParallaxes(UINT width, UINT height, DXGI_SAMPLE_DESC sample_desc) {
  // 視差情報用のテクスチャとレンダーターゲットを作成
  D3D11_TEXTURE2D_DESC parallax_texture2d_desc;
  parallax_texture2d_desc.Width           = width;
  parallax_texture2d_desc.Height          = height;
  parallax_texture2d_desc.MipLevels       = 1;
  parallax_texture2d_desc.ArraySize       = 1;
  parallax_texture2d_desc.Format          = DXGI_FORMAT_R8G8B8A8_UNORM;
  parallax_texture2d_desc.SampleDesc      = sample_desc;
  parallax_texture2d_desc.Usage           = D3D11_USAGE_DEFAULT;
  parallax_texture2d_desc.BindFlags       = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
  parallax_texture2d_desc.CPUAccessFlags  = 0;
  parallax_texture2d_desc.MiscFlags       = 0;
  D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc;
  shader_resource_view_desc.Format        = parallax_texture2d_desc.Format;
  shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  shader_resource_view_desc.Texture2D.MostDetailedMip = 0;
  shader_resource_view_desc.Texture2D.MipLevels       = 1;
  for (int i = 0; i < kNumberOfParallaxes; i++) {
//    p_d3d_device_->CreateTexture2D(&parallax_texture2d_desc, NULL, &p_parallax_textures_[i]);
//    p_d3d_device_->CreateShaderResourceView(p_parallax_textures_[i], &shader_resource_view_desc, &p_parallax_resources_[i]);
//    p_d3d_device_->CreateRenderTargetView(p_parallax_textures_[i], NULL, &p_parallax_targets_[i]);
  }

  parallax_texture2d_desc.Width           = width;
  parallax_texture2d_desc.Height          = height;
  parallax_texture2d_desc.MipLevels       = 1;
  parallax_texture2d_desc.ArraySize       = kNumberOfParallaxes;
  parallax_texture2d_desc.Format          = DXGI_FORMAT_R8G8B8A8_UNORM;
  parallax_texture2d_desc.SampleDesc      = sample_desc;
  parallax_texture2d_desc.Usage           = D3D11_USAGE_DEFAULT;
  parallax_texture2d_desc.BindFlags       = D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
  parallax_texture2d_desc.CPUAccessFlags  = 0;
  parallax_texture2d_desc.MiscFlags       = 0;
  shader_resource_view_desc.Format        = parallax_texture2d_desc.Format;
  shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
  shader_resource_view_desc.Texture2DArray.MostDetailedMip  = 0;
  shader_resource_view_desc.Texture2DArray.MipLevels        = 1;
  shader_resource_view_desc.Texture2DArray.FirstArraySlice  = 0;
  shader_resource_view_desc.Texture2DArray.ArraySize        = kNumberOfParallaxes;
  D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
  render_target_view_desc.Format        = parallax_texture2d_desc.Format;
  render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
  render_target_view_desc.Texture2DArray.MipSlice         = 0;
  render_target_view_desc.Texture2DArray.ArraySize        = 1;
  p_d3d_device_->CreateTexture2D(&parallax_texture2d_desc, NULL, &p_parallax_texture_array_);
  p_d3d_device_->CreateShaderResourceView(p_parallax_texture_array_, &shader_resource_view_desc, &p_parallax_resource_array_);
  for (int i = 0; i < kNumberOfParallaxes; i++) {
    render_target_view_desc.Texture2DArray.FirstArraySlice  = i;
    p_d3d_device_->CreateRenderTargetView(p_parallax_texture_array_, &render_target_view_desc, &p_parallax_targets_[i]);
  }
  return S_OK;
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT Graphics::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {
  HRESULT hr = S_OK;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

  ID3DBlob* pErrorBlob;
  hr = D3DCompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
  if (FAILED(hr)) {
    if (pErrorBlob != NULL)
      OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
    if (pErrorBlob) pErrorBlob->Release();
    return hr;
  }
  if (pErrorBlob) pErrorBlob->Release();

  return S_OK;
}

//--------------------------------------------------------------------------------------
// レンダリング
//--------------------------------------------------------------------------------------
void Graphics::Render() {
  static float t = 0.0f;
  if (g_driverType == D3D_DRIVER_TYPE_REFERENCE) {
    t += (float)DirectX::XM_PI * 0.0125f;
  } else {
    static DWORD dwTimeStart = 0;
    DWORD dwTimeCur = GetTickCount64();
    if (dwTimeStart == 0)
      dwTimeStart = dwTimeCur;
    t = (dwTimeCur - dwTimeStart) / 1000.0f;
  }

  float clear_color[4] = {0.1f, 0.125f, 0.3f, 1.0f};
  UINT stride = sizeof(SimpleVertex);
  UINT offset = 0;
  // 頂点バッファーの設定
  p_immediate_context_->IASetVertexBuffers(0, 1, &p_vertex_buffer_, &stride, &offset);
  // インプットレイアウトの設定
  p_immediate_context_->IASetInputLayout(p_vertex_layout_);
  // インデックスバッファーの設定
  p_immediate_context_->IASetIndexBuffer(p_index_buffer_, DXGI_FORMAT_R16_UINT, 0);
  for (int i = 0; i < kNumberOfParallaxes; i++) {
    // 立方体を動かす
    DirectX::XMMATRIX world = DirectX::XMMatrixRotationY(t + i / 1.0f);
    // レンダーターゲットの設定
    p_immediate_context_->OMSetRenderTargets(1, &p_parallax_targets_[i], p_depth_stencil_view_);
    // テクスチャをクリア
    p_immediate_context_->ClearRenderTargetView(p_parallax_targets_[i], clear_color);
    p_immediate_context_->ClearDepthStencilView(p_depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);

    ConstantBuffer constant_buffer;
    constant_buffer.world = DirectX::XMMatrixTranspose(world);
    constant_buffer.view = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&view_));
    constant_buffer.projection = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&projection_));
    p_immediate_context_->UpdateSubresource(p_constant_buffer_, 0, NULL, &constant_buffer, 0, 0);

    p_immediate_context_->VSSetShader(p_vertex_shader_, NULL, 0);
    p_immediate_context_->VSSetConstantBuffers(0, 1, &p_constant_buffer_);
    p_immediate_context_->PSSetShader(p_pixel_shader_, NULL, 0);
    p_immediate_context_->DrawIndexed(36, 0, 0);
  }

  p_immediate_context_->OMSetRenderTargets(1, &p_render_target_view_, NULL);

  stride = sizeof(Vertex);
  p_immediate_context_->IASetVertexBuffers(0, 1, &p_fixed_vertex_buffer_, &stride, &offset);
  p_immediate_context_->IASetIndexBuffer(p_fixed_index_buffer_, DXGI_FORMAT_R16_UINT, 0);
  p_immediate_context_->IASetInputLayout(p_final_vertex_layout_);

  // バックバッファーの消去
  clear_color[0] = 0.0f;
  p_immediate_context_->ClearRenderTargetView(p_render_target_view_, clear_color);

  // 定数バッファーの更新
  //DirectX::XMStoreFloat4x4(&fixed_world_, DirectX::XMMatrixRotationY(t*2));
  ConstantBuffer constant_buffer;
  constant_buffer.world = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&fixed_world_));
  constant_buffer.view = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&fixed_view_));
  constant_buffer.projection = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&fixed_projection_));
  p_immediate_context_->UpdateSubresource(p_constant_buffer_, 0, NULL, &constant_buffer, 0, 0);
  p_immediate_context_->VSSetConstantBuffers(0, 1, &p_constant_buffer_);

  // 視差情報と画面情報を定数バッファとして設定
  p_immediate_context_->UpdateSubresource(p_display_parameter_, 0, NULL, &display_parameter_, 0, 0);
  p_immediate_context_->PSSetConstantBuffers(1, 1, &p_display_parameter_);

  p_immediate_context_->PSSetShaderResources(0, 1, &p_parallax_resource_array_);
  p_immediate_context_->PSSetSamplers(0, 1, &p_sampler_state_);

  ID3D11ShaderResourceView *null_shader_resources[kNumberOfParallaxes];
  for (int i = 0; i < kNumberOfParallaxes; i++) {
    null_shader_resources[i] = NULL;
  }
  p_immediate_context_->VSSetShader(p_final_vertex_shader_, NULL, 0);
  p_immediate_context_->PSSetShader(p_final_pixel_shader_, NULL, 0);
  p_immediate_context_->DrawIndexed(6, 0, 0);
  p_immediate_context_->PSSetShaderResources(0, 1, null_shader_resources);

  p_swap_chain_->Present(0, 0);
}
