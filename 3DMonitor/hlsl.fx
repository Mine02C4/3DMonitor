// Copyright 2011 MineStudio.

texture tex1;
texture tex2;
texture tex3;
texture tex4;
texture tex5;
texture tex6;
texture tex7;
texture tex8;
texture tex9;
texture tex10;
texture tex11;
texture tex12;
texture tex13;
texture tex14;
texture tex15;
texture tex16;
texture tex17;
texture tex18;
texture tex19;
texture tex20;
texture tex21;
texture tex22;
texture tex23;
texture tex24;
texture tex25;
texture tex26;
texture tex27;
texture tex28;
texture tex29;
texture tex30;
texture tex31;
texture tex32;
texture tex33;
texture tex34;
texture tex35;
texture tex36;

sampler samp1 = sampler_state {Texture = <tex1>;};
sampler samp2 = sampler_state {Texture = <tex2>;};
sampler samp3 = sampler_state {Texture = <tex3>;};
sampler samp4 = sampler_state {Texture = <tex4>;};
sampler samp5 = sampler_state {Texture = <tex5>;};
sampler samp6 = sampler_state {Texture = <tex6>;};
sampler samp7 = sampler_state {Texture = <tex7>;};
sampler samp8 = sampler_state {Texture = <tex8>;};
sampler samp9 = sampler_state {Texture = <tex9>;};
sampler samp10 = sampler_state {Texture = <tex10>;};
sampler samp11 = sampler_state {Texture = <tex11>;};
sampler samp12 = sampler_state {Texture = <tex12>;};
sampler samp13 = sampler_state {Texture = <tex13>;};
sampler samp14 = sampler_state {Texture = <tex14>;};
sampler samp15 = sampler_state {Texture = <tex15>;};
sampler samp16 = sampler_state {Texture = <tex16>;};
sampler samp17 = sampler_state {Texture = <tex17>;};
sampler samp18 = sampler_state {Texture = <tex18>;};
sampler samp19 = sampler_state {Texture = <tex19>;};
sampler samp20 = sampler_state {Texture = <tex20>;};
sampler samp21 = sampler_state {Texture = <tex21>;};
sampler samp22 = sampler_state {Texture = <tex22>;};
sampler samp23 = sampler_state {Texture = <tex23>;};
sampler samp24 = sampler_state {Texture = <tex24>;};
sampler samp25 = sampler_state {Texture = <tex25>;};
sampler samp26 = sampler_state {Texture = <tex26>;};
sampler samp27 = sampler_state {Texture = <tex27>;};
sampler samp28 = sampler_state {Texture = <tex28>;};
sampler samp29 = sampler_state {Texture = <tex29>;};
sampler samp30 = sampler_state {Texture = <tex30>;};
sampler samp31 = sampler_state {Texture = <tex31>;};
sampler samp32 = sampler_state {Texture = <tex32>;};
sampler samp33 = sampler_state {Texture = <tex33>;};
sampler samp34 = sampler_state {Texture = <tex34>;};
sampler samp35 = sampler_state {Texture = <tex35>;};
sampler samp36 = sampler_state {Texture = <tex36>;};

//float4 VS( float4 pos : POSITION ) : POSITION {
//	return pos;
//}

float4 PS( float2 pos : VPOS) : COLOR {
	int px = pos.x;
	int py = pos.y;
	int ppx = px%6;
	int ppy = py%6;
	// R
	int r_view = (ppx*6+5-ppy+31)%36+1;
	// G
	int g_view = (ppx*6+5-ppy+33)%36+1;
	// B
	int b_view = (ppx*6+5-ppy+35)%36+1;
	
	int tx = (px-ppx)/6;
	int ty = (py-ppy)/6;
	
	float2 texuv = {
		(asfloat(tx)-0.5)/680.0,
		(asfloat(ty)-0.5)/400.0
	};
	float r_col,g_col,b_col;
	switch(abs(r_view)) {
		case 1:
		r_col = tex2D( samp1, texuv ).r;
		break;
		case 2:
		r_col = tex2D( samp2, texuv ).r;
		break;
		case 3:
		r_col = tex2D( samp3, texuv ).r;
		break;
		case 4:
		r_col = tex2D( samp4, texuv ).r;
		break;
		case 5:
		r_col = tex2D( samp5, texuv ).r;
		break;
		case 6:
		r_col = tex2D( samp6, texuv ).r;
		break;
		case 7:
		r_col = tex2D( samp7, texuv ).r;
		break;
		case 8:
		r_col = tex2D( samp8, texuv ).r;
		break;
		case 9:
		r_col = tex2D( samp9, texuv ).r;
		break;
		case 10:
		r_col = tex2D( samp10, texuv ).r;
		break;
		case 11:
		r_col = tex2D( samp11, texuv ).r;
		break;
		case 12:
		r_col = tex2D( samp12, texuv ).r;
		break;
		case 13:
		r_col = tex2D( samp13, texuv ).r;
		break;
		case 14:
		r_col = tex2D( samp14, texuv ).r;
		break;
		case 15:
		r_col = tex2D( samp15, texuv ).r;
		break;
		case 16:
		r_col = tex2D( samp16, texuv ).r;
		break;
		case 17:
		r_col = tex2D( samp17, texuv ).r;
		break;
		case 18:
		r_col = tex2D( samp18, texuv ).r;
		break;
		case 19:
		r_col = tex2D( samp19, texuv ).r;
		break;
		case 20:
		r_col = tex2D( samp20, texuv ).r;
		break;
		case 21:
		r_col = tex2D( samp21, texuv ).r;
		break;
		case 22:
		r_col = tex2D( samp22, texuv ).r;
		break;
		case 23:
		r_col = tex2D( samp23, texuv ).r;
		break;
		case 24:
		r_col = tex2D( samp24, texuv ).r;
		break;
		case 25:
		r_col = tex2D( samp25, texuv ).r;
		break;
		case 26:
		r_col = tex2D( samp26, texuv ).r;
		break;
		case 27:
		r_col = tex2D( samp27, texuv ).r;
		break;
		case 28:
		r_col = tex2D( samp28, texuv ).r;
		break;
		case 29:
		r_col = tex2D( samp29, texuv ).r;
		break;
		case 30:
		r_col = tex2D( samp30, texuv ).r;
		break;
		case 31:
		r_col = tex2D( samp31, texuv ).r;
		break;
		case 32:
		r_col = tex2D( samp32, texuv ).r;
		break;
		case 33:
		r_col = tex2D( samp33, texuv ).r;
		break;
		case 34:
		r_col = tex2D( samp34, texuv ).r;
		break;
		case 35:
		r_col = tex2D( samp35, texuv ).r;
		break;
		case 36:
		r_col = tex2D( samp36, texuv ).r;
		break;
	}
	switch(abs(g_view)) {
		case 1:
		g_col = tex2D( samp1, texuv ).g;
		break;
		case 2:
		g_col = tex2D( samp2, texuv ).g;
		break;
		case 3:
		g_col = tex2D( samp3, texuv ).g;
		break;
		case 4:
		g_col = tex2D( samp4, texuv ).g;
		break;
		case 5:
		g_col = tex2D( samp5, texuv ).g;
		break;
		case 6:
		g_col = tex2D( samp6, texuv ).g;
		break;
		case 7:
		g_col = tex2D( samp7, texuv ).g;
		break;
		case 8:
		g_col = tex2D( samp8, texuv ).g;
		break;
		case 9:
		g_col = tex2D( samp9, texuv ).g;
		break;
		case 10:
		g_col = tex2D( samp10, texuv ).g;
		break;
		case 11:
		g_col = tex2D( samp11, texuv ).g;
		break;
		case 12:
		g_col = tex2D( samp12, texuv ).g;
		break;
		case 13:
		g_col = tex2D( samp13, texuv ).g;
		break;
		case 14:
		g_col = tex2D( samp14, texuv ).g;
		break;
		case 15:
		g_col = tex2D( samp15, texuv ).g;
		break;
		case 16:
		g_col = tex2D( samp16, texuv ).g;
		break;
		case 17:
		g_col = tex2D( samp17, texuv ).g;
		break;
		case 18:
		g_col = tex2D( samp18, texuv ).g;
		break;
		case 19:
		g_col = tex2D( samp19, texuv ).g;
		break;
		case 20:
		g_col = tex2D( samp20, texuv ).g;
		break;
		case 21:
		g_col = tex2D( samp21, texuv ).g;
		break;
		case 22:
		g_col = tex2D( samp22, texuv ).g;
		break;
		case 23:
		g_col = tex2D( samp23, texuv ).g;
		break;
		case 24:
		g_col = tex2D( samp24, texuv ).g;
		break;
		case 25:
		g_col = tex2D( samp25, texuv ).g;
		break;
		case 26:
		g_col = tex2D( samp26, texuv ).g;
		break;
		case 27:
		g_col = tex2D( samp27, texuv ).g;
		break;
		case 28:
		g_col = tex2D( samp28, texuv ).g;
		break;
		case 29:
		g_col = tex2D( samp29, texuv ).g;
		break;
		case 30:
		g_col = tex2D( samp30, texuv ).g;
		break;
		case 31:
		g_col = tex2D( samp31, texuv ).g;
		break;
		case 32:
		g_col = tex2D( samp32, texuv ).g;
		break;
		case 33:
		g_col = tex2D( samp33, texuv ).g;
		break;
		case 34:
		g_col = tex2D( samp34, texuv ).g;
		break;
		case 35:
		g_col = tex2D( samp35, texuv ).g;
		break;
		case 36:
		g_col = tex2D( samp36, texuv ).g;
		break;
	}
	switch(abs(b_view)) {
		case 1:
		b_col = tex2D( samp1, texuv ).b;
		break;
		case 2:
		b_col = tex2D( samp2, texuv ).b;
		break;
		case 3:
		b_col = tex2D( samp3, texuv ).b;
		break;
		case 4:
		b_col = tex2D( samp4, texuv ).b;
		break;
		case 5:
		b_col = tex2D( samp5, texuv ).b;
		break;
		case 6:
		b_col = tex2D( samp6, texuv ).b;
		break;
		case 7:
		b_col = tex2D( samp7, texuv ).b;
		break;
		case 8:
		b_col = tex2D( samp8, texuv ).b;
		break;
		case 9:
		b_col = tex2D( samp9, texuv ).b;
		break;
		case 10:
		b_col = tex2D( samp10, texuv ).b;
		break;
		case 11:
		b_col = tex2D( samp11, texuv ).b;
		break;
		case 12:
		b_col = tex2D( samp12, texuv ).b;
		break;
		case 13:
		b_col = tex2D( samp13, texuv ).b;
		break;
		case 14:
		b_col = tex2D( samp14, texuv ).b;
		break;
		case 15:
		b_col = tex2D( samp15, texuv ).b;
		break;
		case 16:
		b_col = tex2D( samp16, texuv ).b;
		break;
		case 17:
		b_col = tex2D( samp17, texuv ).b;
		break;
		case 18:
		b_col = tex2D( samp18, texuv ).b;
		break;
		case 19:
		b_col = tex2D( samp19, texuv ).b;
		break;
		case 20:
		b_col = tex2D( samp20, texuv ).b;
		break;
		case 21:
		b_col = tex2D( samp21, texuv ).b;
		break;
		case 22:
		b_col = tex2D( samp22, texuv ).b;
		break;
		case 23:
		b_col = tex2D( samp23, texuv ).b;
		break;
		case 24:
		b_col = tex2D( samp24, texuv ).b;
		break;
		case 25:
		b_col = tex2D( samp25, texuv ).b;
		break;
		case 26:
		b_col = tex2D( samp26, texuv ).b;
		break;
		case 27:
		b_col = tex2D( samp27, texuv ).b;
		break;
		case 28:
		b_col = tex2D( samp28, texuv ).b;
		break;
		case 29:
		b_col = tex2D( samp29, texuv ).b;
		break;
		case 30:
		b_col = tex2D( samp30, texuv ).b;
		break;
		case 31:
		b_col = tex2D( samp31, texuv ).b;
		break;
		case 32:
		b_col = tex2D( samp32, texuv ).b;
		break;
		case 33:
		b_col = tex2D( samp33, texuv ).b;
		break;
		case 34:
		b_col = tex2D( samp34, texuv ).b;
		break;
		case 35:
		b_col = tex2D( samp35, texuv ).b;
		break;
		case 36:
		b_col = tex2D( samp36, texuv ).b;
		break;
	}
	return (
		r_col,
		g_col,
		b_col,
		1.0
	);
	
}

technique TSHADER {
	pass P0 {
		PixelShader	= compile ps_3_0 PS();
	}
}
